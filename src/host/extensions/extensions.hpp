/*!
@file
@author Nou (korewananda@gmail.com)

@brief Handles loading and unloading client plugins.

This contains the functionality for loading and unload client plugin modules.

https://github.com/NouberNou/intercept

@defgroup plugin_interface Cross-Plugin Interface

*/
#pragma once
#include "arguments.hpp"
#include "logging.hpp"
#include "shared.hpp"
#include "shared/client_types.hpp"
#include "shared/functions.hpp"
#include "singleton.hpp"
#include "signing.hpp"
#include "search.hpp"

#if __linux__
#define DLL_HANDLE void *
#else
#define DLL_HANDLE HMODULE
#endif

#define EXP_FNC_typedef(name, ...) typedef void(CDECL * name##_func)(__VA_ARGS__);
#define EXP_FNC_STRUCT_DEF(name, ...) name##_func name;

namespace intercept {
    /*!
    @namespace module
    @brief Contains the module entry definitions and classes.
    */
    namespace module {
        /*!
        @name Plugin Exported Function Definitions
        */

        /*!@{
        @brief Function definitions.
        */
        typedef int(CDECL *api_version_func)();
        typedef void(CDECL *assign_functions_func)(const struct client_functions funcs, r_string module_name);
        typedef void(CDECL *handle_unload_func)();
        typedef void(CDECL *pre_start_func)();
        typedef void(CDECL *pre_init_func)();
        typedef void(CDECL *post_init_func)();
        typedef void(CDECL *mission_ended_func)();
        typedef void(CDECL *on_frame_func)();
        typedef void(CDECL *on_signal_func)(game_value_parameter this_);
        typedef void(CDECL *on_interface_unload_func)(r_string name_);
        typedef void(CDECL *register_interfaces_func)();
        typedef void(CDECL *client_eventhandler_func)(game_value& retVal, uint8_t ehType, int32_t uid, int handle, game_value args);
        typedef void(CDECL *client_eventhandlers_clear_func)();
        typedef bool(CDECL *is_signed_function)();

        //!@}

