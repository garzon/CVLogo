//
//  moduleControllers.hpp
//  CVLogo
//
//  Created by 储仲尧 on 10/10/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//

#ifndef moduleControllers_hpp
#define moduleControllers_hpp

#include "../json/json.hpp"
#include "../cds/cds.h"
#include "../json/NetworkHandler.hpp"
#include "opencv2/opencv.hpp"

using json = nlohmann::json;
using namespace std;
using namespace cv;

typedef string URL;

const int CLM_SET_TAG=0;
const int CLM_SET_INFO=1;


/* Module of Marking Commodity */
class MCM
{
    json URLs;
    json parameters;
public:
    void loadURL(string urlPath);
    void loadParameter(string parameterPath);
    json fetchInfo();
    bool userTagMatch(string filePath,string resolution,string adTime,string adLength,string adWidth,string adX,string adY,string commidityId,string commodityPicPath);
};

/* Module of Commodity-Logo Matching */
class CLM {
    json URLs;
    json parameters;//logopath, logid, remark
    Mat logo;
    Mat image;
public:
    void loadURL(string urlPath);
    void loadParameter(string parameterPath);
    json fetchTag();
    void cutImage(string videoPath,string resolution,string adTime,string adLength,string adWidth,string adX,string adY);
    void setLogo();
    void setCurrentLogo(string dir);
    bool logoMatch();
    json setMatch(string filmTagId, string logoId);
};

/* Module of Commodity */
class CMM {
    /* Waiting for discussion */
};
#endif /* moduleControllers_hpp */
