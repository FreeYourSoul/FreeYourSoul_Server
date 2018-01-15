//
// Created by FyS on 03/09/17.
//

#ifndef FREESOULS_TOKENGENERATOR_HH
#define FREESOULS_TOKENGENERATOR_HH

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

namespace fys {
    namespace utils {

        class TokenGenerator {
        public:

            static std::unique_ptr<TokenGenerator> getInstance() {
                if (!instance) {
                    instance = std::make_unique<TokenGenerator>();
                }
                return instance;
            }

            const std::string generate() const;
            const std::vector<char> generateByte();

        private:
            TokenGenerator() = default;

        private:
            boost::uuids::random_generator _generator;

            static std::unique_ptr<TokenGenerator> instance;

        };
    }
}


#endif //FREESOULS_TOKENGENERATOR_HH
