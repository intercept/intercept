#include "ctrl.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        int tv_add(int idc_, const std::vector<int> &path_, sqf_string_const_ref text_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               text_});

            return host::functions.invoke_raw_unary(__sqf::unary__tvadd__array__ret__scalar, params);
        }

        int tv_add(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref text_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               text_});

            return host::functions.invoke_raw_binary(__sqf::binary__tvadd__control__array__ret__scalar, ctrl_, params);
        }

        std::vector<int> tv_cursel(int idc_) {
            return __helpers::__convert_to_vector<int>(host::functions.invoke_raw_unary(__sqf::unary__tvcursel__scalar__ret__array, static_cast<float>(idc_)));
        }

        std::vector<int> tv_cursel(const control &ctrl_) {
            return __helpers::__convert_to_vector<int>(host::functions.invoke_raw_unary(__sqf::unary__tvcursel__control__ret__array, ctrl_));
        }

        std::vector<std::vector<int>> tv_selection(const control &ctrl_) {
            auto game_array = host::functions.invoke_raw_unary(__sqf::unary__tvselection__control__ret__array, ctrl_).to_array();
            std::vector<std::vector<int>> paths;
            paths.reserve(game_array.size());
            for (auto& gv : game_array) {
                paths.emplace_back(__helpers::__convert_to_vector<int>(gv));
            }
            return paths;
        }

        void tv_collapse(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            host::functions.invoke_raw_unary(__sqf::unary__tvcollapse__array__ret__nothing, params);
        }

        void tv_collapse(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            host::functions.invoke_raw_binary(__sqf::binary__tvcollapse__control__array__ret__nothing, ctrl_, std::move(path));
        }

        int tv_count(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            return host::functions.invoke_raw_unary(__sqf::unary__tvcount__array__ret__scalar, params);
        }

        int tv_count(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__tvcount__control__array__ret__scalar, ctrl_, std::move(path));
        }

        sqf_return_string tv_data(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            return host::functions.invoke_raw_unary(__sqf::unary__tvdata__array__ret__string, params);
        }

        sqf_return_string tv_data(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__tvdata__control__array__ret__string, ctrl_, std::move(path));
        }

        void tv_delete(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            host::functions.invoke_raw_unary(__sqf::unary__tvdelete__array__ret__nothing, params);
        }

        void tv_delete(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            host::functions.invoke_raw_binary(__sqf::binary__tvdelete__control__array__ret__nothing, ctrl_, std::move(path));
        }

        void tv_expand(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            host::functions.invoke_raw_unary(__sqf::unary__tvexpand__array__ret__nothing, params);
        }

        void tv_expand(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            host::functions.invoke_raw_binary(__sqf::binary__tvexpand__control__array__ret__nothing, ctrl_, std::move(path));
        }

        sqf_return_string tv_picture(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            return host::functions.invoke_raw_unary(__sqf::unary__tvpicture__array__ret__string, params);
        }

        sqf_return_string tv_picture(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__tvpicture__control__array__ret__string, ctrl_, std::move(path));
        }

        sqf_return_string tv_picture_right(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            return host::functions.invoke_raw_unary(__sqf::unary__tvpictureright__array__ret__string, params);
        }

        sqf_return_string tv_picture_right(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__tvpictureright__control__array__ret__string, ctrl_, std::move(path));
        }

        void tv_set_cur_sel(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            host::functions.invoke_raw_unary(__sqf::unary__tvsetcursel__array__ret__nothing, params);
        }

        void tv_set_cur_sel(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            host::functions.invoke_raw_binary(__sqf::binary__tvsetcursel__control__array__ret__nothing, ctrl_, std::move(path));
        }

        void tv_set_data(int idc_, const std::vector<int> &path_, sqf_string_const_ref data_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               data_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsetdata__array__ret__nothing, params);
        }

        void tv_set_data(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref data_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               data_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsetdata__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture(int idc_, const std::vector<int> &path_, sqf_string_const_ref name_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               name_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsetpicture__array__ret__nothing, params);
        }

        void tv_set_picture(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref name_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               name_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsetpicture__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture_right(int idc_, const std::vector<int> &path_, sqf_string_const_ref name_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               name_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsetpictureright__array__ret__nothing, params);
        }

        void tv_set_picture_right(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref name_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               name_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsetpictureright__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture_color(int idc_, const std::vector<int> &path_, const rv_color &color_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsetpicturecolor__array__ret__nothing, params);
        }

        void tv_set_picture_color(const control &ctrl_, const std::vector<int> &path_, const rv_color &color_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsetpicturecolor__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture_right_color(int idc_, const std::vector<int> &path_, const rv_color &color_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsetpicturerightcolor__array__ret__nothing, params);
        }

        void tv_set_picture_right_color(const control &ctrl_, const std::vector<int> &path_, const rv_color &color_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsetpicturerightcolor__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_tooltip(int idc_, const std::vector<int> &path_, sqf_string_const_ref text_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               text_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsettooltip__array__ret__nothing, params);
        }

        void tv_set_tooltip(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref text_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               text_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsettooltip__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_value(int idc_, const std::vector<int> &path_, float value_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path),
                               value_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsetvalue__array__ret__nothing, params);
        }

        void tv_set_value(const control &ctrl_, const std::vector<int> &path_, float value_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               value_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsetvalue__control__array__ret__nothing, ctrl_, params);
        }

        void tv_sort(const control &ctrl_, const std::vector<int> &path_, bool reversed_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               reversed_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsort__control__array__ret__nothing, ctrl_, params);
        }

        void tv_sort_by_value(const control &ctrl_, const std::vector<int> &path_, bool reversed_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({std::move(path),
                               reversed_});

            host::functions.invoke_raw_binary(__sqf::binary__tvsortbyvalue__control__array__ret__nothing, ctrl_, params);
        }

        sqf_return_string tv_text(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            return host::functions.invoke_raw_unary(__sqf::unary__tvtext__array__ret__string, params);
        }

        sqf_return_string tv_text(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__tvtext__control__array__ret__string, ctrl_, std::move(path));
        }

        float tv_value(int idc_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(path)});

            return host::functions.invoke_raw_unary(__sqf::unary__tvvalue__array__ret__scalar, params);
        }

        float tv_value(const control &ctrl_, const std::vector<int> &path_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__tvvalue__control__array__ret__scalar, ctrl_, std::move(path));
        }

        void tv_set_color(const control &control_, const std::vector<int> &path_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsetcolor__control__array__ret__nothing, control_, {std::move(auto_array<game_value>(path_.begin(), path_.end())), color_});
        }

        void tv_set_picture_color_disabled(const control &control_, const std::vector<int> &path_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsetpicturecolordisabled__control__array__ret__nothing, control_, {std::move(auto_array<game_value>(path_.begin(), path_.end())), color_});
        }

        void tv_set_picture_color_selected(const control &control_, const std::vector<int> &path_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsetpicturecolorselected__control__array__ret__nothing, control_, {std::move(auto_array<game_value>(path_.begin(), path_.end())), color_});
        }

        void tv_set_picture_color__right_disabled(const control &control_, const std::vector<int> &path_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsetpicturerightcolordisabled__control__array__ret__nothing, control_, {std::move(auto_array<game_value>(path_.begin(), path_.end())), color_});
        }

        void tv_set_picture_color__right_selected(const control &control_, const std::vector<int> &path_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsetpicturerightcolorselected__control__array__ret__nothing, control_, {std::move(auto_array<game_value>(path_.begin(), path_.end())), color_});
        }

        void tv_set_select_color(const control &control_, const std::vector<int> &path_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsetselectcolor__control__array__ret__nothing, control_, {std::move(auto_array<game_value>(path_.begin(), path_.end())), color_});
        }

        void tv_set_text(const control &control_, const std::vector<int> &path_, sqf_string_const_ref text_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsettext__control__array__ret__nothing, control_, {std::move(auto_array<game_value>(path_.begin(), path_.end())), text_});
        }

        sqf_return_string tv_tooltip(const control &control_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__tvtooltip__control__array__ret__string, control_, std::move(auto_array<game_value>(path_.begin(), path_.end())));
        }

        void tv_collapse_all(int idc_) {
            host::functions.invoke_raw_unary(__sqf::unary__tvcollapseall__scalar__ret__nothing, static_cast<float>(idc_));
        }

        void tv_collapse_all(const control &control_) {
            host::functions.invoke_raw_unary(__sqf::unary__tvcollapseall__control__ret__nothing, control_);
        }

        void tv_expand_all(int idc_) {
            host::functions.invoke_raw_unary(__sqf::unary__tvexpandall__scalar__ret__nothing, static_cast<float>(idc_));
        }

        void tv_expand_all(const control &control_) {
            host::functions.invoke_raw_unary(__sqf::unary__tvexpandall__control__ret__nothing, control_);
        }

        void ctrl_activate(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__ctrlactivate__control__ret__nothing, value_);
        }

        float ctrl_auto_scroll_delay(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrlautoscrolldelay__control__ret__scalar, value_);
        }

        bool ctrl_auto_scroll_rewind(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrlautoscrollrewind__control__ret__bool, value_);
        }

        float ctrl_auto_scroll_speed(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrlautoscrollspeed__control__ret__scalar, value_);
        }

        bool ctrl_checked(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrlchecked__control__ret__bool, value_);
        }

        sqf_return_string ctrl_class_name(const control &value_) {
            return __helpers::__string_unary_control(__sqf::unary__ctrlclassname__control__ret__string, value_);
        }

        bool ctrl_committed(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrlcommitted__control__ret__bool, value_);
        }

        bool ctrl_delete(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrldelete__control__ret__bool, value_);
        }

        bool ctrl_enabled(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrlenabled__control__ret__bool, value_);
        }

        bool ctrl_enabled(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__ctrlenabled__scalar__ret__bool, value_);
        }

        void ctrl_set_disabled_color(const control &control_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetdisabledcolor__control__array__ret__nothing, control_, color_);
        }

        float ctrl_fade(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrlfade__control__ret__scalar, value_);
        }

        bool ctrl_htmlloaded(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrlhtmlloaded__control__ret__bool, value_);
        }

        float ctrl_idc(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrlidc__control__ret__scalar, value_);
        }

        float ctrl_idd(const display &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlidd__display__ret__scalar, value_);
        }

        void ctrl_map_anim_clear(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__ctrlmapanimclear__control__ret__nothing, value_);
        }

        void ctrl_map_anim_commit(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__ctrlmapanimcommit__control__ret__nothing, value_);
        }

        bool ctrl_map_anim_done(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrlmapanimdone__control__ret__bool, value_);
        }

        float ctrl_map_scale(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrlmapscale__control__ret__scalar, value_);
        }

        sqf_return_string ctrl_model(const control &value_) {
            return __helpers::__string_unary_control(__sqf::unary__ctrlmodel__control__ret__string, value_);
        }

        float ctrl_model_scale(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrlmodelscale__control__ret__scalar, value_);
        }

        display ctrl_parent(const control &value_) {
            return display(host::functions.invoke_raw_unary(__sqf::unary__ctrlparent__control__ret__display, value_));
        }

        control ctrl_parent_controls_group(const control &value_) {
            return control(host::functions.invoke_raw_unary(__sqf::unary__ctrlparentcontrolsgroup__control__ret__control, value_));
        }

        float ctrl_scale(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrlscale__control__ret__scalar, value_);
        }

        void ctrl_set_focus(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__ctrlsetfocus__control__ret__nothing, value_);
        }

        bool ctrl_shown(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__ctrlshown__control__ret__bool, value_);
        }

        sqf_return_string ctrl_text(const control &value_) {
            return __helpers::__string_unary_control(__sqf::unary__ctrltext__control__ret__string, value_);
        }

        sqf_return_string ctrl_text(float value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrltext__scalar__ret__string, value_);
        }

        float ctrl_text_height(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrltextheight__control__ret__scalar, value_);
        }

        sqf_return_string ctrl_text_secondary(const control &value_) {
            return __helpers::__string_unary_control(__sqf::unary__ctrltextsecondary__control__ret__string, value_);
        }

        float ctrl_type(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__ctrltype__control__ret__scalar, value_);
        }

        bool ctrl_visible(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__ctrlvisible__scalar__ret__bool, value_);
        }

        void ctrl_commit(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlcommit__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_enable(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlenable__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_enable(int control_id_, bool enable_) {
            game_value params({static_cast<float>(control_id_),
                               enable_});

            host::functions.invoke_raw_unary(__sqf::unary__ctrlenable__array__ret__nothing, params);
        }

        void ctrl_remove_all_event_handlers(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlremovealleventhandlers__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_auto_scroll_delay(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetautoscrolldelay__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_auto_scroll_rewind(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetautoscrollrewind__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_set_auto_scroll_speed(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetautoscrollspeed__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_checked(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetchecked__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_set_fade(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfade__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfont__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h1(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth1__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h1b(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth1b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h2(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth2__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h2b(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth2b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h3(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth3__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h3b(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth3b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h4(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth4__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h4b(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth4b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h5(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth5__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h5b(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth5b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h6(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth6__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h6b(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfonth6b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheight__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h1(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheighth1__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h2(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheighth2__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h3(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheighth3__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h4(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheighth4__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h5(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheighth5__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h6(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheighth6__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_secondary(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontheightsecondary__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_p(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontp__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_p(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontp__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_pb(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontpb__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_secondary(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetfontsecondary__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_model(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetmodel__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_model_scale(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetmodelscale__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_scale(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetscale__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_structured_text(const control &value0_, const rv_text &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetstructuredtext__control__text__ret__nothing, value0_, value1_);
        }

        void ctrl_set_text(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettext__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_text(int control_id_, sqf_string_const_ref text_) {
            game_value params({static_cast<float>(control_id_),
                               text_});

            host::functions.invoke_raw_unary(__sqf::unary__ctrlsettext__array__ret__nothing, params);
        }

        void ctrl_set_text_secondary(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettextsecondary__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_tooltip(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettooltip__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_show(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlshow__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_show(int control_id_, bool show_) {
            game_value params({static_cast<float>(control_id_),
                               show_});
            host::functions.invoke_raw_unary(__sqf::unary__ctrlshow__array__ret__nothing, params);
        }

        void lnb_clear(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__lnbclear__control__ret__nothing, value_);
        }

        void lnb_clear(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__lnbclear__scalar__ret__nothing, value_);
        }

        float lnb_cur_sel_row(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__lnbcurselrow__control__ret__scalar, value_);
        }

        float lnb_cur_sel_row(float value_) {
            return __helpers::__number_unary_number(__sqf::unary__lnbcurselrow__scalar__ret__scalar, value_);
        }

        float lnb_add_column(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lnbaddcolumn__control__scalar__ret__scalar, value0_, value1_);
        }

        void lnb_delete_column(const control &ctrl_, float index_) {
            host::functions.invoke_raw_binary(__sqf::binary__lnbdeletecolumn__control__scalar__ret__nothing, ctrl_, index_);
        }

        void lnb_delete_row(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lnbdeleterow__control__scalar__ret__nothing, value0_, value1_);
        }

        void lnb_set_cur_sel_row(float idc_, float index_) {
            game_value params{
                idc_,
                index_};

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetcurselrow__array__ret__nothing, params);
        }

        void lnb_set_cur_sel_row(const control &ctrl_, float index_) {
            host::functions.invoke_raw_binary(__sqf::binary__lnbsetcurselrow__control__scalar__ret__nothing, ctrl_, index_);
        }

        float lnb_add_array(float idc_, const std::vector<rv_lnb_array> &lnb_array_) {
            auto_array<game_value> lnb_array(lnb_array_.begin(), lnb_array_.end());

            game_value params{
                idc_,
                std::move(lnb_array)};

            return host::functions.invoke_raw_unary(__sqf::unary__lnbaddarray__array__ret__scalar, params);
        }

        float lnb_add_array(const control &ctrl_, const std::vector<rv_lnb_array> &lnb_array_) {
            auto_array<game_value> lnb_array(lnb_array_.begin(), lnb_array_.end());

            game_value params{
                ctrl_,
                std::move(lnb_array)};

            return host::functions.invoke_raw_unary(__sqf::unary__lnbaddarray__array__ret__scalar, params);
        }

        float lnb_add_row(float idc_, sqf_string_list_const_ref strings_) {
            auto_array<game_value> strings(strings_.begin(), strings_.end());

            game_value params{
                idc_,
                std::move(strings)};

            return host::functions.invoke_raw_unary(__sqf::unary__lnbaddcolumn__array__ret__scalar, params);
        }

        float lnb_add_row(const control &ctrl_, sqf_string_list_const_ref strings_) {
            auto_array<game_value> strings(strings_.begin(), strings_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__lnbaddrow__control__array__ret__scalar, ctrl_, std::move(strings));
        }

        rv_color lnb_color(float idc_, float row_, float column_) {
            game_value params({idc_,
                               {row_,
                                column_}});

            return rv_color(host::functions.invoke_raw_unary(__sqf::unary__lnbcolor__array__ret__array, params));
        }

        rv_color lnb_color(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return rv_color(host::functions.invoke_raw_binary(__sqf::binary__lnbcolor__control__array__ret__array, ctrl_, params));
        }

        rv_color lnb_color_right(float idc_, float row_, float column_) {
            game_value params({idc_,
                               {row_,
                                column_}});

            return rv_color(host::functions.invoke_raw_unary(__sqf::unary__lnbcolorright__array__ret__array, params));
        }

        rv_color lnb_color_right(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return rv_color(host::functions.invoke_raw_binary(__sqf::binary__lnbcolorright__control__array__ret__array, ctrl_, params));
        }

        void lnb_sort(float idc_, int column_, bool reversed_) {
            host::functions.invoke_raw_unary(__sqf::unary__lnbdata__array__ret__string, { idc_ , column_ ,reversed_ });
        }

        void lnb_sort(const control &ctrl_, int column_, bool reversed_) {
            host::functions.invoke_raw_binary(__sqf::binary__lnbsort__control__array__ret__nothing, ctrl_, { column_ ,reversed_ });
        }

        void lnb_sort_by_value(float idc_, int column_, bool reversed_) {
            host::functions.invoke_raw_unary(__sqf::unary__lnbdata__array__ret__string, { idc_ ,column_ ,reversed_ });
        }

        void lnb_sort_by_value(const control &ctrl_, int column_, bool reversed_) {
            host::functions.invoke_raw_binary(__sqf::binary__lnbsortbyvalue__control__array__ret__nothing, ctrl_, { column_ ,reversed_ });
        }

        void lnb_sort_by(const control &ctrl_, int column_, sqf_string_const_ref sort_type_, bool reversed_, bool case_sensitive_) {
            host::functions.invoke_raw_binary(__sqf::binary__lnbsortby__array__array__ret__nothing, {ctrl_, column_}, {sort_type_, reversed_, case_sensitive_});
        }

        void lnb_sort_by(int ctrl_, int column_, sqf_string_const_ref sort_type_, bool reversed_, bool case_sensitive_) {
            host::functions.invoke_raw_binary(__sqf::binary__lnbsortby__array__array__ret__nothing, {ctrl_, column_}, {sort_type_, reversed_, case_sensitive_});
        }

        sqf_return_string lnb_data(float idc_, float row_, float column_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item});

            return host::functions.invoke_raw_unary(__sqf::unary__lnbdata__array__ret__string, params);
        }

        sqf_return_string lnb_data(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return host::functions.invoke_raw_binary(__sqf::binary__lnbdata__control__array__ret__string, ctrl_, params);
        }

        void lnb_delete_column(float idc_, float index_) {
            game_value params({idc_,
                               index_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbdeletecolumn__array__ret__nothing, params);
        }

        void lnb_delete_row(float idc_, float index_) {
            game_value params({idc_,
                               index_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbdeleterow__array__ret__nothing, params);
        }

        std::vector<float> lnb_get_columns_position(float idc_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__lnbgetcolumnsposition__scalar__ret__array, idc_));
        }

        std::vector<float> lnb_get_columns_position(const control &ctrl_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__lnbgetcolumnsposition__control__ret__array, ctrl_));
        }

        sqf_return_string lnb_picture(float idc_, float row_, float column_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item});

            return host::functions.invoke_raw_unary(__sqf::unary__lnbpicture__array__ret__string, params);
        }

        sqf_return_string lnb_picture(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return host::functions.invoke_raw_binary(__sqf::binary__lnbpicture__control__array__ret__string, ctrl_, params);
        }

        sqf_return_string lnb_picture_right(float idc_, float row_, float column_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item});

            return host::functions.invoke_raw_unary(__sqf::unary__lnbpictureright__array__ret__string, params);
        }

        sqf_return_string lnb_picture_right(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return host::functions.invoke_raw_binary(__sqf::binary__lnbpictureright__control__array__ret__string, ctrl_, params);
        }

        std::vector<float> lnb_size(float idc_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__lnbsize__control__ret__array, idc_));
        }

        std::vector<float> lnb_size(const control &ctrl_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__lnbsize__scalar__ret__array, ctrl_));
        }

        sqf_return_string lnb_text(float idc_, float row_, float column_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item});

            return host::functions.invoke_raw_unary(__sqf::unary__lnbtext__array__ret__string, params);
        }

        sqf_return_string lnb_text(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return host::functions.invoke_raw_binary(__sqf::binary__lnbtext__control__array__ret__string, ctrl_, params);
        }

        sqf_return_string lnb_text_right(float idc_, float row_, float column_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item});

            return host::functions.invoke_raw_unary(__sqf::unary__lnbtextright__array__ret__string, params);
        }

        sqf_return_string lnb_text_right(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return host::functions.invoke_raw_binary(__sqf::binary__lnbtextright__control__array__ret__string, ctrl_, params);
        }

        float lnb_value(float idc_, float row_, float column_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item});

            return host::functions.invoke_raw_unary(__sqf::unary__lnbvalue__array__ret__scalar, params);
        }

        float lnb_value(const control &ctrl_, float row_, float column_) {
            game_value params({row_,
                               column_});

            return host::functions.invoke_raw_binary(__sqf::binary__lnbvalue__control__array__ret__scalar, ctrl_, params);
        }

        void lnb_set_color(float idc_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetcolor__array__ret__nothing, params);
        }

        void lnb_set_color(const control &ctrl_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetcolor__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_picture_color(float idc_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetpicturecolor__array__ret__nothing, params);
        }

        void lnb_set_picture_color(const control &ctrl_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetpicturecolor__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_picture_color_right(float idc_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetpicturecolorright__array__ret__nothing, params);
        }

        void lnb_set_picture_color_right(const control &ctrl_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetpicturecolorright__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_picture_color_selected(float idc_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetpicturecolorselected__array__ret__nothing, params);
        }

        void lnb_set_picture_color_selected(const control &ctrl_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetpicturecolorselected__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_picture_color_selected_right(float idc_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetpicturecolorselectedright__array__ret__nothing, params);
        }

        void lnb_set_picture_color_selected_right(const control &ctrl_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetpicturecolorselectedright__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_color_right(float idc_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               color_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetcolorright__array__ret__nothing, params);
        }

        void lnb_set_color_right(const control &ctrl_, float row_, float column_, const rv_color &color_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               color_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetcolorright__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_columns_pos(float idc_, std::vector<float> positions_) {
            auto_array<game_value> positions(positions_.begin(), positions_.end());

            game_value params({idc_,
                               std::move(positions)});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetcolumnspos__array__ret__nothing, params);
        }

        void lnb_set_columns_pos(const control &ctrl_, std::vector<float> positions_) {
            auto_array<game_value> positions(positions_.begin(), positions_.end());

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetcolumnspos__control__array__ret__nothing, ctrl_, std::move(positions));
        }

        void lnb_set_data(float idc_, float row_, float column_, sqf_string_const_ref data_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               data_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetdata__array__ret__nothing, params);
        }

        void lnb_set_data(const control &ctrl_, float row_, float column_, sqf_string_const_ref data_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               data_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetdata__control__array__ret__nothing, ctrl_, params);
            // Same as: binary__lnbsetdata__control__array__ret__nothing
        }

        void lnb_set_picture(float idc_, float row_, float column_, sqf_string_const_ref name_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               name_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetpicture__array__ret__nothing, params);
        }

        void lnb_set_picture(const control &ctrl_, float row_, float column_, sqf_string_const_ref name_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               name_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetpicture__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_picture_right(float idc_, float row_, float column_, sqf_string_const_ref name_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               name_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetpictureright__array__ret__nothing, params);
        }

        void lnb_set_picture_right(const control &ctrl_, float row_, float column_, sqf_string_const_ref name_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               name_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetpictureright__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_text(float idc_, float row_, float column_, const game_value &data_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               data_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsettext__array__ret__nothing, params);
        }

        void lnb_set_text(const control &ctrl_, float row_, float column_, const game_value &data_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               data_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsettext__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_text_right(float idc_, float row_, float column_, const game_value &data_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               data_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsettextright__array__ret__nothing, params);
        }

        void lnb_set_text_right(const control &ctrl_, float row_, float column_, const game_value &data_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               data_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsettextright__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_tooltip(float idc_, float row_, float column_, const game_value &data_) {
            game_value item({row_,
                 column_});

            game_value params({idc_,
                               item,
                               data_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsettooltip__array__ret__nothing, params);
        }

        void lnb_set_tooltip(const control &ctrl_, float row_, float column_, const game_value &data_) {
            game_value item({row_,
                 column_});

            game_value params({item,
                               data_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsettooltip__control__array__ret__nothing, ctrl_, params);
        }

        void lnb_set_value(float idc_, float row_, float column_, float value_) {
            game_value item({row_,
                             column_});

            game_value params({idc_,
                               item,
                               value_});

            host::functions.invoke_raw_unary(__sqf::unary__lnbsetvalue__array__ret__nothing, params);
        }

        void lnb_set_value(const control &ctrl_, float row_, float column_, float value_) {
            game_value item({row_,
                             column_});

            game_value params({item,
                               value_});

            host::functions.invoke_raw_binary(__sqf::binary__lnbsetvalue__control__array__ret__nothing, ctrl_, params);
        }

        void tv_clear(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__tvclear__scalar__ret__nothing, value_);
        }

        void tv_clear(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__tvclear__control__ret__nothing, value_);
        }

        void tv_set_text(float idc_, const std::vector<float> &path_, sqf_string_const_ref text_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({idc_,
                               std::move(path),
                               text_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsettext__array__ret__string, params);
        }

        void tv_set_text(const control &ctrl_, const std::vector<float> &path_, sqf_string_const_ref text_) {
            auto_array<game_value> path(path_.begin(), path_.end());

            game_value params({ctrl_,
                               std::move(path),
                               text_});

            host::functions.invoke_raw_unary(__sqf::unary__tvsettext__array__ret__string, params);
        }

        void ctrl_set_position(const control &ctrl_, float x_, float y_, float width_, float height_) {
            game_value args({x_,
                             y_,
                             width_,
                             height_});
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetposition__control__array__ret__nothing, ctrl_, args);
        }

        void ctrl_set_positionh(const control &ctrl_, float height_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetpositionh__control__scalar__ret__nothing, ctrl_, height_);
        }
        void ctrl_set_positionw(const control &ctrl_, float width_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetpositionw__control__scalar__ret__nothing, ctrl_, width_);
        }
        void ctrl_set_positionx(const control &ctrl_, float x_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetpositionx__control__scalar__ret__nothing, ctrl_, x_);
        }
        void ctrl_set_positiony(const control &ctrl_, float y_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetpositiony__control__scalar__ret__nothing, ctrl_, y_);
        }

        void ctrl_map_anim_add(const control &ctrl_, float time_, float zoom_, vector2 pos_) {
            game_value args({time_,
                             zoom_,
                             pos_});
            host::functions.invoke_raw_binary(__sqf::binary__ctrlmapanimadd__control__array__ret__nothing, ctrl_, args);
        }

        vector2 ctrl_map_screen_to_world(const control &ctrl_, const vector2 &screen_pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ctrlmapscreentoworld__control__array__ret__array, ctrl_, screen_pos_);
        }

        void draw_rectangle(const control &ctrl_, vector2 center_pos_, float a_, float b_, float angle_, const rv_color &color_, sqf_string_const_ref fill_texture_) {
            game_value args({center_pos_,
                             a_,
                             b_,
                             angle_,
                             color_,
                             fill_texture_});
            host::functions.invoke_raw_binary(__sqf::binary__drawrectangle__control__array__ret__nothing, ctrl_, args);
        }

        void draw_icon(const control &ctrl_, sqf_string_const_ref texture_, const rv_color &color_, const vector2 &pos_, float width_, float height_, float angle_, sqf_string_const_ref text_, uint32_t shadow_, float text_size_, sqf_string_const_ref font_, sqf_string_const_ref align_) {
            game_value args({texture_,
                             color_,
                             pos_,
                             width_,
                             height_,
                             angle_,
                             text_,
                             static_cast<float>(shadow_),
                             text_size_,
                             font_,
                             align_});
            host::functions.invoke_raw_binary(__sqf::binary__drawicon__control__array__ret__nothing, ctrl_, args);
        }

        void draw_icon(const control &ctrl_, sqf_string_const_ref texture_, const rv_color &color_, const object &pos_, float width_, float height_, float angle_, sqf_string_const_ref text_, uint32_t shadow_, float text_size_, sqf_string_const_ref font_, sqf_string_const_ref align_) {
            game_value args({texture_,
                             color_,
                             pos_,
                             width_,
                             height_,
                             angle_,
                             text_,
                             static_cast<float>(shadow_),
                             text_size_,
                             font_,
                             align_});
            host::functions.invoke_raw_binary(__sqf::binary__drawicon__control__array__ret__nothing, ctrl_, args);
        }

        void cb_set_checked(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__cbsetchecked__control__bool__ret__nothing, value0_, value1_);
        }

        void close_display(float value0_, const display &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__closedisplay__display__scalar__ret__nothing, value0_, value1_);
        }

        control controls_group_ctrl(const control &value0_, float value1_) {
            return control(host::functions.invoke_raw_binary(__sqf::binary__controlsgroupctrl__control__scalar__ret__control, value0_, value1_));
        }

        display create_display(sqf_string_const_ref value0_, const display &value1_) {
            return display(host::functions.invoke_raw_binary(__sqf::binary__createdisplay__display__string__ret__display, value0_, value1_));
        }

        void create_menu(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__createmenu__control__scalar__ret__nothing, value0_, value1_);
        }

        display create_mission_display(sqf_string_const_ref value0_, const display &value1_) {
            return display(host::functions.invoke_raw_binary(__sqf::binary__createmissiondisplay__display__string__ret__display, value0_, value1_));
        }

        control display_ctrl(const display &disp_, float idc_) {
            return control(host::functions.invoke_raw_binary(__sqf::binary__displayctrl__display__scalar__ret__control, disp_, idc_));
        }

        control display_ctrl(float idc_) {
            return control(host::functions.invoke_raw_unary(__sqf::unary__displayctrl__scalar__ret__control, idc_));
        }

        vector2 slider_range(const float &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__sliderrange__scalar__ret__array, value_);
        }

        vector2 slider_range(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__sliderrange__control__ret__array, ctrl_);
        }

        void slider_set_range(float value0_, float value1_, float value2_) {
            game_value args({value0_,
                             value1_,
                             value2_});

            host::functions.invoke_raw_unary(__sqf::unary__slidersetrange__array__ret__nothing, args);
        }

        void slider_set_range(const control &slider_, float min_, float max_) {
            host::functions.invoke_raw_binary(__sqf::binary__slidersetrange__control__array__ret__nothing, slider_, {min_, max_});
        }

        vector2 slider_speed(const float &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__sliderspeed__scalar__ret__array, value_);
        }

        vector2 slider_speed(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__sliderspeed__control__ret__array, ctrl_);
        }

        void slider_set_speed(float value0_, float value1_, float value2_) {
            game_value args({value0_,
                             value1_,
                             value2_});

            host::functions.invoke_raw_unary(__sqf::unary__slidersetspeed__array__ret__nothing, args);
        }

        void slider_set_speed(const control &value0_, float value1_, float value2_) {
            game_value args({value0_,
                             value1_,
                             value2_});

            host::functions.invoke_raw_unary(__sqf::unary__slidersetspeed__array__ret__nothing, args);
        }
        control ctrl_create(const display &display_, sqf_string_const_ref class_, int idc_) {
            game_value params({class_,
                               static_cast<float>(idc_)});

            return host::functions.invoke_raw_binary(__sqf::binary__ctrlcreate__display__array__ret__control, display_, params);
        }

        control ctrl_create(const display &display_, sqf_string_const_ref class_, int idc_, const control &controls_group_) {
            game_value params({class_,
                               static_cast<float>(idc_),
                               controls_group_});

            return host::functions.invoke_raw_binary(__sqf::binary__ctrlcreate__display__array__ret__control, display_, params);
        }

        void ctrl_map_cursor(const control &ctrl_, sqf_string_const_ref default_cursor_, sqf_string_const_ref new_cursor_) {
            game_value params({default_cursor_,
                               new_cursor_});

            host::functions.invoke_raw_binary(__sqf::binary__ctrlmapcursor__control__array__ret__nothing, ctrl_, params);
        }

        vector2 ctrl_map_world_to_screen(const control &ctrl_, const std::variant<vector2, vector3> &position_) {
            if (position_.index() == 0)
                return host::functions.invoke_raw_binary(__sqf::binary__ctrlmapworldtoscreen__control__array__ret__array, ctrl_, std::get<vector2>(position_));
            else
                return host::functions.invoke_raw_binary(__sqf::binary__ctrlmapworldtoscreen__control__array__ret__array, ctrl_, std::get<vector3>(position_));
        }

        void ctrl_set_active_color(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetactivecolor__control__array__ret__nothing, ctrl_, color_);
        }

        void ctrl_set_background_color(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetbackgroundcolor__control__array__ret__nothing, ctrl_, color_);
        }

        void ctrl_set_foreground_color(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetforegroundcolor__control__array__ret__nothing, ctrl_, color_);
        }

        void ctrl_set_model_dir_and_up(const control &ctrl_, const vector3 &dir_, const vector3 &up_) {
            game_value params({dir_,
                               up_});

            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetmodeldirandup__control__array__ret__nothing, ctrl_, params);
        }

        void ctrl_set_text_color(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettextcolor__control__array__ret__nothing, ctrl_, color_);
        }

        void ctrl_set_tooltip_color_box(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettooltipcolorbox__control__array__ret__nothing, ctrl_, color_);
        }

        void ctrl_set_tooltip_color_shade(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettooltipcolorshade__control__array__ret__nothing, ctrl_, color_);
        }

        void ctrl_set_tooltip_color_text(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettooltipcolortext__control__array__ret__nothing, ctrl_, color_);
        }

        float ctrl_set_tooltip_max_width(const control &ctrl_, float width_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ctrlsettooltipmaxwidth__control__scalar__ret__scalar, ctrl_, width_);
        }

        vector2 pos_screen_to_world(const control &ctrl_, const vector2 &pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__posscreentoworld__control__array__ret__array, ctrl_, pos_);
        }

        vector2 pos_world_to_screen(const control &ctrl_, const vector2 &pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__posworldtoscreen__control__array__ret__array, ctrl_, pos_);
        }

        std::vector<vector3> ctrl_model_dir_and_up(const control &ctrl_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__ctrlmodeldirandup__control__ret__array, ctrl_);
            return __helpers::__convert_to_vector<vector3>(ret);
        }

        rv_ctrl_position ctrl_position(const control &ctrl_) {
            return rv_ctrl_position(host::functions.invoke_raw_unary(__sqf::unary__ctrlposition__control__ret__array, ctrl_));
        }

        int ctrl_add_event_handler(const control &ctrl_, sqf_string_const_ref name_, sqf_string_const_ref command_) {
            game_value params({name_,
                               command_});

            return host::functions.invoke_raw_binary(__sqf::binary__ctrladdeventhandler__control__array__ret__scalar, ctrl_, params);
        }

        int ctrl_add_event_handler(const control &ctrl_, sqf_string_const_ref name_, const code &command_) {
            game_value params({name_,
                               command_});

            return host::functions.invoke_raw_binary(__sqf::binary__ctrladdeventhandler__control__array__ret__scalar, ctrl_, params);
        }

        void ctrl_remove_event_handler(const control &ctrl_, sqf_string_const_ref name_, int id_) {
            game_value params({name_,
                               id_});

            host::functions.invoke_raw_binary(__sqf::binary__ctrlremoveeventhandler__control__array__ret__nothing, ctrl_, params);
        }

        void ctrl_set_event_handler(const control &ctrl_, sqf_string_const_ref name_, sqf_string_const_ref command_) {
            game_value params({name_,
                               command_});

            host::functions.invoke_raw_binary(__sqf::binary__ctrlseteventhandler__control__array__ret__nothing, ctrl_, params);
        }

        rv_color ctrl_background_color(const control &ctrl_) {
            return rv_color(host::functions.invoke_raw_unary(__sqf::unary__ctrlbackgroundcolor__control__ret__array, ctrl_));
        }

        rv_color ctrl_foreground_color(const control &ctrl_) {
            return rv_color(host::functions.invoke_raw_unary(__sqf::unary__ctrlforegroundcolor__control__ret__array, ctrl_));
        }

        void button_set_action(int control_id_, sqf_string_const_ref code_) {
            game_value params({static_cast<float>(control_id_),
                               code_});

            host::functions.invoke_raw_unary(__sqf::unary__buttonsetaction__array__ret__nothing, params);
        }

        void button_set_action(const control &control_, sqf_string_const_ref action_) {
            host::functions.invoke_raw_binary(__sqf::binary__buttonsetaction__control__string__ret__nothing, control_, action_);
        }

        float lb_add(int control_id_, sqf_string_const_ref text_) {
            game_value args({static_cast<float>(control_id_),
                             text_});

            return host::functions.invoke_raw_unary(__sqf::unary__lbadd__array__ret__scalar, args);
        }

        float lb_add(const control &control_, sqf_string_const_ref text_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbadd__control__string__ret__scalar, control_, text_);
        }

        float lb_color(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__lbcolor__array__ret__array, args);
        }

        float lb_color(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbcolor__control__scalar__ret__array, control_, static_cast<float>(index_));
        }

        float lb_color_right(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__lbcolorright__array__ret__array, args);
        }

        float lb_color_right(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbcolorright__control__scalar__ret__array, control_, static_cast<float>(index_));
        }

        sqf_return_string lb_data(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__lbdata__array__ret__string, args);
        }

        sqf_return_string lb_data(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbdata__control__scalar__ret__string, control_, static_cast<float>(index_));
        }

        void lb_delete(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            host::functions.invoke_raw_unary(__sqf::unary__lbdelete__array__ret__nothing, args);
        }

        void lb_delete(const control &control_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbdelete__control__scalar__ret__nothing, control_, static_cast<float>(index_));
        }

        sqf_return_string lb_picture(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__lbpicture__array__ret__string, args);
        }

        sqf_return_string lb_picture(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbpicture__control__scalar__ret__string, control_, static_cast<float>(index_));
        }

        sqf_return_string lb_picture_right(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});
            return host::functions.invoke_raw_unary(__sqf::unary__lbpictureright__array__ret__string, args);
        }

        sqf_return_string lb_picture_right(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbpictureright__control__scalar__ret__string, control_, static_cast<float>(index_));
        }

        void lb_set_color(int control_id_, int index_, rv_color color_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetcolor__array__ret__nothing, args);
        }

        void lb_set_color(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetcolor__control__array__ret__nothing, control_, args);
        }

        void lb_set_color_right(int control_id_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetcolorright__array__ret__nothing, args);
        }

        void lb_set_color_right(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetcolorright__control__array__ret__nothing, control_, args);
        }

        void lb_set_cur_sel(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});
            host::functions.invoke_raw_unary(__sqf::unary__lbsetcursel__array__ret__nothing, args);
        }

        void lb_set_cur_sel(const control &control_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbsetcursel__control__scalar__ret__nothing, control_, static_cast<float>(index_));
        }

        void lb_set_data(int control_id_, int index_, sqf_string_const_ref data_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             data_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetdata__array__ret__nothing, args);
        }

        void lb_set_data(const control &control_, int index_, sqf_string_const_ref data_) {
            game_value args({static_cast<float>(index_),
                             data_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetdata__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture(int control_id_, int index_, sqf_string_const_ref name_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             name_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetpicture__array__ret__nothing, args);
        }

        void lb_set_picture(const control &control_, int index_, sqf_string_const_ref name_) {
            game_value args({static_cast<float>(index_),
                             name_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpicture__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_right(int control_id_, int index_, sqf_string_const_ref name_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             name_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetpictureright__array__ret__nothing, args);
        }

        void lb_set_picture_right(const control &control_, int index_, sqf_string_const_ref name_) {
            game_value args({static_cast<float>(index_),
                             name_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpictureright__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_color(int control_id_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetpicturecolor__array__ret__nothing, args);
        }

        void lb_set_picture_color(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpicturecolor__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_color_disabled(int control_id_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetpicturecolordisabled__array__ret__nothing, args);
        }

        void lb_set_picture_color_disabled(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpicturecolordisabled__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_color_selected(int control_id_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetpicturecolorselected__array__ret__nothing, args);
        }

        void lb_set_picture_color_selected(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpicturecolorselected__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_right_color(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpicturerightcolor__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_right_color_disabled(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpicturerightcolordisabled__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_right_color_selected(const control &control_, int index_, const rv_color &color_) {
            game_value args({static_cast<float>(index_),
                             color_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetpicturerightcolorselected__control__array__ret__nothing, control_, args);
        }

        void lb_set_text(const control &control_, int index_, sqf_string_const_ref text_) {
            game_value params_right({index_,
                                     text_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsettext__control__array__ret__nothing, control_, params_right);
        }

        void lb_set_text_right(const control &control_, int index_, sqf_string_const_ref text_) {
            game_value params_right({index_,
                                     text_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsettextright__control__array__ret__nothing, control_, params_right);
        }

        void lb_set_tooltip(int control_id_, int index_, sqf_string_const_ref tooltip_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             tooltip_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsettooltip__array__ret__nothing, args);
        }

        void lb_set_tooltip(const control &control_, int index_, sqf_string_const_ref tooltip_) {
            game_value args({static_cast<float>(index_),
                             tooltip_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsettooltip__control__array__ret__nothing, control_, args);
        }

        void lb_set_value(int control_id_, int index_, float val_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_),
                             val_});

            host::functions.invoke_raw_unary(__sqf::unary__lbsetvalue__array__ret__nothing, args);
        }

        void lb_set_value(const control &control_, int index_, float val_) {
            game_value args({static_cast<float>(index_),
                             val_});

            host::functions.invoke_raw_binary(__sqf::binary__lbsetvalue__control__array__ret__nothing, control_, args);
        }

        sqf_return_string lb_text(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__lbtext__array__ret__string, args);
        }

        sqf_return_string lb_text(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbtext__control__scalar__ret__string, control_, static_cast<float>(index_));
        }

        sqf_return_string lb_text_right(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__lbtextright__array__ret__string, args);
        }

        sqf_return_string lb_text_right(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbtextright__control__scalar__ret__string, control_, static_cast<float>(index_));
        }

        float lb_value(int control_id_, int index_) {
            game_value args({static_cast<float>(control_id_),
                             static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__lbvalue__array__ret__scalar, args);
        }

        float lb_value(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbvalue__control__scalar__ret__scalar, control_, static_cast<float>(index_));
        }

        sqf_return_string lb_tooltip(const control &ctrl_, float index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbtooltip__control__scalar__ret__string, ctrl_, index_);
        }

        void load_overlay(const control &a_control_, const config &a_config_) {
            host::functions.invoke_raw_binary(__sqf::binary__loadoverlay__control__config__ret__nothing, a_control_, a_config_);
        }

        void new_overlay(const control &a_control_, const config &a_config_) {
            host::functions.invoke_raw_binary(__sqf::binary__newoverlay__control__config__ret__nothing, a_control_, a_config_);
        }

        std::vector<control> all_controls(const display &display_) {
            return __helpers::__convert_to_vector<control>(host::functions.invoke_raw_unary(__sqf::unary__allcontrols__display__ret__array, display_));
        }

        std::vector<control> all_controls(const control &ctrl_) {
            return __helpers::__convert_to_vector<control>(host::functions.invoke_raw_unary(__sqf::unary__allcontrols__control__ret__array, ctrl_));
        }

        control control_null() {
            return __helpers::__retrieve_nular_control(__sqf::nular__controlnull__ret__control);
        }

        sqf_return_string button_action(const control &control_) {
            return __helpers::__string_unary_control(__sqf::unary__buttonaction__control__ret__string, control_);
        }

        sqf_return_string button_action(int idc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__buttonaction__scalar__ret__string, static_cast<float>(idc_));
        }

        bool cb_checked(const control &control_) {
            return __helpers::__bool_unary_control(__sqf::unary__cbchecked__control__ret__bool, control_);
        }
        void clear_overlay(const control &map_) {
            __helpers::__empty_unary_control(__sqf::unary__clearoverlay__control__ret__nothing, map_);
        }

        void close_dialog(float val_) {
            __helpers::__empty_unary_number(__sqf::unary__closedialog__scalar__ret__nothing, val_);
        }

        void close_overlay(const control &map_) {
            __helpers::__empty_unary_control(__sqf::unary__closeoverlay__control__ret__nothing, map_);
        }
        void collapse_object_tree(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__collapseobjecttree__control__ret__nothing, value_);
        }

        void commit_overlay(const control &map_) {
            __helpers::__empty_unary_control(__sqf::unary__commitoverlay__control__ret__nothing, map_);
        }

        float gear_slot_ammo_count(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__gearslotammocount__control__ret__scalar, value_);
        }

        sqf_return_string gear_slot_data(const control &value_) {
            return __helpers::__string_unary_control(__sqf::unary__gearslotdata__control__ret__string, value_);
        }

        sqf_return_string get_editor_mode(const control &value_) {
            return __helpers::__string_unary_control(__sqf::unary__geteditormode__control__ret__string, value_);
        }

        void import_all_groups(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__importallgroups__control__ret__nothing, value_);
        }

        bool is_real_time(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__isrealtime__control__ret__bool, value_);
        }

        bool is_showing(const control &value_) {
            return __helpers::__bool_unary_control(__sqf::unary__isshowing3dicons__control__ret__bool, value_);
        }
        void lb_clear(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__lbclear__control__ret__nothing, value_);
        }

        void lb_clear(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__lbclear__scalar__ret__nothing, value_);
        }

        float lb_cur_sel(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__lbcursel__control__ret__scalar, value_);
        }

        float lb_cur_sel(float value_) {
            return __helpers::__number_unary_number(__sqf::unary__lbcursel__scalar__ret__scalar, value_);
        }

        float lb_size(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__lbsize__control__ret__scalar, value_);
        }

        float lb_size(float value_) {
            return __helpers::__number_unary_number(__sqf::unary__lbsize__scalar__ret__scalar, value_);
        }

        float next_menu_item_index(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__nextmenuitemindex__control__ret__scalar, value_);
        }

        float progress_position(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__progressposition__control__ret__scalar, value_);
        }

        void restart_editor_camera(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__restarteditorcamera__control__ret__nothing, value_);
        }

        void save_overlay(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__saveoverlay__control__ret__nothing, value_);
        }

        void selected_editor_objects(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__selectededitorobjects__control__ret__nothing, value_);
        }

        float slider_position(const control &value_) {
            return __helpers::__number_unary_control(__sqf::unary__sliderposition__control__ret__scalar, value_);
        }

        float slider_position(float value_) {
            return __helpers::__number_unary_number(__sqf::unary__sliderposition__scalar__ret__scalar, value_);
        }

        void update_object_tree(const control &value_) {
            __helpers::__empty_unary_control(__sqf::unary__updateobjecttree__control__ret__nothing, value_);
        }

        void allow3dmode(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allow3dmode__control__bool__ret__nothing, value0_, value1_);
        }

        void allow_file_operations(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowfileoperations__control__bool__ret__nothing, value0_, value1_);
        }

        sqf_return_string get_editor_object_scope(const control &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__geteditorobjectscope__control__string__ret__string, value0_, value1_);
        }

        object get_object_proxy(const control &value0_, sqf_string_const_ref value1_) {
            return object(host::functions.invoke_raw_binary(__sqf::binary__getobjectproxy__control__string__ret__object, value0_, value1_));
        }

        void html_load(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__htmlload__control__string__ret__nothing, value0_, value1_);
        }

        sqf_return_string lb_data(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbdata__control__scalar__ret__string, value0_, value1_);
        }

        void lb_delete(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbdelete__control__scalar__ret__nothing, value0_, value1_);
        }

        bool lb_is_selected(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbisselected__control__scalar__ret__bool, value0_, value1_);
        }

        sqf_return_string lb_picture(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbpicture__control__scalar__ret__string, value0_, value1_);
        }

        sqf_return_string lb_picture_right(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbpictureright__control__scalar__ret__string, value0_, value1_);
        }

        void lb_set_cur_sel(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbsetcursel__control__scalar__ret__nothing, value0_, value1_);
        }

        sqf_return_string lb_text(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbtext__control__scalar__ret__string, value0_, value1_);
        }

        sqf_return_string lb_text_right(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbtextright__control__scalar__ret__string, value0_, value1_);
        }

        float lb_value(const control &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lbvalue__control__scalar__ret__scalar, value0_, value1_);
        }

        void map_center_on_camera(const control &main_map_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__mapcenteroncamera__control__bool__ret__array, main_map_, enable_);
        }

        vector3 map_center_on_camera(const control &mini_map_) {
            return host::functions.invoke_raw_unary(__sqf::unary__mapcenteroncamera__control__ret__array, mini_map_);
        }

        void move_object_to_end(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveobjecttoend__control__string__ret__nothing, value0_, value1_);
        }

        void progress_set_position(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__progresssetposition__control__scalar__ret__nothing, value0_, value1_);
        }

        void remove_menu_item(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removemenuitem__control__scalar__ret__nothing, value0_, value1_);
        }

        void remove_menu_item(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removemenuitem__control__string__ret__nothing, value0_, value1_);
        }

        void set_editor_mode(const control &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__seteditormode__control__string__ret__nothing, value0_, value1_);
        }

        void show3dicons(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__show3dicons__control__bool__ret__nothing, value0_, value1_);
        }

        void show_legend(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__showlegend__control__bool__ret__nothing, value0_, value1_);
        }

        void slider_set_position(float value0_, float value1_) {
            game_value args({value0_,
                             value1_});

            host::functions.invoke_raw_unary(__sqf::unary__slidersetposition__array__ret__nothing, args);
        }

        void slider_set_position(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__slidersetposition__control__scalar__ret__nothing, value0_, value1_);
        }

        object get_editor_camera(const control &value_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__geteditorcamera__control__ret__object, value_));
        }

        void cut_obj(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_) {
            game_value args({name_,
                             type_,
                             speed_});

            host::functions.invoke_raw_unary(__sqf::unary__cutobj__array__ret__nothing, args);
        }

        void cut_rsc(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value args({name_,
                             type_,
                             speed_,
                             show_on_map_});

            host::functions.invoke_raw_unary(__sqf::unary__cutrsc__array__ret__nothing, args);
        }

        void cut_text(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value args({name_,
                             type_,
                             speed_,
                             show_on_map_});

            host::functions.invoke_raw_unary(__sqf::unary__cuttext__array__ret__nothing, args);
        }

        //NULAR -- https://github.com/intercept/intercept/issues/13
        sqf_return_string_list all_cut_layers() {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_nular(__sqf::nular__allcutlayers__ret__array));
        }

        int cut_fade_out(sqf_string_const_ref layer_name_, float duration_) {
            return host::functions.invoke_raw_binary(__sqf::binary__cutfadeout__string__scalar__ret__scalar, layer_name_, duration_);
        }

        int cut_fade_out(int layer_, float duration_) {
            return host::functions.invoke_raw_binary(__sqf::binary__cutfadeout__scalar__scalar__ret__nothing, static_cast<float>(layer_), duration_);
        }

        int cut_obj(sqf_string_const_ref layer_name_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value params_right({class_,
                                     type_,
                                     speed_,
                                     show_on_map_});

            return host::functions.invoke_raw_binary(__sqf::binary__cutobj__string__array__ret__scalar, layer_name_, params_right);
        }

        int cut_obj(int layer_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value params_right({class_,
                                     type_,
                                     speed_,
                                     show_on_map_});

            return host::functions.invoke_raw_binary(__sqf::binary__cutobj__scalar__array__ret__nothing, static_cast<float>(layer_), params_right);
        }

        int cut_rsc(sqf_string_const_ref layer_name_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value params_right({class_,
                                     type_,
                                     speed_,
                                     show_on_map_});

            return host::functions.invoke_raw_binary(__sqf::binary__cutrsc__string__array__ret__scalar, layer_name_, params_right);
        }

        int cut_rsc(int layer_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value params_right({class_,
                                     type_,
                                     speed_,
                                     show_on_map_});

            return host::functions.invoke_raw_binary(__sqf::binary__cutrsc__scalar__array__ret__nothing, static_cast<float>(layer_), params_right);
        }

        int cut_text(sqf_string_const_ref layer_name_, sqf_string_const_ref text_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value params_right({text_,
                                     type_,
                                     speed_,
                                     show_on_map_});

            return host::functions.invoke_raw_binary(__sqf::binary__cuttext__string__array__ret__scalar, layer_name_, params_right);
        }

        int cut_text(int layer_, sqf_string_const_ref text_, sqf_string_const_ref type_, float speed_, bool show_on_map_) {
            game_value params_right({text_,
                                     type_,
                                     speed_,
                                     show_on_map_});

            return host::functions.invoke_raw_binary(__sqf::binary__cuttext__scalar__array__ret__nothing, static_cast<float>(layer_), params_right);
        }

        void title_fade_out(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__titlefadeout__scalar__ret__nothing, value_);
        }

        game_value active_title_effect_params(float title_) {
            return host::functions.invoke_raw_unary(__sqf::unary__activetitleeffectparams__scalar__ret__array, title_);
        }

        bool open_dlc_page(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__opendlcpage__scalar__ret__bool, value_);
        }

        bool open_youtube_video(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__openyoutubevideo__string__ret__bool, value_);
        }

        bool open_map(bool value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__openmap__bool__ret__bool, value_);
        }

        bool open_map(bool show_, bool forced_) {
            game_value args({show_,
                             forced_});

            return host::functions.invoke_raw_unary(__sqf::unary__openmap__array__ret__bool, args);
        }

        bool show_subtitles(bool value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__showsubtitles__bool__ret__bool, value_);
        }

        rv_subtitle_options get_subtitle_options() {
            return rv_subtitle_options(host::functions.invoke_raw_nular(__sqf::nular__getsubtitleoptions__ret__array));
        }

        void create_gear_dialog(const object &unit_, sqf_string_const_ref resource_) {
            game_value params({unit_,
                               resource_});

            host::functions.invoke_raw_unary(__sqf::unary__creategeardialog__array__ret__nothing, params);
        }

        bool dialog() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__dialog__ret__bool);
        }

        void disable_serialization() {
            __helpers::__empty_nular(__sqf::nular__disableserialization__ret__nothing);
        }

        display display_null() {
            return __helpers::__retrieve_nular_display(__sqf::nular__displaynull__ret__display);
        }

        void enable_end_dialog() {
            __helpers::__empty_nular(__sqf::nular__enableenddialog__ret__nothing);
        }

        float pixel_h() {
            return __helpers::__retrieve_nular_number(__sqf::nular__pixelh__ret__scalar);
        }

        float pixel_w() {
            return __helpers::__retrieve_nular_number(__sqf::nular__pixelw__ret__scalar);
        }

        float pixel_grid() {
            return host::functions.invoke_raw_nular(__sqf::nular__pixelgrid__ret__scalar);
        }

        float pixel_grid_base() {
            return host::functions.invoke_raw_nular(__sqf::nular__pixelgridbase__ret__scalar);
        }

        float pixel_grid_no_ui_scale() {
            return host::functions.invoke_raw_nular(__sqf::nular__pixelgridnouiscale__ret__scalar);
        }

        int shown_score_table() {
            return static_cast<int>(host::functions.invoke_raw_nular(__sqf::nular__shownscoretable__ret__scalar));
        }

        void end_loading_screen() {
            __helpers::__empty_nular(__sqf::nular__endloadingscreen__ret__nothing);
        }

        void set_compass_oscillation(float angle_, float freq_min_, float freq_max_) {
            game_value params({angle_,
                               freq_min_,
                               freq_max_});

            host::functions.invoke_raw_unary(__sqf::unary__setcompassoscillation__array__ret__nothing, params);
        }

        void set_hud_movement_levels(float min_speed_, float max_speed_, float min_alt_, float max_alt_, float min_dir_, float max_dir_, const object &obj_) {
            game_value params({min_speed_,
                               max_speed_,
                               min_alt_,
                               max_alt_,
                               min_dir_,
                               max_dir_,
                               obj_});

            host::functions.invoke_raw_unary(__sqf::unary__sethudmovementlevels__array__ret__nothing, params);
        }

        void set_hud_movement_levels(float min_speed_, float max_speed_, float min_alt_, float max_alt_, float min_dir_, float max_dir_, const vector3 &pos_) {
            game_value params({min_speed_,
                               max_speed_,
                               min_alt_,
                               max_alt_,
                               min_dir_,
                               max_dir_,
                               pos_});

            host::functions.invoke_raw_unary(__sqf::unary__sethudmovementlevels__array__ret__nothing, params);
        }

        void start_loading_screen(sqf_string_const_ref text_) {
            game_value params({text_});

            host::functions.invoke_raw_unary(__sqf::unary__startloadingscreen__array__ret__nothing, params);
        }

        void start_loading_screen(sqf_string_const_ref text_, sqf_string_const_ref resource_) {
            game_value params({text_,
                               resource_});

            host::functions.invoke_raw_unary(__sqf::unary__startloadingscreen__array__ret__nothing, params);
        }

        display create_mission_display(const display &display_, sqf_string_const_ref mission_) {
            return host::functions.invoke_raw_binary(__sqf::binary__createmissiondisplay__display__array__ret__display, display_, mission_);
        }

        display create_mp_campaign_display(const display &display_, sqf_string_const_ref mission_) {
            return host::functions.invoke_raw_binary(__sqf::binary__creatempcampaigndisplay__display__string__ret__nothing, display_, mission_);
        }

        int display_add_event_handler(const display &display_, sqf_string_const_ref event_name_, sqf_string_const_ref code_) {
            game_value params_right({event_name_,
                                     code_});

            return host::functions.invoke_raw_binary(__sqf::binary__displayaddeventhandler__display__array__ret__scalar, display_, params_right);
        }

        int display_add_event_handler(const display &display_, sqf_string_const_ref event_name_, const code &code_) {
            game_value params_right({event_name_,
                                     code_});

            return host::functions.invoke_raw_binary(__sqf::binary__displayaddeventhandler__display__array__ret__scalar, display_, params_right);
        }

        void display_remove_eventhandler(const display &display_, sqf_string_const_ref event_name_, int id_) {
            game_value params_right({event_name_,
                                     static_cast<float>(id_)});

            host::functions.invoke_raw_binary(__sqf::binary__displayremoveeventhandler__display__array__ret__nothing, display_, params_right);
        }

        void display_set_eventhandler(const display &display_, sqf_string_const_ref event_name_, sqf_string_const_ref code_) {
            game_value params_right({event_name_,
                                     code_});

            host::functions.invoke_raw_binary(__sqf::binary__displayseteventhandler__display__array__ret__nothing, display_, params_right);
        }

        void display_remove_all_event_handlers(sqf_string_const_ref value0_, const display &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__displayremovealleventhandlers__display__string__ret__nothing, value0_, value1_);
        }

        display find_display(float value_) {
            return display(host::functions.invoke_raw_unary(__sqf::unary__finddisplay__scalar__ret__display, value_));
        }

        display display_child(const display &disp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__displaychild__display__ret__display, disp_);
        }

        bool is_tut_hints_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__istuthintsenabled__ret__bool);
        }

        void hint_c(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__hintc__string__ret__nothing, value_);
        }

        void hint_c(sqf_string_const_ref value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__hintc__string__text__ret__nothing, value0_, value1_);
            // Identical from intercept's side: binary__hintc__string__string__ret__nothing
        }

        void hint(sqf_string_const_ref text_) {
            __helpers::__empty_unary_string(__sqf::unary__hint__text_string__ret__nothing, text_);
        }

        void hint_cadet(sqf_string_const_ref text_) {
            __helpers::__empty_unary_string(__sqf::unary__hintcadet__text_string__ret__nothing, text_);
        }

        void hint_silent(sqf_string_const_ref text_) {
            __helpers::__empty_unary_string(__sqf::unary__hintsilent__text_string__ret__nothing, text_);
        }

        void hintc(sqf_string_const_ref title_, sqf_string_list_const_ref content_) {
            auto_array<game_value> ga_content(content_.begin(), content_.end());

            host::functions.invoke_raw_binary(__sqf::binary__hintc__string__array__ret__nothing, title_, std::move(ga_content));
        }

        void task_hint(sqf_string_const_ref text_, const rv_color &color_, sqf_string_const_ref icon_) {
            game_value params({text_,
                               color_,
                               icon_});

            host::functions.invoke_raw_unary(__sqf::unary__taskhint__array__ret__nothing, params);
        }

        void map_anim_clear() {
            __helpers::__empty_nular(__sqf::nular__mapanimclear__ret__nothing);
        }

        void map_anim_commit() {
            __helpers::__empty_nular(__sqf::nular__mapanimcommit__ret__nothing);
        }

        bool map_anim_done() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__mapanimdone__ret__bool);
        }
        bool shown_artillerycomputer() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownartillerycomputer__ret__bool);
        }
        bool shown_compass() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__showncompass__ret__bool);
        }
        bool shown_hud() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownhud__ret__array);
        }
        bool shown_gps() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__showngps__ret__bool);
        }
        bool shown_map() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownmap__ret__bool);
        }
        bool shown_pad() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownpad__ret__bool);
        }
        bool shown_radio() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownradio__ret__bool);
        }
        bool shown_uavfeed() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownuavfeed__ret__bool);
        }
        bool shown_warrant() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownwarrant__ret__bool);
        }
        bool shown_watch() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownwatch__ret__bool);
        }

        bool visible_watch() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__visiblewatch__ret__bool);
        }

        bool visible_map() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__visiblemap__ret__bool);
        }

        bool visible_gps() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__visiblegps__ret__bool);
        }

        bool visible_compass() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__visiblecompass__ret__bool);
        }
        void force_map(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__forcemap__bool__ret__nothing, value_);
        }
        void show_cinema_border(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showcinemaborder__bool__ret__nothing, value_);
        }

        void show_commanding_menu(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__showcommandingmenu__string__ret__nothing, value_);
        }

        void show_compass(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showcompass__bool__ret__nothing, value_);
        }

        void show_gps(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showgps__bool__ret__nothing, value_);
        }

        void show_hud(bool show_) {
            __helpers::__empty_unary_bool(__sqf::unary__showhud__bool__ret__nothing, show_);
        }

        void show_hud(bool hud_, bool info_, bool radar_, bool compass_, bool direction_, bool menu_, bool group_, bool cursors_) {
            game_value params({hud_,
                               info_,
                               radar_,
                               compass_,
                               direction_,
                               menu_,
                               group_,
                               cursors_});

            host::functions.invoke_raw_unary(__sqf::unary__showhud__array__ret__nothing, params);
        }

        void show_map(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showmap__bool__ret__nothing, value_);
        }

        void show_pad(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showpad__bool__ret__nothing, value_);
        }

        void show_radio(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showradio__bool__ret__nothing, value_);
        }

        void show_uavfeed(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showuavfeed__bool__ret__nothing, value_);
        }

        void show_warrant(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showwarrant__bool__ret__nothing, value_);
        }

        void show_watch(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showwatch__bool__ret__nothing, value_);
        }

        sqf_return_string map_grid_position(const object &obj_) {
            return __helpers::__string_unary_object(__sqf::unary__mapgridposition__object_array__ret__string, obj_);
        }

        sqf_return_string map_grid_position(const vector2 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__mapgridposition__object_array__ret__string, pos_);
        }

        void map_anim_add(float time_, float zoom_, const object &object_) {
            game_value params({time_,
                               zoom_,
                               object_});

            host::functions.invoke_raw_unary(__sqf::unary__mapanimadd__array__ret__nothing, params);
        }

        void map_anim_add(float time_, float zoom_, const vector3 &pos_) {
            game_value params({time_,
                               zoom_,
                               pos_});

            host::functions.invoke_raw_unary(__sqf::unary__mapanimadd__array__ret__nothing, params);
        }

        bool preload_title_obj(sqf_string_const_ref name_, sqf_string_const_ref type_) {
            game_value params({name_,
                               type_});

            return host::functions.invoke_raw_unary(__sqf::unary__preloadtitleobj__array__ret__bool, params);
        }

        bool preload_title_obj(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_, bool show_in_map_) {
            game_value params({name_,
                               type_,
                               speed_,
                               show_in_map_});

            return host::functions.invoke_raw_unary(__sqf::unary__preloadtitleobj__array__ret__bool, params);
        }

        bool preload_title_rsc(sqf_string_const_ref name_, sqf_string_const_ref type_) {
            game_value params({name_,
                               type_});

            return host::functions.invoke_raw_unary(__sqf::unary__preloadtitlersc__array__ret__bool, params);
        }

        bool preload_title_rsc(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_, bool show_in_map_) {
            game_value params({name_,
                               type_,
                               speed_,
                               show_in_map_});

            return host::functions.invoke_raw_unary(__sqf::unary__preloadtitlersc__array__ret__bool, params);
        }
        void in_game_ui_set_event_handler(sqf_string_const_ref name_, sqf_string_const_ref command_) {
            game_value params({name_,
                               command_});

            host::functions.invoke_raw_unary(__sqf::unary__ingameuiseteventhandler__array__ret__nothing, params);
        }
        void title_cut(sqf_string_const_ref text_, sqf_string_const_ref type_, const float &speed_) {
            game_value params({text_,
                               type_,
                               speed_});

            host::functions.invoke_raw_unary(__sqf::unary__titlecut__array__ret__nothing, params);
        }

        void title_obj(sqf_string_const_ref class_, sqf_string_const_ref type_, const float &speed_, bool show_on_map_) {
            game_value params({class_,
                               type_,
                               speed_,
                               show_on_map_});

            host::functions.invoke_raw_unary(__sqf::unary__titleobj__array__ret__nothing, params);
        }

        void title_rsc(sqf_string_const_ref text_, sqf_string_const_ref type_, const float &speed_) {
            game_value params({text_,
                               type_,
                               speed_});

            host::functions.invoke_raw_unary(__sqf::unary__titlersc__array__ret__nothing, params);
        }

        void title_text(sqf_string_const_ref text_, sqf_string_const_ref type_, const float &speed_) {
            game_value params({text_,
                               type_,
                               speed_});

            host::functions.invoke_raw_unary(__sqf::unary__titletext__array__ret__nothing, params);
        }

        float safe_zone_x() {
            return __helpers::__retrieve_nular_number(__sqf::nular__safezonex__ret__scalar);
        }
        float safe_zone_y() {
            return __helpers::__retrieve_nular_number(__sqf::nular__safezoney__ret__scalar);
        }
        float safe_zone_h() {
            return __helpers::__retrieve_nular_number(__sqf::nular__safezoneh__ret__scalar);
        }
        float safe_zone_w() {
            return __helpers::__retrieve_nular_number(__sqf::nular__safezonew__ret__scalar);
        }
        float safe_zone_x_abs() {
            return __helpers::__retrieve_nular_number(__sqf::nular__safezonexabs__ret__scalar);
        }
        float safe_zone_w_abs() {
            return __helpers::__retrieve_nular_number(__sqf::nular__safezonewabs__ret__scalar);
        }

        bool create_dialog(sqf_string_const_ref dialog_name_) {
            return __helpers::__bool_unary_string(__sqf::unary__createdialog__string__ret__bool, dialog_name_);
        }

        display create_dialog(sqf_string_const_ref dialog_name_, bool force_on_top_) {
            return host::functions.invoke_raw_unary(__sqf::unary__createdialog__array__ret__display, {dialog_name_, force_on_top_});
        }

        void hc_show_bar(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__hcshowbar__bool__ret__nothing, value_);
        }

        bool hc_shown_bar() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__hcshownbar__ret__bool);
        }

        display display_parent(const display &display_) {
            return host::functions.invoke_raw_unary(__sqf::unary__displayparent__display__ret__display, display_);
        }

        bool visible_score_table() {
            return host::functions.invoke_raw_nular(__sqf::nular__visiblescoretable__ret__bool);
        }

        void show_score_table(int force_) {
            host::functions.invoke_raw_unary(__sqf::unary__showscoretable__scalar__ret__nothing, static_cast<float>(force_));
        }

        bool is_pip_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__ispipenabled__ret__bool);
        }

        void set_mouse_position(float x_, float y_) {
            game_value params({x_,
                               y_});

            host::functions.invoke_raw_unary(__sqf::unary__setmouseposition__array__ret__nothing, params);
        }

        //#TODO: Do we need a function for each type? To get the right arguments? https://community.bistudio.com/wiki/setPiPEffect
        void set_pip_effect(sqf_string_const_ref name_, const game_value &parameters) {
            host::functions.invoke_raw_binary(__sqf::binary__setpipeffect__string__array__ret__nothing, name_, parameters);
        }

        void slider_set_speed(const control &slider_, float line_, int page_) {
            host::functions.invoke_raw_binary(__sqf::binary__slidersetspeed__control__array__ret__nothing, slider_, {line_, page_});
        }
        int lnb_add_row(int idc_, sqf_string_list_const_ref items_) {
            auto_array<game_value> items(items_.begin(), items_.end());

            game_value params({static_cast<float>(idc_),
                               std::move(items)});

            return static_cast<int>(host::functions.invoke_raw_unary(__sqf::unary__lnbaddrow__array__ret__scalar, params));
        }
        std::pair<bool, bool> forced_map() {
            game_value res = host::functions.invoke_raw_nular(__sqf::nular__forcedmap__ret__array);

            return std::pair<bool, bool>({res[0], res[1]});
        }
        void progress_loading_screen(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__progressloadingscreen__scalar__ret__nothing, value_);
        }
        void look_at_pos(const control &map_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__lookatpos__control__array__ret__nothing, map_, position_);
        }
        rv_ct_list ct_add_header(const control &control_) {
            game_value res = host::functions.invoke_raw_unary(__sqf::unary__ctaddheader__control__ret__array, control_);

            return rv_ct_list({res[0], __helpers::__convert_to_vector<control>(res[1])});
        }

        rv_ct_list ct_add_row(const control &control_) {
            game_value res = host::functions.invoke_raw_unary(__sqf::unary__ctaddrow__control__ret__array, control_);

            return rv_ct_list({res[0], __helpers::__convert_to_vector<control>(res[1])});
        }

        void ct_clear(const control &control_) {
            host::functions.invoke_raw_unary(__sqf::unary__ctclear__control__ret__nothing, control_);
        }

        int ct_cur_sel(const control &control_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctcursel__control__ret__scalar, control_);
        }

        int ct_header_count(const control &control_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctheadercount__control__ret__scalar, control_);
        }

        int ct_row_count(const control &control_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrowcount__control__ret__scalar, control_);
        }

        void lb_sort(const control &control_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsort__control__ret__nothing, control_);
        }

        void lb_sort(const control &control_, sqf_string_const_ref sort_order_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsort__array__ret__nothing, {control_, sort_order_});
        }

        //old bodies
        /*
        void lb_sort(const control &control_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsort__control__ret__nothing, control_);
        }

        void lb_sort(const control &control_, sqf_string_const_ref sort_order_) {
            game_value args({
                control_,
                sort_order_
            });

            host::functions.invoke_raw_unary(__sqf::unary__lbsort__array__ret__nothing, args);
        }
        */

        void lb_sort(int control_, sqf_string_const_ref sort_order_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsort__array__ret__nothing, {control_, sort_order_});
        }

        void lb_sort(int control_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsort__scalar__ret__nothing, control_);
        }

        void lb_sort_by_value(const control &control_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsortbyvalue__control__ret__nothing, control_);
        }

        void lb_sort_by_value(int control_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsortbyvalue__scalar__ret__nothing, control_);
        }

        void lb_sort_by(const control &control_, sqf_string_const_ref sort_type_, bool reversed_, bool case_sensitive_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbsortby__control_scalar__array__ret__nothing, control_, {sort_type_, reversed_, case_sensitive_});
        }
        void lb_sort_by(int control_, sqf_string_const_ref sort_type_, bool reversed_, bool case_sensitive_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbsortby__control_scalar__array__ret__nothing, control_, {sort_type_, reversed_, case_sensitive_});
        }

        sqf_return_string ct_data(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ctdata__control__scalar__ret__string, control_, index_);
        }

        std::vector<float> ct_find_header_rows(const control &control_, int index_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_binary(__sqf::binary__ctfindheaderrows__control__scalar__ret__array, control_, index_));
        }

        int ct_find_row_header(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ctfindrowheader__control__scalar__ret__scalar, control_, index_);
        }

        std::vector<control> ct_header_controls(const control &control_, int index_) {
            return __helpers::__convert_to_vector<control>(host::functions.invoke_raw_binary(__sqf::binary__ctheadercontrols__control__scalar__ret__array, control_, index_));
        }

        void ct_remove_headers(const control &control_, const std::vector<int> &header_indexes_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctremoveheaders__control__array__ret__nothing, control_, auto_array<game_value>(header_indexes_.begin(), header_indexes_.end()));
        }

        void ct_remove_rows(const control &control_, const std::vector<int> &row_indexes_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctremoverows__control__array__ret__nothing, control_, auto_array<game_value>(row_indexes_.begin(), row_indexes_.end()));
        }

        std::vector<control> ct_row_controls(const control &control_, int index_) {
            return __helpers::__convert_to_vector<control>(host::functions.invoke_raw_binary(__sqf::binary__ctrowcontrols__control__scalar__ret__array, control_, index_));
        }

        void ct_set_cur_sel(const control &control_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctsetcursel__control__scalar__ret__nothing, control_, index_);
        }

        void ct_set_data(const control &control_, int index_, sqf_string_const_ref data_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctsetdata__control__array__ret__nothing, control_, {index_, data_});
        }

        void ct_set_header_template(const control &control_, const config &config_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctsetheadertemplate__control__config__ret__nothing, control_, config_);
        }

        void ct_set_row_template(const control &control_, const config &config_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctsetrowtemplate__control__config__ret__nothing, control_, config_);
        }

        void ct_set_value(const control &control_, float value_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctsetvalue__control__array__ret__nothing, control_, value_);
        }

        float ct_value(const control &control_, float index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ctvalue__control__scalar__ret__scalar, control_, index_);
        }
        rv_resolution get_resolution() {
            return rv_resolution(host::functions.invoke_raw_nular(__sqf::nular__getresolution__ret__array));
        }

        vector2 get_mouse_position() {
            return host::functions.invoke_raw_nular(__sqf::nular__getmouseposition__ret__array);
        }

        bool is_ui_context() {
            return host::functions.invoke_raw_nular(__sqf::nular__isuicontext__ret__bool);
        }

        void ctrl_animate_model(const control &control_, sqf_string_const_ref source_, float phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlanimatemodel__control__array__ret__nothing, control_, {source_, phase_});
        }

        float ctrl_animation_phase_model(const control &control_, sqf_string_const_ref source_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ctrlanimationphasemodel__control__string__ret__scalar, control_, source_);
        }

        bool ctrl_checked(const control &control_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ctrlchecked__control__scalar__ret__bool, control_, index_);
        }

        void ctrl_set_angle(const control &control_, float angle_, float centerX_, float centerY_, bool now_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetangle__control__array__ret__nothing, control_, {angle_, centerX_, centerY_, now_});
        }

        void ctrl_set_checked(const control &control_, int index_, bool checked_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetchecked__control__array__ret__nothing, control_, {index_, checked_});
        }

        void ctrl_set_mouse_position(const control &control_, float x_, float y_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetmouseposition__control__array__ret__nothing, control_, {x_, y_});
        }

        void ctrl_set_pixel_precision(const control &control_, pixel_precision_types type_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetpixelprecision__control__scalar__ret__nothing, control_, static_cast<int>(type_));
        }

        void ctrl_set_scroll_values(const control &control_, float vScroll_, float hScroll_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsetscrollvalues__control__array__ret__nothing, control_, {vScroll_, hScroll_});
        }

        void ctrl_set_text_selection(const control &control_, float start_, float length_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettextselection__control__array__ret__nothing, control_, {start_, length_});
        }

        void ctrl_set_url(const control &control_, sqf_string_const_ref url_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlseturl__control__string__ret__nothing, control_, url_);
        }

        void draw_triangle(const control &mapCtrl_, const std::vector<vector3> &vertices_, const rv_color &color_, sqf_string_const_ref fill_texture_) {
            host::functions.invoke_raw_binary(__sqf::binary__drawtriangle__control__array__ret__nothing, mapCtrl_, {vertices_, color_, fill_texture_});
        }

        float get_text_width(sqf_string_const_ref string_, sqf_string_const_ref font_, float fontSize_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gettextwidth__string__array__ret__scalar, string_, {font_, fontSize_});
        }

        void lb_set_select_color(const control &control_, int index_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbsetselectcolor__control__array__ret__nothing, control_, {index_, color_});
        }
        void lb_set_select_color(float idc_, int index_, const rv_color &color_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsetselectcolor__array__ret__nothing, {idc_, index_, color_});
        }
        void lb_set_select_color_right(const control &control_, int index_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbsetselectcolorright__control__array__ret__nothing, control_, {index_, color_});
        }
        void lb_set_select_color_right(float idc_, int index_, const rv_color &color_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsetselectcolorright__array__ret__nothing, {idc_, index_, color_});
        }
        void lb_set_selected(const control &control_, int index_, bool selected_) {
            host::functions.invoke_raw_binary(__sqf::binary__lbsetselected__control__array__ret__nothing, control_, {index_, selected_});
        }

        bool tv_is_selected(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__tvisselected__control__array__ret__bool, ctrl_, path_);
        }

        void tv_set_selected(const control &ctrl_, const std::vector<int> &path_, bool select_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsetselected__control__array__ret__nothing, ctrl_, {path_, select_});
        }

        void tv_sort_all(const control &ctrl_, const std::vector<int> &path_, bool reversed_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsortall__control__array__ret__nothing, ctrl_, {path_, reversed_});
        }

        void tv_sort_by_value_all(const control &ctrl_, const std::vector<int> &path_, bool reversed_) {
            host::functions.invoke_raw_binary(__sqf::binary__tvsortbyvalueall__control__array__ret__nothing, ctrl_, {path_, reversed_});
        }

        std::vector<float> all_active_title_effects() {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_nular(__sqf::nular__allactivetitleeffects__ret__array));
        }

        bool is_action_menu_visible() {
            return host::functions.invoke_raw_nular(__sqf::nular__isactionmenuvisible__ret__bool);
        }

        rv_ctrl_angle ctrl_angle(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlangle__control__ret__array, ctrl_);
        }

        float ctrl_font_height(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlfontheight__control__ret__scalar, ctrl_);
        }

        vector2 ctrl_mouse_position(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlmouseposition__control__ret__array, ctrl_);
        }

        vector2 ctrl_scroll_values(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlscrollvalues__control__ret__array, ctrl_);
        }

        float ctrl_style(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlstyle__control__ret__scalar, ctrl_);
        }

        rv_color ctrl_text_color(const control &ctrl_) {
            return rv_color(host::functions.invoke_raw_unary(__sqf::unary__ctrltextcolor__control__ret__array, ctrl_));
        }

        rv_ctrl_text_selection ctrl_text_selection(const control &ctrl_) {
            return rv_ctrl_text_selection(host::functions.invoke_raw_unary(__sqf::unary__ctrltextselection__control__ret__array, ctrl_));
        }

        float ctrl_text_width(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrltextwidth__control__ret__scalar, ctrl_);
        }

        sqf_return_string ctrl_tooltip(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrltooltip__control__ret__string, ctrl_);
        }

        sqf_return_string ctrl_url(const control &ctrl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlurl__control__ret__string, ctrl_);
        }

        control focused_ctrl(const display &disp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__focusedctrl__display__ret__control, disp_);
        }

        std::vector<float> lb_selection(const control &ctrl_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__lbselection__control__ret__array, ctrl_));
        }

        bool open_gps(bool show_) {
            return host::functions.invoke_raw_unary(__sqf::unary__opengps__bool__ret__bool, show_);
        }

        //Menu
        sqf_return_string menu_action(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menuaction__control__array__ret__string, ctrl_, {path_});
        }

        sqf_return_string menu_action(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menuaction__array__ret__string, {idc_, path_});
        }

        void menu_add(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menuadd__control__array__ret__scalar, ctrl_, {path_, value_});
        }

        void menu_add(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menuadd__array__ret__scalar, {idc_, path_, value_});
        }

        bool menu_checked(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menuchecked__control__array__ret__bool, ctrl_, {path_});
        }

        bool menu_checked(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menuchecked__array__ret__bool, {idc_, path_});
        }

        void menu_collapse(const control &ctrl_, const std::vector<int> &path_) {
            host::functions.invoke_raw_binary(__sqf::binary__menucollapse__control__array__ret__nothing, ctrl_, {path_});
        }

        void menu_collapse(float idc_, const std::vector<int> &path_) {
            host::functions.invoke_raw_unary(__sqf::unary__menucollapse__array__ret__nothing, {idc_, path_});
        }

        sqf_return_string menu_data(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menudata__control__array__ret__string, ctrl_, {path_});
        }

        sqf_return_string menu_data(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menudata__array__ret__string, {idc_, path_});
        }

        void menu_delete(const control &ctrl_, const std::vector<int> &path_) {
            host::functions.invoke_raw_binary(__sqf::binary__menudelete__control__array__ret__nothing, ctrl_, {path_});
        }

        void menu_delete(float idc_, const std::vector<int> &path_) {
            host::functions.invoke_raw_unary(__sqf::unary__menudelete__array__ret__nothing, {idc_, path_});
        }

        void menu_enable(const control &ctrl_, const std::vector<int> &path_, bool value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menuenable__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_enable(float idc_, const std::vector<int> &path_, bool value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menuenable__array__ret__nothing, {idc_, path_, value_});
        }

        bool menu_enabled(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menuenabled__control__array__ret__bool, ctrl_, {path_});
        }

        bool menu_enabled(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menuenabled__array__ret__bool, {idc_, path_});
        }

        void menu_expand(const control &ctrl_, const std::vector<int> &path_) {
            host::functions.invoke_raw_binary(__sqf::binary__menuexpand__control__array__ret__nothing, ctrl_, {path_});
        }

        void menu_expand(float idc_, const std::vector<int> &path_) {
            host::functions.invoke_raw_unary(__sqf::unary__menuexpand__array__ret__nothing, {idc_, path_});
        }

        sqf_return_string menu_picture(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menupicture__control__array__ret__string, ctrl_, {path_});
        }

        sqf_return_string menu_picture(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menupicture__array__ret__string, {idc_, path_});
        }

        void menu_set_action(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusetaction__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_action(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusetaction__array__ret__nothing, {idc_, path_, value_});
        }

        void menu_set_check(const control &ctrl_, const std::vector<int> &path_, bool value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusetcheck__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_check(float idc_, const std::vector<int> &path_, bool value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusetcheck__array__ret__nothing, {idc_, path_, value_});
        }

        void menu_set_data(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusetdata__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_data(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusetdata__array__ret__nothing, {idc_, path_, value_});
        }

        void menu_set_picture(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusetpicture__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_picture(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusetpicture__array__ret__nothing, {idc_, path_, value_});
        }

        void menu_set_shortcut(const control &ctrl_, const std::vector<int> &path_, int value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusetshortcut__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_shortcut(float idc_, const std::vector<int> &path_, int value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusetshortcut__array__ret__nothing, {idc_, path_, value_});
        }

        void menu_set_text(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusettext__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_text(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusettext__array__ret__nothing, {idc_, path_, value_});
        }

        void menu_set_url(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menuseturl__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_url(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menuseturl__array__ret__nothing, {idc_, path_, value_});
        }

        void menu_set_value(const control &ctrl_, const std::vector<int> &path_, float value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusetvalue__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_set_value(float idc_, const std::vector<int> &path_, float value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusetvalue__array__ret__nothing, {idc_, path_, value_});
        }

        float menu_shortcut(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menushortcuttext__control__array__ret__string, ctrl_, {path_});
        }

        float menu_shortcut(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menushortcuttext__array__ret__string, {idc_, path_});
        }

        sqf_return_string menu_shortcut_text(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menushortcut__control__array__ret__scalar, ctrl_, {path_});
        }

        sqf_return_string menu_shortcut_text(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menushortcut__array__ret__scalar, {idc_, path_});
        }

        float menu_size(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menusize__control__array__ret__scalar, ctrl_, {path_});
        }

        float menu_size(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menusize__array__ret__scalar, {idc_, path_});
        }

        void menu_sort(const control &ctrl_, const std::vector<int> &path_, bool value_) {
            host::functions.invoke_raw_binary(__sqf::binary__menusort__control__array__ret__nothing, ctrl_, {path_, value_});
        }

        void menu_sort(float idc_, const std::vector<int> &path_, bool value_) {
            host::functions.invoke_raw_unary(__sqf::unary__menusort__array__ret__nothing, {idc_, path_, value_});
        }

        sqf_return_string menu_text(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menutext__control__array__ret__string, ctrl_, {path_});
        }

        sqf_return_string menu_text(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menutext__array__ret__string, {idc_, path_});
        }

        sqf_return_string menu_url(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menuurl__control__array__ret__string, ctrl_, {path_});
        }

        sqf_return_string menu_url(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menuurl__array__ret__string, {idc_, path_});
        }

        float menu_value(const control &ctrl_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__menuvalue__control__array__ret__scalar, ctrl_, {path_});
        }

        float menu_value(float idc_, const std::vector<int> &path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__menuvalue__array__ret__scalar, {idc_, path_});
        }

        void menu_clear(const control &ctrl_) {
            host::functions.invoke_raw_unary(__sqf::unary__menuclear__control__ret__nothing, ctrl_);
        }

        void menu_clear(float idc_) {
            host::functions.invoke_raw_unary(__sqf::unary__menuclear__scalar__ret__nothing, idc_);
        }

        std::vector<int> menu_hover(const control& ctrl_) {
            return __helpers::__convert_to_vector<int>(host::functions.invoke_raw_unary(__sqf::unary__menuhover__control__ret__array, ctrl_));
        }

        std::vector<int> menu_hover(float idc_) {
            return __helpers::__convert_to_vector<int>(host::functions.invoke_raw_unary(__sqf::unary__menuhover__scalar__ret__array, idc_));
        }

        void ctrl_set_text_color_secondary(const control &ctrl_, const rv_color &color_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlsettextcolorsecondary__control__array__ret__nothing, ctrl_, color_);
        }

        void ctrl_map_set_position(const control &ctrl_, const vector2 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlmapsetposition__control__array__ret__nothing, ctrl_, pos_);
        }

        void ctrl_map_set_position(const control &ctrl_, float x_, float y_, float width_, float height_) {
            host::functions.invoke_raw_binary(__sqf::binary__ctrlmapsetposition__control__array__ret__nothing, ctrl_, {x_, y_, width_, height_});
        }

        rv_ctrl_position ctrl_map_position(const control& map_) {
            return rv_ctrl_position(host::functions.invoke_raw_unary(__sqf::unary__ctrlmapposition__control__ret__array, map_));
         }

        game_value ctrl_map_mouse_over(const control& map_) {
            return host::functions.invoke_raw_unary(__sqf::unary__ctrlmapmouseover__control__ret__array, map_);
        }

        vector2 get_texture_info(sqf_string_const_ref path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__gettextureinfo__string__ret__array, path_);
        }
    }  // namespace sqf
}  // namespace intercept
