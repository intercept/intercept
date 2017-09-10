#include "shared/types.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"
#include <assert.h>
#include <future>
#include <sstream> //Debugging

#define INTERNAL_TAG 0x0000dede

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

        uintptr_t game_data_team::type_def;
        uintptr_t game_data_team::data_type_def;

        uintptr_t game_data_rv_namespace::type_def;
        uintptr_t game_data_rv_namespace::data_type_def;

        uintptr_t game_data_object::type_def;
        uintptr_t game_data_object::data_type_def;



        uintptr_t game_value::__vptr_def;
        uintptr_t sqf_script_type::type_def;


        value_types sqf_script_type::type() const {
            if (single_type != nullptr) {
                return{ static_cast<std::string>(single_type->_name) };
            } else {
                return{
                    static_cast<std::string>(compound_type->types->first->_name),
                    static_cast<std::string>(compound_type->types->second->_name)
                };
            }
        }

        std::string sqf_script_type::type_str() const {
            if (single_type != nullptr) {
                return static_cast<std::string>(single_type->_name);
            } else {
                return
                    static_cast<std::string>(compound_type->types->first->_name) + "_" +
                    static_cast<std::string>(compound_type->types->second->_name);
            }
        }

    #pragma region GameData Types
        game_data_number::game_data_number() {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = 0.0f;
        }

        game_data_number::game_data_number(float val_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = val_;
        }

        game_data_number::game_data_number(const game_data_number & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = copy_.number;
        }

        game_data_number::game_data_number(game_data_number && move_) {
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

        game_data_number & game_data_number::operator=(game_data_number && move_) {
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

        game_data_bool::game_data_bool(game_data_bool && move_) {
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

        game_data_bool & game_data_bool::operator=(game_data_bool && move_) {
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

        game_data_string::game_data_string() {
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

        game_data_string::game_data_string(game_data_string && move_) {
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

        game_data_string & game_data_string::operator=(game_data_string && move_) {
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

        game_data_array::game_data_array(game_data_array && move_) {
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

        game_data_array & game_data_array::operator = (game_data_array &&move_) {
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

        void __internal::add_game_datatype(r_string name, GameDataType type) {
            additionalTypes[static_cast<std::string>(name)] = type;
        };

    #pragma endregion

    #pragma region GameValue

        game_value::game_value() {
            set_vtable(__vptr_def);
            data = nullptr;
        }

        void game_value::copy(const game_value & copy_) {
            set_vtable(__vptr_def); //Whatever vtable copy_ has.. if it's different then it's wrong
            if (copy_.data) {
                data = copy_.data;
            }
        }

        game_value::game_value(const game_value & copy_) {
            copy(copy_);
        }

        game_value::game_value(game_value && move_) noexcept {
            set_vtable(__vptr_def);//Whatever vtable move_ has.. if it's different then it's wrong
            data = move_.data;
            move_.data = nullptr;
        }

        game_value::~game_value() {
            data = nullptr;
        }

        game_value::game_value(game_data* val_) {
            set_vtable(__vptr_def);
            data = val_;
        }

        game_value::game_value(float val_) {
            set_vtable(__vptr_def);
            data = new game_data_number(val_);
        }

        game_value::game_value(int val_) : game_value(static_cast<float>(val_)) {}

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

        uintptr_t game_value::get_vtable() const {
            return *reinterpret_cast<const uintptr_t*>(this);
        }

        void game_value::set_vtable(uintptr_t vt) {
            *reinterpret_cast<uintptr_t*>(this) = vt;
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
                auto type = data->get_vtable();
                if (type == game_data_code::type_def || type == game_data_string::type_def)
                    return static_cast<std::string>(data->get_as_string());
                return static_cast<std::string>(data->to_string());
            }
                
            return {};
        }

        game_value::operator r_string () const {
            if (data) {
                auto type = data->get_vtable();
                if (type == game_data_code::type_def || type == game_data_string::type_def)
                    return data->get_as_string();
                return data->to_string();
            }

            return {};
        }

        auto_array<game_value>& game_value::to_array() {
            if (data) {
                if (data->get_vtable() != game_data_array::type_def) throw game_value_conversion_error("Invalid conversion to array");
                return data->get_as_array();
            }
            static auto_array<game_value> dummy;//else we would return a temporary.
            dummy.clear(); //In case user modified it before
            return dummy;
        }

        const auto_array<game_value>& game_value::to_array() const {
            if (data) {
                if (data->get_vtable() != game_data_array::type_def) throw game_value_conversion_error("Invalid conversion to array");
                return data->get_as_const_array();
            }
            static auto_array<game_value> dummy;//else we would return a temporary.
            dummy.clear(); //In case user modified it before
            return dummy;
        }

        game_value& game_value::operator [](size_t i_) {
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

        game_value game_value::operator [](size_t i_) const {
            if (!data) return {};
            if(data->get_vtable() != game_data_array::type_def)throw game_value_conversion_error("Invalid array access");
            auto& array = data->get_as_array();
            if (array.count() >= i_)
                return array[i_];
            return {};
        }

        uintptr_t game_value::type() const {
            if (data)
                return *reinterpret_cast<uintptr_t*>(data.getRef()); //#TODO use GetType virtual func instead
            return 0x0;
        }

        size_t game_value::length() const {
            return size();
        }

        size_t game_value::size() const {
            if (!data) return 0;
            if (data->get_vtable() != game_data_array::type_def) return 0;
            return data->get_as_array().count();
        }

        bool game_value::is_nil() const {
            if (!data) return true;
            return (data->is_nil());
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
            auto _type = data->get_vtable();
            if (_type == game_data_object::type_def)
                return reinterpret_cast<game_data_object*>(data.getRef())->hash();
            if (_type == game_data_number::type_def)
                return reinterpret_cast<game_data_number*>(data.getRef())->hash();
            if (_type == game_data_string::type_def)
                return reinterpret_cast<game_data_string*>(data.getRef())->hash();
            if (_type == game_data_array::type_def)
                return reinterpret_cast<game_data_array*>(data.getRef())->hash();
            if (_type == game_data_bool::type_def)
                return reinterpret_cast<game_data_bool*>(data.getRef())->hash();
            if (_type == game_data_group::type_def)
                return reinterpret_cast<game_data_group*>(data.getRef())->hash();
            if (_type == game_data_config::type_def)
                return reinterpret_cast<game_data_config*>(data.getRef())->hash();
            if (_type == game_data_control::type_def)
                return reinterpret_cast<game_data_control*>(data.getRef())->hash();
            if (_type == game_data_display::type_def)
                return reinterpret_cast<game_data_display*>(data.getRef())->hash();
            if (_type == game_data_location::type_def)
                return reinterpret_cast<game_data_location*>(data.getRef())->hash();
            if (_type == game_data_script::type_def)
                return reinterpret_cast<game_data_script*>(data.getRef())->hash();
            if (_type == game_data_side::type_def)
                return reinterpret_cast<game_data_side*>(data.getRef())->hash();
            if (_type == game_data_rv_text::type_def)
                return reinterpret_cast<game_data_rv_text*>(data.getRef())->hash();
            if (_type == game_data_rv_namespace::type_def)
                return reinterpret_cast<game_data_rv_namespace*>(data.getRef())->hash();
            if (_type == game_data_code::type_def)
                return reinterpret_cast<game_data_code*>(data.getRef())->hash();
            return 0;
        };

        void* game_value::operator new(std::size_t sz_) {
            return rv_allocator<game_value>::createArray(sz_);
        }

        void game_value::operator delete(void* ptr_, std::size_t) {
            rv_allocator<game_value>::deallocate(static_cast<game_value*>(ptr_));
        }
       
        bool exiting = false;

        extern "C" DLLEXPORT void CDECL handle_unload_internal() {
            exiting = true;
        }

        game_value_static::~game_value_static() {
            if (exiting) data._ref = nullptr;
        }

    #pragma endregion

    #pragma region Allocator
        class MemTableFunctions { //We don't want to expose this in the header. It's only used here
        public:
            virtual void *New(size_t size) = 0;
            virtual void *New(size_t size, const char *file, int line) = 0;
            virtual void Delete(void *mem) = 0;
            virtual void Delete(void *mem, const char *file, int line) = 0;
            virtual void *Realloc(void *mem, size_t size) = 0;
            virtual void *Realloc(void *mem, size_t size, const char *file, int line) = 0;
            virtual void *Resize(void *mem, size_t size) = 0; //This actually doesn't do anything.

            virtual void *NewPage(size_t size, size_t align) = 0;
            virtual void DeletePage(void *page, size_t size) = 0;

            virtual void *HeapAlloc(void *mem, size_t size) = 0;
            virtual void *HeapAlloc(void *mem, size_t size, const char *file, int line) = 0;//HeapAlloc

            virtual void *HeapDelete(void *mem, size_t size) = 0;
            virtual void *HeapDelete(void *mem, size_t size, const char *file, int line) = 0;//HeapFree

        #ifdef __linux__
            virtual int something1(void* mem, size_t unknown) = 0; //memalign alloc and memmove
            virtual int something2(void* mem, size_t unknown) = 0; //redirect to something1
            virtual int something3(void* mem, size_t unknown) = 0; //ret 0
        #endif

            virtual int something(void* mem, size_t unknown) = 0; //Returns HeapSize(mem) - (unknown<=4 ? 4 : unknown) -(-0 & 3) -3
            //In Linux binary this calls malloc_usable_size(unknown)
            //In Linux binary this allocates aligned memory and moves memory. But on linux it also takes 4 args

            virtual size_t GetPageRecommendedSize() = 0;

            virtual void *HeapBase() = 0;
            virtual size_t HeapUsed() = 0;

            virtual size_t HeapUsedByNew() = 0;
            virtual size_t HeapCommited() = 0;
            virtual int FreeBlocks() = 0;
            virtual int MemoryAllocatedBlocks() = 0;
            virtual void Report() = 0;//Does nothing on release build. Maybe on Profiling build
            virtual bool CheckIntegrity() = 0;//Does nothing on release build. Maybe on Profiling build returns true.
            virtual bool IsOutOfMemory() = 0;//If true we are so full we are already moving memory to disk.

            virtual void CleanUp() = 0;//Does nothing? I guess.
                                       //Synchronization for Multithreaded access
            virtual void Lock() = 0;
            virtual void Unlock() = 0;
            const char* arr[6]{ "tbb4malloc_bi","tbb3malloc_bi","jemalloc_bi","tcmalloc_bi","nedmalloc_bi","custommalloc_bi" };
        };

        void __internal::set_game_value_vtable(uintptr_t vtable) {
            game_value::__vptr_def = vtable;
        }

        void* __internal::rv_allocator_allocate_generic(size_t size) {
            static auto allocatorBase = GET_ENGINE_ALLOCATOR;
        #ifdef __linux__
            MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(reinterpret_cast<uintptr_t>(&(allocatorBase->genericAllocBase)));
        #else
            MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(allocatorBase->genericAllocBase);
        #endif
            return alloc->New(size);
        }

        void __internal::rv_allocator_deallocate_generic(void* _Ptr) {
            //#TODO assert when _ptr is not 32/64bit aligned
            // deallocate object at _Ptr
            static auto allocatorBase = GET_ENGINE_ALLOCATOR;
        #ifdef __linux__
            MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(reinterpret_cast<uintptr_t>(&(allocatorBase->genericAllocBase)));
        #else
            MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(allocatorBase->genericAllocBase);
        #endif
            alloc->Delete(_Ptr);
        }

        void* __internal::rv_allocator_reallocate_generic(void* _Ptr, size_t _size) {
            //#TODO assert when _ptr is not 32/64bit aligned
            // deallocate object at _Ptr
            static auto allocatorBase = GET_ENGINE_ALLOCATOR;
        #ifdef __linux__
            MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(reinterpret_cast<uintptr_t>(&(allocatorBase->genericAllocBase)));
        #else
            MemTableFunctions* alloc = reinterpret_cast<MemTableFunctions*>(allocatorBase->genericAllocBase);
        #endif
            return alloc->Realloc(_Ptr, _size);
        }

        //template<class Type>
        //void rv_allocator<Type>::deallocate(Type* _Ptr, size_t) {
        //    //#TODO assert when _ptr is not 32/64bit aligned
        //    // deallocate object at _Ptr
        //    auto allocatorBase = GET_ENGINE_ALLOCATOR;
        //    MemTableFunctions* alloc = (MemTableFunctions*) allocatorBase->genericAllocBase;
        //    //std::stringstream stream;
        //    //stream << "deallocate " << "x * " << typeid(Type).name() << "@" << std::hex << (int)_Ptr << "\n";
        //    //OutputDebugStringA(stream.str().c_str());
        //    alloc->Delete(_Ptr);
        //}
        //
        //template<class Type>
        //Type* rv_allocator<Type>::allocate(size_t _count) {	// allocate array of _Count elements
        //
        //    auto allocatorBase = GET_ENGINE_ALLOCATOR;
        //    //uintptr_t allocatorBase = GET_ENGINE_ALLOCATOR;    
        //    MemTableFunctions* alloc = (MemTableFunctions*) allocatorBase->genericAllocBase;
        //    Type* newData = reinterpret_cast<Type*>(alloc->New(sizeof(Type)*_count));
        //    //std::stringstream stream;
        //    //stream << "allocate " << _count << " * " << typeid(Type).name() << "@" << std::hex << (int) newData << "\n";
        //    //OutputDebugStringA(stream.str().c_str());
        //    return newData;
        //}


        //template<class Type>
        //Type* rv_allocator<Type>::reallocate(Type* _Ptr, size_t _count) {
        //    auto allocatorBase = GET_ENGINE_ALLOCATOR;   
        //    MemTableFunctions* alloc = (MemTableFunctions*) allocatorBase->genericAllocBase;
        //    Type* newData = reinterpret_cast<Type*>(alloc->Realloc(_Ptr,sizeof(Type)*_count));
        //    return newData;
        //}

        void* rv_pool_allocator::allocate(size_t count) {
        #ifdef __linux__
            __internal::rv_allocator_allocate_generic(count);
        #else
            static auto allocatorBase = GET_ENGINE_ALLOCATOR;
            typedef void*(__thiscall *allocFunc)(rv_pool_allocator*, size_t /*count*/);
            allocFunc alloc = reinterpret_cast<allocFunc>(allocatorBase->poolFuncAlloc);
            auto allocation = alloc(this, count);
            return allocation;
        #endif
        }

        void rv_pool_allocator::deallocate(void* data) {
        #ifdef __linux__
            __internal::rv_allocator_deallocate_generic(data);
        #else
            static auto allocatorBase = GET_ENGINE_ALLOCATOR;
            typedef void(__thiscall *deallocFunc)(rv_pool_allocator*, void* /*data*/);
            deallocFunc dealloc = reinterpret_cast<deallocFunc>(allocatorBase->poolFuncDealloc);
            dealloc(this, data);
        #endif
        }
    #pragma endregion

    #pragma region Serialization
        intercept::types::serialization_return param_archive::serialize(r_string name, serialize_class & value, int min_version) {
            if (_version < min_version) return serialization_return::version_too_new;
            param_archive sub_archive;
            sub_archive._version = _version;
            sub_archive._p3 = _p3;
            sub_archive._parameters = _parameters;
            sub_archive._isExporting = _isExporting;
            delete sub_archive._p1;
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
                delete sub_archive._p1;
                sub_archive._p1 = nullptr;
            }
            return ret;
        }

        serialization_return param_archive::serialize(r_string name, r_string& value, int min_version) {
            if (_version < min_version) return serialization_return::version_too_new;
            if (_isExporting) {
                _p1->add_entry(name, value);
            } else {
                auto entry = _p1->get_entry_by_name(name);
                value = static_cast<r_string>(*entry);   //#TODO check if entry actually contains the type that we want
                return serialization_return::no_error;
            }
            return serialization_return::no_error;
        }

        serialization_return param_archive::serialize(r_string name, bool& value, int min_version) {
            if (_version < min_version) return serialization_return::version_too_new;
            if (_isExporting) {
                _p1->add_entry(name, static_cast<int>(value));//I don't know why.. BI does this..
            } else {
                auto entry = _p1->get_entry_by_name(name);
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
            serialization_return err = serialize(name, value, min_version);
            // if the value is not found, load the default one
            if (err == serialization_return::no_entry) {
                value = default_value;
                return serialization_return::no_error;
            }
            return err;
        }

        serialization_return game_value::serialize(param_archive& ar) {
            if (!data) data = new game_data_bool(false);//#TODO use game_data_nothing and rv allocator
            ar.serialize(r_string("data"sv), data, 1);
            //#TODO check if type == game_data_nothing. Can probably just use strcmp
            //if (data && data->type() == game_data_nothing) data = nullptr;
            return serialization_return::no_error;
        }
    #pragma endregion
    }
}


