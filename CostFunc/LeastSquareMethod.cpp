#include "LeastSquareMethod.h"

LeastSquareMethod::LeastSquareMethod():dimension(-1),functionNum(0){}
LeastSquareMethod::LeastSquareMethod(int _dimension):dimension(-1),functionNum(0) {
    setDimension(_dimension);
}

void LeastSquareMethod::setDimension(int _dimension){
    if (dimension>0){
        std::cout<<"Error!You have alreaty set the param dimension!"<<std::endl;
        throw std::runtime_error("Dimension can only be set once!");
    }
    if(_dimension<=0) {
        std::cout<<"Error! Dimension can not be smaller than 0! "<<std::endl;
        throw std::runtime_error("Dimension can not be smaller than 0!");
    }
    dimension=_dimension;
    alphas=new std::vector<double>[dimension];
    solution.resize(dimension);
    return;
}

void LeastSquareMethod::addFunction(const std::vector<double> &alpha, double beta){
    if(dimension<=0){
        std::cout<<"Error! You have not yet initialized the dimension of LeastSquareMethod"<<std::endl;
        throw std::runtime_error("Dimension of LeastSquareMethod have not be initialized");
    }
    if(alpha.size()!=dimension){
        std::cout<<"Error! The function's dimension is not equal to  the dimension of the example of LeastSquareMethod !"<<std::endl;
        throw std::runtime_error("The funfction's dimension is not suitable");
    }
    for(int i=0;i<dimension;i++){
        alphas[i].push_back(alpha[i]);
    }
    this->beta.push_back(beta);
    functionNum++;
    return;
}
void LeastSquareMethod::addFunction(double *alpha, double beta){
    if(dimension<=0){
        std::cout<<"Error! You have not yet initialized the dimension of LeastSquareMethod"<<std::endl;
        throw std::runtime_error("Dimension of LeastSquareMethod have not be initialized");
    }
    for(int i=0;i<dimension;i++){
        alphas[i].push_back(alpha[i]);
    }
    this->beta.push_back(beta);
    functionNum++;
    return;
}

double LeastSquareMethod::innerProduct(std::vector<double> &v1, std::vector<double> &v2){
    double result=0.0;
    for(int i=0;i<functionNum;i++){
        result+=v1.at(i)*v2.at(i);
    }
    return result;
}

double LeastSquareMethod::normalize(std::vector<double> &v1, std::vector<double> &v2){
    double temp=innerProduct(v1,v2)/innerProduct(v2,v2);
    for(int i=0;i<functionNum;i++){
        v1[i]-=temp*v2[i];
    }
    return temp;
}

double LeastSquareMethod::operator ()(){        //计算最优解的接口函数
    if (functionNum==0){
        std::cout<<"Error! No function in LeastSquareMethod!"<<std::endl;
        throw std::runtime_error("No function in LeastSquareMethod");
    }
    std::vector<double>* translateParam=new std::vector<double>[dimension];
    bool* if_0_vec=new bool[dimension];
    std::vector<double>* _alphas=new std::vector<double>[dimension];
    for(int i=0;i<dimension;i++){
        _alphas[i]=alphas[i];
        for(int j=0;j<i;j++){
            if(if_0_vec[j]){
                translateParam[i].push_back(0);
                continue;
            }
            translateParam[i].push_back(normalize(_alphas[i],_alphas[j]));
        }
        if_0_vec[i]=(L2_norm(_alphas[i])<eps) ;
    }               //将alphas正交化，记录入_alphas，并记录变换系数，同时对正交化成0的向量（即能被其它向量线性表示的向量）做标记
    for(int i=0;i<dimension;i++){
        if(if_0_vec[i]){
            solution[i]=0;
            continue;
        }
        solution[i]=innerProduct(beta,_alphas[i])/innerProduct(_alphas[i],_alphas[i]);
    }               //计算在正交的系数_alphas下的最优解
    for(int i=dimension-1;i>=0;i--){
        if(if_0_vec[i]) continue;
        for(int j=0;j<i;j++){
            solution[j]-=solution[i]*translateParam[i][j];
        }
    }           //将正交系数下的最优解转换维原系数alphas下的最优解
    std::vector<double> dis(beta);
    for(int i=0;i<functionNum;i++){
        for(int j=0;j<dimension;j++){
            dis[i]-=solution[j]*alphas[j][i];
        }
    }           //计算最优解下的值与期望值的距离。

    delete[] if_0_vec;
    delete[] translateParam;
    delete[] _alphas;
    return L2_norm(dis);
}

LeastSquareMethod::~LeastSquareMethod(){
    delete[] alphas;
    //delete[] _alphas;
}













