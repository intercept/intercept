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
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        enum class pixel_precision_types {
            AUTO,  //control position (x, y, w, h) is always rounded to whole pixels (game default)
            ON,    //control position (x, y, w, h) is rounded to whole pixels only when not animating
            OFF    //control position (x, y, w, h) is always precise, no pixel rounding applies here
        };

        struct rv_ctrl_angle {
            float angle {};
            float x_center{};
            float y_center{};
            rv_ctrl_angle(const game_value &gv_)
                : angle(gv_[0]),
                  x_center(gv_[1]),
                  y_center(gv_[2]) {}
        };
        struct rv_ctrl_text_selection {
            sqf_string text{};
            float start_pos{};
            float length{};
            explicit rv_ctrl_text_selection(const game_value &gv_)
                : start_pos(gv_[0]),
                  length(gv_[1]),
                  text(gv_[2]) {}
        };
        struct rv_lnb_array {
            sqf_string texts;
            sqf_string datas;
            std::vector<float> values;
            operator game_value() {
                std::vector<game_value> texts_gv, values_gv, datas_gv;
                for (auto& item : texts) {
                    texts_gv.emplace_back(item);
                }
                for (auto& item : values) {
                    values_gv.emplace_back(item);
                }
                for (auto& item : datas) {
                    datas_gv.emplace_back(item);
                }
                return game_value(std::vector<game_value>({texts_gv,
                                                           values_gv,
                                                           datas_gv}));
            }

            operator game_value() const {
                std::vector<game_value> texts_gv, values_gv, datas_gv;
                for (auto item : texts) {
                    texts_gv.emplace_back(item);
                }
                for (auto item : values) {
                    values_gv.emplace_back(item);
                }
                for (auto item : datas) {
                    datas_gv.emplace_back(item);
                }
                return game_value(std::vector<game_value>({texts_gv,
                                                           values_gv,
                                                           datas_gv}));
            }
        };

        struct rv_ctrl_position {
            float x, y, w, h;
            explicit rv_ctrl_position(const game_value& gv_)
                : x(gv_[0]), y(gv_[1]), w(gv_[2]), h(gv_[3])
            {}
        };

        struct rv_ct_list {
            int header_index;
            std::vector<control> controls;
        };

        struct rv_resolution {
            vector2 resolution;
            vector2 viewport;
            float aspect_ratio;
            float ui_scale;
            vector2 fov;
            float texture_quality;
            bool triple_head;

            explicit rv_resolution(const game_value& gv_)
                : resolution(gv_[0], gv_[1]),
                  viewport(gv_[2], gv_[3]),
                  aspect_ratio(gv_[4]),
                  ui_scale(gv_[5]),
                  fov(gv_[7], gv_[6]),
                  triple_head(gv_[8]),
                  texture_quality(gv_[9])
            {}
           
        };

        /*ctrl_ */

        control ctrl_create(const display &display_, sqf_string_const_ref class_, int idc_);
        control ctrl_create(const display &display_, sqf_string_const_ref class_, int idc_, const control &controls_group_);

        bool ctrl_auto_scroll_rewind(const control &ctrl_);
        bool ctrl_checked(const control &ctrl_);
        bool ctrl_checked(const control &control_, int index_);
        bool ctrl_committed(const control &ctrl_);
        bool ctrl_delete(const control &ctrl_);
        bool ctrl_enabled(const control &ctrl_);
        bool ctrl_enabled(float value_);
        bool ctrl_htmlloaded(const control &ctrl_);
        bool ctrl_map_anim_done(const control &ctrl_);
        bool ctrl_shown(const control &ctrl_);
        bool ctrl_visible(float value_);
        void ctrl_commit(const control &ctrl0_, float value1_);
        void ctrl_enable(int control_id_, bool enable_);
        void ctrl_enable(const control &control_, bool enable_);
        void ctrl_set_disabled_color(const control &control_, const rv_color &color_);
        void ctrl_set_fade(const control &ctrl0_, float value1_);
        void ctrl_set_font(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h1(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h1b(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h2(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h2b(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h3(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h3b(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h4(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h4b(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h5(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h5b(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h6(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_h6b(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_height(const control &ctrl0_, float value1_);
        void ctrl_set_font_height_h1(const control &ctrl0_, float value1_);
        void ctrl_set_font_height_h2(const control &ctrl0_, float value1_);
        void ctrl_set_font_height_h3(const control &ctrl0_, float value1_);
        void ctrl_set_font_height_h4(const control &ctrl0_, float value1_);
        void ctrl_set_font_height_h5(const control &ctrl0_, float value1_);
        void ctrl_set_font_height_h6(const control &ctrl0_, float value1_);
        void ctrl_set_font_height_secondary(const control &ctrl0_, float value1_);
        void ctrl_set_font_p(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_p(const control &ctrl0_, float value1_);
        void ctrl_set_font_pb(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_font_secondary(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_model(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_model_scale(const control &ctrl0_, float value1_);
        void ctrl_set_scale(const control &ctrl0_, float value1_);
        void ctrl_set_structured_text(const control &ctrl0_, const rv_text &value1_);
        void ctrl_set_text(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_text(int control_id_, sqf_string_const_ref text_);
        void ctrl_set_text_secondary(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_set_tooltip(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_show(const control &ctrl0_, bool value1_);
        void ctrl_show(int control_id_, bool show_);
        void ctrl_set_foreground_color(const control &ctrl_, const rv_color &color_);
        void ctrl_set_model_dir_and_up(const control &ctrl_, const vector3 &dir_, const vector3 &up_);
        void ctrl_set_text_color(const control &ctrl_, const rv_color &color_);
        void ctrl_set_tooltip_color_box(const control &ctrl_, const rv_color &color_);
        void ctrl_set_tooltip_color_shade(const control &ctrl_, const rv_color &color_);
        void ctrl_set_tooltip_color_text(const control &ctrl_, const rv_color &color_);
        float ctrl_set_tooltip_max_width(const control &ctrl_, float width_);
        void ctrl_activate(const control &ctrl_);
        void ctrl_activate(const control &ctrl_, bool full_);
        void ctrl_map_anim_clear(const control &ctrl_);
        void ctrl_map_anim_commit(const control &ctrl_);
        void ctrl_map_cursor(const control &ctrl_, sqf_string_const_ref default_cursor_, sqf_string_const_ref new_cursor_);
        void ctrl_set_active_color(const control &ctrl_, const rv_color &color_);
        void ctrl_set_auto_scroll_delay(const control &ctrl0_, float value1_);
        void ctrl_set_auto_scroll_rewind(const control &ctrl0_, bool value1_);
        void ctrl_set_auto_scroll_speed(const control &ctrl0_, float value1_);
        void ctrl_set_background_color(const control &ctrl_, const rv_color &color_);
        void ctrl_set_checked(const control &ctrl0_, bool value1_);
        void ctrl_set_checked(const control &control_, int index_, bool checked_);
        void ctrl_set_focus(const control &ctrl_);
        float ctrl_auto_scroll_delay(const control &ctrl_);
        float ctrl_auto_scroll_speed(const control &ctrl_);
        float ctrl_fade(const control &ctrl_);
        float ctrl_idc(const control &ctrl_);
        float ctrl_idd(const display &value_);
        float ctrl_map_scale(const control &ctrl_);
        float ctrl_model_scale(const control &ctrl_);
        float ctrl_scale(const control &ctrl_);
        float ctrl_text_height(const control &ctrl_);
        float ctrl_type(const control &ctrl_);
        int ctrl_shadow(const control &ctrl_);
        void ctrl_set_shadow(const control &ctrl_, int shadow_);
        sqf_return_string ctrl_class_name(const control &ctrl_);
        sqf_return_string ctrl_model(const control &ctrl_);
        sqf_return_string ctrl_text(const control &ctrl_);
        sqf_return_string ctrl_text(float value_);
        sqf_return_string ctrl_text_secondary(const control &ctrl_);
        void ctrl_set_position(const control &ctrl_, float x_, float y_, float width_, float height_);

        void ctrl_set_positionh(const control &ctrl_, float height_);
        void ctrl_set_positionw(const control &ctrl_, float width_);
        void ctrl_set_positionx(const control &ctrl_, float x_);
        void ctrl_set_positiony(const control &ctrl_, float y_);

        rv_ctrl_position ctrl_position(const control &ctrl_);

        void ctrl_map_anim_add(const control &ctrl_, float time_, float zoom_, vector2 pos_);
        display ctrl_parent(const control &ctrl_);
        control ctrl_parent_controls_group(const control &ctrl_);
        std::vector<vector3> ctrl_model_dir_and_up(const control &ctrl_);

        vector2 ctrl_map_world_to_screen(const control &ctrl_, const std::variant<vector2, vector3> &position_);
        vector2 ctrl_map_screen_to_world(const control &ctrl_, const vector2 &screen_pos_);

        void ctrl_set_event_handler(const control &ctrl_, sqf_string_const_ref name_, sqf_string_const_ref command_);
        int ctrl_add_event_handler(const control &ctrl_, sqf_string_const_ref name_, sqf_string_const_ref command_);
        int ctrl_add_event_handler(const control &ctrl_, sqf_string_const_ref name_, const code &command_);
        void ctrl_remove_all_event_handlers(const control &ctrl0_, sqf_string_const_ref value1_);
        void ctrl_remove_event_handler(const control &ctrl_, sqf_string_const_ref name_, int id_);
        rv_color ctrl_background_color(const control &ctrl_);
        rv_color ctrl_foreground_color(const control &ctrl_);

        //listbox/combobox
        void lnb_delete_column(const control &ctrl_, float index_);
        void lnb_delete_row(const control &ctrl0_, float value1_);
        void lnb_set_cur_sel_row(float idc_, float index_);
        void lnb_set_cur_sel_row(const control &ctrl_, float index_);
        void lnb_delete_column(float idc_, float index_);
        void lnb_delete_row(float idc_, float index_);
        void lnb_set_color(float idc_, float row_, float column_, const rv_color &color_);
        void lnb_set_color(const control &ctrl_, float row_, float column_, const rv_color &color_);
        void lnb_set_color_right(float idc_, float row_, float column_, const rv_color &color_);
        void lnb_set_color_right(const control &ctrl_, float row_, float column_, const rv_color &color_);
        void lnb_set_columns_pos(float idc_, std::vector<float> positions_);
        void lnb_set_columns_pos(const control &ctrl_, std::vector<float> positions_);
        void lnb_set_data(float idc_, float row_, float column_, sqf_string_const_ref data_);
        void lnb_set_data(const control &ctrl_, float row_, float column_, sqf_string_const_ref data_);
        void lnb_set_picture(float idc_, float row_, float column_, sqf_string_const_ref name_);
        void lnb_set_picture(const control &ctrl_, float row_, float column_, sqf_string_const_ref name_);
        void lnb_set_picture_right(float idc_, float row_, float column_, sqf_string_const_ref name_);
        void lnb_set_picture_right(const control &ctrl_, float row_, float column_, sqf_string_const_ref name_);
        void lnb_set_text(float idc_, float row_, float column_, const game_value &data_);
        void lnb_set_text(const control &ctrl_, float row_, float column_, const game_value &data_);
        void lnb_set_text_right(float idc_, float row_, float column_, const game_value &data_);
        void lnb_set_text_right(const control &ctrl_, float row_, float column_, const game_value &data_);
        void lnb_set_tooltip(float idc_, float row_, float column_, const game_value &data_);
        void lnb_set_tooltip(const control &ctrl_, float row_, float column_, const game_value &data_);
        void lnb_set_value(float idc_, float row_, float column_, float value_);
        void lnb_set_value(const control &ctrl_, float row_, float column_, float value_);
        void lnb_clear(const control &ctrl_);
        void lnb_clear(float value_);
        float lnb_add_array(float idc_, const std::vector<rv_lnb_array> &lnb_array_);
        float lnb_add_array(const control &ctrl_, const std::vector<rv_lnb_array> &lnb_array_);
        float lnb_add_row(float idc_, sqf_string_list_const_ref strings_);
        float lnb_add_row(const control &ctrl_, sqf_string_list_const_ref strings_);
        float lnb_value(float idc_, float row_, float column_);
        float lnb_value(const control &ctrl_, float row_, float column_);
        float lnb_add_column(const control &ctrl0_, float value1_);
        float lnb_cur_sel_row(const control &ctrl_);
        float lnb_cur_sel_row(float value_);
        sqf_return_string lnb_data(float idc_, float row_, float column_);
        sqf_return_string lnb_data(const control &ctrl_, float row_, float column_);
        sqf_return_string lnb_picture(float idc_, float row_, float column_);
        sqf_return_string lnb_picture(const control &ctrl_, float row_, float column_);
        sqf_return_string lnb_text(float idc_, float row_, float column_);
        sqf_return_string lnb_text(const control &ctrl_, float row_, float column_);
        sqf_return_string lnb_text_right(float idc_, float row_, float column_);
        sqf_return_string lnb_text_right(const control &ctrl_, float row_, float column_);
        std::vector<float> lnb_get_columns_position(float idc_);
        std::vector<float> lnb_get_columns_position(const control &ctrl_);
        std::vector<float> lnb_size(float idc_);
        std::vector<float> lnb_size(const control &ctrl_);
        rv_color lnb_color(float idc_, float row_, float column_);
        rv_color lnb_color(const control &ctrl_, float row_, float column_);
        rv_color lnb_color_right(float idc_, float row_, float column_);
        rv_color lnb_color_right(const control &ctrl_, float row_, float column_);
        sqf_return_string lnb_picture_right(float idc_, float row_, float column_);
        sqf_return_string lnb_picture_right(const control &ctrl_, float row_, float column_);
        void lnb_sort(float idc_, int column_, bool reversed_ = false);
        void lnb_sort(const control &ctrl_, int column_, bool reversed_ = false);
        void lnb_sort_by_value(float idc_, int column_, bool reversed_ = false);
        void lnb_sort_by_value(const control &ctrl_, int column_, bool reversed_ = false);
        void lnb_sort_by(const control &ctrl_, int column_, sqf_string_const_ref sort_type_, bool reversed_ = false, bool case_sensitive_ = false);
        void lnb_sort_by(int ctrl_, int column_, sqf_string_const_ref sort_type_, bool reversed_ = false, bool case_sensitive_ = false);

        //listbox
        bool lb_is_selected(const control &ctrl0_, float value1_);
        void lb_delete(int control_id_, int index_);
        void lb_delete(const control &control_, int index_);
        // TODO std::vector<float> lb_selection(const control &control_); // USE lb_cur_sel IN A3 https://community.bistudio.com/wiki/lbSelection
        void lb_set_color(int control_id_, int index_, rv_color color_);
        void lb_set_color(const control &control_, int index_, const rv_color &color_);
        void lb_set_color_right(int control_id_, int index_, const rv_color &color_);
        void lb_set_color_right(const control &control_, int index_, const rv_color &color_);
        void lb_set_cur_sel(int control_id_, int index_);
        void lb_set_cur_sel(const control &control_, int index_);
        void lb_set_data(int control_id_, int index_, sqf_string_const_ref data_);
        void lb_set_data(const control &control_, int index_, sqf_string_const_ref data_);
        void lb_set_picture(int control_id_, int index_, sqf_string_const_ref name_);
        void lb_set_picture(const control &control_, int index_, sqf_string_const_ref name_);
        void lb_set_picture_right(int control_id_, int index_, sqf_string_const_ref name_);
        void lb_set_picture_right(const control &control_, int index_, sqf_string_const_ref name_);
        void lb_set_picture_color(int control_id_, int index_, const rv_color &color_);
        void lb_set_picture_color(const control &control_, int index_, const rv_color &color_);
        void lb_set_picture_color_disabled(int control_id_, int index_, const rv_color &color_);
        void lb_set_picture_color_disabled(const control &control_, int index_, const rv_color &color_);
        void lb_set_picture_color_selected(int control_id_, int index_, const rv_color &color_);
        void lb_set_picture_color_selected(const control &control_, int index_, const rv_color &color_);
        void lb_set_picture_right_color(const control &control_, int index_, const rv_color &color_);
        void lb_set_picture_right_color_disabled(const control &control_, int index_, const rv_color &color_);
        void lb_set_picture_right_color_selected(const control &control_, int index_, const rv_color &color_);
        void lb_set_text(const control &control_, int index_, sqf_string_const_ref text_);
        void lb_set_text_right(const control &control_, int index_, sqf_string_const_ref text_);
        void lb_set_tooltip(int control_id_, int index_, sqf_string_const_ref tooltip_);
        void lb_set_tooltip(const control &control_, int index_, sqf_string_const_ref tooltip_);
        void lb_set_value(int control_id_, int index_, float val_);
        void lb_set_value(const control &control_, int index_, float val_);
        void lb_clear(const control &ctrl_);
        void lb_clear(float value_);
        float lb_add(int control_id_, sqf_string_const_ref text_);
        float lb_add(const control &control_, sqf_string_const_ref text_);
        float lb_color(int control_id_, int index_);
        float lb_color(const control &control_, int index_);
        float lb_color_right(int control_id_, int index_);
        float lb_color_right(const control &control_, int index_);
        float lb_value(int control_id_, int index_);
        float lb_value(const control &control_, int index_);
        float lb_cur_sel(const control &ctrl_);
        float lb_cur_sel(float value_);
        float lb_size(const control &ctrl_);
        float lb_size(float value_);
        sqf_return_string lb_tooltip(const control &ctrl_, float index_);

        sqf_return_string lb_data(int control_id_, int index_);
        sqf_return_string lb_data(const control &control_, int index_);
        sqf_return_string lb_picture(int control_id_, int index_);
        sqf_return_string lb_picture(const control &control_, int index_);
        sqf_return_string lb_picture_right(int control_id_, int index_);
        sqf_return_string lb_picture_right(const control &control_, int index_);
        sqf_return_string lb_text(int control_id_, int index_);
        sqf_return_string lb_text(const control &control_, int index_);
        sqf_return_string lb_text_right(int control_id_, int index_);
        sqf_return_string lb_text_right(const control &control_, int index_);
        void lb_delete(const control &ctrl0_, float value1_);
        void lb_set_cur_sel(const control &ctrl0_, float value1_);
        float lb_value(const control &ctrl0_, float value1_);
        sqf_return_string lb_data(const control &ctrl0_, float value1_);
        sqf_return_string lb_picture(const control &ctrl0_, float value1_);
        sqf_return_string lb_picture_right(const control &ctrl0_, float value1_);
        sqf_return_string lb_text(const control &ctrl0_, float value1_);
        sqf_return_string lb_text_right(const control &ctrl0_, float value1_);

        //treeview
        void tv_set_text(float idc_, const std::vector<float> &path_, sqf_string_const_ref text_);
        void tv_set_text(const control &ctrl_, const std::vector<float> &path_, sqf_string_const_ref text_);
        void tv_collapse(int idc_, const std::vector<int> &path_);
        void tv_collapse(const control &ctrl_, const std::vector<int> &path_);
        void tv_delete(int idc_, const std::vector<int> &path_);
        void tv_delete(const control &ctrl_, const std::vector<int> &path_);
        void tv_expand(int idc_, const std::vector<int> &path_);
        void tv_expand(const control &ctrl_, const std::vector<int> &path_);
        void tv_set_cur_sel(int idc_, const std::vector<int> &path_);
        void tv_set_cur_sel(const control &ctrl_, const std::vector<int> &path_);
        void tv_set_data(int idc_, const std::vector<int> &path_, sqf_string_const_ref data_);
        void tv_set_data(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref data_);
        void tv_set_picture(int idc_, const std::vector<int> &path_, sqf_string_const_ref name_);
        void tv_set_picture(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref name_);
        void tv_set_picture_right(int idc_, const std::vector<int> &path_, sqf_string_const_ref name_);
        void tv_set_picture_right(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref name_);
        void tv_set_picture_color(int idc_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_picture_color(const control &ctrl_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_picture_right_color(int idc_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_picture_right_color(const control &ctrl_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_tooltip(int idc_, const std::vector<int> &path_, sqf_string_const_ref text_);
        void tv_set_tooltip(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref text_);
        void tv_set_value(const control &ctrl_, const std::vector<int> &path_, float value_);
        void tv_set_value(int idc_, const std::vector<int> &path_, float value_);
        void tv_sort(const control &ctrl_, const std::vector<int> &path_, bool reversed_ = false);
        void tv_sort_by_value(const control &ctrl_, const std::vector<int> &path_, bool reversed_ = false);
        void tv_clear(float value_);
        void tv_clear(const control &ctrl_);
        //#TODO typedef for const std::vector<int>
        sqf_return_string tv_data(int idc_, const std::vector<int> &path_);
        sqf_return_string tv_data(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string tv_picture(int idc_, const std::vector<int> &path_);
        sqf_return_string tv_picture(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string tv_picture_right(int idc_, const std::vector<int> &path_);
        sqf_return_string tv_picture_right(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string tv_text(int idc_, const std::vector<int> &path_);
        sqf_return_string tv_text(const control &ctrl_, const std::vector<int> &path_);
        float tv_value(int idc_, const std::vector<int> &path_);
        float tv_value(const control &ctrl_, const std::vector<int> &path_);
        int tv_add(int idc_, const std::vector<int> &path_, sqf_string_const_ref text_);
        int tv_add(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref text_);
        int tv_count(int idc_, const std::vector<int> &path_);
        int tv_count(const control &ctrl_, const std::vector<int> &path_);

        std::vector<int> tv_cursel(int idc_);
        std::vector<int> tv_cursel(const control &ctrl_);
        std::vector<std::vector<int>> tv_selection(const control &ctrl_);

        void tv_set_color(const control &control_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_picture_color_disabled(const control &control_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_picture_color_selected(const control &control_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_picture_color__right_selected(const control &control_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_picture_color__right_disabled(const control &control_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_select_color(const control &control_, const std::vector<int> &path_, const rv_color &color_);
        void tv_set_text(const control &control_, const std::vector<int> &path_, sqf_string_const_ref text_);
        sqf_return_string tv_tooltip(const control &control_, const std::vector<int> &path_);
        void tv_collapse_all(int idc_);
        void tv_collapse_all(const control &control_);
        void tv_expand_all(int idc_);
        void tv_expand_all(const control &control_);

        //Slider
        void slider_set_range(float value0_, float value1_, float value2_);
        void slider_set_range(const control &slider_, float min_, float max_);
        void slider_set_speed(float value0_, float value1_, float value2_);
        void slider_set_speed(const control &ctrl0_, float value1_, float value2_);
        void slider_set_position(float value0_, float value1_);
        void slider_set_position(const control &ctrl0_, float value1_);
        vector2 slider_range(const float &value_);
        vector2 slider_range(const control &ctrl_);
        vector2 slider_speed(const float &value_);
        vector2 slider_speed(const control &ctrl_);
        float slider_position(const control &ctrl_);
        float slider_position(float value_);

        //Overlay
        void clear_overlay(const control &map_);
        void close_overlay(const control &map_);
        void commit_overlay(const control &map_);
        void save_overlay(const control &ctrl_);
        void load_overlay(const control &a_control_, const config &a_config_);
        void new_overlay(const control &a_control_, const config &a_config_);

        //cut
        //NULAR -- https://github.com/intercept/intercept/issues/13
        sqf_return_string_list all_cut_layers();
        int cut_fade_out(sqf_string_const_ref layer_name_, float duration_);
        int cut_fade_out(int layer_, float duration_);
        int cut_obj(sqf_string_const_ref layer_name_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_);
        int cut_obj(int layer_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_);
        int cut_rsc(sqf_string_const_ref layer_name_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_);
        int cut_rsc(int layer_, sqf_string_const_ref class_, sqf_string_const_ref type_, float speed_, bool show_on_map_);
        int cut_text(sqf_string_const_ref layer_name_, sqf_string_const_ref text_, sqf_string_const_ref type_, float speed_, bool show_on_map_);
        int cut_text(int layer_, sqf_string_const_ref text_, sqf_string_const_ref type_, float speed_, bool show_on_map_);
        

        //Array in format [<string:type>, <string:effect>, <number:speed>, <boolean:showInMap>] or []
        game_value active_title_effect_params(float title_);
        

        void title_fade_out(float value_);

        bool open_dlc_page(float value_);
        bool open_map(bool value_);
        bool open_youtube_video(sqf_string_const_ref value_);
        bool open_map(bool show_, bool forced_);
        bool show_subtitles(bool value_);

        struct rv_subtitle_options {
            bool subtitles;
            bool radioSubtitles;

            rv_subtitle_options(const game_value& data_) :
                subtitles(data_[0]),
                radioSubtitles(data_[1]) {
            }
        };

        rv_subtitle_options get_subtitle_options();

        void create_gear_dialog(const object &unit_, sqf_string_const_ref resource_);
        bool dialog();
        display display_null();
        void disable_serialization();
        void enable_end_dialog();
        void end_loading_screen();
        float pixel_h();
        float pixel_w();

        void set_compass_oscillation(float angle_, float freq_min_, float freq_max_);
        void set_compass_declination(float angle_);
        void set_hud_movement_levels(float min_speed_, float max_speed_, float min_alt_, float max_alt_, float min_dir_, float max_dir_, const object &obj_);
        void set_hud_movement_levels(float min_speed_, float max_speed_, float min_alt_, float max_alt_, float min_dir_, float max_dir_, const vector3 &pos_);
        void start_loading_screen(sqf_string_const_ref text_);
        void start_loading_screen(sqf_string_const_ref text_, sqf_string_const_ref resource_);
        display create_mission_display(const display &display_, sqf_string_const_ref mission_);
        display create_mp_campaign_display(const display &display_, sqf_string_const_ref mission_);

        float pixel_grid();
        float pixel_grid_base();
        float pixel_grid_no_ui_scale();
        int shown_score_table();
        int display_add_event_handler(const display &display_, sqf_string_const_ref event_name_, sqf_string_const_ref code_);
        int display_add_event_handler(const display &display_, sqf_string_const_ref event_name_, const code &code_);
        void display_remove_eventhandler(const display &display_, sqf_string_const_ref event_name_, int id_);
        void display_set_eventhandler(const display &display_, sqf_string_const_ref event_name_, sqf_string_const_ref code_);
        void display_remove_all_event_handlers(sqf_string_const_ref value0_, const display &value1_);
        display find_display(float value_);
        display find_display(sqf_string_const_ref value_);
        display display_child(const display &disp_);

        bool is_tut_hints_enabled();
        void hint_c(sqf_string_const_ref value_);
        void hint_c(sqf_string_const_ref value0_, sqf_string_const_ref value1_);
        void hint(sqf_string_const_ref text_);
        void hint_cadet(sqf_string_const_ref text_);
        void hint_silent(sqf_string_const_ref text_);
        void hintc(sqf_string_const_ref title_, sqf_string_list_const_ref content_);
        void task_hint(sqf_string_const_ref text_, const rv_color &color_, sqf_string_const_ref icon_);

        bool visible_watch();
        bool visible_map();
        bool visible_gps();
        bool visible_compass();
        bool cb_checked(const control &control_);
        void cb_set_checked(const control &ctrl0_, bool value1_);
        bool create_dialog(sqf_string_const_ref dialog_name_);
        display create_dialog(sqf_string_const_ref dialog_name_, bool force_on_top_ = false);

        bool is_real_time(const control &ctrl_);
        bool is_showing(const control &ctrl_);

        bool map_anim_done();

        //show / shown
        bool shown_artillerycomputer();
        bool shown_compass();
        bool shown_gps();
        bool shown_hud();
        bool shown_map();
        bool shown_pad();
        bool shown_radio();
        bool shown_uavfeed();
        bool shown_warrant();
        bool shown_watch();

        void show_cinema_border(bool value_);
        void show_commanding_menu(sqf_string_const_ref value_);
        void show_compass(bool value_);
        void show_gps(bool value_);
        void show_hud(bool show_);
        void show_hud(bool hud_, bool info_, bool radar_, bool compass_, bool direction_, bool menu_, bool group_, bool cursors_);
        void show_map(bool value_);
        void show_pad(bool value_);
        void show_radio(bool value_);
        void show_uavfeed(bool value_);
        void show_warrant(bool value_);
        void show_watch(bool value_);
        bool hc_shown_bar();
        void hc_show_bar(bool value_);

        //Somewhat unsorted stuff //#sort

        bool preload_title_obj(sqf_string_const_ref name_, sqf_string_const_ref type_);
        bool preload_title_obj(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_, bool show_in_map_);  // speed is ignored - source: BIKI
        bool preload_title_rsc(sqf_string_const_ref name_, sqf_string_const_ref type_);
        bool preload_title_rsc(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_, bool show_in_map_);  // speed is ignored - source: BIKI
        /* potential namespace: gui, ui */
        void cut_obj(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_ = 1.0f);
        void cut_rsc(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_ = 1.0f, bool show_on_map_ = false);
        void cut_text(sqf_string_const_ref name_, sqf_string_const_ref type_, float speed_ = 1.0f, bool show_on_map_ = false);
        void title_cut(sqf_string_const_ref text_, sqf_string_const_ref type_, const float &speed_ = 1);
        void title_obj(sqf_string_const_ref class_, sqf_string_const_ref type_, const float &speed_ = 1, bool show_on_map_ = false);
        void title_rsc(sqf_string_const_ref text_, sqf_string_const_ref type_, const float &speed_ = 1);
        void title_text(sqf_string_const_ref text_, sqf_string_const_ref type_, const float &speed_ = 1);
        void map_anim_add(float time_, float zoom_, const object &object_);
        void map_anim_add(float time_, float zoom_, const vector3 &pos_);

        void close_dialog(float val_);
        void close_display(float value0_, const display &value1_);

        //@TODO: draw_icon could stand to have a few enums probably for arguments like shadow and align.
        void draw_icon(const control &ctrl_, sqf_string_const_ref texture_, const rv_color &color_, const vector2 &pos_, float width_, float height_, float angle_, sqf_string_const_ref text_, uint32_t shadow_, float text_size_, sqf_string_const_ref font_, sqf_string_const_ref align_);
        void draw_icon(const control &ctrl_, sqf_string_const_ref texture_, const rv_color &color_, const object &pos_, float width_, float height_, float angle_, sqf_string_const_ref text_, uint32_t shadow_, float text_size_, sqf_string_const_ref font_, sqf_string_const_ref align_);

        void draw_rectangle(const control &ctrl_, vector2 center_pos_, float a_, float b_, float angle_, const rv_color &color_, sqf_string_const_ref fill_texture_);

        void collapse_object_tree(const control &ctrl_);
        void import_all_groups(const control &ctrl_);

        void restart_editor_camera(const control &ctrl_);
        void selected_editor_objects(const control &ctrl_);
        void update_object_tree(const control &ctrl_);
        void allow3dmode(const control &ctrl0_, bool value1_);
        void allow_file_operations(const control &ctrl0_, bool value1_);
        void create_menu(const control &ctrl0_, float value1_);
        void html_load(const control &ctrl0_, sqf_string_const_ref value1_);

        void map_center_on_camera(const control &main_map, bool enable_);
        void move_object_to_end(const control &ctrl0_, sqf_string_const_ref value1_);
        void progress_set_position(const control &ctrl0_, float value1_);
        void remove_menu_item(const control &ctrl0_, float value1_);
        void remove_menu_item(const control &ctrl0_, sqf_string_const_ref value1_);
        void set_editor_mode(const control &ctrl0_, sqf_string_const_ref value1_);
        void show3dicons(const control &ctrl0_, bool value1_);
        void show_legend(const control &ctrl0_, bool value1_);
        /* potential namespace: controls, ui, gui, misc */
        void button_set_action(int control_id_, sqf_string_const_ref code_);
        void button_set_action(const control &control_, sqf_string_const_ref action_);
        void map_anim_clear();
        void map_anim_commit();
        void force_map(bool value_);
        void in_game_ui_set_event_handler(sqf_string_const_ref name_, sqf_string_const_ref command_);

        float gear_slot_ammo_count(const control &ctrl_);
        float next_menu_item_index(const control &ctrl_);
        float progress_position(const control &ctrl_);
        float safe_zone_x();
        float safe_zone_y();
        float safe_zone_h();
        float safe_zone_w();
        float safe_zone_x_abs();
        float safe_zone_w_abs();

        sqf_return_string button_action(const control &control_);
        sqf_return_string button_action(int idc_);

        sqf_return_string gear_slot_data(const control &ctrl_);
        sqf_return_string get_editor_mode(const control &ctrl_);
        sqf_return_string get_editor_object_scope(const control &ctrl0_, sqf_string_const_ref value1_);
        sqf_return_string map_grid_position(const object &obj_);
        sqf_return_string map_grid_position(const vector2 &pos_);
        display create_display(sqf_string_const_ref value0_, const display &value1_);
        display create_mission_display(sqf_string_const_ref value0_, const display &value1_);
        control control_null();
        control controls_group_ctrl(const control &ctrl0_, float value1_);
        control display_ctrl(const display &disp_, float idc_);
        control display_ctrl(float idc_);
        vector3 map_center_on_camera(const control &mini_map_);

        vector2 pos_screen_to_world(const control &ctrl_, const vector2 &pos_);
        vector2 pos_world_to_screen(const control &ctrl_, const vector2 &pos_);
        std::vector<control> all_controls(const display &display_);
        std::vector<control> all_controls(const control &ctrl_);
        object get_editor_camera(const control &ctrl_);
        object get_object_proxy(const control &ctrl0_, sqf_string_const_ref value1_);

        display display_parent(const display &display_);

        bool visible_score_table();
        void show_score_table(int force_);
        bool is_pip_enabled();
        void set_mouse_position(float x_, float y_);

        void set_pip_effect(sqf_string_const_ref parameter_left, const game_value &parameters_left);

        void slider_set_speed(const control &slider_, float line_, int page_);
        int lnb_add_row(int idc_, sqf_string_list_const_ref items_);
        std::pair<bool, bool> forced_map();
        void progress_loading_screen(float value_);
        void look_at_pos(const control &map_, const vector3 &position_);
        rv_ct_list ct_add_header(const control &control_);
        rv_ct_list ct_add_row(const control &control_);
        void ct_clear(const control &control_);
        int ct_cur_sel(const control &control_);
        int ct_header_count(const control &control_);
        int ct_row_count(const control &control_);
        void lb_sort(const control &control_);
        void lb_sort(const control &control_, sqf_string_const_ref sort_order_);
        void lb_sort(int control_, sqf_string_const_ref sort_order_);
        void lb_sort(int control_);
        void lb_sort_by_value(const control& control_);
        void lb_sort_by_value(int control_);
        void lb_sort_by(const control &control_, sqf_string_const_ref sort_type_, bool reversed_ = false, bool case_sensitive_ = false);
        void lb_sort_by(int control_, sqf_string_const_ref sort_type_, bool reversed_ = false, bool case_sensitive_ = false);

        sqf_return_string ct_data(const control &control_, int index_);
        std::vector<float> ct_find_header_rows(const control &control_, int index_);
        int ct_find_row_header(const control &control_, int index_);
        std::vector<control> ct_header_controls(const control &control_, int index_);
        void ct_remove_headers(const control &control_, const std::vector<int> &header_indexes_);
        void ct_remove_rows(const control &control_, const std::vector<int> &row_indexes_);
        std::vector<control> ct_row_controls(const control &control_, int index_);
        void ct_set_cur_sel(const control &control_, int index_);
        void ct_set_data(const control &control_, int index_, sqf_string_const_ref data_);
        void ct_set_header_template(const control &control_, const config &config_);
        void ct_set_row_template(const control &control_, const config &config_);
        void ct_set_value(const control &control_, float value_);
        float ct_value(const control &control_, float index_);
        rv_resolution get_resolution();
        vector2 get_mouse_position();
        bool is_ui_context();
        void ctrl_animate_model(const control &control_, sqf_string_const_ref source_, float phase_);
        float ctrl_animation_phase_model(const control &control_, sqf_string_const_ref source_);
        void ctrl_set_angle(const control &control_, float angle_, float centerX_, float centerY_, bool now_ = true);
        void ctrl_set_mouse_position(const control &control_, float x_, float y_);
        void ctrl_set_pixel_precision(const control &control_, pixel_precision_types type_);
        void ctrl_set_scroll_values(const control &control_, float vScroll_, float hScroll_);
        void ctrl_set_text_selection(const control &control_, float start_, float length_);
        void ctrl_set_url(const control &control_, sqf_string_const_ref url_);
        void draw_triangle(const control &mapCtrl_, const std::vector<vector3>& vertices_, const rv_color &color_, sqf_string_const_ref fill_texture_ = "");
        float get_text_width(sqf_string_const_ref string_, sqf_string_const_ref font_, float fontSize_);
        void lb_set_select_color(const control &control_, int index_, const rv_color &color_);
        void lb_set_select_color(float idc_, int index_, const rv_color &color_);
        void lb_set_select_color_right(const control &control_, int index_, const rv_color &color_);
        void lb_set_select_color_right(float idc_, int index_, const rv_color &color_);
        void lb_set_selected(const control &control_, int index_, bool selected_);
        void lnb_set_picture_color(float idc_, float row_, float column_, const rv_color &color_);
        void lnb_set_picture_color(const control &ctrl_, float row_, float column_, const rv_color &color_);
        void lnb_set_picture_color_right(float idc_, float row_, float column_, const rv_color &color_);
        void lnb_set_picture_color_right(const control &ctrl_, float row_, float column_, const rv_color &color_);
        void lnb_set_picture_color_selected(float idc_, float row_, float column_, const rv_color &color_);
        void lnb_set_picture_color_selected(const control &ctrl_, float row_, float column_, const rv_color &color_);
        void lnb_set_picture_color_selected_right(float idc_, float row_, float column_, const rv_color &color_);
        void lnb_set_picture_color_selected_right(const control &ctrl_, float row_, float column_, const rv_color &color_);
        bool tv_is_selected(const control &ctrl_, const std::vector<int> &path_);
        void tv_set_selected(const control &ctrl_, const std::vector<int> &path_, bool select_);
        void tv_sort_all(const control &ctrl_, const std::vector<int> &path_, bool reversed_);
        void tv_sort_by_value_all(const control &ctrl_, const std::vector<int> &path_, bool reversed_);
        std::vector<float> all_active_title_effects();
        bool is_action_menu_visible();
        rv_ctrl_angle ctrl_angle(const control &ctrl_);
        float ctrl_font_height(const control &ctrl_);
        vector2 ctrl_mouse_position(const control &ctrl_);
        vector2 ctrl_scroll_values(const control &ctrl_);
        float ctrl_style(const control &ctrl_);
        rv_color ctrl_text_color(const control &ctrl_);
        rv_ctrl_text_selection ctrl_text_selection(const control &ctrl_);
        float ctrl_text_width(const control &ctrl_);
        sqf_return_string ctrl_tooltip(const control &ctrl_);
        sqf_return_string ctrl_url(const control &ctrl_);
        control focused_ctrl(const display &disp_);
        std::vector<float> lb_selection(const control &ctrl_);
        bool open_gps(bool show_);

        //Menu
        sqf_return_string menu_action(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string menu_action(float idc_, const std::vector<int> &path_);
        void menu_add(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_add(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_);
        bool menu_checked(const control &ctrl_, const std::vector<int> &path_);
        bool menu_checked(float idc_, const std::vector<int> &path_);
        void menu_collapse(const control &ctrl_, const std::vector<int> &path_);
        void menu_collapse(float idc_, const std::vector<int> &path_);
        sqf_return_string menu_data(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string menu_data(float idc_, const std::vector<int> &path_);
        void menu_delete(const control &ctrl_, const std::vector<int> &path_);
        void menu_delete(float idc_, const std::vector<int> &path_);
        void menu_enable(const control &ctrl_, const std::vector<int> &path_, bool value_);
        void menu_enable(float idc_, const std::vector<int> &path_, bool value_);
        bool menu_enabled(const control &ctrl_, const std::vector<int> &path_);
        bool menu_enabled(float idc_, const std::vector<int> &path_);
        void menu_expand(const control &ctrl_, const std::vector<int> &path_);
        void menu_expand(float idc_, const std::vector<int> &path_);
        sqf_return_string menu_picture(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string menu_picture(float idc_, const std::vector<int> &path_);
        void menu_set_action(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_action(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_check(const control &ctrl_, const std::vector<int> &path_, bool value_);
        void menu_set_check(float idc_, const std::vector<int> &path_, bool value_);
        void menu_set_data(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_data(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_picture(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_picture(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_shortcut(const control &ctrl_, const std::vector<int> &path_, int value_);
        void menu_set_shortcut(float idc_, const std::vector<int> &path_, int value_);
        void menu_set_text(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_text(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_url(const control &ctrl_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_url(float idc_, const std::vector<int> &path_, sqf_string_const_ref value_);
        void menu_set_value(const control &ctrl_, const std::vector<int> &path_, float value_);
        void menu_set_value(float idc_, const std::vector<int> &path_, float value_);
        float menu_shortcut(const control &ctrl_, const std::vector<int> &path_);
        float menu_shortcut(float idc_, const std::vector<int> &path_);
        sqf_return_string menu_shortcut_text(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string menu_shortcut_text(float idc_, const std::vector<int> &path_);
        float menu_size(const control &ctrl_, const std::vector<int> &path_);
        float menu_size(float idc_, const std::vector<int> &path_);
        void menu_sort(const control &ctrl_, const std::vector<int> &path_, bool value_);
        void menu_sort(float idc_, const std::vector<int> &path_, bool value_);
        sqf_return_string menu_text(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string menu_text(float idc_, const std::vector<int> &path_);
        sqf_return_string menu_url(const control &ctrl_, const std::vector<int> &path_);
        sqf_return_string menu_url(float idc_, const std::vector<int> &path_);
        float menu_value(const control &ctrl_, const std::vector<int> &path_);
        float menu_value(float idc_, const std::vector<int> &path_);
        void ctrl_set_text_color_secondary(const control &ctrl_, const rv_color &color_);
        void menu_clear(const control &ctrl_);
        void menu_clear(float idc_);
        std::vector<int> menu_hover(const control &ctrl_);
        std::vector<int> menu_hover(float idc_);

        void ctrl_map_set_position(const control &ctrl_, const vector2 &pos_);
        void ctrl_map_set_position(const control &ctrl_, float x_, float y_, float width_, float height_);
        rv_ctrl_position ctrl_map_position(const control &map_);

        game_value ctrl_map_mouse_over(const control &map_);
        float ctrl_map_dir(const control &map_);

        vector2 get_texture_info(sqf_string_const_ref path_);

        control ctrl_at(const display &disp_, const vector2 &pos_);
        int ctrl_url_overlay_mode(const control &ctrl_);
        void ctrl_set_url_overlay_mode(const control &ctrl_, int mode_);

        sqf_return_string display_unique_name(const display &disp_);
        void display_update(const display &disp_);
    }  // namespace sqf
}  // namespace intercept
