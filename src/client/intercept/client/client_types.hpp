#pragma once
#include "shared.hpp"
#include "shared\types.hpp"
#include <memory>

namespace intercept {
    namespace client {
        namespace types {
            class internal_ptr {
            public:
                internal_ptr();
                internal_ptr(rv_types::game_value value_);
                ~internal_ptr();
                rv_types::game_value value;
                operator rv_types::game_value() { return value; }
                operator rv_types::game_value *() { return &value; }
            };

            class object_ptr : public internal_ptr {
            public:
                object_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~object_ptr();
            };
            class group_ptr : public internal_ptr {
            public:
                group_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~group_ptr();
            };
            class code_ptr : public internal_ptr {
            public:
                code_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~code_ptr();
            };
            class config_ptr : public internal_ptr {
            public:
                config_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~config_ptr();
            };
            class control_ptr : public internal_ptr {
            public:
                control_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~control_ptr();
            };
            class display_ptr : public internal_ptr {
            public:
                display_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~display_ptr();
            };
            class location_ptr : public internal_ptr {
            public:
                location_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~location_ptr();
            };
            class script_ptr : public internal_ptr {
            public:
                script_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~script_ptr();
            };
            class side_ptr : public internal_ptr {
            public:
                side_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~side_ptr();
            };
            class text_ptr : public internal_ptr {
            public:
                text_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~text_ptr();
            };
            class team_member_ptr : public internal_ptr {
            public:
                team_member_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~team_member_ptr();
            };
            class rv_namespace_ptr : public internal_ptr {
            public:
                rv_namespace_ptr(rv_types::game_value value_) : internal_ptr(value_) {};
                ~rv_namespace_ptr();
            };


            typedef std::shared_ptr<object_ptr> object;
            typedef std::shared_ptr<group_ptr> group;
            typedef std::shared_ptr<code_ptr> code;
            typedef std::shared_ptr<config_ptr> config;
            typedef std::shared_ptr<control_ptr> control;
            typedef std::shared_ptr<display_ptr> display;
            typedef std::shared_ptr<location_ptr> location;
            typedef std::shared_ptr<script_ptr> script;
            typedef std::shared_ptr<side_ptr> side;
            typedef std::shared_ptr<text_ptr> text;
            typedef std::shared_ptr<team_member_ptr> team_member;
            typedef std::shared_ptr<rv_namespace_ptr> rv_namespace;

        }
    }
}