#ifndef SIFTPARAMS_h
#define SIFTPARAMS_h
#include <vector>

#include "IParams.h"
class SiftParams:public IParams{
public:
    SiftParams();
    SiftParams( std::vector<double>& _params);
    SiftParams(double,double,double,double,double,double,double,double);//8个double。8个参数。
};

//参数顺序：alpha, beta, tau, Nr, eps,threshold, responseThresholdx,responseThresholdy, rectangleThreshold;











#endif // SIFTPARAMS_h
