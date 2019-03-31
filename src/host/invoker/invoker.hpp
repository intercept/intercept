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
#include "shared/types.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>
#include "eventhandlers.hpp"
#include "sqf_functions.hpp"


using namespace intercept::types;


namespace intercept {
    class _invoker_unlock;
    /*!
    @brief Handles invoking SQF functions. Used as an interface between clients, 
    RV Engine, and the intercept::loader.

    The invoker class handles all of the bread and butter tasks of Intercept, it 
    is used as a bridge between client plugins, the RV Engine, and the data gathered 
    by the loader class.

    This includes:
    - Invoking specific SQF functions.
    - Releasing Memory
    - Defining and handling SQF internal types.
    - Testing the validity of the Intercept system at boot/mission start.
    */
    class invoker
        : public singleton<invoker>
    {
    public:
        invoker();
        ~invoker();

        /*!
        @brief Attaches intercept::controller commands from this class to the main
        controller.
        */
        void attach_controller();
        
        /*!
        @name Invoke Functions
        */
        //!@{
        /*!@{
        @brief Nular invoke functions.

        Invoke a nular SQF function, either by function pointer or by name.

        @return Returns a raw intercept::types::rv_game_value struct. This is often
        passed into a intercept::types::game_value to be unwound into the appropriate
        return type, or passed to a complex argument constructor such as `object`
        or `group`, etc.
        */
        static game_value invoke_raw_nolock(const nular_function function_) noexcept;
        game_value invoke_raw(std::string_view function_name_) const;
        //!@}

        /*!@{
        @brief Unary invoke functions.

        Invoke a unary SQF function, either by function pointer or by name and 
        arguement signatures.

        @return Returns a raw intercept::types::rv_game_value struct. This is often
        passed into a intercept::types::game_value to be unwound into the appropriate
        return type, or passed to a complex argument constructor such as `object`
        or `group`, etc.
        */
        static game_value invoke_raw_nolock(const unary_function function_, const game_value &right_) noexcept;
        game_value invoke_raw(std::string_view function_name_, const game_value &right_) const;
        game_value invoke_raw(std::string_view function_name_, const game_value &right_, const std::string &right_type_) const;
        //!@}

        /*!@{
        @brief Binary invoke functions.

        Invoke a binary SQF function, either by function pointer or by name and
        arguement signatures.

        @return Returns a raw intercept::types::rv_game_value struct. This is often
        passed into a intercept::types::game_value to be unwound into the appropriate
        return type, or passed to a complex argument constructor such as `object`
        or `group`, etc.
        */
        static game_value invoke_raw_nolock(const binary_function function_, const game_value &left_, const game_value &right_) noexcept;
        game_value invoke_raw(std::string_view function_name_, const game_value &left_, const game_value &right_) const;
        game_value invoke_raw(std::string_view function_name_, const game_value &left_, const std::string &left_type_, const game_value &right_, const std::string &right_type_) const;
        //!@}
        //!@}

        /*!
        @name Type Functions
        */
        //!@{
        /*!
        @brief Returns the numerical type id. This is the vtable ptr of the data
        type.
        */
        static uintptr_t get_type(const game_value &value_);

        /*!
        @brief Returns the string representation of the data type. IE: "ARRAY",
        "STRING", "SCALAR", etc.
        */
        std::string_view get_type_str(const game_value &value_) const;
        //!@}

        /*!
        @name Controller Functions
        */
        //!@{
        /*!
        @brief Hooks the SQF `str` function to derive type information at boot.
        */
        bool invoker_begin_register(const arguments & args_, std::string & result_);

        /*!
        @brief Defines what the next variable type will be from the hooked function.
        */
        bool invoker_register(const arguments & args_, std::string & result_);

        /*!
        @brief Unhooks the SQF `str` function.
        */
        bool invoker_end_register(const arguments & args_, std::string & result_);

        /*!
        @brief Initializes the Invoker at mission start. This assignes the delete
        storage array, and sets the zero/max size arguments.
        */
        bool init_invoker(const arguments & args_, std::string & result_);

        /*!
        @brief Tests the invoker. This function will attempt to get the Steam profile
        name of the current game user and compare the value with the same call
        made in normal SQF.
        */
        bool test_invoker(const arguments & args_, std::string & result_);

        /*!
        @brief Opens the RV Engine up for a period of time to allow client threads
        access.

        This is easily the most important function in the invoker as it is the 
        function that dictates when other threads can access the game engine.

        This function is invoked from a per-frame handler in SQF, each frame this
        controller function is called and the Invoker will unlock all client threads
        for 3ms of access to the RV Engine and then it will close. Before it closes
        though it invokes the clients `on_frame()` function, which is a blocking
        function call that each client plugin can define for guaranteed per-frame
        execution.
        */
        bool do_invoke_period();

        /*!
        @brief Consume an event from the RV Engine and dispatches it.
        */
        bool rv_event(const std::string& event_name_, game_value_parameter params_);
        

        static game_value _intercept_signal(game_value_parameter left_arg_, game_value_parameter right_arg_);
        /*!
        @brief Get signal from sqf code dispatch it.
        */
        bool signal(const std::string& extension_name, const std::string& signal_name, game_value_parameter args);
        //!@}

        /*!
        @brief Adds a bound event handler-handler to the map of event handler binds 
        for invoking a RV event handler in the client plugins.

        @param name_ The name of the event being raised from SQF (these need to
        be bound in SQF to call into the `rv_event` `callExtension` event in this
        class).
        @param func_ The function bind.

        @return Returns `true` if it was bound, `false` if it was not.
        */
        bool add_eventhandler(std::string_view name_, std::function<void(game_value_parameter)> func_);

        /*!
        @brief A map of vtable ptrs to string stypes.
        */
        std::unordered_map<uintptr_t, std::string_view> type_map;

        /*!
        @brief A map of string type names to their corresponding vtable ptrs.
        */
        std::unordered_map<std::string_view, std::pair<uintptr_t, uintptr_t>> type_structures;

        void lock();

        void unlock();

        //static game_data_string_pool<> string_pool;
        static game_state* sqf_game_state;

        static bool invoker_accessible;
        static bool invoker_accessible_all;

        //#TODO documentation and move to seperate file
        auto_array<r_string> files_in_pbo_banks;
        void init_file_bank_list();
    protected:



        std::atomic<uint32_t> _thread_count;
        std::atomic<uint32_t> _thread_waiting_for_lock_count;

        /*!
        @brief The interceptEvent SQF Function that's used to get events with arguments
        */
        static game_value _intercept_event(game_value_parameter left_arg_, game_value_parameter right_arg_);
        registered_sqf_function _intercept_event_function;
        static game_value _intercept_do_invoke_period();
        registered_sqf_function _intercept_do_invoke_period_function;
        registered_sqf_function _intercept_signal_function;

        /*!
        @brief The hook function for getting type information. Hooked via intercept::invoker_begin_register.
        */
        static game_value _intercept_registerTypes(const game_value& left_arg_);
        registered_sqf_function _intercept_registerTypes_function;
        /*!
        @brief The trampoline for `str` that is used as the type registration function.
        */
        static unary_function _register_hook_trampoline;

        /*!
        @brief The current type of variable being passed to `str` for type analysis.
        */
        std::string _registration_type;

        /*!
        @brief The mission namespace, used for getting variables.
        */
        //game_value _mission_namespace;

        //game_value _eh_params;
        //game_value _signal_params;

        //game_value _eh_params_name;

        /*!
        @brief The address of the game state object.

        This address needs to be passed to every SQF function for proper execution.
        */
        uintptr_t _sqf_game_state;

        /*!@{
        @brief Various mutexes and `std::` locking devices used for concurrency
        and RV Engine access.
        */
        std::recursive_mutex _invoke_mutex;
        std::mutex _state_mutex;
        std::condition_variable _invoke_condition;
        //!@}

        /*!
        @brief A collection of demo threads, used for testing locking/concurrency.
        */
        std::vector<std::thread> _demo_threads;

        /*!
        @brief A collection of bound functions for processing event handlers in
        the client plugins.
        */
        std::unordered_map <std::string, std::function<void(game_value_parameter)> > _eventhandlers;

        bool _patched;
        bool _attached;
        bool _mission_init;

        std::queue<game_data *> _to_delete;

        binary_function _get_variable_func;

        /*!
        @brief A RAII style mutex handler for access to the RV Engine

        Provides a safe way to unlock other threads or invokes to the RV engine. 
        Will unlock an invoker passed in, by default only allowing access to invokes
        from the invokers own thread. If `all_threads_` is set to true in the constructor
        it will unlock all threads attempting to invoke. It is also possible to
        delay unlocking, so that the unlock can happen based on a condition but
        still retain the safety of being bound to the scope in which it was declared.

        Instances of this class are NOT moveable or copyable.
        */
        class _invoker_unlock {
        public:
            _invoker_unlock(invoker *instance_, bool all_threads_ = false, bool delayed_ = false);
            _invoker_unlock(const _invoker_unlock &) = delete;
            _invoker_unlock(_invoker_unlock &&) = delete;
            _invoker_unlock & operator=(const _invoker_unlock &) = delete;
            _invoker_unlock & operator=(_invoker_unlock &&) = delete;
            ~_invoker_unlock();
            void unlock();
        protected:
            bool _unlocked;
            invoker *_instance;
            bool _all;
        };
    };


}
