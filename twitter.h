#ifndef TWITTER_H
#define TWITTER_H

#include <twitcurl.h>

class Twitter
{
public:
    Twitter();
    bool connect();
    bool login(std::string &accessTokenKey, std::string &accessTokenSecret,
               std::string userName, std::string passWord);
    const char* getTimeLine();

private:
    twitCurl twitterObj;
    std::string consumerKey = "hUhGxoavwt9iGnQxUSe8a3xgf";
    std::string consumerSecret = "b3BXefp6YBXMgV2e260jtOsfBVajckilONdrIPt9XiEwGXGLZs";
    std::string accessTokenKey, accessTokenSecret;
};

#endif // TWITTER_H
