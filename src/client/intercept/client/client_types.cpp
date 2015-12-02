#include "client_types.hpp"
#include "shared\functions.hpp"
extern intercept::client_functions functions;
namespace intercept {
    namespace client {
        namespace types {
            object_ptr::object_ptr()
            {
            }

            object_ptr::object_ptr(rv_types::game_value rv_obj_) : rv_obj(rv_obj_)
            {
            }

            object_ptr::~object_ptr()
            {
                functions.free_value(&rv_obj);
            }
        }
    }
}