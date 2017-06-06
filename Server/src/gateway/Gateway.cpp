//
// Created by FyS on 23/05/17.
//

#include "../../include/gateway/Gateway.hh"

fys::gateway::Gateway::~Gateway() { }

fys::gateway::Gateway::Gateway(const fys::gateway::Context &ctx) : _acceptor(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), ctx.getPort())) { }

void fys::gateway::Gateway::handlePlayerConnection(fys::network::TcpConnection::pointer &newSession) {
    newSession->readOnSocket();
    _gamerConnections.addPendingConnection(newSession);
    runPlayerAccept();
}

void fys::gateway::Gateway::runPlayerAccept() {
    network::TcpConnection::pointer session = network::TcpConnection::create(_ios);

    _acceptor.async_accept(session->getSocket(), boost::bind(&handlePlayerConnection, this, session));
}

