
#include "SiftCost.h"
//#define DEBUG

//下面一部分是SiftCost的核心接口costFunction(...)以及其具体实现所用到的几个函数
double SiftCost::costFunction(const SiftParams& siftParams)
{
#ifdef DEBUG
    std::cout<<trainSetNum<<" "<<logoExists<<std::endl;
#endif
    if(trainSetNum<=0){
        std::cout<<"Error in SiftCost::costFunction:"<<std::endl<<"No training set!"<<std::endl;
        throw std::runtime_error("In SiftCost::costFunction: No training set");
    }
    if(!logoExists){
        std::cout<<"Error in SiftCost::costFunction:"<<std::endl<<"No logo!"<<std::endl;
        throw std::runtime_error("In SiftCost::costFunction: No logo");
    }
    double cost=0.0;
    if (siftParams.params.size()<8){
        std::cout<<"Error in SiftCost::costFunction:"<<std::endl<<"Too less params! There should be 8 params."<<std::endl;
        throw std::runtime_error("In SiftCost::costFunction: Too less params");
    }
    if (siftParams.params.size()>8){
        std::cout<<"Error in SiftCost::costFunction:"<<std::endl<<"Too many params! There should be 8 params."<<std::endl;
        throw std::runtime_error("In SiftCost::costFunction: Too many params");
    }                                                                                                               //判定一些意外情况。


    for(int i=0;i<trainSetNum;i++){
        cds[i]->param.alpha=siftParams.params[0];
        cds[i]->param.beta=siftParams.params[1];
        cds[i]->param.tau=siftParams.params[2];
        cds[i]->param.Nr=siftParams.params[3];
        cds[i]->param.threshold=siftParams.params[4];
        cds[i]->param.responseThresholdx=siftParams.params[5];
        cds[i]->param.responseThresholdy=siftParams.params[6];
        cds[i]->param.rectangleThreshold=siftParams.params[7];              //设置系数。
        cds[i]->param.eps=0.001;
        cds[i]->param.eeps=0.000001;
        cds[i]->param.maxtheta=16;
        cds[i]->param.maxrho=16;
        cds[i]->param.maxt=30;
        cds[i]->setParameters(cds[i]->param);
#ifdef DEBUG
        std::cout<<"params converting finished!"<<std::endl;
#endif
        cds[i]->computeContextX();
        cds[i]->computeContextY();
#ifdef DEBUG
        std::cout<<"Context computing finished!"<<std::endl;
#endif
        cds[i]->computeCDSMatrix();
#ifdef DEBUG
        std::cout<<"CDSMatrix computing finished!"<<std::endl;
#endif
        if(!cds[i]->match()) {
            cost+=costOfNoMatch();//这里要改！!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#ifdef DEBUG
            std::cout<<"not match in match "<<i<<":"<<std::endl;
#endif
        }
#ifdef DEBUG
        std::cout<<"matching finished!"<<std::endl;
#endif
        matchs.resize(trainSetNum);
        matchs[i]=cds[i]->getMatchVec();
#ifdef DEBUG
        std::cout<<"getting matchVec finished!"<<std::endl;
#endif
    }
    if(pictureUpdate){
        Sys.resize(trainSetNum);
        for(int i=0;i<trainSetNum;i++) {
            cds[i]->getSiftKeyPoint(Sx,Sys[i]);
        }
        pictureUpdate=false;
#ifdef DEBUG
        std::cout<<"Picture update finished!"<<std::endl;
#endif
    }
    //计算匹配点对matchs


    for(int i=0;i<trainSetNum;i++){
        cost+=(costOfMismatch(i)+costOfWrongMatch(i));       //costOfWrongMatch(i)应该会比较耗时。可以并行。
    }
#ifdef DEBUG
        for(int i=0;i<trainSetNum;i++){cds[i]->visualize();}
#endif
    return cost;
}

double SiftCost::costOfMismatch(int index)                                           //这里是一个纯数学的函数。本质是代价函数中的一项的实现
{
    double cost=0.0;
    int nomatch=keyPointNum-matchs[index].size();
    if (nomatch<=keyPointNum*toleranceOfNoMatch) cost=0;
    else cost=pow(nomatch-keyPointNum*toleranceOfNoMatch,2);
    if (Sys[index].size()<=minKeyPointNum) cost+=1000;
    if (Sx.size()<=minKeyPointNum) cost+=1000;
#ifdef DEBUG
    std::cout<<"costOfMismatch in match "<<index<<":"<<cost<<std::endl;
#endif
    return cost;
}

double SiftCost::costOfWrongMatch(int index)                                //这里是一个纯数学的函数。本质是代价函数中的一项的实现
{
    double cost=0.0;
    int n=matchs[index].size();
#ifdef DEBUG
    std::cout<<"num of matchs "<<index<<":"<<matchs[index].size()<<std::endl;
#endif
    double*  proportion= NULL;
    proportion = new double[n*(n-1)/2];      //这个数组里装的是dis(xi,yi)和dis(xj,yj)的比例
    double disX,disY;       //装dis(xi,xj),dis(yi,yj)的临时变量
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
#ifdef DEBUG
            //std::cout<<"param now:"<<i*(i-1)/2+j<<":"<<std::endl;
#endif
            disX=distanceX(index,i,j);
            disY=distanceY(index,i,j);
            if(disX<Eps&&disY<Eps)  proportion[i*(i-1)/2+j]=1;
            else if (disX<Eps||disY<Eps) proportion[i*(i-1)/2+j]=maxProportation;
            else{
            double temp;
                if(disX<disY) temp=disX/disY;
                else temp=disY/disX;
                //std::cout << temp << '  ' << i*(i-1)/2+j<< std::endl;
                if (temp<maxProportation) proportion[i*(i-1)/2+j]=temp;
                else proportion[i*(i-1)/2+j]=maxProportation;     //这条分支几乎不会出现。只是为了程序的鲁棒性。
            }
        }
    }
