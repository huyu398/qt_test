#include "twitter.h"
#include "json.hpp"

using nlohmann::json;

Twitter::Twitter()
{
}

bool Twitter::connect()
{
    std::cout << "Passed" << std::endl;
    return true;
}

bool Twitter::login(std::string &accessTokenKey, std::string &accessTokenSecret,
                    std::string userName, std::string passWord)
{
    try {
        this->twitterObj.getOAuth().setConsumerKey(this->consumerKey);
        this->twitterObj.getOAuth().setConsumerSecret(this->consumerSecret);

        if (accessTokenKey.empty() || accessTokenSecret.empty()) {
            if (userName.empty() || passWord.empty()) {
                return false;
            }
            this->twitterObj.setTwitterUsername(userName);
            this->twitterObj.setTwitterPassword(passWord);

            std::string authUrl;
            this->twitterObj.oAuthRequestToken(authUrl);
            this->twitterObj.oAuthHandlePIN(authUrl);
            this->twitterObj.oAuthAccessToken();

            this->twitterObj.getOAuth().getOAuthTokenKey(accessTokenKey);
            this->twitterObj.getOAuth().getOAuthTokenSecret(accessTokenSecret);
        } else {
            this->twitterObj.getOAuth().setOAuthTokenKey(accessTokenKey);
            this->twitterObj.getOAuth().setOAuthTokenSecret(accessTokenSecret);
        }

        if (!this->twitterObj.accountVerifyCredGet()) {
            std::string errorMessage;
            this->twitterObj.getLastCurlError(errorMessage);
            std::cerr << "twitCurl::accountVerifyCredGet() error: "
                      << errorMessage.c_str() << std::endl;
            return false;
        }
    } catch (char *e) {
        std::cerr << "[EXCEPTION] " << e << std::endl;
        return false;
    }

    return true;
}

std::list<Tweet>* Twitter::getTimeLine()
{
    std::list<Tweet>* tweetList = new std::list<Tweet>;
    std::string tweet, tweetDecoded;

    this->twitterObj.timelineHomeGet();
    this->twitterObj.getLastWebResponse(tweet);

    json j = json::parse(tweet);
    for (json::iterator it = j.begin(); it != j.end(); it++) {
        std::string userName, tweetContent;
        userName = (*it)["user"]["name"].get<std::string>();
        tweetContent = (*it)["text"].get<std::string>();
        tweetList->emplace_back(userName, tweetContent);
    }

    return tweetList;
}
