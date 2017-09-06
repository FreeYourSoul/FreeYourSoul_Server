//
// Created by FyS on 26/05/17.
//

#ifndef FREESOULS_CONTEXT_HH
#define FREESOULS_CONTEXT_HH

#include <string>
#include <ostream>
#include "GameServerInstance.hh"

#define GTW_INI_PORT "server.port"
#define GTW_INI_ASIO_THREADS "server.asioThread"
#define GTW_INI_BUS_PATH "bus.iniPath"
#define GTW_QUEUES_SIZE "bus.queuesSize"

namespace fys {
    namespace gateway {

        enum { BUS_QUEUES_SIZE = 1024 };

        class Context {

        public:
            ~Context();
            Context(const int ac, const char *const *av);
            Context(const Context&);
            Context(Context&&);

            friend std::ostream &operator<<(std::ostream &os, const Context &context);

            u_short getPort() const;
            void setPort(const u_short port);
            const std::string &getBusIniFilePath() const;
            void setBusIniFilePath(const std::string &busIniFilePath);
            size_t getAsioThread() const;
            void setAsioThread(const size_t asioThread);
            std::size_t getQueuesSize() const;
            bool isVerbose() const;
            void setVerbose(bool _verbose);
            void setQueuesSize(const std::size_t _queuesSize);

        private:
            void initializeFromIni(const std::string &iniPath);

        private:
            u_short _port;
            std::size_t _asioThread;
            std::string _busIniFilePath;
            std::size_t _queuesSize;
            bool _verbose;

            std::vector<gateway::GameServerInstance> _gameServers;
        };

    }
}


#endif //FREESOULS_CONTEXT_HH
