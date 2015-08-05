#include <iostream>
#include <cmath>
#include <vector>
#include<cstring>
#include <stdexcept>
#include<opencv2/features2d/features2d.hpp>


//#typedef vector<KeyPoint> KeyPointSet
//#typedef vector<DMatch> MatchSet
class CostFunction
{
    virtual double costFunction(const std::vector<double>&)=0;
};

class SiftCost:public CostFunction
{
public:
    SiftCost(const std::vector<std::string>& trainSets,double _toleranceOfNoMatch);         //double _toleranceOfNoMatch有默认值0.25
    SiftCost(double _toleranceOfNoMatch);           //double _toleranceOfNoMatch有默认值0.25
    SiftCost(std::string trainSet,double _toleranceOfNoMatch);                  //double _toleranceOfNoMatch有默认值0.25
    virtual double costFunction(const std::vector<double>&  );
    bool addTrainSet(std::string trainSet);
    bool addTrainSet(const std::vector<std::string>& trainSets);
    void setTolerance(double);
protected:
    double costOfNoMatch(int index);
    double costOfWrongMatch(int index);
    std::vector<cv::KeyPoint> Sx;            //商标图的特征点集
    std::vector<std::vector<cv::KeyPoint> > Sys;           //训练集的特征点集构成的vector   vector<KeyPoint>本质是一幅图的特征点集合
    std::vector<std::vector<cv::DMatch> > matchs;      //vector<DMatch>
    double toleranceOfNoMatch;
    int keyPointNum;
    int trainSetNum;
};

