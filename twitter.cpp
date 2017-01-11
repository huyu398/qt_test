#include "twitter.h"
#include "picojson.h"

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
            this->accessTokenKey = accessTokenKey;
            this->accessTokenSecret = accessTokenSecret;
        } else {
            this->twitterObj.getOAuth().setOAuthTokenKey(this->accessTokenKey);
            this->twitterObj.getOAuth().setOAuthTokenSecret(this->accessTokenSecret);
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

const char* Twitter::getTimeLine()
{
    std::string tweet;

    this->twitterObj.timelineHomeGet("818509501208752130");
    this->twitterObj.getLastWebResponse(tweet);

    picojson::value v;
    std::stringstream ss;
    ss << tweet;
    ss >> v;

    if (!picojson::get_last_error().empty()) {
        std::cerr << "error" << std::endl;
        return NULL;
    }

    picojson::array& a = v.get<picojson::array>();
    tweet = std::to_string((long int)a[0].get<picojson::object>()["id"].get<double>());

    return tweet.c_str();
}
