//
//  NetworkHandler.hpp
//  CVLogo
//
//  Created by 储仲尧 on 10/11/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//

#ifndef NetworkHandler_hpp
#define NetworkHandler_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <curl/curl.h>

using namespace std;

namespace net {

    
    static size_t
    WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
    
    bool post(const char *url, const std::string &data);
    
    bool get(const char *url, std::string &str);
   
}

#endif /* NetworkHandler_hpp */
