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
        clm.setCurrentLogo(currentTag["logoPath"]);
        clm.cutImage(currentTag["videoPath"],currentTag["resolution"], currentTag["adTime"],currentTag["adLength"],currentTag["adWidth"], currentTag["adX"], currentTag["adY"]);
        if(clm.logoMatch())
            clm.setMatch(currentTag["filmTagId"],currentTag["logoId"]);
    }
    
    //waitKey();
    
    return 0;
}

//
//int main(int argvs, char* argv[]){
//    
//    json test;
//    
//    json config=configure(argv[1]); //load configure file
//    ifstream urlFile(config["URL_PATH"].get<string>(), std::ios::binary);
//    string s = string(std::istreambuf_iterator<char>(urlFile),
//                      std::istreambuf_iterator<char>());
//    json URLs=json::parse(s.c_str());
//    
//    string getallfilmtaginfo="http://ivory.edwardchor.com/CVLogo/getallfilmtaginfo.php";
//    string setmatch="http://ivory.edwardchor.com/CVLogo/setMatch.php?film_tag_id=001&logo_id=001&is_match=001";
//   
//    string _res;
//    cout<<URLs["CLM_FETCH_TAG_URL"]<<endl;
//    
//    while(!net::get(URLs["CLM_FETCH_TAG_URL"].get<string>().c_str(), _res)) {
//        sleep(5);
//    }
//
//    cout<<"the stream fetched:"<<_res<<endl;
//    json res=json::parse(_res);
//
//    json tags=res;
//    json currentTag;
//    
//    int size=tags["list"].size(); // size of the tag array
//    int counter=0;
//    cout<<"The size of the fetched list: "<<size<<endl;
//    while(counter<size){
//        cout<<"The adUrl of tag indexed of "<<counter<<endl;
//        currentTag=tags["list"][counter++];
//        cout<<currentTag["adUrl"]<<endl;
//    }
//    
//    waitKey();
//    return 0;
//}
