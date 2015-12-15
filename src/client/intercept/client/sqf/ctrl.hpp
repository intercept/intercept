#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
	namespace sqf {
		namespace ctrl {
			void ctrl_activate(control value_);
			float ctrl_auto_scroll_delay(control value_);
			bool ctrl_auto_scroll_rewind(control value_);
			float ctrl_auto_scroll_speed(control value_);
			bool ctrl_checked(control value_);
			std::string ctrl_class_name(control value_);
			bool ctrl_committed(control value_);
			bool ctrl_delete(control value_);
			bool ctrl_enabled(control value_);
			bool ctrl_enabled(float value_);
			float ctrl_fade(control value_);
			bool ctrl_htmlloaded(control value_);
			float ctrl_idc(control value_);
			float ctrl_idd(display value_);
			void ctrl_map_anim_clear(control value_);
			void ctrl_map_anim_commit(control value_);
			bool ctrl_map_anim_done(control value_);
			float ctrl_map_scale(control value_);
			std::string ctrl_model(control value_);
			float ctrl_model_scale(control value_);
			display ctrl_parent(control value_);
			control ctrl_parent_controls_group(control value_);
			float ctrl_scale(control value_);
			void ctrl_set_focus(control value_);
			bool ctrl_shown(control value_);
			std::string ctrl_text(control value_);
			std::string ctrl_text(float value_);
			float ctrl_text_height(control value_);
			std::string ctrl_text_secondary(control value_);
			float ctrl_type(control value_);
			bool ctrl_visible(float value_);

			void ctrl_commit(float value0_, control value1_);
			void ctrl_enable(bool value0_, control value1_);
			void ctrl_remove_all_event_handlers(const std::string& value0_, control value1_);
			void ctrl_set_auto_scroll_delay(float value0_, control value1_);
			void ctrl_set_auto_scroll_rewind(bool value0_, control value1_);
			void ctrl_set_auto_scroll_speed(float value0_, control value1_);
			void ctrl_set_checked(bool value0_, control value1_);
			void ctrl_set_fade(float value0_, control value1_);
			void ctrl_set_font(const std::string& value0_, control value1_);
			void ctrl_set_font_h1(const std::string& value0_, control value1_);
			void ctrl_set_font_h1b(const std::string& value0_, control value1_);
			void ctrl_set_font_h2(const std::string& value0_, control value1_);
			void ctrl_set_font_h2b(const std::string& value0_, control value1_);
			void ctrl_set_font_h3(const std::string& value0_, control value1_);
			void ctrl_set_font_h3b(const std::string& value0_, control value1_);
			void ctrl_set_font_h4(const std::string& value0_, control value1_);
			void ctrl_set_font_h4b(const std::string& value0_, control value1_);
			void ctrl_set_font_h5(const std::string& value0_, control value1_);
			void ctrl_set_font_h5b(const std::string& value0_, control value1_);
			void ctrl_set_font_h6(const std::string& value0_, control value1_);
			void ctrl_set_font_h6b(const std::string& value0_, control value1_);
			void ctrl_set_font_height(float value0_, control value1_);
			void ctrl_set_font_height_h1(float value0_, control value1_);
			void ctrl_set_font_height_h2(float value0_, control value1_);
			void ctrl_set_font_height_h3(float value0_, control value1_);
			void ctrl_set_font_height_h4(float value0_, control value1_);
			void ctrl_set_font_height_h5(float value0_, control value1_);
			void ctrl_set_font_height_h6(float value0_, control value1_);
			void ctrl_set_font_height_secondary(float value0_, control value1_);
			void ctrl_set_font_p(const std::string& value0_, control value1_);
			void ctrl_set_font_p(float value0_, control value1_);
			void ctrl_set_font_pb(const std::string& value0_, control value1_);
			void ctrl_set_font_secondary(const std::string& value0_, control value1_);
			void ctrl_set_model(const std::string& value0_, control value1_);
			void ctrl_set_model_scale(float value0_, control value1_);
			void ctrl_set_scale(float value0_, control value1_);
			void ctrl_set_structured_text(control value0_, const std::string& value1_);
			void ctrl_set_text(const std::string& value0_, control value1_);
			void ctrl_set_text_secondary(const std::string& value0_, control value1_);
			void ctrl_set_tooltip(const std::string& value0_, control value1_);
			void ctrl_show(bool value0_, control value1_);
		}
    }
}
