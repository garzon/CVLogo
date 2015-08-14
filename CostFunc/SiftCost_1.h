#ifndef SIFTCOST_1_H
#define SIFTCOST_1_H
#include "SiftCost.h"
#include "LeastSquareMethod.h"

/*
使用方法：
创建SiftCost_1实体对象，随意用哪个构造函数。支持SiftCost_1对象数组的创建（即有默认构造函数）
记得一定要传入logo图和训练集。可以在构造函数中传入，也可以后来再传入。
参数double toleranceOfNoMatch有默认值，可以不用自己传入。
详见SiftCost.h
本质上和SiftCost的接口一模一样。
*/

class SiftCost_1:public SiftCost
{
public:
    SiftCost_1(const std::vector<std::string>& trainSets,std::string logo,double _toleranceOfNoMatch=0.25);         //double _toleranceOfNoMatch有默认值0.25
    SiftCost_1(double _toleranceOfNoMatch=0.25);           //double _toleranceOfNoMatch有默认值0.25
    SiftCost_1(std::string trainSet,std::string logo,double _toleranceOfNoMatch=0.25);                  //double _toleranceOfNoMatch有默认值0.25
    virtual ~SiftCost_1(){}
protected:
    //virtual double costOfNoMatch(int index);
    virtual double costOfWrongMatch(int index);
};
#endif // SIFTCOST_1_H

