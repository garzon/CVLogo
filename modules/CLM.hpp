//
//  CLM.hpp
//  CVLogo
//
//  Created by 储仲尧 on 10/10/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//

#ifndef CLM_hpp
#define CLM_hpp

#include <iostream>
using namespace std;
class CLM {
    char* url;
public:
    void setUrl(char* targetUrl);
    void fetch_video_tag();
};


void CLM::setUrl(char* targetUrl){
    this->url=targetUrl;
}

void CLM::fetch_video_tag() {
    
}

#endif /* CLM_hpp */
