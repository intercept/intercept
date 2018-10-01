#pragma once

#include "ai.hpp"
#include "actions.hpp"
#include "chat.hpp"
#include "core.hpp"
#include "position.hpp"
#include "misc.hpp"
#include "intersects.hpp"
#include "world.hpp"
#include "ctrl.hpp"
#include "marker.hpp"
#include "curator.hpp"
#include "eden.hpp"
#include "group.hpp"
#include "multiplayer.hpp"
#include "config.hpp"
#include "camera.hpp"
#include "inventory.hpp"
#include "hc.hpp"
#include "sound.hpp"
#include "cargo.hpp"
#include "tasks.hpp"
#include "debug.hpp"
#include "rotorlib.hpp"
#include "units.hpp"
#include "vehicles.hpp"
#include "waypoint.hpp"

#include "uncategorized.hpp"
#include <regex>

#define __XXXSQF_QUOTE(...) #__VA_ARGS__
#define __XXXSQF_EXPAND_AND_QUOTE(str) __XXXSQF_QUOTE(str)
#define __XXXSQF_L1(...) __SQF(##__VA_ARGS__##)__SQF
#define __XXXSQF_L2(...) __XXXSQF_EXPAND_AND_QUOTE(__XXXSQF_L1(__VA_ARGS__))

#define __XXXSQF_CAT(a,b) a##b
#define __XXXSQF_EXPAND_AND_CAT(a,b) __XXXSQF_CAT(a,b)

#define __XXXSQF_ARG(...) __XXXSQF_EXPAND_AND_CAT(R,__XXXSQF_L2(__VA_ARGS__))

#define __SQF(...) __inline_sqf_helper_launcher::generate(__XXXSQF_ARG(__VA_ARGS__))

class __inline_sqf_helper_launcher {
protected:
    class __inline_sqf_helper {
    public:
        __inline_sqf_helper(std::string&& sqf_) : _sqf(std::move(sqf_)), _do_return(false), _capture_return(nullptr) {
            _capture_args = game_value();
        }

        ~__inline_sqf_helper() {
            const std::regex escape("\\\\(.)");
            _sqf = std::regex_replace(_sqf, escape, "$1");
            const auto sqf_fnc = intercept::sqf::compile(_sqf);
            if (_capture_return) {
                *_capture_return = intercept::sqf::call(sqf_fnc, _capture_args);
            } else {
                intercept::sqf::call(sqf_fnc, _capture_args);
            }
        }

        void capture(game_value capture_args_) {
            _capture_args = std::move(capture_args_);
        }

        void capture(game_value capture_args_, game_value &capture_return_) {
            _capture_args = std::move(capture_args_);
            _capture_return = &capture_return_;
            _do_return = true;
        }

    protected:
        std::string _sqf;
        bool _do_return;
        game_value _capture_args;
        game_value *_capture_return;
    };

public:
    static __inline_sqf_helper generate(std::string sqf_) {
        return __inline_sqf_helper(std::move(sqf_));
    }
};
