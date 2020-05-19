#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <queue>

#include "shared.hpp"
#include "arguments.hpp"
#include "singleton.hpp"
#include <chrono>
using namespace std::literals::chrono_literals;
namespace intercept {
    class controller_module {
    public:
        controller_module() noexcept : _stopped(false) { }
        ~controller_module() { }

        void stop() {
            std::lock_guard<std::mutex> lock(_stop_lock);
            _stopped = true;
        }
        bool stopped() {
            std::lock_guard<std::mutex> lock(_stop_lock);
            return _stopped;
        }
    protected:
        std::mutex _stop_lock;
        
        bool _stopped;
    };

    class dispatcher {
    public:
        dispatcher() noexcept : _ready(true) { }

        virtual bool call(const std::string_view name_, arguments & args_, std::string & result_) {
            auto method = _methods.find(name_);
            if (method != _methods.end()) {
                return method->second(args_, result_);
            }
            return false;
        }

        bool add(const std::string_view name_, std::function<bool(arguments &, std::string &)> func_) {
            if (_methods.find(name_) != _methods.end()) {
                // @TODO: Exceptions
                return false;
            }
            _methods[name_] = func_;

            return true;
        }
        
        bool ready() const noexcept { return _ready;  }
        void ready(bool r) noexcept { _ready.exchange(r); }
    protected:
        std::unordered_map < std::string_view, std::function<bool(arguments &, std::string &)> > _methods;
        std::atomic_bool _ready;
    };
    class dispatch : public dispatcher, public singleton<dispatch> { };

    struct dispatch_message {
        dispatch_message(std::string_view command_, const arguments & args_, const uint64_t id_) : command(command_), args(args_), id(id_) {}
        std::string command;
        arguments args;
        uint64_t    id;
    };
    struct dispatch_result {
        dispatch_result() noexcept {}
        dispatch_result(std::string res, const uint64_t id_) noexcept : message(std::move(res)), id(id_) {}
        std::string message;
        uint64_t    id{};
    };

    class threaded_dispatcher : public dispatcher {
    public:
        threaded_dispatcher() noexcept : _stop(false), _message_id(0) {
 
        }

        virtual ~threaded_dispatcher() {}
        
        bool call(const std::string_view name_, arguments & args_, std::string & result_, bool threaded) {
            if (_methods.find(name_) == _methods.end()) {
                // @TODO: Exceptions
                return false;
            }
            if (threaded) {
                if (!_thread_running) start_thread();
                std::lock_guard<std::mutex> lock(_messages_lock);
                _messages.push(dispatch_message(name_, args_, _message_id));
                
                // @TODO: We should provide an interface for this serialization.
                std::stringstream ss;
                ss << "[\"result_id\", " << _message_id << "]";
                result_ = ss.str();

                _message_id = _message_id + 1;
            } else {
#ifdef _DEBUG
                if (name_ != "fetch_result" && name_ != "do_invoke_period") {
                    TRACE("dispatch[immediate]:\t[{}] { {} }", name_, args_.get());
                }
#endif
                return dispatcher::call(name_, args_, result_);
            }

            return true;
        }
        bool call(const std::string_view name_, arguments & args_, std::string & result_) override {
            return call(name_, args_, result_, false);
        }

        void push_result(const dispatch_result & result) {
            {
                std::lock_guard<std::mutex> lock(_results_lock);
                _results.push(result);
            }
        }
        void push_result(const std::string & result) {
            push_result(dispatch_result(result, -1));
        }
        void stop() {
            for (auto module : _modules) {
                module->stop();
            }
            std::lock_guard<std::mutex> lock(_messages_lock);
            _stop = true;
        }

        void add_module(std::shared_ptr<controller_module> module_) {
            _modules.push_back(module_);
        }

    protected:
        void start_thread() {
            _worker = std::thread(&intercept::threaded_dispatcher::monitor, this);
            _thread_running = true;
        }
        void monitor() {
            _ready = false;
            while (!_stop) {//#TODO rewrite to use condition variable
                
                bool empty = false;
                {
                    std::lock_guard<std::mutex> lock(_messages_lock);
                    empty = _messages.empty();
                }
                while (!empty) {
                    if (_ready) {
                        _messages_lock.lock();
                        dispatch_result result;
                        dispatch_message _message = std::move(_messages.front());
                        _messages.pop();
                        _messages_lock.unlock();

                        result.id = _message.id;
                        result.message.resize(4096);
#ifdef _DEBUG
                        if (_message.command != "fetch_result") {
                            TRACE("dispatch[threaded]:\t[{}]", _message.command);
                            if (_message.args.size() > 0) {
                                //    LOG(TRACE) << "\t{ " << _messages.front().args.get() << " }";
                            }
                        }
#endif
                        dispatcher::call(_message.command, _message.args, result.message);
                        {
                            std::lock_guard<std::mutex> lock(_results_lock);
                            _results.push(result);
                        }
                        {
                            std::lock_guard<std::mutex> lock(_messages_lock);
                            empty = _messages.empty();
                        }
                            
                    }
                }
                std::this_thread::sleep_for(5ms);
            }
        }
        std::atomic_bool                _stop;
        std::queue<dispatch_result>     _results;
        std::mutex                      _results_lock;

        std::queue<dispatch_message>    _messages;
        std::mutex                      _messages_lock;

        std::thread                     _worker;

        uint64_t                        _message_id;

        bool                            _thread_running{false};

        std::vector<std::shared_ptr<controller_module>> _modules;
    };
    class threaded_dispatch : public threaded_dispatcher, public singleton<dispatch> { };
}
