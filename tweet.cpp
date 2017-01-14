#include "tweet.h"

Tweet::Tweet(std::string userName, std::string tweetContent)
    : userName(userName), tweetContent(tweetContent)
{
}

QString Tweet::getUserName() {
    return QString::fromStdString(this->userName);
}

QString Tweet::getTweetContent() {
    return QString::fromStdString(this->tweetContent);
}
