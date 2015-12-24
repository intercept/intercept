/*!
@file
@author Nou (korewananda@gmail.com)

@brief Contains the intercept::invoker class.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "loader.hpp"
#include "shared\types.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>


using namespace intercept::types;


namespace intercept {
    /*!
    @brief Contains all the wrapper functions to calling events from the RV engine
    in client plugins.
    */
    class eventhandlers
        : public singleton<eventhandlers>
    {
    public:
        eventhandlers();
        ~eventhandlers();

        void initialize();

        void pre_init(const std::string &name_, game_value &args_);
        void post_init(const std::string &name_, game_value &args_);
        void mission_stopped(const std::string &name_, game_value &args_);
        void fired(const std::string &name_, game_value &args_);

    protected:
        bool _initialized;
    };

}