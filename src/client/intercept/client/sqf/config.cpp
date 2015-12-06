#include "config.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        namespace configs {

            std::vector<config> config_hierarchy(config config_entry_) {
                game_value output = host::functions.invoke_raw_unary(client::__sqf::unary__confighierarchy__config__ret__array, *config_entry_);
                return __helpers::__convert_to_configs_vector(output);
            }

            std::string config_name(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__configname__config__ret__string, *config_entry_);
                std::string rv = ((game_data_string *)ret_value.data)->get_string();
                host::functions.free_value(&ret_value);
                return rv;
            }

            std::vector<config> config_properties(config config_entry, const std::string& condition_ = "true", bool inherit = true) {
                game_value_array<3> array_entry({
                    config_entry->value,
                    game_value_string(condition_),
                    game_value_bool(inherit)
                });
                game_value output = host::functions.invoke_raw_unary(client::__sqf::unary__configproperties__array__ret__array, array_entry);
                return __helpers::__convert_to_configs_vector(output);
            }

            std::string config_source_mod(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__configsourcemod__config__ret__string, *config_entry_);
                std::string rv = ((game_data_string *)ret_value.data)->get_string();
                host::functions.free_value(&ret_value);
                return rv;
            }

            std::vector<std::string> config_source_mod_list(config config_entry_) {
                game_value output = host::functions.invoke_raw_unary(client::__sqf::unary__configsourcemodlist__config__ret__array, *config_entry_);
                return __helpers::__convert_to_strings_vector(output);
            }

            float count(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__count__config__ret__scalar, *config_entry_);
                float rv = ((game_data_number *)ret_value.data)->number;
                host::functions.free_value(&ret_value);
                return rv;
            }

            //std::vector<game_value> get_array(config config_entry_) {
            // TODO implement
            //}

             config get_mission_config(const std::string& value_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__getmissionconfig__string__ret__config, game_value_string(value_));
                return std::make_shared<config_ptr>(ret_value);
            }

            float get_number(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__getnumber__config__ret__scalar, *config_entry_);
                float rv = ((game_data_number *)ret_value.data)->number;
                host::functions.free_value(&ret_value);
                return rv;
            }

            std::string get_text(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__gettext__config__ret__string, *config_entry_);
                std::string rv = ((game_data_string *)ret_value.data)->get_string();
                host::functions.free_value(&ret_value);
                return rv;
            }

            config inherits_from(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__inheritsfrom__config__ret__config, *config_entry_);
                return std::make_shared<config_ptr>(ret_value);
            }

            bool is_array(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isarray__config__ret__bool, *config_entry_);
                bool rv = ((game_data_bool *)ret_value.data)->value;
                host::functions.free_value(&ret_value);
                return rv;
            }

            bool is_class(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isclass__config__ret__bool, *config_entry_);
                bool rv = ((game_data_bool *)ret_value.data)->value;
                host::functions.free_value(&ret_value);
                return rv;
            }

            bool is_null(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnull__config__ret__bool, *config_entry_);
                bool rv = ((game_data_bool *)ret_value.data)->value;
                host::functions.free_value(&ret_value);
                return rv;
            }

            bool is_number(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnumber__config__ret__bool, *config_entry_);
                bool rv = ((game_data_bool *)ret_value.data)->value;
                host::functions.free_value(&ret_value);
                return rv;
            }

            bool is_text(config config_entry_) {
                game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__istext__config__ret__bool, *config_entry_);
                bool rv = ((game_data_bool *)ret_value.data)->value;
                host::functions.free_value(&ret_value);
                return rv;
            }

            std::vector<std::string> config_classes(const std::string& value_, config a_config_) {
                game_value output = host::functions.invoke_raw_binary(client::__sqf::binary__configclasses__string__config__ret__array, game_value_string(value_), *a_config_);
                return __helpers::__convert_to_strings_vector(output);
            }

            void load_overlay(control a_control_, config a_config_) {
                host::functions.invoke_raw_binary(client::__sqf::binary__loadoverlay__control__config__ret__nothing, *a_control_, *a_config_);
            }

            void new_overlay(control a_control_, config a_config_) {
                host::functions.invoke_raw_binary(client::__sqf::binary__newoverlay__control__config__ret__nothing, *a_control_, *a_config_);
            }
            
            config select(config a_config_, float a_number_) {
                game_value ret_value = host::functions.invoke_raw_binary(client::__sqf::binary__select__config__scalar__ret__config, *a_config_, game_value_number(a_number_));
                return std::make_shared<config_ptr>(ret_value);
            }

            config campaign_config_file() {
                game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__campaignconfigfile__ret__config);
                return std::make_shared<config_ptr>(ret_value);
            }

            config config_file() {
                game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__configfile__ret__config);
                return std::make_shared<config_ptr>(ret_value);
            }

            config config_null() {
                game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__confignull__ret__config);
                return std::make_shared<config_ptr>(ret_value);
            }

            config mission_config_file() {
                game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__missionconfigfile__ret__config);
                return std::make_shared<config_ptr>(ret_value);
            }
            
        }
    }
}
