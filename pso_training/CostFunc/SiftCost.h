#ifndef SIFTCOST_h
#define SIFTCOST_h

#include <iostream>
#include <cmath>
#include <vector>
//#include<cstring>
#include <stdexcept>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "SiftParams.h"
#include "../pso/icostfunction.h"
#include "../../cds/cds.h"

#ifndef Eps
#define Eps 0.000001
#endif // Eps
#ifndef maxProportation
#define maxProportation 100000
#endif // maxProportation
#ifndef minKeyPointNum
#define minKeyPointNum 20
#endif
//#define DEBUG
/*
使用方法：
创建SiftCost实体对象，随意用哪个构造函数。支持SiftCost对象数组的创建（即有默认构造函数）
记得一定要传入logo图和训练集。可以在构造函数中传入，也可以后来再传入。
参数double toleranceOfNoMatch有默认值，可以不用自己传入。
后来传入的方式见“对训练集的操作”和“对Logo的操作“两部分。
*/

class SiftCost: public ICostFunction<SiftParams> {
public:
    //构造函数
    SiftCost(const std::vector<std::string>& trainSets,std::string logo,double _toleranceOfNoMatch=0.25);         //double _toleranceOfNoMatch有默认值0.25
    SiftCost(double _toleranceOfNoMatch=0.25);           //double _toleranceOfNoMatch有默认值0.25
    SiftCost(std::string trainSet,std::string logo,double _toleranceOfNoMatch=0.25);                  //double _toleranceOfNoMatch有默认值0.25

    //核心功能接口：costFunction(...)
	virtual double costFunction(const SiftParams&);

    //对训练集的操作
    int addTrainSet(std::string trainSet);                                                                  //返回成功读入的训练图像的数量
    int addTrainSet(const std::vector<std::string>& trainSets);                 //返回成功读入的训练图像的数量
    void clearTrainSet();
    int resetTrainSet(const std::vector<std::string>& trainSets);               //返回成功读入的训练图像的数量
    int resetTrainSet(std::string trainSet);                                                                //返回成功读入的训练图像的数量

    //对Logo的操作
    bool setLogo(std::string Logo);

    void setTolerance(double);                              //这里是设置一个参数。该参数表示对没有匹配点占logo总点数的比例的忍耐度

    virtual ~SiftCost();

protected:
    virtual double costOfMismatch(int index);                         //这里是一个纯数学的函数。本质是代价函数中的一项的实现
    virtual double costOfWrongMatch(int index);                 //这里是一个纯数学的函数。本质是代价函数中的一项的实现
    virtual double costOfNoMatch(){
        return 1000;
    }

    double distanceX(int index,int i,int j);                                //index代表第几个训练集。计算第i对匹配点对、第j对匹配点对在Logo上的距离。
    double distanceY(int index,int i,int j);                              //计算第i对匹配点对、第j对匹配点对在训练集上的距离。

    cv::Mat logo;                       //装logo的图像
    std::vector<cv::KeyPoint> Sx;            //商标图的特征点集
    std::vector<std::vector<cv::KeyPoint> > Sys;           //训练集的特征点集构成的vector   vector<KeyPoint>本质是一幅图的特征点集合
    std::vector<std::vector<cv::DMatch> > matchs;      //vector<DMatch>
    std::vector<CDS*> cds;


    double toleranceOfNoMatch;

    bool logoExists;
    int keyPointNum;
    int trainSetNum;

    bool pictureUpdate;

};

#endif // SIFTCOST_h
