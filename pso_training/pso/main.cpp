#include <iostream>
#include <time.h>

#include "costfunctiondemo.h"
#include "paramsdemo.h"
#include "pso_icp.h"

using namespace std;
using namespace cv;

#define WIDTH 500
#define HEIGHT 500

// some usseful converters

inline pair<double,double> mat2d(const Mat &a){
    assert(a.rows==2);
    assert(a.cols==1);
    pair<double,double> res;
    const double *p=a.ptr<double>();
    res.first=*p;
    p++;
    res.second=*p;
    return res;
}

ParamsDemo d2Mat(const pair<double,double> &d2){
    double x=d2.first,y=d2.second;
	vector<double> res;
	res.emplace_back(x);
	res.emplace_back(y);
	return ParamsDemo(res);
}

pair<double,double> imagePos2d(double x,double y){
    return make_pair<double,double>(
		Particle<ParamsDemo>::map(x, 0, HEIGHT, ParamsDemo::paramRange[0].first, ParamsDemo::paramRange[0].second),
		Particle<ParamsDemo>::map(y, 0, WIDTH, ParamsDemo::paramRange[1].first, ParamsDemo::paramRange[1].second)
    );
}

pair<double,double> d2imagePos(pair<double,double> d){
    return make_pair<double,double>(
		Particle<ParamsDemo>::map(d.first, ParamsDemo::paramRange[0].first, ParamsDemo::paramRange[0].second, 0, HEIGHT),
		Particle<ParamsDemo>::map(d.second, ParamsDemo::paramRange[1].first, ParamsDemo::paramRange[1].second, 0, WIDTH)
    );
};

// iterate all pixels to draw the costFunction
cv::Mat drawCostFunction(CostFunctionDemo *costFunc, std::pair<double,double> *global_best_point=NULL){

    double imax = -COST_INF, imin = COST_INF;
    cv::Mat res(HEIGHT,WIDTH,CV_8UC3);
    uchar *p = res.ptr<uchar>();
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            double cost = costFunc->costFunction(d2Mat(imagePos2d(i,j)));
            imax = max(imax,cost);
            if(cost < imin){
                imin = cost;
                if(global_best_point != NULL) {
                    global_best_point->first = i;
                    global_best_point->second = j;
                }
            }
        }
    }
    cout<<"Real max: "<<imax<<endl;
    cout<<"Real min: "<<imin<<endl;
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            double cost = costFunc->costFunction(d2Mat(imagePos2d(i,j)));
            cost = Particle<ParamsDemo>::map(cost,imin,imax,0,255);
            if((saturate_cast<uchar>(cost)%30)!=0){
                p[0]=0;//Particle::map(i,0,HEIGHT,0,255);
                p[1]=saturate_cast<uchar>(255-cost);
                p[2]=saturate_cast<uchar>(cost);
            }else{
                p[1]=p[0]=p[2]=0;
            }
            p+=3;
        }
    }
    return res;

}

int main(){

    // init
    srand(time(0));

    while(true){

        CostFunctionDemo costFunc;

        // a variable to store the real global best point by iterate all possible pixel of the solution space
        // for debug
        std::pair<double,double> global_best_point;

        // visualize the costFunction
        cv::Mat map = drawCostFunction(&costFunc, &global_best_point);

        PSO_ICP<ParamsDemo> solver(&costFunc); // build a PSO solver with the costFunc

		ParamsDemo _best_point = solver.solve(); // get the solution from PSO

		cv::Mat best_point = _best_point.toMat();

        // calc the cost of the solution and output
        cout << "The cost of the found solution: " << costFunc.costFunction(_best_point) << endl;

        // visualize the result
        std::pair<double,double> myPoint = d2imagePos(mat2d(best_point));

        // white : real global best one
        cv::circle(map,cv::Point2d(global_best_point.second,global_best_point.first),3,cv::Scalar::all(255),3);
        // blue : the found one
        cv::circle(map,cv::Point2d(myPoint.second,myPoint.first),3,cv::Scalar(255,0,0),2);

        imshow("map", map);

        // press q to exit
        char c = cv::waitKey();
        if(c == 'q') break;

    }
    return 0;
}
