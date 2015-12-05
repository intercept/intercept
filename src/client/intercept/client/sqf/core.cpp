#include "chat.hpp"
#include "client\pointers.hpp"

namespace intercept {
    namespace sqf {
        object player() {
            game_value player_obj = host::functions.invoke_raw_nular(client::__sqf::nular__player__ret__object);
            return std::make_shared<object_ptr>(player_obj);
        }
    }
}
