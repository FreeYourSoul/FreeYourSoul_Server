//
// Created by FyS on 27/06/17.
//

#ifndef FREESOULS_MOCKVERIFIER_HH
#define FREESOULS_MOCKVERIFIER_HH

#include <string>
#include <FysBus.hh>
#include <boost/test/test_tools.hpp>
#include <functional>
#include <map>

namespace FSeam {

    /**
     * \brief basic structure that contains description and utilisation of mocked method
     *
     */
    struct MethodCallVerifier {
        std::string _methodName;
        std::size_t _called = 0;

        std::function<void(void*)> _handler;
    };

    /**
     * \brief Mocking class, it contains all mocked method / save all calls to methods
     * \todo improve the mocking class to take the arguments and compare them in a verify
     */
    class MockClassVerifier {
    public:
        void invokeDupedMethod(std::string &&className, std::string &&methodName, void *arg = nullptr) {
            std::string key = std::move(className) + std::move(methodName);

            if (_verifiers.find(key) != _verifiers.end()) {
                _verifiers.at(key)->_handler(arg);
            }
        }

        /**
         * This method has to be called each time a mocked class is calling a method (in order to register the call)
         *
         * \param className name of the mocked class
         * \param methodName name of the method called
         */
        void methodCall(std::string &&className, std::string &&methodName) {
            auto methodCallVerifier = std::make_shared<MethodCallVerifier>();
            std::string key = std::move(className) + methodName;

            if (_verifiers.find(key) != _verifiers.end())
                methodCallVerifier = _verifiers.at(key);
            methodCallVerifier->_methodName = std::move(methodName);
            methodCallVerifier->_called += 1;
            _verifiers[key] = methodCallVerifier;
            std::cout << "The method " << key << " has been called " << methodCallVerifier->_called << " times" << std::endl;
        }

        /**
         * \brief This method make it possible to dupe a method in order to have it do what you want.
         *
         * \tparam T handler type
         * \param className name of the class to mock
         * \param methodName method name to dupe
         * \param handler dupped method
         */
        void dupeMethod(std::string &&className, std::string &&methodName, std::function<void(void*)> handler) {
            auto methodCallVerifier = std::make_shared<MethodCallVerifier>();
            std::string key = std::move(className) + methodName;

            if (_verifiers.find(key) != _verifiers.end())
                methodCallVerifier = _verifiers.at(key);
            methodCallVerifier->_methodName = std::move(methodName);
            methodCallVerifier->_called = 0;
            methodCallVerifier->_handler = handler;
            _verifiers[key] = methodCallVerifier;
            std::cout << "The method " << key << " has been mocked" << std::endl;
        }

        /**
         * \brief Verify if a method has been called under certain conditions (number of times)
         *
         * \param className class name to verify
         * \param methodName method to verify
         * \param times number of times you verify that the mocked method has been called, if no value set, this method
         * verify you at least have the mocked method called once
         * \return true if the method encounter your conditions (number of times called), false otherwise
         */
        bool verify(std::string &&className, std::string &&methodName, const int times = -1) const {
            std::string key = std::move(className) + std::move(methodName);

            if (_verifiers.find(key) == _verifiers.end()) {
                std::cerr << key << " method hasn't been mocked" << std::endl;
                return false;
            }
            return (_verifiers.at(key)->_called > 0 && times == -1) ||
                   (_verifiers.at(key)->_called == times);
        }

    private:
        std::map<std::string, std::shared_ptr<MethodCallVerifier> > _verifiers;
    };

    /**
     * \brief Mocking singleton, this class contains all the mock
     */
    class MockVerifier {
        static std::unique_ptr<MockVerifier> inst;
        static std::once_flag once_flag;

    public:
        MockVerifier() = default;
        ~MockVerifier() = default;

        static MockVerifier &instance() {
            std::call_once(once_flag, []() {
                inst = std::make_unique<MockVerifier>();
            });
            return *(inst.get());
        }

        std::shared_ptr<MockClassVerifier> &getMock(const void *mockPtr) {
            if (inst->_mockedClass.find(mockPtr) == inst->_mockedClass.end())
                return addMock(mockPtr);
            return inst->_mockedClass.at(mockPtr);
        }

        template <typename T>
        std::shared_ptr<MockClassVerifier> &addMock(const T *mockPtr) {
            auto classVerifier = std::make_shared<MockClassVerifier>();
            inst->_mockedClass[mockPtr] = classVerifier;
            return inst->_mockedClass.at(mockPtr);
        }

    private:
        std::map<const void*, std::shared_ptr<MockClassVerifier> > _mockedClass;
    };

    // ------------------------ Helper Method --------------------------


}



#endif //FREESOULS_MOCKVERIFIER_HH
