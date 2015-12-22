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
    class invoker_lock;
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
        rv_game_value invoke_raw(nular_function function_);
        rv_game_value invoke_raw(std::string function_name_);
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
        rv_game_value invoke_raw(unary_function function_, const game_value * right_);
        rv_game_value invoke_raw(std::string function_name_, const game_value *right_);
        rv_game_value invoke_raw(std::string function_name_, const game_value *right_, std::string right_type_);
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
        rv_game_value invoke_raw(binary_function function_, const game_value * left_, const game_value * right_);
        rv_game_value invoke_raw(std::string function_name_, const game_value *left_, const game_value *right_);
        rv_game_value invoke_raw(std::string function_name_, const game_value *left_, std::string left_type_, const game_value *right_, std::string right_type_);
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
        uintptr_t get_type(const game_value *value_) const;

        /*!
        @brief Returns the string representation of the data type. IE: "ARRAY",
        "STRING", "SCALAR", etc.
        */
        const std::string get_type_str(const game_value *value_) const;
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
        bool release_value(game_value * value_, bool immediate_ = false);

        /*!
        @brief Actually resizes the collection array to 0 and back to its normal
        size of 100.

        This function is separate from the release_value function for organizational
        reasons. It invokes an atomic lock that ensures that the array is resized
        to 0 and back to its normal size in one step and that no other variables
        might accidently race and be added to a 0 size array.
        */
        void invoke_delete();

        /*!
        @brief Collects a string and adds it to a queue that waits for its internal
        ref counter to reach 1, at which point it can be safely released.

        Strings allocated by Intercept are allocated in the Intercept host memory
        because the engine may or may not use them right away. In some cases the
        string may be held in some sort of execution logic for a significant time.
        Since these strings are normal internal strings, the engine will adjust
        their ref counter to account for this, and we need to monitor the ref counter
        to make sure that we can safely release it.

        @param str_ A pointer to the string to release.
        */
        void collect_string(rv_string *str_);
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
        bool do_invoke_period(const arguments & args_, std::string & result_);

        /*!
        @brief Consume an event from the RV Engine and dispatches it.
        */
        bool rv_event(const arguments & args_, std::string & result_);
        
        /*!
        This is a general purpose function to test the invoker. It is not meant
        for public use and is only there to serve as an easy test bed for development.
        */
        bool invoker_demo(const arguments & args_, std::string & result_);
        //!@}

        /*!
        @brief A map of vtable ptrs to string stypes.
        */
        std::unordered_map<uintptr_t, std::string> type_map;

        /*!
        @brief A map of string type names to their corresponding vtable ptrs.
        */
        std::unordered_map<std::string, std::pair<uintptr_t, uintptr_t>> type_structures;

        friend class invoker_lock;
    protected:
        /*!
        @brief Thread for the string collector.
        */
        std::thread _collection_thread;

        /*!
        @brief Monitors collected strings for deletion.
        
        This function runs in its own thread, and contains a loop to monitor
        the ref count of freed strings, freeing the memory of them when their ref
        counter allows for deletion.
        */
        void _string_collector();

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
        
        /*!
        @brief A list of strings to monitor for deletion, used by the string collector.
        */
        std::list<rv_string *> _string_collection;

        /*!@{
        @brief Various mutexes and `std::` locking devices used for concurrency
        and RV Engine access.
        */
        std::mutex _invoke_mutex;
        std::mutex _state_mutex;
        std::mutex _delete_mutex;
        std::mutex _string_collection_mutex;
        std::condition_variable _invoke_condition;
        //!@}

        /*!
        @brief A collection of demo threads, used for testing locking/concurrency.
        */
        std::vector<std::thread> _demo_threads;

        bool _patched;
        bool _attached;
    };

    class invoker_lock {
    public:
        invoker_lock(invoker *instance_, bool all_ = false);
        invoker_lock(const invoker &) = delete;
        invoker_lock(invoker &&) = delete;
        invoker_lock & operator=(const invoker_lock &) = delete;
        invoker_lock & operator=(invoker_lock &&) = delete;
        ~invoker_lock();
    protected:
        invoker *_instance;
        bool _all;
    };
}