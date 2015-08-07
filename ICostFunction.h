#ifndef COSTFUNCTION_H
#define COSTFUNCTION_H

#include <iostream>
#include <cmath>
#include <vector>

#include "IParams.h"
//#include <stdexcept>
//#include<opencv2/features2d/features2d.hpp>


//#typedef vector<KeyPoint> KeyPointSet
//#typedef vector<DMatch> MatchSet
class ICostFunction
{
    virtual double costFunction(const IParams&)=0;
};


#endif
