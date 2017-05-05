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
        static game_value invoke_raw_nolock(const nular_function function_);
        game_value invoke_raw(const std::string &function_name_) const;
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
        static game_value invoke_raw_nolock(const unary_function function_, const game_value &right_);
        game_value invoke_raw(const std::string &function_name_, const game_value &right_) const;
        game_value invoke_raw(const std::string &function_name_, const game_value &right_, const std::string &right_type_) const;
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
        static game_value invoke_raw_nolock(const binary_function function_, const game_value &left_, const game_value &right_);
        game_value invoke_raw(const std::string &function_name_, const game_value &left_, const game_value &right_) const;
        game_value invoke_raw(const std::string &function_name_, const game_value &left_, const std::string &left_type_, const game_value &right_, const std::string &right_type_) const;
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
        const std::string& get_type_str(const game_value &value_) const;
        //!@}

        /*!
        @name Memory Functions
        */
        //!@{
        /*!
        @brief Releases a value that was obtained from the RV Engine.

        This function releases the data of a value obtained from inside the RV
        Engine. Data obtained in the RV Engine must be released in the RV Engine
        and as such we need to have a method of doing this.

        The way that Intercept handles this is by defining a global array in SQF
        and populating tha array with values that need to be freed. When the array
        reaches a certain size, it is resized to 0 and this invokes SQF to release
        the variable memory (depending on the internal ref-count, which can be
        manipulated both in Intercept and inside the RV Engine itself via SQF.

        @param value_ A pointer to the value that is to be freed.
        @param immediate_ If this value should be released immediately. If set 
        to true, this will also free any other variables waiting to be freed.

        @return `true` if the value was added to the collection array, `false`
        if the value was not released (due to it not being properly owned by the
        RV Engine).
        */
        bool release_value(game_value &value_, bool immediate_ = true);

        /*!
        @brief Actually resizes the collection array to 0 and back to its normal
        size of 100.

        This function is separate from the release_value function for organizational
        reasons. It invokes an atomic lock that ensures that the array is resized
        to 0 and back to its normal size in one step and that no other variables
        might accidently race and be added to a 0 size array.
        */
        void invoke_delete();
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
        bool rv_event(const std::string& event_name_, game_value& params_);
        
        /*!
        @brief Get signal from sqf code dispatch it.
        */
        bool signal(const arguments & args_, std::string & result_);
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
        bool add_eventhandler(const std::string & name_, std::function<void(const std::string &, game_value &)> func_);

        /*!
        @brief A map of vtable ptrs to string stypes.
        */
        std::unordered_map<uintptr_t, std::string> type_map;

        /*!
        @brief A map of string type names to their corresponding vtable ptrs.
        */
        std::unordered_map<std::string, std::pair<uintptr_t, uintptr_t>> type_structures;

        void lock();

        void unlock();

        static game_data_string_pool<> string_pool;
        static uintptr_t sqf_game_state;
        static char *sqf_this;

        static bool invoker_accessible;
        static bool invoker_accessible_all;
    protected:



        std::atomic<uint32_t> _thread_count;

        /*!
        @brief The interceptEvent SQF Function that's used to get events with arguments
        */
        static game_value _intercept_event(game_value left_arg_, game_value right_arg_);
        registered_sqf_function _intercept_event_function;
        static game_value _intercept_do_invoke_period(game_value right_arg_);
        registered_sqf_function _intercept_do_invoke_period_function;

        /*!
        @brief The hook function for getting type information. Hooked via intercept::invoker_begin_register.
        */
        static int __cdecl _register_hook(char *sqf_this_, uintptr_t sqf_game_state_, uintptr_t right_arg_);

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
        game_value _mission_namespace;

        /*!
        @brief The delete array for collecting values.
        */
        game_value _delete_array_ptr;

        /*!
        @brief The scalar game_value for resizing the delete array to 0.
        */
        game_value _delete_size_zero;

        /*!
        @brief The scalar game_value for resizing the delete array back to its 
        max size.
        */
        game_value _delete_size_max;

        game_value _eh_params;
        game_value _signal_params;

        game_value _eh_params_name;

        /*!
        @brief The index counter for the delete array.
        */
        uint32_t _delete_index;

        /*!
        @brief This is actually null. Really it should just be exchanged with a
        null literal where it is used.

        This is a pointless `__thiscall` convention `this` pointer. It is never
        used by any SQF function because they are not member functions.
        */
        char *_sqf_this;

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
        std::mutex _delete_mutex;
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
        std::unordered_map < std::string, std::function<void(const std::string &, game_value &)> > _eventhandlers;

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