#include "config.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        config_entry::config_entry() : _initialized(false) {

        }
        config_entry::config_entry(config entry_) : _config_entry(entry_), _initialized(true) {}
        config_entry::config_entry(config_entry const & copy_) {
            _config_entry = copy_._config_entry;
            _initialized = copy_._initialized;
        }
        config_entry::config_entry(config_entry && move_) {
            _config_entry = std::move(move_._config_entry);
            _initialized = move_._initialized;
        }
        config_entry & config_entry::operator=(const config_entry & copy_) {
            _config_entry = copy_._config_entry;
            _initialized = copy_._initialized;
            return *this;
        }
        config_entry & config_entry::operator=(config_entry && move_) {
            if (this == &move_)
                return *this;
            _config_entry = std::move(move_._config_entry);
            _initialized = move_._initialized;
            return *this;
        }
        config_entry config_entry::operator>>(const std::string & entry_) {
            if (!_initialized) {
                _config_entry = host::functions.invoke_raw_nular(__sqf::nular__configfile__ret__config);
                _initialized = true;
            }
            return config_entry(config(host::functions.invoke_raw_binary(__sqf::binary__configaccessor__config__string__ret__config, _config_entry, entry_)));
        }
        config_entry::operator config&() {
            return _config_entry;
        }



        /* Config */

        std::vector<config> config_hierarchy(const config &config_entry_) {
            game_value output = host::functions.invoke_raw_unary(__sqf::unary__confighierarchy__config__ret__array, config_entry_);
            return __helpers::__convert_to_configs_vector(output);
        }

        std::string config_name(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__configname__config__ret__string, config_entry_);
        }

        std::vector<config> config_properties(const config &config_entry, const std::string& condition_, bool inherit) {
            game_value array_entry({
                config_entry,
                condition_,
                inherit
            });
            game_value output = host::functions.invoke_raw_unary(__sqf::unary__configproperties__array__ret__array, array_entry);
            return __helpers::__convert_to_configs_vector(output);
        }

        std::string config_source_mod(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__configsourcemod__config__ret__string, config_entry_);
        }

        std::vector<std::string> config_source_mod_list(const config &config_entry_) {
            game_value output = host::functions.invoke_raw_unary(__sqf::unary__configsourcemodlist__config__ret__array, config_entry_);
            return __helpers::__convert_to_strings_vector(output);
        }

        float count(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__count__config__ret__scalar, config_entry_);
        }

        //std::vector<game_value> get_array(const config &config_entry_) {
        // TODO implement get_array
        //}

        config get_mission_config(const std::string& value_) {
            return config(host::functions.invoke_raw_unary(__sqf::unary__getmissionconfig__string__ret__config, value_));
        }

        float get_number(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getnumber__config__ret__scalar, config_entry_);
        }

        std::string get_text(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__gettext__config__ret__string, config_entry_);
        }

        config inherits_from(const config &config_entry_) {
            return config(host::functions.invoke_raw_unary(__sqf::unary__inheritsfrom__config__ret__config, config_entry_));
        }

        bool is_array(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isarray__config__ret__bool, config_entry_);
        }

        bool is_class(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isclass__config__ret__bool, config_entry_);
        }

        bool is_null(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__config__ret__bool, config_entry_);
        }

        bool is_number(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnumber__config__ret__bool, config_entry_);
        }

        bool is_text(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__istext__config__ret__bool, config_entry_);
        }

        std::vector<std::string> config_classes(const std::string& value_, const config & a_config_) {
            game_value output = host::functions.invoke_raw_binary(__sqf::binary__configclasses__string__config__ret__array, value_, a_config_);
            return __helpers::__convert_to_strings_vector(output);
        }

        config select(const config &a_config_, float a_number_) {
            return config(host::functions.invoke_raw_binary(__sqf::binary__select__config__scalar__ret__config, a_config_, a_number_));
        }

        config campaign_config_file() {
            return config(host::functions.invoke_raw_nular(__sqf::nular__campaignconfigfile__ret__config));
        }

        config config_file() {
            return config(host::functions.invoke_raw_nular(__sqf::nular__configfile__ret__config));
        }

        config config_null() {
            return config(host::functions.invoke_raw_nular(__sqf::nular__confignull__ret__config));
        }

        config mission_config_file() {
            return config(host::functions.invoke_raw_nular(__sqf::nular__missionconfigfile__ret__config));
        }












    }
}
