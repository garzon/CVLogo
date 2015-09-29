#include "SiftCost_1.h"

double SiftCost_1::costOfWrongMatch(int index){
    LeastSquareMethod lsm(6);
    double temp[6];
    std::vector<cv::DMatch>& match=matchs[index];
    std::vector<cv::KeyPoint>& Sy=Sys[index];
    if (match.size()==0) return 0;
    for(int i=0;i<match.size();i++){                                          //本质：(x,y,1)*(a11,a12|a21,a22|a31,a32)=(x*|y*)  其中1为平移项，|代表矩阵中换行。这段循环是将其化为向量形式
        temp[0]=Sy[match[i].trainIdx].pt.x,temp[1]=Sy[match[i].trainIdx].pt.y,temp[2]=1;
        temp[3]=0,temp[4]=0,temp[5]=0;
        lsm.addFunction(temp,Sx[match[i].queryIdx].pt.x);
        temp[3]=Sy[match[i].trainIdx].pt.x,temp[4]=Sy[match[i].trainIdx].pt.y,temp[5]=1;
        temp[0]=0,temp[1]=0,temp[2]=0;
        lsm.addFunction(temp,Sx[match[i].queryIdx].pt.y);
    }
    return lsm();
}

SiftCost_1::SiftCost_1(const std::vector<std::string> &trainSets, std::string logo, double _toleranceOfNoMatch):SiftCost(trainSets,logo,_toleranceOfNoMatch){}
SiftCost_1::SiftCost_1(double _toleranceOfNoMatch):SiftCost(_toleranceOfNoMatch){}
SiftCost_1::SiftCost_1(std::string trainSet, std::string logo, double _toleranceOfNoMatch):SiftCost(trainSet,logo,_toleranceOfNoMatch){}
