#include "ctrl.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
		namespace ctrl {
			void ctrl_activate(control value_) {
				__helpers::__empty_unary_control(client::__sqf::unary__ctrlactivate__control__ret__nothing, value_);
			}

			float ctrl_auto_scroll_delay(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrlautoscrolldelay__control__ret__scalar, value_);
			}

			bool ctrl_auto_scroll_rewind(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrlautoscrollrewind__control__ret__bool, value_);
			}

			float ctrl_auto_scroll_speed(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrlautoscrollspeed__control__ret__scalar, value_);
			}

			bool ctrl_checked(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrlchecked__control__ret__bool, value_);
			}

			std::string ctrl_class_name(control value_) {
				return __helpers::__string_unary_control(client::__sqf::unary__ctrlclassname__control__ret__string, value_);
			}

			bool ctrl_committed(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrlcommitted__control__ret__bool, value_);
			}

			bool ctrl_delete(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrldelete__control__ret__bool, value_);
			}

			bool ctrl_enabled(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrlenabled__control__ret__bool, value_);
			}

			bool ctrl_enabled(float value_) {
				return __helpers::__bool_unary_number(client::__sqf::unary__ctrlenabled__scalar__ret__bool, value_);
			}

			float ctrl_fade(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrlfade__control__ret__scalar, value_);
			}

			bool ctrl_htmlloaded(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrlhtmlloaded__control__ret__bool, value_);
			}

			float ctrl_idc(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrlidc__control__ret__scalar, value_);
			}

			float ctrl_idd(display value_) {
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__ctrlidd__display__ret__scalar, value_));
			}

			void ctrl_map_anim_clear(control value_) {
				__helpers::__empty_unary_control(client::__sqf::unary__ctrlmapanimclear__control__ret__nothing, value_);
			}

			void ctrl_map_anim_commit(control value_) {
				__helpers::__empty_unary_control(client::__sqf::unary__ctrlmapanimcommit__control__ret__nothing, value_);
			}

			bool ctrl_map_anim_done(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrlmapanimdone__control__ret__bool, value_);
			}

			float ctrl_map_scale(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrlmapscale__control__ret__scalar, value_);
			}

			std::string ctrl_model(control value_) {
				return __helpers::__string_unary_control(client::__sqf::unary__ctrlmodel__control__ret__string, value_);
			}

			float ctrl_model_scale(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrlmodelscale__control__ret__scalar, value_);
			}

			display ctrl_parent(control value_) {
				return display(host::functions.invoke_raw_unary(client::__sqf::unary__ctrlparent__control__ret__display, value_));
			}

			control ctrl_parent_controls_group(control value_) {
				return control(host::functions.invoke_raw_unary(client::__sqf::unary__ctrlparentcontrolsgroup__control__ret__control, value_));
			}

			float ctrl_scale(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrlscale__control__ret__scalar, value_);
			}

			void ctrl_set_focus(control value_) {
				__helpers::__empty_unary_control(client::__sqf::unary__ctrlsetfocus__control__ret__nothing, value_);
			}

			bool ctrl_shown(control value_) {
				return __helpers::__bool_unary_control(client::__sqf::unary__ctrlshown__control__ret__bool, value_);
			}

			std::string ctrl_text(control value_) {
				return __helpers::__string_unary_control(client::__sqf::unary__ctrltext__control__ret__string, value_);
			}

			std::string ctrl_text(float value_) {
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__ctrltext__scalar__ret__string, value_));
			}

			float ctrl_text_height(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrltextheight__control__ret__scalar, value_);
			}

			std::string ctrl_text_secondary(control value_) {
				return __helpers::__string_unary_control(client::__sqf::unary__ctrltextsecondary__control__ret__string, value_);
			}

			float ctrl_type(control value_) {
				return __helpers::__number_unary_control(client::__sqf::unary__ctrltype__control__ret__scalar, value_);
			}

			bool ctrl_visible(float value_) {
				return __helpers::__bool_unary_number(client::__sqf::unary__ctrlvisible__scalar__ret__bool, value_);
			}

			void ctrl_commit(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlcommit__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_enable(control value0_, bool value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlenable__control__bool__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_remove_all_event_handlers(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlremovealleventhandlers__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_auto_scroll_delay(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetautoscrolldelay__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_auto_scroll_rewind(control value0_, bool value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetautoscrollrewind__control__bool__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_auto_scroll_speed(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetautoscrollspeed__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_checked(control value0_, bool value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetchecked__control__bool__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_fade(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfade__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfont__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h1(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth1__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h1b(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth1b__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h2(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth2__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h2b(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth2b__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h3(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth3__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h3b(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth3b__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h4(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth4__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h4b(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth4b__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h5(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth5__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h5b(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth5b__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h6(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth6__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_h6b(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth6b__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheight__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height_h1(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth1__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height_h2(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth2__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height_h3(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth3__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height_h4(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth4__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height_h5(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth5__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height_h6(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth6__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_height_secondary(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheightsecondary__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_p(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontp__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_p(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontp__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_pb(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontpb__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_font_secondary(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontsecondary__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_model(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetmodel__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_model_scale(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetmodelscale__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_scale(control value0_, float value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetscale__control__scalar__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_structured_text(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetstructuredtext__control__text__ret__nothing, value0_, game_value(value1_));
			}

			void ctrl_set_text(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsettext__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_text_secondary(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsettextsecondary__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_set_tooltip(control value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsettooltip__control__string__ret__nothing, game_value(value0_), value1_);
			}

			void ctrl_show(control value0_, bool value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__ctrlshow__control__bool__ret__nothing, game_value(value0_), value1_);
			}
		}
    }
}
