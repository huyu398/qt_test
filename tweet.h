#ifndef TWEET_H
#define TWEET_H

#include <string>
#include <QString>

class Tweet
{
public:
    Tweet(std::string userName, std::string tweetContent);
    QString getUserName();
    QString getTweetContent();

private:
    std::string userName;
    std::string tweetContent;
};

#endif // TWEET_H