#ifdef DEBUG
    std::cout<<"Succeed in contracting proportion in match"<<index<<std::endl;
#endif
    double sum=0;
    for(int i=0;i<n*(n-1)/2;i++) sum+=proportion[i];
    sum/=n*(n-1)/2;
    for(int i=0;i<n*(n-1)/2;i++) proportion[i]/=sum;        //这行和上2行使proportion均值为1
    for(int i=0;i<n*(n-1)/2;i++) cost+=std::abs(1-proportion[i]);
#ifdef DEBUG
    std::cout<<"costOfWrongMatch in match "<<index<<":"<<cost<<std::endl;
#endif
    delete[] proportion;
    //std::cout<<"!" << std::endl;
    return cost;
}

double SiftCost::distanceX(int index,int i,int j)
{
    return sqrt(pow(Sx[matchs[index][i].trainIdx].pt.x-Sx[matchs[index][j].trainIdx].pt.x,2)
                +pow(Sx[matchs[index][i].trainIdx].pt.y-Sx[matchs[index][j].trainIdx].pt.y,2));
}
double SiftCost::distanceY(int index,int i,int j)
{
    return sqrt(pow(Sx[matchs[index][i].queryIdx].pt.x-Sx[matchs[index][j].queryIdx].pt.x,2)
                +pow(Sx[matchs[index][i].queryIdx].pt.y-Sx[matchs[index][j].queryIdx].pt.y,2));
}

//设置系数
void SiftCost::setTolerance(double _toleranceOfNoMatch)                 //这里可以考虑写成内联函数？
{
    if(_toleranceOfNoMatch<0) toleranceOfNoMatch=0;
    else if(_toleranceOfNoMatch>1) toleranceOfNoMatch=1;
    else toleranceOfNoMatch=_toleranceOfNoMatch;
    return;
}

//对训练集的操作
int SiftCost::addTrainSet(const std::vector<std::string>& trainSets)        //这个地方可以考虑用并行
{
    int count=0;
    for(int i=0;i<trainSets.size();i++){
        count+=addTrainSet(trainSets[i]);
    }
    return count;
}

int SiftCost::addTrainSet(const std::string trainSet)
{
    cv::Mat trainPicture=cv::imread(trainSet);
    if(trainPicture.empty()){
        std::cout<<"Warning! Can't read the training picture:"<<trainSet<<std::endl;
        return 0;
    }
    CDS* temp=new CDS();
    temp->setTestImage(trainPicture);
    temp->extractSIFTKeyPointY();
    if(logoExists){
        temp->setInputImage(logo);
        temp->extractSIFTKeyPointX();
    }

    cds.push_back(temp);
    pictureUpdate=true;
    trainSetNum++;
    return 1;
}

void SiftCost::clearTrainSet()
{
    Sys.clear();
    for(int i=0;i<trainSetNum;i++){
        delete cds[i];
    }
    cds.clear();
    trainSetNum=0;
    return;
}
int SiftCost::resetTrainSet(const std::vector<std::string>& trainSets)
{
    clearTrainSet();
    return addTrainSet(trainSets);
}
int SiftCost::resetTrainSet(std::string trainSet)
{
    clearTrainSet();
     return addTrainSet(trainSet);
}

//对Logo的操作
bool SiftCost::setLogo(std::string logoAdd)
{
    logo=cv::imread(logoAdd);
    if (logo.empty()) {
        std::cout<<"Warning! Can't read logo picture:"<<logoAdd<<std::endl;
        logoExists=false;
        return false;
    }
    logoExists=true;
    for(int i=0;i<trainSetNum;i++){
        cds[i]->setInputImage(logo);
        cds[i]->extractSIFTKeyPointX();
    }
   pictureUpdate=true;
    return true;
}

//构造函数
SiftCost::SiftCost(double _toleranceOfNoMatch):
    keyPointNum(0),trainSetNum(0),logoExists(false),pictureUpdate(false)
{
    setTolerance(_toleranceOfNoMatch);
}

SiftCost::SiftCost(const std::vector<std::string>& trainSets,std::string logo,double _toleranceOfNoMatch):
    keyPointNum(0),trainSetNum(0),logoExists(false),pictureUpdate(false)
{
    setTolerance(_toleranceOfNoMatch);
    addTrainSet(trainSets);
    setLogo(logo);
}
SiftCost::SiftCost(std::string trainSet,std::string logo,double _toleranceOfNoMatch):
    keyPointNum(0),trainSetNum(0),logoExists(false),pictureUpdate(false)
{
    setTolerance(_toleranceOfNoMatch);
    addTrainSet(trainSet);
    setLogo(logo);
}

SiftCost::~SiftCost(){
    for(int i=0;i<trainSetNum;i++)
        delete cds[i];
}


