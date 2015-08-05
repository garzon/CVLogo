#include "CostFunction.h"

double SiftCost::costFunction(const std::vector<double>& params)
{
    if(trainSetNum==0){
        std::cout<<"Error in SiftCost::costFunction:"<<std::endl<<"No training set!";
        throw std::runtime_error("In SiftCost::costFunction: No training set");
    }


    double cost=0.0;
    for(int i=0;i<trainSetNum;i++){
        cost+=(costOfNoMatch(i)+costOfWrongMatch(i));       //costOfWrongMatch(i)应该会比较耗时。可以并行。
    }
    return cost;
}

double SiftCost::costOfNoMatch(int index)
{
    int nomatch=keyPointNum-matchs[index].size();
    if (nomatch<=keyPointNum*toleranceOfNoMatch) return 0;
    return pow(nomatch-keyPointNum*toleranceOfNoMatch,2);
}

double SiftCost::costOfWrongMatch(int index)
{


    return 0;
}

void SiftCost::setTolerance(double _toleranceOfNoMatch)                 //这里可以考虑写成内联函数？
{
    if(_toleranceOfNoMatch<0) toleranceOfNoMatch=0;
    else if(_toleranceOfNoMatch>1) toleranceOfNoMatch=0;
    else toleranceOfNoMatch=_toleranceOfNoMatch;
}

bool SiftCost::addTrainSet(const std::vector<std::string>& trainSets)        //这个地方可以考虑用并行
{

    return true;
}

bool SiftCost::addTrainSet(const std::string trainSet)
{

    return true;
}

SiftCost::SiftCost(double _toleranceOfNoMatch=0.25)
{
    setTolerance(_toleranceOfNoMatch);
}

SiftCost::SiftCost(const std::vector<std::string>& trainSets,double _toleranceOfNoMatch=0.25)
{
    setTolerance(_toleranceOfNoMatch);
    addTrainSet(trainSets);
}
SiftCost::SiftCost(std::string trainSet,double _toleranceOfNoMatch=0.25)
{
    setTolerance(_toleranceOfNoMatch);
    addTrainSet(trainSet);
}

int main(){return 0;}