        /*!
        @brief Holds the addresses of exported functions from client plugins.
        */
        struct functions_list {
            /*!@{
            @brief Addresses of exported functions.
            */
            api_version_func api_version;
            assign_functions_func assign_functions;
            handle_unload_func handle_unload;
            handle_unload_func handle_unload_internal;
            pre_start_func pre_start;
            pre_start_func post_start;
            pre_init_func pre_init;
            pre_init_func pre_pre_init;
            post_init_func post_init;
            mission_ended_func mission_ended;
            on_frame_func on_frame;
            on_signal_func on_signal;
            on_interface_unload_func on_interface_unload;
            register_interfaces_func register_interfaces;
            client_eventhandler_func client_eventhandler;
            client_eventhandlers_clear_func client_eventhandlers_clear;
            //!@}
        };

//name,arguments...
#define EH_LIST(XX)                                                                                                                       \
    XX(anim_changed, object &unit_, r_string anim_name_)                                                                                  \
    XX(anim_done, object &unit_, r_string anim_name_)                                                                                     \
    XX(anim_state_changed, object &unit_, r_string anim_name_)                                                                            \
    XX(container_closed, object &container_, object &player_)                                                                             \
    XX(controls_shifted, object &vehicle_, object &new_controller_, object &old_controller_)                                              \
    XX(dammaged, object &unit_, r_string selection_name_, float damage_)                                                                  \
    XX(engine, object &vehicle_, bool engine_state_)                                                                                      \
    XX(epe_contact, object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_)                         \
    XX(epe_contact_end, object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_)                     \
    XX(epe_contact_start, object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_)                   \
    XX(explosion, object &vehicle_, float damage_)                                                                                        \
    XX(fired, object &unit_, r_string weapon_, r_string muzzle_, r_string mode_, r_string ammo_, r_string magazine, object &projectile_)  \
    XX(fired_near, object &unit_, object &firer_, float distance_, r_string weapon_, r_string muzzle_, r_string mode_, r_string ammo_)    \
    XX(fuel, object &vehicle_, bool fuel_state_)                                                                                          \
    XX(gear, object &vehicle_, bool gear_state_)                                                                                          \
    XX(get_in, object &vehicle_, r_string position_, object &unit_, rv_turret_path turret_path)                                           \
    XX(get_out, object &vehicle_, r_string position_, object &unit_, rv_turret_path turret_path)                                          \
    XX(handle_damage, object &unit_, r_string selection_name_, float damage_, object &source_, r_string projectile_, int hit_part_index_) \
    XX(handle_heal, object &unit_, object &healder_, bool healer_can_heal_)                                                               \
    XX(handle_rating, object &unit_, float rating_)                                                                                       \
    XX(handle_score, object &unit_, object &object_, float score_)                                                                        \
    XX(hit, object &unit_, object &caused_by_, float damage_)                                                                             \
    XX(hit_part, auto_array<hit_part_data> &data_)                                                                                        \
    XX(init, object &unit_)                                                                                                               \
    XX(incoming_missile, object &unit_, r_string ammo_, object &firer_)                                                                   \
    XX(inventory_closed, object &object_, object &container_)                                                                             \
    XX(inventory_opened, object &object_, object &container_)                                                                             \
    XX(killed, object &unit_, object &killer_)                                                                                            \
    XX(landed_touch_down, object &plane_, int airport_id_)                                                                                \
    XX(landed_stopped, object &plane_, int airport_id_)                                                                                   \
    XX(local, object &object_, bool local_)                                                                                               \
    XX(post_reset)                                                                                                                        \
    XX(put, object &unit_, object &container_, r_string item_)                                                                            \
    XX(respawn, object &unit_, object &corpse_)                                                                                           \
    XX(rope_attach, object &object1, object &rope_, object &object2_)                                                                     \
    XX(rope_break, object &object1, object &rope_, object &object2_)                                                                      \
    XX(seat_switched, object &vehicle_, object &unit1_, object &unit2_)                                                                   \
    XX(sound_played, object &unit_, int sound_code_)                                                                                      \
    XX(take, object &unit_, object &container_, r_string item_)                                                                           \
    XX(task_set_as_current, object &unit_, task &task_)                                                                                   \
    XX(weapon_assembled, object &unit_, object &weapon_)                                                                                  \
    XX(weapon_disassembled, object &unit_, object &primary_bag_, object &secondary_bag_)                                                  \
    XX(weapon_deployed, object &unit_, bool is_deployed_)                                                                                 \
    XX(weapon_rested, object &unit_, bool is_rested_)


        EH_LIST(EXP_FNC_typedef)

        struct eventhandlers_list {
            EH_LIST(EXP_FNC_STRUCT_DEF)
        };

        /*!
        @brief This contains all information to identify a specific version of a specific plugin interface.
        */
        class plugin_interface_identifier {
        public:
            plugin_interface_identifier(r_string name_, r_string module_name_, uint32_t api_version_) : name(name_), module_name(module_name_), api_version(api_version_) {}

            bool operator<(const plugin_interface_identifier &other) const {
                return name < other.name || (name == other.name && api_version < other.api_version);
            }
            bool operator==(const plugin_interface_identifier &other) const {
                return api_version == other.api_version && name == other.name;
            }
            r_string name;
            r_string module_name;  //name of the module that registered this interface
            uint32_t api_version;
        };

        /*!
        @brief A interface exported by a plugin. Used for inter-plugin communication
        */
        class plugin_interface {
        public:
            plugin_interface(plugin_interface_identifier identifier_, void *interface_class_) : identifier(identifier_), interface_class(interface_class_) {}

