#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
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
        void ctrl_remove_all_event_handlers(std::string value0_, control value1_);
        void ctrl_set_auto_scroll_delay(float value0_, control value1_);
        void ctrl_set_auto_scroll_rewind(bool value0_, control value1_);
        void ctrl_set_auto_scroll_speed(float value0_, control value1_);
        void ctrl_set_checked(bool value0_, control value1_);
        void ctrl_set_fade(float value0_, control value1_);
        void ctrl_set_font(std::string value0_, control value1_);
        void ctrl_set_font_h1(std::string value0_, control value1_);
        void ctrl_set_font_h1b(std::string value0_, control value1_);
        void ctrl_set_font_h2(std::string value0_, control value1_);
        void ctrl_set_font_h2b(std::string value0_, control value1_);
        void ctrl_set_font_h3(std::string value0_, control value1_);
        void ctrl_set_font_h3b(std::string value0_, control value1_);
        void ctrl_set_font_h4(std::string value0_, control value1_);
        void ctrl_set_font_h4b(std::string value0_, control value1_);
        void ctrl_set_font_h5(std::string value0_, control value1_);
        void ctrl_set_font_h5b(std::string value0_, control value1_);
        void ctrl_set_font_h6(std::string value0_, control value1_);
        void ctrl_set_font_h6b(std::string value0_, control value1_);
        void ctrl_set_font_height(float value0_, control value1_);
        void ctrl_set_font_height_h1(float value0_, control value1_);
        void ctrl_set_font_height_h2(float value0_, control value1_);
        void ctrl_set_font_height_h3(float value0_, control value1_);
        void ctrl_set_font_height_h4(float value0_, control value1_);
        void ctrl_set_font_height_h5(float value0_, control value1_);
        void ctrl_set_font_height_h6(float value0_, control value1_);
        void ctrl_set_font_height_secondary(float value0_, control value1_);
        void ctrl_set_font_p(std::string value0_, control value1_);
        void ctrl_set_font_p(float value0_, control value1_);
        void ctrl_set_font_pb(std::string value0_, control value1_);
        void ctrl_set_font_secondary(std::string value0_, control value1_);
        void ctrl_set_model(std::string value0_, control value1_);
        void ctrl_set_model_scale(float value0_, control value1_);
        void ctrl_set_scale(float value0_, control value1_);
        void ctrl_set_structured_text(control value0_, std::string value1_);
        void ctrl_set_text(std::string value0_, control value1_);
        void ctrl_set_text_secondary(std::string value0_, control value1_);
        void ctrl_set_tooltip(std::string value0_, control value1_);
        void ctrl_show(bool value0_, control value1_);     
    }
}
