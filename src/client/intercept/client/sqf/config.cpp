#include "config.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        config_entry::config_entry() : _initialized(false)
        {

        }
        config_entry::config_entry(types::config entry_) : _config_entry(entry_), _initialized(true)
        {
        }
        config_entry::config_entry(config_entry const & copy_)
        {
            _config_entry = copy_._config_entry;
            _initialized = copy_._initialized;
        }
        config_entry::config_entry(config_entry && move_)
        {
            _config_entry = std::move(move_._config_entry);
            _initialized = move_._initialized;
        }
        config_entry & config_entry::operator=(const config_entry & copy_)
        {
            _config_entry = copy_._config_entry;
            _initialized = copy_._initialized;
            return *this;
        }
        config_entry & config_entry::operator=(config_entry && move_)
        {
            if (this == &move_)
                return *this;
            _config_entry = std::move(move_._config_entry);
            _initialized = move_._initialized;
            return *this;
        }
        config_entry config_entry::operator>>(const std::string & entry_)
        {
            if (!_initialized) {
                _config_entry = host::functions.invoke_raw_nular(__sqf::nular__configfile__ret__config);
                _initialized = true;
            }
            return config_entry(config(host::functions.invoke_raw_binary(__sqf::binary__configaccessor__config__string__ret__config, _config_entry, entry_)));
        }
        config_entry::operator config&()
        {
            return _config_entry;
        }
        
    }
}
