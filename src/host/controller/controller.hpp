#pragma once

#include "shared.hpp"
#include "singleton.hpp"
#include "arguments.hpp"
#include "dispatch.hpp"


namespace intercept {
    
    

    class controller 
        : public singleton<controller>,
        public threaded_dispatcher {
    public:
        controller();

        
        bool init(const arguments &, std::string &);
        bool reset(const arguments &, std::string &);
        bool get_ready(const arguments &, std::string &) const;

        bool fetch_result(const arguments &, std::string &);

        bool export_ptr_list(const arguments & _args, std::string & result) const;

        bool do_stop(const arguments &, std::string &) {
            stop();
            _worker.join();
            return true;
        }
    
    protected:
        bool _initiated;
        std::vector<std::shared_ptr<controller_module>> _modules;
    };

    
}

