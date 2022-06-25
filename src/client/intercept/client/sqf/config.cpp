#include "config.hpp"
#include <utility>
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        config_entry::config_entry() : _initialized(false) {
        }
        config_entry::config_entry(config entry_) : _config_entry(std::move(entry_)), _initialized(true) {}
        config_entry::config_entry(config_entry const &copy_) {
            _config_entry = copy_._config_entry;
            _initialized = copy_._initialized;
        }
        config_entry::config_entry(config_entry &&move_) noexcept {
            _config_entry = std::move(move_._config_entry);
            _initialized = move_._initialized;
        }
        config_entry &config_entry::operator=(config_entry &&move_) noexcept {
            if (this == &move_)
                return *this;
            _config_entry = std::move(move_._config_entry);
            _initialized = move_._initialized;
            return *this;
        }

        bool config_entry::operator==(const config_entry &other_) const {
            if (_initialized != other_._initialized) return false;
            if (!_initialized) return true;
            return _config_entry == other_._config_entry;
        }

        config_entry config_entry::operator>>(sqf_string_const_ref entry_) const {
            if (!_initialized) {
                _config_entry = host::functions.invoke_raw_nular(__sqf::nular__configfile__ret__config);
                _initialized = true;
            }
            return config_entry(config(host::functions.invoke_raw_binary(__sqf::binary__configaccessor__config__string__ret__config, _config_entry, entry_)));
        }

        config_entry config_entry::operator[](size_t index_) const {
            return sqf::select(*this, index_);
        }

        size_t config_entry::count() const {
            if (!_initialized) return 0;
            return sqf::count(_config_entry);
        }

        config_entry::iterator config_entry::begin() const { return iterator(*this); }
        config_entry::iterator config_entry::end() const { return iterator(*this, count() - 1); }

        config_entry::operator config &() const {
            return _config_entry;
        }

        /* Config */

        std::vector<config> config_hierarchy(const config &config_entry_) {
            game_value output = host::functions.invoke_raw_unary(__sqf::unary__confighierarchy__config__ret__array, config_entry_);
            return __helpers::__convert_to_vector<config>(output);
        }

        sqf_return_string config_name(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__configname__config__ret__string, config_entry_);
        }

        std::vector<config> config_properties(const config &config_entry, sqf_string_const_ref condition_, bool inherit) {
            game_value array_entry({config_entry,
                                    condition_,
                                    inherit});
            game_value output = host::functions.invoke_raw_unary(__sqf::unary__configproperties__array__ret__array, array_entry);
            return __helpers::__convert_to_vector<config>(output);
        }

        sqf_return_string config_source_mod(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__configsourcemod__config__ret__string, config_entry_);
        }

        sqf_return_string_list config_source_mod_list(const config &config_entry_) {
            game_value output = host::functions.invoke_raw_unary(__sqf::unary__configsourcemodlist__config__ret__array, config_entry_);
            return __helpers::__convert_to_vector<sqf_return_string>(output);
        }

        int count(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__count__config__ret__scalar, config_entry_);
        }

        config get_mission_config(sqf_string_const_ref value_) {
            return config(host::functions.invoke_raw_unary(__sqf::unary__getmissionconfig__string__ret__config, value_));
        }

        float get_number(const config &config_entry_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getnumber__config__ret__scalar, config_entry_);
        }

        sqf_return_string get_text(const config &config_entry_) {
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

        std::vector<config> config_classes(sqf_string_const_ref condition_, const config &config_) {
            return __helpers::__convert_to_vector<config>(host::functions.invoke_raw_binary(__sqf::binary__configclasses__string__config__ret__array, condition_, config_));
        }

        config select(const config &a_config_, int a_number_) {
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

        config config_of(const object &obj_) {
            return config(host::functions.invoke_raw_unary(__sqf::unary__configof__object__ret__config, obj_));
        }

        game_value get_array(const config &config_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getarray__config__ret__array, config_);
        }

        game_value get_mission_config_value(sqf_string_const_ref attribute_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getmissionconfigvalue__string_array__ret__array_string, attribute_);
        }

        game_value get_mission_config_value(sqf_string_const_ref attribute_, game_value default_value_) {
            return game_value(
                host::functions.invoke_raw_unary(__sqf::unary__getmissionconfigvalue__string_array__ret__array_string, {attribute_, default_value_}));
        }

        bool is_kind_of(const object &obj_, sqf_string_const_ref type_) {
            return host::functions.invoke_raw_binary(__sqf::binary__iskindof__object__string__ret__bool, obj_, type_);
        }

        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_) {
            return host::functions.invoke_raw_binary(__sqf::binary__iskindof__string__string__ret__bool, type1_, type2_);
        }

        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_, const config &target_config_) {
            game_value params({type2_,
                               target_config_});

            return host::functions.invoke_raw_binary(__sqf::binary__iskindof__string__array__ret__bool, type1_, params);
        }
        sqf_return_string_list config_source_addon_list(const config &config_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__configsourceaddonlist__config__ret__array, config_));
        }

        std::vector<game_value> mod_params(sqf_string_const_ref mod_class_, mod_params_options options_) {
            auto_array<game_value> options;

            if (options_ & mod_params_options::name) options.push_back("name"sv);
            if (options_ & mod_params_options::picture) options.push_back("picture"sv);
            if (options_ & mod_params_options::logo) options.push_back("logo"sv);
            if (options_ & mod_params_options::logoOver) options.push_back("logoOver"sv);
            if (options_ & mod_params_options::logoSmall) options.push_back("logoSmall"sv);
            if (options_ & mod_params_options::tooltip) options.push_back("tooltip"sv);
            if (options_ & mod_params_options::tooltipOwned) options.push_back("tooltipOwned"sv);
            if (options_ & mod_params_options::action) options.push_back("action"sv);
            if (options_ & mod_params_options::actionName) options.push_back("actionName"sv);
            if (options_ & mod_params_options::overview) options.push_back("overview"sv);
            if (options_ & mod_params_options::hidePicture) options.push_back("hidePicture"sv);
            if (options_ & mod_params_options::hideName) options.push_back("hideName"sv);
            if (options_ & mod_params_options::defaultMod) options.push_back("defaultMod"sv);
            if (options_ & mod_params_options::serverOnly) options.push_back("serverOnly"sv);
            if (options_ & mod_params_options::active) options.push_back("active"sv);

            return __helpers::__convert_to_vector<game_value>(
                host::functions.invoke_raw_unary(__sqf::unary__modparams__array__ret__array, {mod_class_, std::move(options)}));
        }
        sqf_return_string type_of(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__typeof__object__ret__string, value_);
        }

        sqf_return_string get_text_raw(const config &config_) {
            return host::functions.invoke_raw_unary(__sqf::unary__gettextraw__config__ret__string, config_);
        }

        config load_config(sqf_string_const_ref file_path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__loadconfig__string__ret__config, file_path_);
        }

    }  // namespace sqf
}  // namespace intercept
