#include "shared/types.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"
#include <assert.h>
#include <future>
#include <sstream> //Debugging

#if INTERCEPT_HOST_DLL
#include "loader.hpp"
#define GET_ENGINE_ALLOCATOR intercept::loader::get().get_allocator();
#else
#define GET_ENGINE_ALLOCATOR client::host::functions.get_engine_allocator()
#endif

namespace intercept {
    namespace __internal {
        /*
        class mem_leak_watcher {
        public:
            mem_leak_watcher() {
                static auto fut = std::async(std::launch::async, [&]() {
                    while (game_data_number::pool_alloc_base == nullptr) std::this_thread::sleep_for(std::chrono::seconds(5));
                    while (true) {
                        _mut.lock();
                        auto it = _allocs.begin();
                        auto _now = std::chrono::system_clock::now() - std::chrono::seconds(5);
                        while (it != _allocs.end() && it->second > _now) {
                            static auto numberdef = game_data_number::type_def;
                            if (*reinterpret_cast<uintptr_t*>(static_cast<refcount*>(it->first)) != numberdef) {//Was already deleted
                                _allocs.erase(it);
                                it = _allocs.begin();
                                if (it == _allocs.end()) break;
                            }
                            ++it;
                        };


                        if (it != _allocs.end()) {
                            std::stringstream stream;
                            stream << "memLeak " << "SCALAR " << std::hex << it->first << "\n";
                            OutputDebugStringA(stream.str().c_str());
                            _allocs.erase(it);
                        }
                        _mut.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                        std::stringstream stream;
                        stream << "ScalarPool " << game_data_number::pool_alloc_base->allocated_count << "\n";
                        OutputDebugStringA(stream.str().c_str());

                    }
                });
            }
            void add_alloc(game_data_number* _al) {
                _mut.lock();
                _allocs.insert({ _al,std::chrono::system_clock::now() });
                _mut.unlock();
            }

            std::map<game_data_number*, std::chrono::system_clock::time_point> _allocs;
            std::mutex _mut;
        };
        */

    }


    namespace types {
        uintptr_t game_data_string::type_def;
        uintptr_t game_data_string::data_type_def;
        rv_pool_allocator* game_data_string::pool_alloc_base;

        uintptr_t game_data_number::type_def;
        uintptr_t game_data_number::data_type_def;
        rv_pool_allocator* game_data_number::pool_alloc_base;

        uintptr_t game_data_array::type_def;
        uintptr_t game_data_array::data_type_def;
        rv_pool_allocator* game_data_array::pool_alloc_base;

        uintptr_t game_data_bool::type_def;
        uintptr_t game_data_bool::data_type_def;
        rv_pool_allocator* game_data_bool::pool_alloc_base;

        uintptr_t game_data_code::type_def;
        uintptr_t game_data_code::data_type_def;

        uintptr_t game_data_group::type_def;
        uintptr_t game_data_group::data_type_def;

        uintptr_t game_data_config::type_def;
        uintptr_t game_data_config::data_type_def;

        uintptr_t game_data_control::type_def;
        uintptr_t game_data_control::data_type_def;

        uintptr_t game_data_display::type_def;
        uintptr_t game_data_display::data_type_def;

        uintptr_t game_data_location::type_def;
        uintptr_t game_data_location::data_type_def;

        uintptr_t game_data_script::type_def;
        uintptr_t game_data_script::data_type_def;

        uintptr_t game_data_side::type_def;
        uintptr_t game_data_side::data_type_def;

        uintptr_t game_data_rv_text::type_def;
        uintptr_t game_data_rv_text::data_type_def;

        uintptr_t game_data_team_member::type_def;
        uintptr_t game_data_team_member::data_type_def;

        uintptr_t game_data_rv_namespace::type_def;
        uintptr_t game_data_rv_namespace::data_type_def;

        uintptr_t game_data_nothing::type_def;
        uintptr_t game_data_nothing::data_type_def;

        uintptr_t game_data_object::type_def;
        uintptr_t game_data_object::data_type_def;



        uintptr_t game_value::__vptr_def;
        uintptr_t sqf_script_type::type_def;


        value_types sqf_script_type::type() const {
            if (single_type != nullptr) {
                return{ static_cast<std::string>(single_type->_name) };
            }

            return{
                static_cast<std::string>(compound_type->types->first->_name),
                static_cast<std::string>(compound_type->types->second->_name)
            };
        }