            const plugin_interface_identifier identifier;
            /*!
            @brief A pointer to the interface class or struct that the plugin exposes
            */
            void *const interface_class;
            ///List of Modules that use this Interface
            std::vector<r_string> modules_using_interface;
        };

        /*!
        @brief A client entry. Stores, name handles, function pointers, etc.
        */
        class entry {
        public:
            entry() noexcept : name(""), handle(nullptr) {}
            entry(const std::string &name_, DLL_HANDLE handle_, cert::signing::security_class security_class_) : name(name_), handle(handle_), security_class(security_class_) {}
            /*!
            @brief The name of the module
            */
            std::string name;

            /*!
            @brief The path of the loaded module
            */
        #ifdef __linux
            std::string
        #else
            std::wstring
        #endif
            path;

            /*!
            @brief A intercept::module::functions struct containing pointers to
            plugin exported functions.
            */
            functions_list functions {};

            /*!
            @brief A intercept::module::eventhandlers struct containing pointers to
            plugin exported event handler functions.
            */
            eventhandlers_list eventhandlers;

            /*!
            @brief A list of exported functions called by the signal ability.
            */
            std::unordered_map<std::string, on_signal_func> signal_funcs;

            /*!
            @brief A handle to the plugin dynamic library.
            */
            DLL_HANDLE handle;

            /*!
            @brief A list of names of exported Plugin Interfaces.
            @note Used to keep track of exported Interfaces so we can remove them and notify other plugins about the removal then the plugin unloads.
            @remark Uses r_string as string container because that can easily be passed over the dll boundary.
            */
            std::vector<plugin_interface_identifier> exported_interfaces;
            
            /// @todo doc
            cert::signing::security_class security_class;
        };
    }  // namespace module

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
        bool load(const std::string &path_, std::optional<std::string> certPath);

        void reload_all();

        /*!
        @brief Unloads a client plugin.

        Unloads and removes a client plugin.
        */
        bool unload(std::string path_); //the string copy is intentional

        /*!
        @brief Returns a list of all loaded modules to SQF.
        */
        bool list(const arguments &args_, std::string &result);
        //!@}


        /// @ingroup plugin_interface
        register_plugin_interface_result register_plugin_interface(r_string module_name_, std::string_view name_, uint32_t api_version_, void *interface_class_);
        /// @ingroup plugin_interface
        std::pair<r_string, auto_array<uint32_t>> list_plugin_interfaces(std::string_view name_);
        //

        /**
         * @brief Searches for a Plugin Interface
         * @param name_ Name of the Interface you are searching for
         * @param api_version_ API version of the Interface you are searching for
         * @return pointer to the interface if it was found
         * @ingroup plugin_interface
         */
        std::optional<void*> request_plugin_interface(r_string module_name_, std::string_view name_, uint32_t api_version_);

        /*!
        @brief Returns the map of all loaded modules.
        */
        std::unordered_map<std::string, module::entry> &modules();

        /*!
        @brief The struct that contains the functions exported to client plugins.
        */
        client_functions functions;

        /*!
        @brief A list of exported Plugin Interfaces.
        @remark Uses r_string as string container because that can easily be passed over the dll boundary.
        */
        std::map<module::plugin_interface_identifier, module::plugin_interface> exported_interfaces;

        bool do_reload = false;

        bool ignore_cert_fail = false;

        cert::signing::security_class get_module_security_class(uintptr_t mod_base) {
            auto found = _module_security_classes.find(mod_base);
            if (found != _module_security_classes.end())
                return found->second;
            return cert::signing::security_class::not_signed;
        }


    protected:
        /*!
        @brief The map of all loaded modules.
        */
        std::unordered_map<std::string, module::entry> _modules;

        /// @brief a map of module base adresses to their security class
        std::map<uintptr_t, cert::signing::security_class> _module_security_classes;

        search::plugin_searcher _searcher;
        cert::signing _signTool;
    };

}  // namespace intercept
