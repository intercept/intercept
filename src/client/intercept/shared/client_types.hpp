#pragma once
#include "shared.hpp"
#include "types.hpp"
#include <vector>
#include <memory>
namespace intercept {
    namespace types {

        class game_value_shared_wrapper {
        public:
            game_value_shared_wrapper(game_value value_);
            ~game_value_shared_wrapper();
            game_value value;
        };

        class internal_object {
        public:
            internal_object();
            internal_object(game_value value_);
            internal_object(const internal_object &copy_);
            operator game_value();
            operator game_value() const;
            operator game_value &();
            std::shared_ptr<game_value_shared_wrapper> value;
        };

        class object : public internal_object {
        public:
            object();
            object(game_value value_);
            object(const object &copy_);
        };
        class group : public internal_object {
        public:
            group();
            group(game_value value_);
            group(const group &copy_);
        };
        class code : public internal_object {
        public:
            code();
            code(game_value value_);
            code(const code &copy_);
        };
        class config : public internal_object {
        public:
            config();
            config(game_value value_);
            config(const config &copy_);
        };
        class control : public internal_object {
        public:
            control();
            control(game_value value_);
            control(const control &copy_);
        };
        class display : public internal_object {
        public:
            display();
            display(game_value value_);
            display(const display &copy_);
        };
        class location : public internal_object {
        public:
            location();
            location(game_value value_);
            location(const location &copy_);
        };
        class script : public internal_object {
        public:
            script();
            script(game_value value_);
            script(const script &copy_);
        };
        class side : public internal_object {
        public:
            side();
            side(game_value value_);
            side(const side &copy_);
        };
        class text : public internal_object {
        public:
            text();
            text(game_value value_);
            text(const text &copy_);
        };
        class team_member : public internal_object {
        public:
            team_member();
            team_member(game_value value_);
            team_member(const team_member &copy_);
        };
        class rv_namespace : public internal_object {
        public:
            rv_namespace();
            rv_namespace(game_value value_);
            rv_namespace(const rv_namespace &copy_);
        };
        class task : public internal_object {
        public:
            task();
            task(game_value value_);
            task(const task &copy_);
        };

        typedef std::string marker;
    }
}