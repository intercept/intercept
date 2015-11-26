#include "controller.hpp"
#include "invoker.hpp"
#include "loader.hpp"

#include <chrono>

#ifdef _DEBUG
#define DEBUG_DISPATCH(x, y) { std::string empty; _debug_display->call(x, arguments(y), empty); }
#else
#define DEBUG_DISPATCH(x, y)
#endif

namespace intercept {
    controller::controller() : threaded_dispatcher() {
        _initiated = false;
		add("init", std::bind(&intercept::controller::init, this, std::placeholders::_1, std::placeholders::_2));
        add("reset", std::bind(&intercept::controller::reset, this, std::placeholders::_1, std::placeholders::_2));
        add("ready", std::bind(&intercept::controller::get_ready, this, std::placeholders::_1, std::placeholders::_2));
		add("stop", std::bind(&controller::do_stop, this, std::placeholders::_1, std::placeholders::_2));
        // action results
        add("fetch_result", std::bind(&intercept::controller::fetch_result, this, std::placeholders::_1, std::placeholders::_2));
    }
    controller::~controller() { }

	bool controller::init(const arguments &_args, std::string & result) {
		if (!_initiated) {
            loader::get().attach_controller();
            invoker::get().attach_controller();
            result = "1";
			_initiated = true;
		}
		return true;
	}

    bool controller::get_ready(const arguments &_args, std::string & result) {
        result = "0";

        if (!_ready)
            result = "-1";

        return true;
    }

    bool controller::reset(const arguments &_args, std::string & result) {
        _ready = false;


        { 
            std::lock_guard<std::mutex> lock_results(_results_lock);

            while (!_results.empty()) {
                _results.pop();
            }

            while (!_messages.empty()) {
                _messages.pop();
            }
        }

        _ready = true;

        return true;
    }

    bool controller::fetch_result(const arguments &_args, std::string & result) {
        result = "";
        if (_results.size() > 0) {
            std::lock_guard<std::mutex> _lock(_results_lock);
            dispatch_result res = _results.front();
			std::stringstream ss;
			ss << "[" << res.id << ",[" << res.message << "]]";
            result = ss.str();
            _results.pop();
        }
        return true;
    }
}

