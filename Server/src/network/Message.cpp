//
// Created by FyS on 23/05/17.
//

#include <boost/array.hpp>
#include <cstring>
#include "../../include/network/Message.hh"

fys::network::Message::~Message() {}

fys::network::Message::Message() {
}

fys::network::Message::Message(unsigned char rawMessage[]) {
//    std::copy(std::begin(rawMessage), std::end(rawMessage), _rawMessage);
    loadOpCode();
}

void fys::network::Message::loadOpCode() {
    BitConvert btc;

    for (int i = 0; i < 2; ++i)
        btc.byte[i] = _rawMessage[i];
    _opCode = btc.tbytes[0];
}

unsigned int fys::network::Message::byteToInt(unsigned int index) {
    BitConvert bti;

    for (int i = 0; i < 4; ++i)
        bti.byte[i] = _rawMessage[index + i];
    return bti.integer;
}

unsigned char *fys::network::Message::intToChar(unsigned int toConvert) {
    BitConvert bti;
    unsigned char *ret = new unsigned char[4];

    bti.integer = toConvert;
    memcpy(ret, bti.byte, 4);
    return ret;
}
