#include "SiftParams.h"

 SiftParams::SiftParams()
{
    paramRange.push_back(std::make_pair(1.0,500.0));        //alpha
    paramRange.push_back(std::make_pair(1.0,500.0));        //beta
    paramRange.push_back(std::make_pair(0.0,1.0));              //tau
    paramRange.push_back(std::make_pair(0.0,500.0));        //Nr
    //eps还是不要调了？
    paramRange.push_back(std::make_pair(0.0,1.0));              //threshold
    paramRange.push_back(std::make_pair(0.0,1.0));              //responseThresholdx
    paramRange.push_back(std::make_pair(0.0,1.0));              //responseThresholdy
    paramRange.push_back(std::make_pair(0.0,1.0));              //rectangleThreshold
}
SiftParams::SiftParams(const std::vector<double>& _params)
{
    if(_params.size()!=8) std::cout<<"Warning! Number of params  is not suitable!"<<std::endl;
    if(_params.size)
    paramRange.push_back(std::make_pair(1.0,500.0));        //alpha
    paramRange.push_back(std::make_pair(1.0,500.0));        //beta
    paramRange.push_back(std::make_pair(0.0,1.0));              //tau
    paramRange.push_back(std::make_pair(0.0,500.0));        //Nr
    //eps还是不要调了？
    paramRange.push_back(std::make_pair(0.0,1.0));              //threshold
    paramRange.push_back(std::make_pair(0.0,1.0));              //responseThresholdx
    paramRange.push_back(std::make_pair(0.0,1.0));              //responseThresholdy
    paramRange.push_back(std::make_pair(0.0,1.0));              //rectangleThreshold
    params=_params;
}
SiftParams::SiftParams(double alpha,double beta, double tau,double  Nr,
                       double threshold,double  responseThresholdx,double responseThresholdy,double  rectangleThreshold)
{
    params.push_back(alpha);
    params.push_back(beta);
    params.push_back(tau);
    params.push_back(Nr);
    params.push_back(threshold);
    params.push_back(responseThresholdx);
    params.push_back(responseThresholdy);
    params.push_back(rectangleThreshold);
    paramRange.push_back(std::make_pair(1.0,500.0));        //alpha
    paramRange.push_back(std::make_pair(1.0,500.0));        //beta
    paramRange.push_back(std::make_pair(0.0,1.0));              //tau
    paramRange.push_back(std::make_pair(0.0,500.0));        //Nr
    //eps还是不要调了？
    paramRange.push_back(std::make_pair(0.0,1.0));              //threshold
    paramRange.push_back(std::make_pair(0.0,1.0));              //responseThresholdx
    paramRange.push_back(std::make_pair(0.0,1.0));              //responseThresholdy
    paramRange.push_back(std::make_pair(0.0,1.0));              //rectangleThreshold
}
