#pragma once

#include "shared.hpp"

namespace intercept { 
    namespace pbo {
        class search {
        public:
            search();
            const std::vector<std::string> & active_pbo_list() { return _active_pbo_list;  }
        protected:
            bool generate_pbo_list();

            std::vector<std::string> _active_pbo_list;
        };
        typedef std::shared_ptr<search> search_p;
    }
}