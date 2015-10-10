//
//  main.cpp
//  CVLogo
//
//  Created by 储仲尧 on 9/29/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <curl/curl.h>
#include "../json/json.hpp"
#include "../modules/CLM.hpp"
#include "../modules/MCM.hpp"

using namespace std;
using namespace cv;

char* MCM_fetchInfoUrl="http://localhost:8080/VideoInfo/getcommodity.do";
char* CLM_fetchTagUrl="http://localhost:8080/VideoInfo/getallfilmtaginfo.do?";
char* CLM_sendInfoUrl="http://localhost:8080/VideoInfo/setmatch.do?";

int test(){
    char* url;
    
    /* set the processig url */
    url="http://ivory.edwardchor.com/CVLogo/generator.php";
    CURL *curl;
    CURLcode res;
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL,url);
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        cout<<endl;
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    
    return 0;
}

int main(int argvs,char* argv[]){
    test();
    return 0;
}