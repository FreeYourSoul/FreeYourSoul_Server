//
// Created by FyS on 31/08/17.
//

#ifndef FREESOULS_AUTHENTICATION_HH
#define FREESOULS_AUTHENTICATION_HH

#include <FySMessage.pb.h>
#include <FySAuthenticationResponse.pb.h>
#include <FySAuthenticationLoginMessage.pb.h>
#include "Gateway.hh"

namespace fys::gateway::buslistener {

    class Authenticator {

    public:
        enum { IndexInBus = 0 };

        Authenticator(Gateway::ptr&);

        void operator()(mq::QueueContainer<fys::pb::FySMessage> msg);

    private:
        void authGameServer(const uint indexSession, pb::LoginMessage &&loginMessage);
        void authPlayer(const uint indexSession, pb::LoginMessage &&loginMessage);
        void authAuthServer(const uint indexSession, pb::LoginMessage &&loginMessage);

        void sendError(const uint indexSession, std::string&& error, fys::pb::LoginErrorResponse::Type errorType);

    private:
        Gateway::ptr _gtw;
    };

}


#endif //FREESOULS_AUTHENTICATION_HH
