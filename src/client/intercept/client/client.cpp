#include "client.hpp"
#include "shared\client_types.hpp"
#include "shared\vector.hpp"
#include "pointers.hpp"

using namespace intercept::types;
namespace intercept {
    namespace client {
        client_functions host::functions;
        host::mem_watcher host::memory_watcher;

        // Using __cdecl to prevent name mangling and provide better backwards compatibility
        void __cdecl assign_functions(const struct intercept::client_functions funcs) {
            host::functions = funcs;

            __sqf::__initialize();

            uintptr_t type_def;
            uintptr_t data_type_def;

            host::functions.get_type_structure("ARRAY", type_def, data_type_def);
            auto allocator_info = host::functions.get_engine_allocator();
            game_data_array::type_def = type_def;
            game_data_array::data_type_def = data_type_def;
            game_data_array::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(types::__internal::GameDataType::ARRAY)];


            host::functions.get_type_structure("SCALAR", type_def, data_type_def);
            game_data_number::type_def = type_def;
            game_data_number::data_type_def = data_type_def;
            game_data_number::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(types::__internal::GameDataType::SCALAR)];

            host::functions.get_type_structure("STRING", type_def, data_type_def);
            game_data_string::type_def = type_def;
            game_data_string::data_type_def = data_type_def;
            game_data_string::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(types::__internal::GameDataType::STRING)];

            host::functions.get_type_structure("OBJECT", type_def, data_type_def);
            game_data_object::type_def = type_def;
            game_data_object::data_type_def = data_type_def;

            host::functions.get_type_structure("BOOL", type_def, data_type_def);
            game_data_bool::type_def = type_def;
            game_data_bool::data_type_def = data_type_def;
            game_data_bool::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(types::__internal::GameDataType::BOOL)];

            
            host::functions.get_type_structure("CODE", type_def, data_type_def);
            game_data_code::type_def = type_def;
            game_data_code::data_type_def = data_type_def;

            host::functions.get_type_structure("GROUP", type_def, data_type_def);
            game_data_group::type_def = type_def;
            game_data_group::data_type_def = data_type_def;

            host::functions.get_type_structure("CONFIG", type_def, data_type_def);
            game_data_config::type_def = type_def;
            game_data_config::data_type_def = data_type_def;

            host::functions.get_type_structure("CONTROL", type_def, data_type_def);
            game_data_control::type_def = type_def;
            game_data_control::data_type_def = data_type_def;

            host::functions.get_type_structure("DISPLAY", type_def, data_type_def);
            game_data_display::type_def = type_def;
            game_data_display::data_type_def = data_type_def;

            host::functions.get_type_structure("LOCATION", type_def, data_type_def);
            game_data_location::type_def = type_def;
            game_data_location::data_type_def = data_type_def;

            host::functions.get_type_structure("SCRIPT", type_def, data_type_def);
            game_data_script::type_def = type_def;
            game_data_script::data_type_def = data_type_def;

            host::functions.get_type_structure("SIDE", type_def, data_type_def);
            game_data_side::type_def = type_def;
            game_data_side::data_type_def = data_type_def;

            host::functions.get_type_structure("TEXT", type_def, data_type_def);
            game_data_rv_text::type_def = type_def;
            game_data_rv_text::data_type_def = data_type_def;

            host::functions.get_type_structure("TEAM_MEMBER", type_def, data_type_def);
            game_data_team::type_def = type_def;
            game_data_team::data_type_def = data_type_def;

            host::functions.get_type_structure("NAMESPACE", type_def, data_type_def);
            game_data_rv_namespace::type_def = type_def;
            game_data_rv_namespace::data_type_def = data_type_def;
            


            host::functions.get_type_structure("GV", type_def, data_type_def);
            game_value::__vptr_def = type_def;
        }

        void __cdecl handle_unload()
        {

        }

        invoker_lock::invoker_lock(bool delayed_) : _locked(false)
        {
            if (!delayed_)
                lock();
        }

        invoker_lock::~invoker_lock()
        {
            if (_locked)
                host::functions.invoker_unlock();
        }

        inline void invoker_lock::lock()
        {
            if (!_locked) {
                host::functions.invoker_lock();
                _locked = true;
            }
        }
            
        host::mem_watcher::mem_watcher() {
        }

        host::mem_watcher::~mem_watcher() {
        }

        void host::mem_watcher::clean() {
            /*
            auto data = _watch_data.begin();
            while (data != _watch_data.end()) {
                if (data->rv_data.data->ref_count_internal <= 1) {
                    data->rv_data.data->ref_count_internal = ref_count(1, 1, true);
                    _watch_data.erase(data++);
                }
                else {
                    data++;
                }
            }
            */
        }

        void host::mem_watcher::add_watch(game_value & data_) {
            /*
            _add(data_);
            clean();
            */
        }

        void host::mem_watcher::_add(game_value & data_)
        {
            /*
            if (data_.rv_data.data) {
                if (data_.type() == game_data_array::type_def) {
                    for (uint32_t i = 0; i < data_.length(); ++i) {
                        _add(data_[i]);
                    }
                }

                if (data_.rv_data.data->ref_count_internal.is_intercept()) {
                    data_.rv_data.data->ref_count_internal.clear_initial();
                    _watch_data.push_back(data_);
                }
            }
            */
        }
       

}
}