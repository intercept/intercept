#pragma once
#include "shared.hpp"
#include "types.hpp"
#include <vector>
#include <memory>
namespace intercept {
    namespace types {

        class game_value_shared_wrapper {
        public:
            game_value_shared_wrapper(rv_game_value value_);
            ~game_value_shared_wrapper();
            game_value value;
        };

        class internal_object {
        public:
            internal_object();
            internal_object(rv_game_value value_);
            internal_object(const internal_object &copy_);
            operator game_value();
            operator game_value() const;
            operator game_value *();
            std::shared_ptr<game_value_shared_wrapper> value;
        };

#define RV_GENERIC_OBJECT_DEC(type) class type : public internal_object {\
            public:\
                type##();\
                type##(rv_game_value value_);\
                type##(const type &copy_);\
            }

        RV_GENERIC_OBJECT_DEC(object);
        RV_GENERIC_OBJECT_DEC(group);
        RV_GENERIC_OBJECT_DEC(code);
        RV_GENERIC_OBJECT_DEC(config);
        RV_GENERIC_OBJECT_DEC(control);
        RV_GENERIC_OBJECT_DEC(display);
        RV_GENERIC_OBJECT_DEC(location);
        RV_GENERIC_OBJECT_DEC(script);
        RV_GENERIC_OBJECT_DEC(side);
        RV_GENERIC_OBJECT_DEC(text);
        RV_GENERIC_OBJECT_DEC(team_member);
        RV_GENERIC_OBJECT_DEC(rv_namespace);
        RV_GENERIC_OBJECT_DEC(task);

        typedef std::string marker;
    }
}