//
// Created by FyS on 26/05/17.
//

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "Context.hh"

fys::gateway::Context::~Context() {}

fys::gateway::Context::Context(const std::string &iniPath) {
    try {
        this->initializeFromIni(iniPath);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

unsigned short fys::gateway::Context::getPort() const {
    return _port;
}

void fys::gateway::Context::setPort(const unsigned short port) {
    Context::_port = port;
}

const std::string &fys::gateway::Context::getBusIniFilePath() const {
    return _busIniFilePath;
}

void fys::gateway::Context::setBusIniFilePath(const std::string &busIniFilePath) {
    Context::_busIniFilePath = busIniFilePath;
}

size_t fys::gateway::Context::getAsioThread() const {
    return _asioThread;
}

void fys::gateway::Context::setAsioThread(const size_t asioThread) {
    Context::_asioThread = asioThread;
}

void fys::gateway::Context::initializeFromIni(const std::string &iniPath) {
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(iniPath, pt);

    setPort(pt.get<short>(GTW_INI_PORT));
    setAsioThread(pt.get<std::size_t>(GTW_INI_ASIO_THREADS));
    setBusIniFilePath(pt.get<std::string>(GTW_INI_BUS_PATH));
    std::cout << "Context Initialization -> " << this << std::endl;
}

std::ostream &fys::gateway::Context::operator<<(std::ostream &os, const fys::gateway::Context &context) {
    os << "_port: " << context._port << " _asioThread: " << context._asioThread << " _busIniFilePath: "
       << context._busIniFilePath;
    return os;
}
