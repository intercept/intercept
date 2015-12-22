/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Functions for manipulating UI controls.

These are all part of the RV Engine UI system.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
	namespace sqf {
		void ctrl_activate(const control &value_);
		float ctrl_auto_scroll_delay(const control &value_);
		bool ctrl_auto_scroll_rewind(const control &value_);
		float ctrl_auto_scroll_speed(const control &value_);
		bool ctrl_checked(const control &value_);
		std::string ctrl_class_name(const control &value_);
		bool ctrl_committed(const control &value_);
		bool ctrl_delete(const control &value_);
		bool ctrl_enabled(const control &value_);
		bool ctrl_enabled(float value_);
		float ctrl_fade(const control &value_);
		bool ctrl_htmlloaded(const control &value_);
		float ctrl_idc(const control &value_);
		float ctrl_idd(const display &value_);
		void ctrl_map_anim_clear(const control &value_);
		void ctrl_map_anim_commit(const control &value_);
		bool ctrl_map_anim_done(const control &value_);
		float ctrl_map_scale(const control &value_);
		std::string ctrl_model(const control &value_);
		float ctrl_model_scale(const control &value_);
		display ctrl_parent(const control &value_);
		control ctrl_parent_controls_group(const control &value_);
		float ctrl_scale(const control &value_);
		void ctrl_set_focus(const control &value_);
		bool ctrl_shown(const control &value_);
		std::string ctrl_text(const control &value_);
		std::string ctrl_text(float value_);
		float ctrl_text_height(const control &value_);
		std::string ctrl_text_secondary(const control &value_);
		float ctrl_type(const control &value_);
		bool ctrl_visible(float value_);

		void ctrl_commit(const control &value0_, float value1_);
        void ctrl_enable(int control_id_, bool enable_);
        void ctrl_enable(const control &control_, bool enable_);
		void ctrl_remove_all_event_handlers(const control &value0_, const std::string& value1_);
		void ctrl_set_auto_scroll_delay(const control &value0_, float value1_);
		void ctrl_set_auto_scroll_rewind(const control &value0_, bool value1_);
		void ctrl_set_auto_scroll_speed(const control &value0_, float value1_);
		void ctrl_set_checked(const control &value0_, bool value1_);
		void ctrl_set_fade(const control &value0_, float value1_);
		void ctrl_set_font(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h1(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h1b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h2(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h2b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h3(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h3b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h4(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h4b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h5(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h5b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h6(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h6b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_height(const control &value0_, float value1_);
		void ctrl_set_font_height_h1(const control &value0_, float value1_);
		void ctrl_set_font_height_h2(const control &value0_, float value1_);
		void ctrl_set_font_height_h3(const control &value0_, float value1_);
		void ctrl_set_font_height_h4(const control &value0_, float value1_);
		void ctrl_set_font_height_h5(const control &value0_, float value1_);
		void ctrl_set_font_height_h6(const control &value0_, float value1_);
		void ctrl_set_font_height_secondary(const control &value0_, float value1_);
		void ctrl_set_font_p(const control &value0_, const std::string& value1_);
		void ctrl_set_font_p(const control &value0_, float value1_);
		void ctrl_set_font_pb(const control &value0_, const std::string& value1_);
		void ctrl_set_font_secondary(const control &value0_, const std::string& value1_);
		void ctrl_set_model(const control &value0_, const std::string& value1_);
		void ctrl_set_model_scale(const control &value0_, float value1_);
		void ctrl_set_scale(const control &value0_, float value1_);
		void ctrl_set_structured_text(const control &value0_, const std::string& value1_);
		void ctrl_set_text(const control &value0_, const std::string& value1_);
        void ctrl_set_text(int control_id_, const std::string &text_);
		void ctrl_set_text_secondary(const control &value0_, const std::string& value1_);
		void ctrl_set_tooltip(const control &value0_, const std::string& value1_);
		void ctrl_show(const control &value0_, bool value1_);
        void ctrl_show(int control_id_, bool show_);
    }
}
