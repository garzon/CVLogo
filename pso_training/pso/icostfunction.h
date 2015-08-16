#ifndef COSTFUNCTION_H
#define COSTFUNCTION_H

#include <iostream>
#include <cmath>
#include <vector>

#include "IParams.h"

template <typename _ParamsType>
class ICostFunction {
	typedef _ParamsType ParamsType;
public:
	virtual double costFunction(const _ParamsType&) = 0;
};


#endif
