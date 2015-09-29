#ifndef SIFTPARAMS_h
#define SIFTPARAMS_h

#include <vector>
#include <iostream>

#include "../pso/IParams.h"

class SiftParams:public IParams{
public:
	static const int dimension_of_freedom;
	static std::vector<std::pair<double, double> > paramRange;
    SiftParams();
	SiftParams(const std::vector<double>& _params): IParams(_params) {};
	SiftParams(cv::Mat m): IParams(m) {};
	SiftParams(double alpha, double beta, double tau, double  Nr,
		double threshold, double  responseThresholdx, double responseThresholdy,
		double rectangleThreshold);
};

#endif // SIFTPARAMS_h
