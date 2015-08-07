#ifndef IPARAMS_h
#define IPARAMS_h

#include <vector>

class IParams
{
public:
    std::vector<double> params;
    static const std::vector<std::pair<double,double> > paramRange;
};














#endif // IPARAMS_h
