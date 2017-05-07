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

        struct rv_lnb_array {
            std::vector<std::string> texts;
            std::vector<float> values;
            std::vector<std::string> datas;

            operator game_value() {
                std::vector<game_value> texts_gv, values_gv, datas_gv;
                for (auto item : texts) {
                    texts_gv.push_back(game_value(item));
                }
                for (auto item : values) {
                    values_gv.push_back(game_value(item));
                }
                for (auto item : datas) {
                    datas_gv.push_back(game_value(item));
                }
                return game_value(std::vector<game_value>({
                    texts_gv,
                    values_gv,
                    datas_gv
                }));
            }

            operator game_value() const {
                std::vector<game_value> texts_gv, values_gv, datas_gv;
                for (auto item : texts) {
                    texts_gv.push_back(game_value(item));
                }
                for (auto item : values) {
                    values_gv.push_back(game_value(item));
                }
                for (auto item : datas) {
                    datas_gv.push_back(game_value(item));
                }
                return game_value(std::vector<game_value>({
                    texts_gv,
                    values_gv,
                    datas_gv
                }));
            }
        };

        /*ctrl_ */

        control ctrl_create(const display& display_, const std::string& class_, int idc_);
        control ctrl_create(const display& display_, const std::string& class_, int idc_, const control& controls_group_);



        bool ctrl_auto_scroll_rewind(const control &value_);
        bool ctrl_checked(const control &value_);
        bool ctrl_committed(const control &value_);
        bool ctrl_delete(const control &value_);
        bool ctrl_enabled(const control &value_);
        bool ctrl_enabled(float value_);
        bool ctrl_htmlloaded(const control &value_);
        bool ctrl_map_anim_done(const control &value_);
        bool ctrl_shown(const control &value_);
        bool ctrl_visible(float value_);
        void ctrl_commit(const control &value0_, float value1_);
        void ctrl_enable(int control_id_, bool enable_);
        void ctrl_enable(const control &control_, bool enable_);
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
        void ctrl_set_foreground_color(const control& ctrl_, const rv_color& color_);
        void ctrl_set_model_dir_and_up(const control& ctrl_, const vector3& dir_, const vector3& up_);
        void ctrl_set_text_color(const control& ctrl_, const rv_color& color_);
        void ctrl_set_tooltip_color_box(const control& ctrl_, const rv_color& color_);
        void ctrl_set_tooltip_color_shade(const control& ctrl_, const rv_color& color_);
        void ctrl_set_tooltip_color_text(const control& ctrl_, const rv_color& color_);
        void ctrl_activate(const control &value_);
        void ctrl_map_anim_clear(const control &value_);
        void ctrl_map_anim_commit(const control &value_);
        void ctrl_map_cursor(const control& ctrl_, const std::string& default_cursor_, const std::string& new_cursor_);
        void ctrl_remove_all_event_handlers(const control &value0_, const std::string& value1_);
        void ctrl_remove_event_handler(const control &ctrl_, const std::string &name_, float &id_);
        void ctrl_set_active_color(const control& ctrl_, const rv_color& color_);
        void ctrl_set_auto_scroll_delay(const control &value0_, float value1_);
        void ctrl_set_auto_scroll_rewind(const control &value0_, bool value1_);
        void ctrl_set_auto_scroll_speed(const control &value0_, float value1_);
        void ctrl_set_background_color(const control& ctrl_, const rv_color& color_);
        void ctrl_set_checked(const control &value0_, bool value1_);
        void ctrl_set_focus(const control &value_);
        float ctrl_auto_scroll_delay(const control &value_);
        float ctrl_auto_scroll_speed(const control &value_);
        float ctrl_fade(const control &value_);
        float ctrl_idc(const control &value_);
        float ctrl_idd(const display &value_);
        float ctrl_map_scale(const control &value_);
        float ctrl_model_scale(const control &value_);
        float ctrl_scale(const control &value_);
        float ctrl_text_height(const control &value_);
        float ctrl_type(const control &value_);
        std::string ctrl_class_name(const control &value_);
        std::string ctrl_model(const control &value_);
        std::string ctrl_text(const control &value_);
        std::string ctrl_text(float value_);
        std::string ctrl_text_secondary(const control &value_);
        void ctrl_set_position(const control &ctrl_, float x_, float y_, float width_, float height_);
        std::vector<float> ctrl_position(const control &ctrl_);
        void ctrl_map_anim_add(const control &ctrl_, float time_, float zoom_, vector2 pos_);
        display ctrl_parent(const control &value_);
        control ctrl_parent_controls_group(const control &value_);
        std::vector<vector3> ctrl_model_dir_and_up(const control &ctrl_);

        vector2 ctrl_map_world_to_screen(const control& ctrl_, const std::vector<float>& position_);
        vector2 ctrl_map_screen_to_world(const control &ctrl_, const vector2 &screen_pos_);


        void ctrl_set_event_handler(const control &ctrl_, const std::string &name_, const std::string &command_);
        float ctrl_add_event_handler(const control &ctrl_, const std::string &name_, const std::string &command_);
        float ctrl_add_event_handler(const control &ctrl_, const std::string &name_, const code &command_);


        //listbox/combobox
        void lnb_delete_column(const control& ctrl_, float index_);
        void lnb_delete_row(const control &value0_, float value1_);
        void lnb_set_cur_sel_row(float idc_, float index_);
        void lnb_set_cur_sel_row(const control& ctrl_, float index_);
        void lnb_delete_column(float idc_, float index_);
        void lnb_delete_row(float idc_, float index_);
        void lnb_set_color(float idc_, float row_, float column_, const rv_color& color_);
        void lnb_set_color(const control& ctrl_, float row_, float column_, const rv_color& color_);
        void lnb_set_columns_pos(float idc_, std::vector<float> positions_);
        void lnb_set_columns_pos(const control& ctrl_, std::vector<float> positions_);
        void lnb_set_data(float idc_, float row_, float column_, const std::string& data_);
        void lnb_set_data(const control& ctrl_, float row_, float column_, const std::string& data_);
        void lnb_set_picture(float idc_, float row_, float column_, const std::string& name_);
        void lnb_set_picture(const control& ctrl_, float row_, float column_, const std::string& name_);
        void lnb_set_text(float idc_, float row_, float column_, const game_value& data_);
        void lnb_set_text(const control& ctrl_, float row_, float column_, const game_value& data_);
        void lnb_set_value(float idc_, float row_, float column_, float value_);
        void lnb_set_value(const control& ctrl_, float row_, float column_, float value_);
        void lnb_clear(const control &value_);
        void lnb_clear(float value_);
        float lnb_add_array(float idc_, const std::vector<rv_lnb_array>& lnb_array_);
        float lnb_add_array(const control& ctrl_, const std::vector<rv_lnb_array>& lnb_array_);
        float lnb_add_row(float idc_, const std::vector<std::string>& strings_);
        float lnb_add_row(const control& ctrl_, std::vector<std::string>& strings_);
        float lnb_value(float idc_, float row_, float column_);
        float lnb_value(const control& ctrl_, float row_, float column_);
        float lnb_add_column(const control &value0_, float value1_);
        float lnb_cur_sel_row(const control &value_);
        float lnb_cur_sel_row(float value_);
        std::string lnb_data(float idc_, float row_, float column_);
        std::string lnb_data(const control& ctrl_, float row_, float column_);
        std::string lnb_picture(float idc_, float row_, float column_);
        std::string lnb_picture(const control& ctrl_, float row_, float column_);
        std::string lnb_text(float idc_, float row_, float column_);
        std::string lnb_text(const control& ctrl_, float row_, float column_);
        std::vector<float> lnb_get_columns_position(float idc_);
        std::vector<float> lnb_get_columns_position(const control& ctrl_);
        std::vector<float> lnb_size(float idc_);
        std::vector<float> lnb_size(const control& ctrl_);
        rv_color lnb_color(float idc_, float row_, float column_);
        rv_color lnb_color(const control& ctrl_, float row_, float column_);

        //listbox
        bool lb_is_selected(const control &value0_, float value1_);
        void lb_delete(int control_id_, int index_);
        void lb_delete(const control &control_, int index_);
        // TODO std::vector<float> lb_selection(const control &control_); // USE lb_cur_sel IN A3 https://community.bistudio.com/wiki/lbSelection
        void lb_set_color(int control_id_, int index_, rv_color color_);
        void lb_set_color(const control &control_, int index_, const rv_color & color_);
        void lb_set_color_right(int control_id_, int index_, const rv_color & color_);
        void lb_set_color_right(const control &control_, int index_, const rv_color & color_);
        void lb_set_cur_sel(int control_id_, int index_);
        void lb_set_cur_sel(const control &control_, int index_);
        void lb_set_data(int control_id_, int index_, const std::string &data_);
        void lb_set_data(const control &control_, int index_, const std::string &data_);
        void lb_set_picture(int control_id_, int index_, const std::string &name_);
        void lb_set_picture(const control &control_, int index_, const std::string &name_);
        void lb_set_picture_right(int control_id_, int index_, const std::string &name_);
        void lb_set_picture_right(const control &control_, int index_, const std::string &name_);
        void lb_set_picture_color(int control_id_, int index_, const rv_color & color_);
        void lb_set_picture_color(const control &control_, int index_, const rv_color & color_);
        void lb_set_picture_color_disabled(int control_id_, int index_, const rv_color & color_);
        void lb_set_picture_color_disabled(const control &control_, int index_, const rv_color & color_);
        void lb_set_picture_color_selected(int control_id_, int index_, const rv_color & color_);
        void lb_set_picture_color_selected(const control &control_, int index_, const rv_color & color_);
        void lb_set_picture_right_color(const control &control_, int index_, const rv_color & color_);
        void lb_set_picture_right_color_disabled(const control &control_, int index_, const rv_color & color_);
        void lb_set_picture_right_color_selected(const control &control_, int index_, const rv_color & color_);
        void lb_set_tooltip(int control_id_, int index_, const std::string &tooltip_);
        void lb_set_tooltip(const control &control_, int index_, const std::string &tooltip_);
        void lb_set_value(int control_id_, int index_, float val_);
        void lb_set_value(const control &control_, int index_, float val_);
        void lb_sort(const control &control_);
        void lb_sort(const control &control_, const std::string &sort_order_);
        void lb_set_select_color(int idc_, int index_, const rv_color & color_);
        void lb_set_select_color_right(int idc_, int index_, const rv_color & color_);
        void lb_clear(const control &value_);
        void lb_clear(float value_);
        float lb_add(int control_id_, const std::string &text_);
        float lb_add(const control &control_, const std::string &text_);
        float lb_color(int control_id_, int index_);
        float lb_color(const control &control_, int index_);
        float lb_color_right(int control_id_, int index_);
        float lb_color_right(const control &control_, int index_);
        float lb_value(int control_id_, int index_);
        float lb_value(const control &control_, int index_);
        float lb_cur_sel(const control &value_);
        float lb_cur_sel(float value_);
        float lb_size(const control &value_);
        float lb_size(float value_);
        float lb_sort_by_value(const control &value_);
        std::string lb_data(int control_id_, int index_);
        std::string lb_data(const control &control_, int index_);
        std::string lb_picture(int control_id_, int index_);
        std::string lb_picture(const control &control_, int index_);
        std::string lb_picture_right(int control_id_, int index_);
        std::string lb_picture_right(const control &control_, int index_);
        std::string lb_text(int control_id_, int index_);
        std::string lb_text(const control &control_, int index_);
        std::string lb_text_right(int control_id_, int index_);
        std::string lb_text_right(const control &control_, int index_);
        void lb_delete(const control &value0_, float value1_);
        void lb_set_cur_sel(const control &value0_, float value1_);
        float lb_value(const control &value0_, float value1_);
        std::string lb_data(const control &value0_, float value1_);
        std::string lb_picture(const control &value0_, float value1_);
        std::string lb_picture_right(const control &value0_, float value1_);
        std::string lb_text(const control &value0_, float value1_);
        std::string lb_text_right(const control &value0_, float value1_);

        //treeview
        void tv_set_text(float idc_, const std::vector<float>& path_, const std::string& text_);
        void tv_set_text(const control& ctrl_, const std::vector<float>& path_, const std::string& text_);
        void tv_collapse(int idc_, const std::vector<int>& path_);
        void tv_collapse(const control& ctrl_, const std::vector<int>& path_);
        void tv_delete(int idc_, const std::vector<int>& path_);
        void tv_delete(const control& ctrl_, const std::vector<int>& path_);
        void tv_expand(int idc_, const std::vector<int>& path_);
        void tv_expand(const control& ctrl_, const std::vector<int>& path_);
        void tv_set_cur_sel(int idc_, const std::vector<int>& path_);
        void tv_set_cur_sel(const control& ctrl_, const std::vector<int>& path_);
        void tv_set_data(int idc_, const std::vector<int>& path_, const std::string& data_);
        void tv_set_data(const control& ctrl_, const std::vector<int>& path_, const std::string& data_);
        void tv_set_picture(int idc_, const std::vector<int>& path_, const std::string& name_);
        void tv_set_picture(const control& ctrl_, const std::vector<int>& path_, const std::string& name_);
        void tv_set_picture_right(int idc_, const std::vector<int>& path_, const std::string& name_);
        void tv_set_picture_right(const control& ctrl_, const std::vector<int>& path_, const std::string& name_);
        void tv_set_picture_color(int idc_, const std::vector<int>& path_, const rv_color& color_);
        void tv_set_picture_color(const control& ctrl_, const std::vector<int>& path_, const rv_color& color_);
        void tv_set_picture_color_right(int idc_, const std::vector<int>& path_, const rv_color& color_);
        void tv_set_picture_color_right(const control& ctrl_, const std::vector<int>& path_, const rv_color& color_);
        void tv_set_tooltip(int idc_, const std::vector<int>& path_, const std::string& text_);
        void tv_set_tooltip(const control& ctrl_, const std::vector<int>& path_, const std::string& text_);
        void tv_set_value(const control& ctrl_, const std::vector<int>& path_, float value_);
        void tv_set_value(int idc_, const std::vector<int>& path_, float value_);
        void tv_sort(const control& ctrl_, const std::vector<int>& path_, bool reversed_ = false);
        void tv_sort_by_value(const control& ctrl_, const std::vector<int>& path_, bool reversed_ = false);
        void tv_clear(float value_);
        void tv_clear(const control &value_);
        std::string tv_data(int idc_, const std::vector<int>& path_);
        std::string tv_data(const control& ctrl_, const std::vector<int>& path_);
        std::string tv_picture(int idc_, const std::vector<int>& path_);
        std::string tv_picture(const control& ctrl_, const std::vector<int>& path_);
        std::string tv_picture_right(int idc_, const std::vector<int>& path_);
        std::string tv_picture_right(const control& ctrl_, const std::vector<int>& path_);
        std::string tv_text(int idc_, const std::vector<int>& path_);
        std::string tv_text(const control& ctrl_, const std::vector<int>& path_);
        float tv_value(int idc_, const std::vector<int>& path_);
        float tv_value(const control& ctrl_, const std::vector<int>& path_);
        int tv_add(int idc_, const std::vector<int>& path_, const std::string& text_);
        int tv_add(const control& ctrl_, const std::vector<int>& path_, const std::string& text_);
        int tv_count(int idc_, const std::vector<int>& path_);
        int tv_count(const control& ctrl_, const std::vector<int>& path_);
        //std::string tv_tooltip(const control &value0_, float value1_);
        std::vector<int> tv_cursel(int idc_);
        std::vector<int> tv_cursel(const control& ctrl_);

        //Slider
        void slider_set_range(float value0_, float value1_, float value2_);
        void slider_set_range(const control &value0_, float value1_, float value2_);
        void slider_set_speed(float value0_, float value1_, float value2_);
        void slider_set_speed(const control &value0_, float value1_, float value2_);
        void slider_set_position(float value0_, float value1_);
        void slider_set_position(const control &value0_, float value1_);
        vector2 slider_range(const float &value_);
        vector2 slider_range(const control &ctrl_);
        vector2 slider_speed(const float &value_);
        vector2 slider_speed(const control &ctrl_);
        float slider_position(const control &value_);
        float slider_position(float value_);

        //Overlay
        void clear_overlay(const control & map_);
        void close_overlay(const control & map_);
        void commit_overlay(const control & map_);
        void save_overlay(const control &value_);
        void load_overlay(const control &a_control_, const config & a_config_);
        void new_overlay(const control &a_control_, const config & a_config_);





        bool visible_watch();
        bool visible_map();
        bool visible_gps();
        bool visible_compass();
        bool cb_checked(const control & control_);
        void cb_set_checked(const control &value0_, bool value1_);
        bool create_dialog(const std::string & dialog_name_);

        bool is_real_time(const control &value_);
        bool is_showing(const control &value_);

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
        void show_commanding_menu(const std::string &value_);
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



        bool preload_title_obj(const std::string &name_, const std::string &type_);
        bool preload_title_obj(const std::string &name_, const std::string &type_, float speed_, bool show_in_map_); // speed is ignored - source: BIKI
        bool preload_title_rsc(const std::string &name_, const std::string &type_);
        bool preload_title_rsc(const std::string &name_, const std::string &type_, float speed_, bool show_in_map_); // speed is ignored - source: BIKI      
        /* potential namespace: gui, ui */
        void cut_obj(const std::string &name_, const std::string &type_, float speed_ = 1.0f);
        void cut_rsc(const std::string &name_, const std::string &type_, float speed_ = 1.0f, bool show_on_map_ = false);
        void cut_text(const std::string &name_, const std::string &type_, float speed_ = 1.0f, bool show_on_map_ = false);
        void title_cut(const std::string& text_, const std::string& type_, const float& speed_ = 1);
        void title_obj(const std::string& class_, const std::string& type_, const float& speed_ = 1, bool show_on_map_ = false);
        void title_rsc(const std::string& text_, const std::string& type_, const float& speed_ = 1);
        void title_text(const std::string& text_, const std::string& type_, const float& speed_ = 1);
        void map_anim_add(float time_, float zoom_, const object &object_);
        void map_anim_add(float time_, float zoom_, const vector3 &pos_);

        void close_dialog(float val_);
        void close_display(float value0_, const display &value1_);



        //@TODO: draw_icon could stand to have a few enums probably for arguments like shadow and align.
        void draw_icon(const control &ctrl_, const std::string &texture_, const rv_color &color_, const vector2 &pos_, float width_, float height_, float angle_, const std::string &text_, uint32_t shadow_, float text_size_, const std::string &font_, const std::string &align_);
        void draw_icon(const control &ctrl_, const std::string &texture_, const rv_color &color_, const object &pos_, float width_, float height_, float angle_, const std::string &text_, uint32_t shadow_, float text_size_, const std::string &font_, const std::string &align_);


        void draw_rectangle(const control &ctrl_, const vector2 center_pos_, float a_, float b_, float angle_, const rv_color &color_, const std::string &fill_texture_);

        void collapse_object_tree(const control &value_);
        void import_all_groups(const control &value_);


        void restart_editor_camera(const control &value_);
        void selected_editor_objects(const control &value_);
        void update_object_tree(const control &value_);
        void allow3dmode(const control &value0_, bool value1_);
        void allow_file_operations(const control &value0_, bool value1_);
        void create_menu(const control &value0_, float value1_);
        void html_load(const control &value0_, const std::string& value1_);

        void map_center_on_camera(const control &main_map, bool enable_);
        void move_object_to_end(const control &value0_, const std::string& value1_);
        void progress_set_position(const control &value0_, float value1_);
        void remove_menu_item(const control &value0_, float value1_);
        void remove_menu_item(const control &value0_, const std::string& value1_);
        void set_editor_mode(const control &value0_, const std::string& value1_);
        void show3dicons(const control &value0_, bool value1_);
        void show_legend(const control &value0_, bool value1_);
        /* potential namespace: controls, ui, gui, misc */
        void button_set_action(int control_id_, const std::string &code_);
        void button_set_action(const control &control_, const std::string &code_);
        void map_anim_clear();
        void map_anim_commit();
        void force_map(bool value_);
        void in_game_ui_set_event_handler(const std::string& name_, const std::string& command_);




        float gear_slot_ammo_count(const control &value_);
        float next_menu_item_index(const control &value_);
        float progress_position(const control &value_);
        float safe_zone_x();
        float safe_zone_y();
        float safe_zone_h();
        float safe_zone_w();
        float safe_zone_x_abs();
        float safe_zone_w_abs();

        std::string button_action(const control & control_);
        std::string button_action(int idc_);


        std::string gear_slot_data(const control &value_);
        std::string get_editor_mode(const control &value_);
        std::string get_editor_object_scope(const control &value0_, const std::string& value1_);
        std::string map_grid_position(const object &obj_);
        std::string map_grid_position(const vector2 &pos_);
        display create_display(const std::string& value0_, const display &value1_);
        display create_mission_display(const std::string& value0_, const display &value1_);
        control control_null();
        control controls_group_ctrl(const control &value0_, float value1_);
        control display_ctrl(float value0_, const display &value1_);
        vector3 map_center_on_camera(const control &mini_map_);

        vector2 pos_screen_to_world(const control &ctrl_, const vector2 &pos_);
        vector2 pos_world_to_screen(const control &ctrl_, const vector2 &pos_);
        std::vector<control> all_controls(const display &display_);
        object get_editor_camera(const control &value_);
        object get_object_proxy(const control &value0_, const std::string& value1_);


        game_value get_variable(const control & ctrl_, const std::string & var_name_, game_value default_value_);
    }
}