        std::string sqf_script_type::type_str() const {
            if (single_type != nullptr) {
                return static_cast<std::string>(single_type->_name);
            }

            return
                static_cast<std::string>(compound_type->types->first->_name) + "_" +
                static_cast<std::string>(compound_type->types->second->_name);

        }

    #pragma region GameData Types
        game_data_number::game_data_number() noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = 0.0f;
        }

        game_data_number::game_data_number(float val_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = val_;
        }

        game_data_number::game_data_number(const game_data_number & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = copy_.number;
        }

        game_data_number::game_data_number(game_data_number && move_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            number = move_.number;
        }

        game_data_number & game_data_number::operator=(const game_data_number & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = copy_.number;
            return *this;
        }

        game_data_number & game_data_number::operator=(game_data_number && move_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            number = move_.number;
            return *this;
        }

        inline void * game_data_number::operator new(std::size_t) {
        #ifdef __linux__
            return pool_alloc_base->allocate(sizeof(game_data_number));
        #else
            return pool_alloc_base->allocate(1);
        #endif
        }

        inline void game_data_number::operator delete(void * ptr_, std::size_t) {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_data_bool::game_data_bool() {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = false;
        }

        game_data_bool::game_data_bool(bool val_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = val_;
        }

        game_data_bool::game_data_bool(const game_data_bool & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = copy_.val;
        }

        game_data_bool::game_data_bool(game_data_bool && move_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            val = move_.val;
        }

        game_data_bool & game_data_bool::operator=(const game_data_bool & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = copy_.val;
            return *this;
        }

        game_data_bool & game_data_bool::operator=(game_data_bool && move_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            val = move_.val;
            return *this;
        }

        inline void * game_data_bool::operator new(std::size_t) {
        #ifdef __linux__
            return pool_alloc_base->allocate(sizeof(game_data_bool));
        #else
            return pool_alloc_base->allocate(1);
        #endif
        }

        inline void game_data_bool::operator delete(void * ptr_, std::size_t) {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_data_string::game_data_string() noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
        }

        game_data_string::game_data_string(const std::string &str_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            raw_string = r_string(str_);
        }
        game_data_string::game_data_string(const r_string &str_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            raw_string = str_;
        }

        game_data_string::game_data_string(const game_data_string & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            raw_string = copy_.raw_string;
        }

        game_data_string::game_data_string(game_data_string && move_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            raw_string = move_.raw_string;
            move_.raw_string.clear();
        }

        game_data_string & game_data_string::operator=(const game_data_string & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            raw_string = copy_.raw_string;
            return *this;
        }

        game_data_string & game_data_string::operator=(game_data_string && move_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            raw_string = move_.raw_string;
            move_.raw_string.clear();
            return *this;
        }

        game_data_string::~game_data_string() {}

        void * game_data_string::operator new(std::size_t) {
        #ifdef __linux__
            return pool_alloc_base->allocate(sizeof(game_data_string));
        #else
            return pool_alloc_base->allocate(1);
        #endif
        }

        void game_data_string::operator delete(void * ptr_, std::size_t) {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_data_array::game_data_array() {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
        }

        game_data_array::game_data_array(size_t size_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            data.resize(size_);
        }

        game_data_array::game_data_array(const std::initializer_list<game_value> &init_) : data(init_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
        }

        game_data_array::game_data_array(auto_array<game_value> &&init_) : data(std::move(init_)) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
        }

        game_data_array::game_data_array(const std::vector<game_value> &init_) : data(init_.begin(), init_.end()) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
        }

        game_data_array::game_data_array(const game_data_array & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            data = copy_.data;
        }

        game_data_array::game_data_array(game_data_array && move_) noexcept {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            data = std::move(move_.data);
        }

        game_data_array & game_data_array::operator = (const game_data_array &copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            data = copy_.data;
            return *this;
        }

        game_data_array & game_data_array::operator = (game_data_array &&move_) noexcept {
            if (this == &move_)
                return *this;
            data = std::move(move_.data);
            return *this;
        }

        game_data_array::~game_data_array() {}

        void * game_data_array::operator new(std::size_t) {
        #ifdef __linux__
            return pool_alloc_base->allocate(sizeof(game_data_array));
        #else
            return pool_alloc_base->allocate(1);
        #endif
        }

