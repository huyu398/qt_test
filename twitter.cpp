#include "twitter.h"
#include "picojson.h"

// tmp func
bool decode_unicode_escape_to_utf8(const std::string& src, std::string& dst) {
    std::string result("");
    result.resize(src.size());

    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = '\0';
    }

    size_t result_index = 0;
    bool in_surrogate_pair = false;
    size_t surrogate_buffer = 0;
    for (size_t i = 0; i < src.size(); ++i) {
        if (i + 1 < src.size() && src[i] == '\\' && src[i+1] == 'u') {
            size_t octet = 0;
            {  // calculate octet
                const char* const hex = &src[i + 2];
                for (int j = 0; j < 4; ++j) {
                    octet *= 16;
                    if ('0' <= hex[j] && hex[j] <= '9') {
                        octet += static_cast<int>(hex[j] - '0');
                    } else if ('a' <= hex[j] && hex[j] <= 'f') {
                        octet += static_cast<int>(hex[j] - 'a' + 10);
                    } else if ('A' <= hex[j] && hex[j] <= 'F') {
                        octet += static_cast<int>(hex[j] - 'A' + 10);
                    } else {
                        return false;
                    }
                }
            }
            {  // fill up sequence
                char* const sequence = &result[result_index];
                if (in_surrogate_pair) {
                    if (0xdc00 <= octet && octet <= 0xdfff) {
                        // low surrogate pair
                        const size_t joined = surrogate_buffer + (octet & 0x03ff) + 0x10000;
                        sequence[0] = (static_cast<char>(joined >> 18)  &  0x3) | 0xf0;
                        sequence[1] = (static_cast<char>(joined >> 12)  & 0x3f) | 0x80;
                        sequence[2] = (static_cast<char>(joined >> 6)   & 0x3f) | 0x80;
                        sequence[3] = (static_cast<char>(joined & 0xff) & 0x3f) | 0x80;
                        result_index += 4;
                        in_surrogate_pair = false;
                    } else {
                        return false;
                    }
                } else if (octet < 0x7f) {
                    sequence[0] = static_cast<char>(octet) & 0x7f;
                    result_index += 1;
                } else if (octet < 0x7ff) {
                    sequence[0] = (static_cast<char>(octet >> 6) & 0xdf) | 0xc0;
                    sequence[1] = (static_cast<char>(octet)      & 0x3f) | 0x80;
                    result_index += 2;
                } else if (0xdbff) {
                    // high surrogate pair
                    in_surrogate_pair = true;
                    surrogate_buffer = (octet & 0x03ff) * 0x400;
                } else {
                    sequence[0] = (static_cast<char>(octet >> 12) & 0x0f) | 0xe0;
                    sequence[1] = (static_cast<char>(octet >> 6)  & 0x3f) | 0x80;
                    sequence[2] = (static_cast<char>(octet)       & 0x3f) | 0x80;
                    result_index += 3;
                }
            }
            i += 5;  // \\uXXXX is 6 bytes, so + 5 here, and + 1 in next loop
        } else {  // not unicode
            if (in_surrogate_pair) {
                return false;
            }
            result[result_index] = src[i];
            result_index += 1;
        }
        // next char
    }
    result.resize(result_index);
    dst.swap(result);
    return true;
}
//

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

    picojson::value v;
    std::stringstream ss;
    decode_unicode_escape_to_utf8()
    ss << tweet;
    ss >> v;

    if (!picojson::get_last_error().empty()) {
        std::cerr << "error" << std::endl;
        return NULL;
    }

    picojson::array& a = v.get<picojson::array>();
    for (picojson::array::iterator it = a.begin(); it != a.end(); it++) {
        picojson::object o = it->get<picojson::object>();
        std::string userName, tweetContent;
        decode_unicode_escape_to_utf8(
                    o["user"].get<picojson::object>()["name"].get<std::string>(),
                    userName
                );
        decode_unicode_escape_to_utf8(o["text"].get<std::string>(), tweetContent);
        tweetList->emplace_back(userName, tweetContent);
    }
//    tweet = std::to_string((long int)a[0].get<picojson::object>()["id"].get<double>());
    std::cout << tweet << std::endl;
    for (std::list<Tweet>::iterator it = tweetList->begin(); it != tweetList->end(); it++) {
        std::cout << "user name: " << it->getUserName() << std::endl
                  << "content: " << it->getTweetContent() << std::endl;
    }

    return tweetList;
}
