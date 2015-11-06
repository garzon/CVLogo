//
//  main.cpp
//  CVLogo
//
//  Created by 储仲尧 on 9/29/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//



#include "moduleControllers.hpp"


using namespace std;

CLM clm;

int captureTest(string filePath,int start,int end,string savePath){
    cv:: VideoCapture capture(filePath);
    if(!capture.isOpened()){
        cerr<<"Opening video faild."<<endl;
        return 1;
    }
    
    /* Set capture property */
    capture.set(CV_CAP_PROP_POS_FRAMES,start);
    
    double rate=capture.get(CV_CAP_PROP_FPS);
    bool stop(false);
    cv::Mat frame;
    cv::namedWindow("Extracted Frame");
    long nFrame=static_cast<long>(capture.get(CV_CAP_PROP_FRAME_COUNT));
    cout<<nFrame<<endl;
    
    while(!stop){
        if(!capture.read(frame))
            break;
            cv::imshow("Extracted Frame",frame);
            if(cv::waitKey())
                stop=true;
        capture.release();
    }
    
    return 0;
}

void moduleTest(CLM clm,string urlPath){
    //clm.loadURL(urlPath);
    

}
json configure(string configurePath){
    ifstream configFile(configurePath, std::ios::binary);
    string s = string(std::istreambuf_iterator<char>(configFile),
                      std::istreambuf_iterator<char>());
    json configPara=json::parse(s.c_str());
    return configPara;
}


int main(int argvs,char* argv[]){
    
    json config=configure(argv[1]); //load configure file
    
    clm.loadURL(config["URL_PATH"].get<string>()); //load URLs
    clm.loadParameter(config["PARA_PATH"].get<string>()); //load parameters

    clm.setLogo(); //set the logo
    
    json tags=clm.fetchTag();
    json currentTag;
    
    int size=tags["list"].size(); // size of the tag array
    int counter=0;
    while(counter<size){
        currentTag=tags["list"][counter];
        clm.cutImage(currentTag["videoPath"],currentTag["resolution"], currentTag["adTime"],currentTag["adLength"],currentTag["adWidth"], currentTag["adX"], currentTag["adY"]);
        if(clm.logoMatch())
            clm.setMatch(currentTag["filmTagId"]);
    }
    
    //waitKey();
    
    return 0;
}


//int main(){
//    CDS cds;
//    cv::Mat logo;
//    cv::Mat image;
//    logo=cv::imread("./logo.jpeg");
//    image=cv::imread("./1.jpeg");
//    cds.setInputImage(logo);
//    cds.setTestImage(image);
//    if(cds.process())
//    {
//        cout<<"Matched!"<<endl;
//    }
//    else{
//        cout<<"MisMatched!"<<endl;
//    }
//    return 0;
//}