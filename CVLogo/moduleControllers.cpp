//
//  moduleControllers.cpp
//  CVLogo
//
//  Created by 储仲尧 on 10/10/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//

#include "moduleControllers.hpp"
/* Set URLs */

bool IS_MATCH=true;
bool DIS_MATCH=false;

CDS cds;

/* Module of Marking Commodity */

void MCM::loadURL(string urlPath){
    ifstream urlFile(urlPath, std::ios::binary);
    string s = string(std::istreambuf_iterator<char>(urlFile),
                      std::istreambuf_iterator<char>());
    URLs=json::parse(s.c_str());
    return;
}

void MCM:: loadParameter(string parameterPath){
    ifstream paraFile(parameterPath, std::ios::binary);
    string s = string(std::istreambuf_iterator<char>(paraFile),
                      std::istreambuf_iterator<char>());
    parameters=json::parse(s.c_str());
    return;
}


json MCM::fetchInfo(){
    string pUrl;
    pUrl+=this->URLs["MCM_FETCH_INFO_URL"].get<string>();
    pUrl+="filmNameid="+parameters["filmNameId"].get<string>();
    pUrl+="&actor="+parameters["actorId"].get<string>();
    pUrl+="&director="+parameters["directorId"].get<string>()+"&remark=''";
    
    string _res;
    while(!net::get(pUrl.c_str(), _res)) {
        sleep(5);
    }
    json res=json::parse(_res);
    return res;
}

bool MCM::userTagMatch(string filePath,string resolution,string adTime,string adLength,string adWidth,string adX,string adY,string commidityId,string commodityPicPath){
    /* Set the frame capture */
    cv:: VideoCapture capture(filePath);
    if(!capture.isOpened()){
        cerr<<"Opening video faild."<<endl;
        return 1;
    }
    /* Set capture property */
    capture.set(CV_CAP_PROP_POS_FRAMES,atoi(adTime.c_str()));
    
    double rate=capture.get(CV_CAP_PROP_FPS);
    bool stop(false);
    cv::Mat frame;
    cv::namedWindow("Extracted Frame");
    
    int delay=1000/rate;
    
    while(!stop){
        
        if(!capture.read(frame))
            break;
            cv::imshow("Extracted Frame",frame);
            if(cv::waitKey(delay)>=0)
                stop=true;
        
        capture.release();
    }
    
    return IS_MATCH;
}




/* Module of Commodity Logo */

void CLM:: loadURL(string urlPath){
    ifstream urlFile(urlPath, std::ios::binary);
    string s = string(std::istreambuf_iterator<char>(urlFile),
                      std::istreambuf_iterator<char>());
    URLs=json::parse(s.c_str());
    return;
}

void CLM:: loadParameter(string parameterPath){
    ifstream paraFile(parameterPath, std::ios::binary);
    string s = string(std::istreambuf_iterator<char>(paraFile),
                      std::istreambuf_iterator<char>());
    parameters=json::parse(s.c_str());
    return;
}



json CLM::fetchTag(){
    string pUrl=URLs["CLM_FETCH_TAG_URL"].get<string>();
    string _res;
    while(!net::get(pUrl.c_str(), _res)) {
        sleep(5);
    }
    json res=json::parse(_res);
    return res;
}



json CLM::setMatch(string filmTagId){
    string pUrl=URLs["CLM_SET_MATCH_URL"].get<string>();
    pUrl+="filmtagid="+filmTagId;
    pUrl+="&logoid="+parameters["logoId"].get<string>();
    string _res;
    while(!net::get(pUrl.c_str(), _res)) {
        sleep(5);
    }
    json res=json::parse(_res);
    return res;
}

void CLM:: cutImage(string videoPath,string resolution,string adTime,string adLength,string adWidth,string adX,string adY){
    cv::VideoCapture capture(videoPath);
    cv::Mat frame;

    
    /* Set capture property */
    capture.set(CV_CAP_PROP_POS_MSEC,atoi(adTime.c_str())); // set the timestamp of target frame


    capture.read(frame);
    
    cv::Rect rect(atoi(adX.c_str()),atoi(adY.c_str()),atoi(adWidth.c_str()),atoi(adLength.c_str()));
    cv::Mat frameCut=frame(rect);
    
    capture.release();
    
    
    image=frameCut;
    return;
}

void CLM::setLogo(){
    logo=cv::imread(parameters["logoPath"]);
    return;
}

bool CLM::logoMatch(){
    cds.setInputImage(logo);
    cds.setTestImage(image);
    
    return cds.process();
}