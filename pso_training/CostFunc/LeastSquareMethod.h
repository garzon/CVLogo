#ifndef LEASTSQUAREMETHOD_H
#define LEASTSQUAREMETHOD_H

#ifndef eps
#define eps 0.000001
#endif

#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>

/*
这个类用于寻找（矛盾）方程组的（L2意义下最近的最优）解
本方法不用担心矩阵不可逆的情况。对任何方程组都适用。

有默认构造函数，支持数组创建。
但一定要记得传入参数dimension 。在传入之前对本类做任何其它操作都会 runtime_error
dimension只能传入一次，不允许改动。不允许为负数。
使用addFunction(……)来向类中添加方程。

核心接口double operator() ();  返回 矛盾方程组最优解情况下最优解距离希望解的L2_norm
getSolution()用于获取最优解。
*/

class LeastSquareMethod {
public:
    LeastSquareMethod();
    LeastSquareMethod(int _dimension);          //_dimension:矛盾方程组的维数（未知数个数）
    void setDimension(int _dimension);
    void addFunction(const std::vector<double>& alpha,double beta);
    void addFunction(double* alpha,double beta);

    double operator() ();           //

    std::vector<double>& getSolution(){         //返回方程组的（最优）解
        return solution;
    }
    ~LeastSquareMethod();
private:
    std::vector<double>* alphas;        //列向量
    std::vector<double> beta;           //期望值向量
    std::vector<double> solution;           //解向量
    int dimension;
    int functionNum;            //有多少个方程

    double innerProduct(std::vector<double>& v1,std::vector<double>& v2);       //向量内积
    double L2_norm(std::vector<double>& v){             //向量范数
        return std::sqrt(innerProduct(v,v));
    }
    double normalize(std::vector<double>& v1,std::vector<double>& v2);          //将v1减去k倍v2，使得v1、v2相互垂直。返回k

};

#endif // LEASTSQUAREMETHOD_H

