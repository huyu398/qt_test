#ifndef TWEET_H
#define TWEET_H

#include <string>

class Tweet
{
public:
    Tweet(std::string userName, std::string tweetContent);
    std::string getUserName();
    std::string getTweetContent();

private:
    std::string userName;
    std::string tweetContent;
};

#endif // TWEET_H
