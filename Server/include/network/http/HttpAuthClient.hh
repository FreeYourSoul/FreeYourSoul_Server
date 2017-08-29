//
// Created by FyS on 28/08/17.
//

#ifndef FREESOULS_HTTPCLIENT_HH
#define FREESOULS_HTTPCLIENT_HH

#include <curl/curl.h>
#include <vector>
#include <string>
#include "GameServerInstance.hh"

namespace fys {
    namespace network {

        class AuthMessage;

        namespace http {

            static const char *URL_SERVICE = "https://restcountries.eu/rest/v2/region/europe";

            class HttpAuthClient {

            public:
                using funcPtr = void (fys::network::http::HttpAuthClient::*)(const fys::network::AuthMessage &);

                ~HttpAuthClient();
                HttpAuthClient();

                bool authenticate(const std::string& user, const std::string& password);

            private:
                CURL *_curl;

            };

        }
    }
}


#endif //FREESOULS_HTTPCLIENT_HH
