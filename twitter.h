#ifndef TWITTER_H
#define TWITTER_H

#include <twitcurl.h>

#include "tweet.h"

class Twitter
{
public:
    Twitter();
    bool connect();
    bool login(std::string &accessTokenKey, std::string &accessTokenSecret,
               std::string userName, std::string passWord);
    std::list<Tweet>* getTimeLine();

private:
    twitCurl twitterObj;
    std::string consumerKey = "hUhGxoavwt9iGnQxUSe8a3xgf";
    std::string consumerSecret = "b3BXefp6YBXMgV2e260jtOsfBVajckilONdrIPt9XiEwGXGLZs";
};

#endif // TWITTER_H
