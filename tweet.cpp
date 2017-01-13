#include "tweet.h"

Tweet::Tweet(std::string userName, std::string tweetContent)
    : userName(userName), tweetContent(tweetContent)
{
}

std::string Tweet::getUserName() {
    return this->userName;
}

std::string Tweet::getTweetContent() {
    return this->tweetContent;
}
