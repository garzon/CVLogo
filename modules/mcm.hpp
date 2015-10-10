//
//  mcm.hpp
//  CVLogo
//
//  Created by 储仲尧 on 10/10/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//

#ifndef mcm_hpp
#define mcm_hpp

#include <stdio.h>
#include <curl/curl.h>
#include "../json/json.hpp"
#include "../cds/cds.cpp"

using namespace std;


class MCM
{
    char* url;
public:
    void setUrl(char* targetUrl);
    void fetch_item_info();
};


void MCM::setUrl(char *targetUrl){
    this->url=targetUrl;
}

void MCM::fetch_item_info(){
    
}

#endif /* mcm_hpp */
