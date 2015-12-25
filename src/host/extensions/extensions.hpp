/*!
@file
@author Nou (korewananda@gmail.com)

@brief Handles loading and unloading client plugins.

This contains the functionality for loading and unload client plugin modules.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "shared\functions.hpp"
#include "shared\client_types.hpp"

namespace intercept {
    /*!
    @namespace
    @brief Contains the module entry definitions and classes.
    */
    namespace module {
        /*!
        @name Plugin Exported Function Definitions
        */
        /*!@{
        @brief Function definitions.
        */
        typedef int(__cdecl *api_version_func)();
        typedef void(__cdecl *assign_functions_func)(const struct intercept::client_functions funcs);
        typedef void(__cdecl *pre_init_func)();
        typedef void(__cdecl *post_init_func)();
        typedef void(__cdecl *mission_end_func)();
        typedef void(__cdecl *mission_stopped_func)();
        typedef void(__cdecl *on_frame_func)();
        typedef void(__cdecl *fired_func)(
            object &unit_,
            std::string &weapon_,
            std::string &muzzle_,
            std::string &mode_,
            std::string &ammo_,
            std::string &magazine,
            object &projectile_);
        //!@}

        /*!
        @brief Holds the addresses of exported functions from client plugins.
        */
        struct functions {
            /*!@{
            @brief Addresses of exported functions.
            */
            api_version_func api_version;
            assign_functions_func assign_functions;
            pre_init_func pre_init;
            post_init_func post_init;
            mission_end_func mission_end;
            mission_stopped_func mission_stopped;
            on_frame_func on_frame;
            fired_func fired;
            //!@}
        };

        /*!
        @brief A client entry. Stores, name handles, function pointers, etc.
        */
        class entry {
        public:
            entry() : handle(nullptr), name("") {}
            entry(const std::string & name_, HMODULE handle_) : handle(handle_), name(name_) {}
            /*!
            @brief The name of the module
            */
            std::string name;

            /*!
            @brief A intercept::module::functions struct containing pointers to
            plugin exported functions.
            */
            functions functions;

            /*!
            @brief A handle to the plugin dynamic library.
            */
            HMODULE     handle;
        };
    }

    /*!
    @brief Extension controller module.

    This controller module handles loading and unloading client plugins.
    */
    class extensions : public singleton<extensions> {
    public:
        extensions();
        ~extensions();

        /*!
        @brief Attaches the controller functions to the main controllers.
        */
        void attach_controller();
        /*!
        @name Controller Functions
        */
        //!@{
        /*!
        @brief Loads a client plugin.

        This handles all the initialization of a client plugin, and storing the
        results in the map of loaded clients.
        */
        bool load(const arguments & args_, std::string & result);

        /*!
        @brief Unloads a client plugin.

        Unloads and removes a client plugin.
        */
        bool unload(const arguments & args_, std::string & result);

        /*!
        @brief Returns a list of all loaded modules to SQF.
        */
        bool list(const arguments & args_, std::string & result);
        //!@}

        /*!
        @brief Returns the map of all loaded modules.
        */
        const std::unordered_map<std::string, module::entry>& modules();

        /*!
        @brief The struct that contains the functions exported to client plugins.
        */
        client_functions functions;
    protected:
        /*!
        @brief The map of all loaded modules.
        */
        std::unordered_map<std::string, module::entry> _modules;
    };
};