        void game_data_array::operator delete(void * ptr_, std::size_t) {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_data* game_data::createFromSerialized(param_archive& ar) {
            bool isNil = false;
            if (ar.serialize(r_string("nil"sv), isNil, 1, false) != serialization_return::no_error) {
                return nullptr;
            }

            sqf_script_type _type;
            if (ar.serialize(r_string("type"sv), _type, 1) != serialization_return::no_error) return nullptr;

            if (isNil) {
                //#TODO create GameDataNil or GameDataNothing
                return nullptr;
            }

            auto gs = reinterpret_cast<intercept::__internal::game_state *>(ar._parameters.front());
            return gs->create_gd_from_type(_type, &ar);
        }

        static std::map<std::string, types::GameDataType> additionalTypes;
        types::GameDataType __internal::game_datatype_from_string(const r_string& name) {
            //I know this is ugly. Feel free to make it better
            if (name == "SCALAR"sv) return types::GameDataType::SCALAR;
            if (name == "BOOL"sv) return types::GameDataType::BOOL;
            if (name == "ARRAY"sv) return types::GameDataType::ARRAY;
            if (name == "STRING"sv) return types::GameDataType::STRING;
            if (name == "NOTHING"sv) return types::GameDataType::NOTHING;
            if (name == "ANY"sv) return types::GameDataType::ANY;
            if (name == "NAMESPACE"sv) return types::GameDataType::NAMESPACE;
            if (name == "NaN"sv) return types::GameDataType::NaN;
            if (name == "CODE"sv) return types::GameDataType::CODE;
            if (name == "OBJECT"sv) return types::GameDataType::OBJECT;
            if (name == "SIDE"sv) return types::GameDataType::SIDE;
            if (name == "GROUP"sv) return types::GameDataType::GROUP;
            if (name == "TEXT"sv) return types::GameDataType::TEXT;
            if (name == "SCRIPT"sv) return types::GameDataType::SCRIPT;
            if (name == "TARGET"sv) return types::GameDataType::TARGET;
            if (name == "CONFIG"sv) return types::GameDataType::CONFIG;
            if (name == "DISPLAY"sv) return types::GameDataType::DISPLAY;
            if (name == "CONTROL"sv) return types::GameDataType::CONTROL;
            if (name == "NetObject"sv) return types::GameDataType::NetObject;
            if (name == "SUBGROUP"sv) return types::GameDataType::SUBGROUP;
            if (name == "TEAM_MEMBER"sv) return types::GameDataType::TEAM_MEMBER;
            if (name == "TASK"sv) return types::GameDataType::TASK;
            if (name == "DIARY_RECORD"sv) return types::GameDataType::DIARY_RECORD;
            if (name == "LOCATION"sv) return types::GameDataType::LOCATION;
            auto found = additionalTypes.find(static_cast<std::string>(name));
            if (found != additionalTypes.end())
                return found->second;
            return types::GameDataType::end;
        }

        std::string __internal::to_string(GameDataType type) {
            switch (type) {
                case GameDataType::SCALAR: return "SCALAR";
                case GameDataType::BOOL: return "BOOL";
                case GameDataType::ARRAY: return "ARRAY";
                case GameDataType::STRING: return "STRING";
                case GameDataType::NOTHING: return "NOTHING";
                case GameDataType::ANY: return "ANY";
                case GameDataType::NAMESPACE: return "NAMESPACE";
                case GameDataType::NaN: return "NaN";
                case GameDataType::CODE: return "CODE";
                case GameDataType::OBJECT: return "OBJECT";
                case GameDataType::SIDE: return "SIDE";
                case GameDataType::GROUP: return "GROUP";
                case GameDataType::TEXT: return "TEXT";
                case GameDataType::SCRIPT: return "SCRIPT";
                case GameDataType::TARGET: return "TARGET";
                case GameDataType::CONFIG: return "CONFIG";
                case GameDataType::DISPLAY: return "DISPLAY";
                case GameDataType::CONTROL: return "CONTROL";
                case GameDataType::SUBGROUP:  return "SUBGROUP";
                case GameDataType::TEAM_MEMBER:return "TEAM_MEMBER";
                case GameDataType::TASK: return "TASK";
                case GameDataType::DIARY_RECORD: return "DIARY_RECORD";
                case GameDataType::LOCATION: return "LOCATION";
                default:;
            }
            for (auto& it : additionalTypes) {
                if (it.second == type)
                    return it.first;
            }
            return "";
        }

        void __internal::add_game_datatype(const r_string name_, const GameDataType type_) {
            additionalTypes[static_cast<std::string>(name_)] = type_;
        }

    #pragma endregion

    #pragma region GameValue

        game_value::game_value(float val_) {
            set_vtable(__vptr_def);
            data = new game_data_number(val_);
        }

        game_value::game_value(int val_) : game_value(static_cast<float>(val_)) {}

        game_value::game_value(size_t val_) : game_value(static_cast<float>(val_)) {}

        game_value::game_value(bool val_) {
            set_vtable(__vptr_def);
            data = new game_data_bool(val_);
        }

        game_value::game_value(const std::string &val_) {
            set_vtable(__vptr_def);
            data = new game_data_string(val_);
        }

        game_value::game_value(const r_string &val_) {
            set_vtable(__vptr_def);
            data = new game_data_string(val_);
        }

        game_value::game_value(std::string_view val_) {
            set_vtable(__vptr_def);
            data = new game_data_string(val_);
        }

        game_value::game_value(const std::vector<game_value> &list_) {
            set_vtable(__vptr_def);
            data = new game_data_array(list_);
        }

        game_value::game_value(const std::initializer_list<game_value> &list_) {
            set_vtable(__vptr_def);
            data = new game_data_array(list_);
        }

        game_value::game_value(auto_array<game_value> &&array_) {
            set_vtable(__vptr_def);
            data = new game_data_array(std::move(array_));
        }

        game_value::game_value(const vector3 & vec_) {
            set_vtable(__vptr_def);
            data = new game_data_array({ vec_.x, vec_.y, vec_.z });
        }

        game_value::game_value(const vector2 & vec_) {
            set_vtable(__vptr_def);
            data = new game_data_array({ vec_.x, vec_.y });
        }
        game_value::game_value(const internal_object &internal_) {
            set_vtable(__vptr_def); //object class has bugged vtable :u
            data = internal_.data;
        }

        game_value & game_value::operator = (const game_value &copy_) {
            copy(copy_);
            return *this;
        }
        game_value & game_value::operator = (game_value &&move_) noexcept {
            if (this == &move_)
                return *this;
            set_vtable(__vptr_def);
            data = move_.data;
            move_.data = nullptr;
            return *this;
        }

        game_value & game_value::operator=(const float val_) {
            data = new game_data_number(val_);
            return *this;
        }

        game_value & game_value::operator=(bool val_) {
            data = new game_data_bool(val_);
            return *this;
        }

        game_value & game_value::operator=(const std::string &val_) {
            data = new game_data_string(val_);
            return *this;
        }

        game_value & game_value::operator=(const r_string &val_) {
            data = new game_data_string(val_);
            return *this;
        }

        game_value & game_value::operator=(std::string_view val_) {
            data = new game_data_string(val_);
            return *this;
        }

        game_value & game_value::operator=(const std::vector<game_value> &list_) {
            data = new game_data_array(list_);
            return *this;
        }

        game_value & game_value::operator=(const vector3 &vec_) {
            data = new game_data_array({ vec_.x, vec_.y, vec_.z });
            return *this;
        }

        game_value & game_value::operator=(const vector2 &vec_) {
            data = new game_data_array({ vec_.x, vec_.y });
            return *this;
        }

        game_value & game_value::operator=(const internal_object &internal_) {
            data = internal_.data;
            set_vtable(__vptr_def);
            return *this;
        }

        game_value::operator int() const {
            if (data)
                return static_cast<int>(data->get_as_number());
            return 0;
        }

        game_value::operator float() const {
            if (data)
                return data->get_as_number();
            return 0.f;
        }

        game_value::operator bool() const {
            if (data)
                return data->get_as_bool();
            return false;
        }

        game_value::operator vector3() const {
            if (!data) return {};
            auto& array = data->get_as_array();
            if (array.count() == 3)
                return vector3{ array[0], array[1], array[2] };
            return vector3();
        }

        game_value::operator vector2() const {
            if (!data) return {};
            auto& array = data->get_as_array();
            if (array.count() == 2)
                return vector2{ array[0], array[1] };
            return {};
        }

        game_value::operator std::string() const {
            if (data) {
                const auto type = data->get_vtable();
                if (type == game_data_code::type_def || type == game_data_string::type_def)
                    return static_cast<std::string>(data->get_as_string());
                return static_cast<std::string>(data->to_string());
            }
                
            return {};
        }

        game_value::operator r_string () const {
            if (data) {
                const auto type = data->get_vtable();
                if (type == game_data_code::type_def || type == game_data_string::type_def)
                    return data->get_as_string();
                return data->to_string();
            }

            return {};
        }

        auto_array<game_value>& game_value::to_array() const {
            if (data) {
                if (data->get_vtable() != game_data_array::type_def) throw game_value_conversion_error("Invalid conversion to array");
                return data->get_as_array();
            }
            static auto_array<game_value> dummy;//else we would return a temporary.
            dummy.clear(); //In case user modified it before
            return dummy;
        }

        game_value& game_value::operator [](size_t i_) const {
            if (data) {
                if (data->get_vtable() != game_data_array::type_def) throw game_value_conversion_error("Invalid array access");
                auto& array = data->get_as_array();
                if (array.count() >= i_)
                    return array[i_];
            }
            static game_value dummy;//else we would return a temporary.
            dummy.clear(); //In case user modified it before
            return dummy;
        }

        std::optional<game_value> game_value::get(size_t i_) const {
            if (data) {
                if (data->get_vtable() != game_data_array::type_def) return *this;
                auto& array = data->get_as_array();
                if (array.count() >= i_)
                    return array[i_];
            }
            return {};
        }

        uintptr_t game_value::type() const {
            if (data)
                return *reinterpret_cast<uintptr_t*>(data.get()); //#TODO use GetType virtual func instead
            return 0x0;
        }

        types::GameDataType game_value::type_enum() const {//#TODO make a static sorted table in the same order as enum. turns this search into a binary search
            if (!data) return GameDataType::NOTHING;
            const auto _type = data->get_vtable();
            if (_type == game_data_object::type_def)
                return GameDataType::OBJECT;
            if (_type == game_data_number::type_def)
                return GameDataType::SCALAR;
            if (_type == game_data_string::type_def)
                return GameDataType::STRING;
            if (_type == game_data_array::type_def)
                return GameDataType::ARRAY;
            if (_type == game_data_bool::type_def)
                return GameDataType::BOOL;
            if (_type == game_data_group::type_def)
                return GameDataType::GROUP;
            if (_type == game_data_config::type_def)
                return GameDataType::CONFIG;
            if (_type == game_data_control::type_def)
                return GameDataType::CONTROL;
            if (_type == game_data_display::type_def)
                return GameDataType::DISPLAY;
            if (_type == game_data_location::type_def)
                return GameDataType::LOCATION;
            if (_type == game_data_script::type_def)
                return GameDataType::SCRIPT;
            if (_type == game_data_side::type_def)
                return GameDataType::SIDE;
            if (_type == game_data_rv_text::type_def)
                return GameDataType::TEXT;
            if (_type == game_data_rv_namespace::type_def)
                return GameDataType::NAMESPACE;
            if (_type == game_data_code::type_def)
                return GameDataType::CODE;
            if (_type == game_data_nothing::type_def)
                return GameDataType::NOTHING;
            return GameDataType::ANY;
        }

        size_t game_value::size() const {
            if (!data) return 0;
            if (data->get_vtable() != game_data_array::type_def) return 0;
            return data->get_as_array().count();
        }

        bool game_value::is_nil() const {
            if (!data) return true;
            return data->is_nil();
        }

        bool game_value::is_null() const {
            if (!data) return true;
            if (data->is_nil()) return true;
            auto type = type_enum();
            switch (type) {

                case GameDataType::SCALAR:      //[[fallthrough]] //#TODO fix when MSVC get's their stuff together
                case GameDataType::BOOL:        //[[fallthrough]]
                case GameDataType::ARRAY:       //[[fallthrough]]
                case GameDataType::STRING:      //[[fallthrough]]
                case GameDataType::NOTHING:     //[[fallthrough]]
                case GameDataType::ANY:         //[[fallthrough]]
                case GameDataType::NAMESPACE:   //[[fallthrough]]
                case GameDataType::NaN:         //[[fallthrough]]
                case GameDataType::CODE:        //[[fallthrough]]
                case GameDataType::SIDE:        //[[fallthrough]]
                case GameDataType::TEXT:        //[[fallthrough]]
                case GameDataType::TARGET:      //[[fallthrough]]
                case GameDataType::NetObject:   //[[fallthrough]]
                case GameDataType::SUBGROUP:    //[[fallthrough]]
                case GameDataType::DIARY_RECORD:
                    return false;
                case GameDataType::OBJECT:      //[[fallthrough]] //SL
                case GameDataType::GROUP:       //[[fallthrough]] //LL
                case GameDataType::SCRIPT:      //[[fallthrough]] //LL
                case GameDataType::DISPLAY:     //[[fallthrough]] //LL
                case GameDataType::CONTROL:     //[[fallthrough]] //LL
                case GameDataType::TEAM_MEMBER: //[[fallthrough]] //SLP
                case GameDataType::TASK:        //[[fallthrough]] //LL
                case GameDataType::LOCATION://LL
                { 
                    const uintptr_t datax = reinterpret_cast<uintptr_t>(data.get());
                    const uintptr_t data_1 = datax + sizeof(uintptr_t) * 3;
                    const uintptr_t data_2 = *reinterpret_cast<uintptr_t *>(data_1);
                    if (data_2) {
                        const uintptr_t data_3 = data_2 + sizeof(uintptr_t);
                        const uintptr_t val = *reinterpret_cast<uintptr_t *>(data_3);
                        return !val;
                    }
                    return true;
                }
                case GameDataType::CONFIG: {
                    return !reinterpret_cast<game_data_config*>(data.get())->path.is_empty();//#TODO test
                }


                default: ;
            }
            

            return false; //Dunno that Type. Users fault.
        }

        bool game_value::operator==(const game_value& other) const {
            if (!data || !other.data) return false;
            if (data->type() != other.data->type()) return false;
            return data->equals(other.data);

        }
        bool game_value::operator!=(const game_value& other) const {
            if (!data || !other.data) return true;
            if (data->type() != other.data->type()) return true;
            return !data->equals(other.data);
        }

        size_t game_value::hash() const {
            if (!data) return 0;

            switch(type_enum()) {
                case GameDataType::SCALAR: return reinterpret_cast<game_data_number*>(data.get())->hash();
                case GameDataType::BOOL: return reinterpret_cast<game_data_bool*>(data.get())->hash();
                case GameDataType::ARRAY: return reinterpret_cast<game_data_array*>(data.get())->hash();
                case GameDataType::STRING: return reinterpret_cast<game_data_string*>(data.get())->hash();
                case GameDataType::NOTHING: return reinterpret_cast<game_data*>(data.get())->to_string().hash();
                case GameDataType::NAMESPACE: return reinterpret_cast<game_data_rv_namespace*>(data.get())->hash();
                case GameDataType::NaN: return reinterpret_cast<game_data*>(data.get())->to_string().hash();
                case GameDataType::CODE: return reinterpret_cast<game_data_code*>(data.get())->hash();
                case GameDataType::OBJECT: return reinterpret_cast<game_data_object*>(data.get())->hash();
                case GameDataType::SIDE: return reinterpret_cast<game_data_side*>(data.get())->hash();
                case GameDataType::GROUP: return reinterpret_cast<game_data_group*>(data.get())->hash();
                case GameDataType::TEXT: return reinterpret_cast<game_data_rv_text*>(data.get())->hash();
                case GameDataType::SCRIPT: return reinterpret_cast<game_data_script*>(data.get())->hash();
                case GameDataType::TARGET: return reinterpret_cast<game_data*>(data.get())->to_string().hash();
                case GameDataType::CONFIG: return reinterpret_cast<game_data_config*>(data.get())->hash();
                case GameDataType::DISPLAY: return reinterpret_cast<game_data_display*>(data.get())->hash();
                case GameDataType::CONTROL: return reinterpret_cast<game_data_control*>(data.get())->hash();
#if defined(_DEBUG) && defined(_MSC_VER)
                //If you encounter any of these give Dedmen a repro.
                case GameDataType::ANY: __debugbreak(); break;//ANY should never be seen as a value.
                case GameDataType::NetObject: __debugbreak(); break;
                case GameDataType::SUBGROUP: __debugbreak(); break;
#else
                case GameDataType::ANY: return 0;
                case GameDataType::NetObject: return 0;
                case GameDataType::SUBGROUP: return 0;
#endif
                case GameDataType::TEAM_MEMBER: return reinterpret_cast<game_data_team_member*>(data.get())->hash();
                case GameDataType::TASK: return reinterpret_cast<game_data*>(data.get())->to_string().hash(); //"Task %s (id %d)" or "No Task"
                case GameDataType::DIARY_RECORD: return reinterpret_cast<game_data*>(data.get())->to_string().hash(); //"No diary record" or... The text of that record? Text might be long and make this hash heavy
                case GameDataType::LOCATION: return reinterpret_cast<game_data_location*>(data.get())->hash();
                case GameDataType::end: return 0;
            }

            return types::__internal::pairhash<uintptr_t,uintptr_t>(data->get_vtable(),reinterpret_cast<uintptr_t>(data.get()));
        }

        void* game_value::operator new(const std::size_t sz_) {
            return rv_allocator<game_value>::create_array(sz_);
        }

        void game_value::operator delete(void* ptr_, std::size_t) {
            rv_allocator<game_value>::deallocate(static_cast<game_value*>(ptr_));
        }
       
        bool exiting = false;
        /// @private
        extern "C" DLLEXPORT void CDECL handle_unload_internal() {
            exiting = true;
        }

        game_value_static::~game_value_static() {
            if (exiting) data._ref = nullptr;
        }

    #pragma endregion

    #pragma region Serialization
        uintptr_t param_archive::get_game_state() {
            auto allocinfo = GET_ENGINE_ALLOCATOR;
            return allocinfo->gameState;
        }

        intercept::types::serialization_return param_archive::serialize(r_string name, serialize_class & value, int min_version) {
            if (_version < min_version) return serialization_return::version_too_new;
            param_archive sub_archive(nullptr);
            sub_archive._version = _version;
            sub_archive._p3 = _p3;
            sub_archive._parameters = _parameters;
            sub_archive._isExporting = _isExporting;
            if (_isExporting) {
                sub_archive._p1 = _p1->add_entry_class(name, false);
            } else {
                sub_archive._p1 = _p1->get_entry_by_name(name);
            }

            if (!sub_archive._p1) {
                return serialization_return::no_entry;
            }

            auto ret = value.serialize(sub_archive);
            if (_isExporting) {
                sub_archive._p1->compress();
                rv_allocator<param_archive_entry>::destroy_deallocate(sub_archive._p1);
                sub_archive._p1 = nullptr;
            }
            return ret;
        }

        serialization_return param_archive::serialize(r_string name, r_string& value, int min_version) {
            if (_version < min_version) return serialization_return::version_too_new;
            if (_isExporting) {
                _p1->add_entry(name, value);
            } else {
                unique_ref<param_archive_entry> entry = _p1->get_entry_by_name(name);
                if (!entry) return serialization_return::no_entry;
                value = static_cast<r_string>(std::move(*entry));   //#TODO check if entry actually contains the type that we want
                return serialization_return::no_error;
            }
            return serialization_return::no_error;
        }

        serialization_return param_archive::serialize(r_string name, bool& value, int min_version) {
            if (_version < min_version) return serialization_return::version_too_new;
            if (_isExporting) {
                _p1->add_entry(name, static_cast<int>(value));//I don't know why.. BI does this..
            } else {
                unique_ref<param_archive_entry> entry = _p1->get_entry_by_name(name);
                if (!entry) return serialization_return::no_entry;
                value = static_cast<int>(*entry); //#TODO check if entry actually contains the type that we want
                return serialization_return::no_error;
            }
            return serialization_return::no_error;
        }

        serialization_return param_archive::serialize(r_string name, bool& value, int min_version, bool default_value) {
            if (_version < min_version) {
                if (!_isExporting) value = default_value;
                return serialization_return::no_error;
            }
            if (_isExporting && value == default_value) return serialization_return::no_error;
            const serialization_return err = serialize(name, value, min_version);
            // if the value is not found, load the default one
            if (err == serialization_return::no_entry) {
                value = default_value;
                return serialization_return::no_error;
            }
            return err;
        }

        serialization_return game_value::serialize(param_archive& ar) {
            if (!data) data = rv_allocator<game_data_nothing>::create_single();
            ar.serialize(r_string("data"sv), data, 1);

            if (data && data->get_vtable() == game_data_nothing::type_def) data = nullptr;
            return serialization_return::no_error;
        }
    #pragma endregion
    }
}


