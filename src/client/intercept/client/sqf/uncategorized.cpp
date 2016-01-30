#include "uncategorized.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"


using namespace intercept::types;

namespace intercept {
    namespace sqf {

        const std::string waypoint::__speed_lookup[4] = { "UNCHANGED", "LIMITED", "NORMAL", "FULL" };
        const std::string waypoint::__show_lookup[4] = { "NEVER", "EASY", "ALWAYS", "ERROR" };
        const std::string waypoint::__type_lookup[22] = { "MOVE","DESTROY","GETIN","SAD","JOIN","LEADER","GETOUT","CYCLE","LOAD","UNLOAD","TR UNLOAD","HOLD","SENTRY","GUARD","TALK","SCRIPTED","SUPPORT","GETIN NEAREST","DISMISS","LOITER","AND","OR" };
        const std::string waypoint::__behaviour_lookup[6] = { "UNCHANGED", "CARELESS", "SAFE", "AWARE", "COMBAT", "STEALTH" };
        const std::string waypoint::__combat_mode_lookup[6] = { "NO CHANGE", "BLUE", "GREEN", "WHITE", "YELLOW", "RED" };
        const std::string waypoint::__formation_lookup[10] = { "NO_CHANGE","COLUMN","STAG_COLUMN","WEDGE","ECH_LEFT","ECH_RIGHT","VEE","LINE","FILE","DIAMOND" };
        const std::string waypoint::__loiter_lookup[2] = { "CIRCLE", "CIRCLE_L" };

        /////////////////////// DO NOT IMPLEMENT THESE FUNCTIONS /////////////////////////
        ///////// They are haram. Discuss on slack prior to removing from list. //////////
        // unary__abs__scalar_nan__ret__scalar_nan
        // unary__acos__scalar_nan__ret__scalar_nan
        // unary__asin__scalar_nan__ret__scalar_nan
        // unary__atan__scalar_nan__ret__scalar_nan
        // unary__atg__scalar_nan__ret__scalar_nan
        // unary__case__any__ret__switch
        // unary__count__array__ret__scalar
        // unary__ceil__scalar_nan__ret__scalar_nan
        // unary__cos__scalar_nan__ret__scalar_nan
        // unary__debuglog__any__ret__nothing
        // unary__default__code__ret__nothing
        // unary__deg__scalar_nan__ret__scalar_nan
        // unary__exp__scalar_nan__ret__scalar_nan
        // unary__floor__scalar_nan__ret__scalar_nan
        // unary__for__string__ret__for
        // unary__for__array__ret__for
        // unary__goto__string__ret__nothing
        // unary__if__bool__ret__if
        // unary__ln__scalar_nan__ret__scalar_nan
        // unary__log__scalar_nan__ret__scalar_nan
        // unary__not__bool__ret__bool
        // unary__oneachframe__code_string__ret__nothing
        // unary__ongroupiconclick__code_string__ret__nothing
        // unary__ongroupiconoverenter__code_string__ret__nothing
        // unary__ongroupiconoverleave__code_string__ret__nothing
        // unary__onhcgroupselectionchanged__code_string__ret__nothing
        // unary__onmapsingleclick__code_string__ret__nothing
        // unary__onplayerconnected__code_string__ret__nothing
        // unary__onplayerdisconnected__code_string__ret__nothing
        // unary__onpreloadfinished__code_string__ret__nothing
        // unary__onpreloadstarted__code_string__ret__nothing
        // unary__onteamswitch__code_string__ret__nothing
        // unary__param__array__ret__any
        // unary__params__array__ret__bool
        // unary__private__string_array__ret__nothing
        // unary__rad__scalar_nan__ret__scalar_nan
        // unary__random__array__ret__scalar_nan
        // unary__random__scalar_nan__ret__scalar_nan
        // unary__reverse__array__ret__nothing
        // unary__round__scalar_nan__ret__scalar_nan
        // unary__selectrandom__array__ret__any
        // unary__sin__scalar_nan__ret__scalar_nan
        // unary__str__any__ret__string
        // unary__sqrt__scalar_nan__ret__scalar_nan
        // unary__switch__any__ret__switch
        // unary__tan__scalar_nan__ret__scalar_nan
        // unary__tg__scalar_nan__ret__scalar_nan
        // unary__throw__any__ret__nothing
        // unary__toarray__string__ret__array
        // unary__tostring__array__ret__string
        // unary__try__code__ret__exception
        // unary__vectormagnitude__array__ret__scalar
        // unary__vectormagnitudesqr__array__ret__scalar
        // unary__vectornormalized__array__ret__array
        // unary__waituntil__code__ret__nothing
        // unary__while__code__ret__while
        // unary__with__namespace__ret__with

        // binary__and__bool__bool__ret__bool
        // binary__and__bool__code__ret__bool
        // binary__append__array__array__ret__nothing
        // binary__arrayintersect__array__array__ret__array
        // binary__atan2__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__breakout__any__string__ret__any
        // binary__camsetdir__object__array__ret__nothing
        // binary__catch__exception__code__ret__any
        // binary__count__code__array__ret__scalar
        // binary__deleteat__array__scalar__ret__any
        // binary__deleterange__array__array__ret__nothing
        // binary__do__while__code__ret__nothing
        // binary__do__with__code__ret__nothing
        // binary__do__for__code__ret__any
        // binary__do__switch__code__ret__any
        // binary__else__code__code__ret__array
        // binary__exitwith__if__code__ret__any
        // binary__find__array__any__ret__scalar
        // binary__find__string__string__ret__scalar
        // binary__foreach__code__array__ret__nothing
        // binary__foreachmember__code__team_member__ret__nothing
        // binary__foreachmemberagent__code__team_member__ret__nothing
        // binary__foreachmemberteam__code__team_member__ret__nothing
        // binary__from__for__scalar__ret__for
        // binary__in__any__array__ret__bool
        // binary__isequalto__any__any__ret__bool
        // binary__isequaltype__any__any__ret__bool
        // binary__isequaltypeall__array__any__ret__bool
        // binary__isequaltypeany__any__array__ret__bool
        // binary__isequaltypearray__array__array__ret__bool
        // binary__isequaltypeparams__any__array__ret__bool
        // binary__joinstring__array__string__ret__string
        // binary__max__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__min__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__mod__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__lbsetselected__control__array__ret__nothing (Depreciated in favor of lbSetCurSel)
        // binary__or__bool__bool__ret__bool
        // binary__or__bool__code__ret__bool
        // binary__param__any__array__ret__any
        // binary__params__any__array__ret__bool
        // binary__pushback__array__any__ret__scalar
        // binary__resize__array__scalar__ret__nothing
        // binary__select__array__scalar__ret__any
        // binary__select__array__bool__ret__any
        // binary__select__array__array__ret__array
        // binary__select__string__array__ret__string
        // binary__set__array__array__ret__nothing
        // binary__sort__array__bool__ret__nothing
        // binary__spawn__any__code__ret__script ------------------------------------------------------------------------
        // binary__splitstring__string__string__ret__array
        // binary__step__for__scalar__ret__for
        // binary__then__if__code__ret__any
        // binary__then__if__array__ret__any
        // binary__throw__if__any__ret__nothing
        // binary__to__for__scalar__ret__for
        // binary__try__any__code__ret__exception
        // binary__vectoradd__array__array__ret__array
        // binary__vectorcos__array__array__ret__scalar
        // binary__vectorcrossproduct__array__array__ret__array
        // binary__vectordiff__array__array__ret__array
        // binary__vectordistance__array__array__ret__scalar
        // binary__vectordistancesqr__array__array__ret__scalar
        // binary__vectordotproduct__array__array__ret__scalar
        // binary__vectorfromto__array__array__ret__array
        // binary__vectormultiply__array__scalar__ret__array

        // nular__allsites__ret__array (deprecated - source: BI Wiki)
        // nular__false__ret__bool
        // nular__netobjnull__ret__netobject ----------------------------------------------------------------------------------
        // nular__nil__ret__any
        // nular__true__ret__bool

        /// investigate
        /* No documentation.*/
        // nular__airdensitycurvertd__ret__array

        /* No documentation.*/
        // nular__getdlcassetsusage__ret__array

        /* No documentation.*/
        // nular__getmissiondlcs__ret__array

        /* No documentation.*/
        // nular__getmouseposition__ret__array

        /* Appears to return [show markers on map true/false, show markers on HUD true/false] array that setGroupIconsVisible takes. Scarce documentation.*/
        // nular__groupiconsvisible__ret__array

        /* Last parameter can be position (x, y, z) or target, unknown what target is.*/
        // nular__hudmovementlevels__ret__array

        /* No documentation for type Team.*/
        // nular__teams__ret__array

        /* No documentation.*/
        // nular__windrtd__ret__array

        /* These functions apparently send arbatary messages across the network. They are apparently inactive.*/
        // unary__sendaumessage__array__ret__nothing
        // unary__sendudpmessage__array__ret__bool

        /* This function does _something_ to a listbox. No documentation.*/
        // binary__lbsettextright__control__array__ret__nothing

        /* This function is apparently depreciated but the functionality is different to the command which replaces it.*/
        // unary__lbselection__control__ret__array

        /* This undocumented function has the potential to be useful, my guess is it returns a float between 1 and 0 which
            corresponds to how visible a particular unit is from another unit. */
        // binary__checkvisibility__array__array__ret__scalar
        /////////////////////// DO NOT IMPLEMENT ABOVE FUNCTIONS /////////////////////////


        void draw_line_3d(const vector3 & pos1_, const vector3 & pos2_, const rv_color & color_)
        {
            game_value args({
                pos1_,
                pos2_,
                color_
            });
            host::functions.invoke_raw_unary(client::__sqf::unary__drawline3d__array__ret__nothing, args);
        }

        void draw_icon_3d(const std::string & texture_, const rv_color & color_, const vector3 & pos_agl_, float width_, float height_, float angle_, const std::string & text_, float shadow_, float text_size_, const std::string & font_)
        {
            game_value args({
                texture_,
                color_,
                pos_agl_,
                width_,
                height_,
                angle_,
                text_,
                shadow_,
                text_size_,
                font_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__drawicon3d__array__ret__nothing, args);
        }

        vector3 vector_dir(const object &obj_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__vectordir__object__ret__array, obj_));
        }

        vector3 vector_dir_visual(const object & obj_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__vectordirvisual__object__ret__array, obj_));
        }

        vector3 selection_positon(const object & obj_, const std::string & selection_name_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__selectionposition__object__string_array__ret__array, obj_, selection_name_));
        }

        game_value get_variable(const rv_namespace & namespace_, const std::string & var_name_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__namespace__string__ret__any, namespace_, var_name_));
        }

        game_value get_variable(const rv_namespace & namespace_, const std::string & var_name_, game_value& default_value_)
        {
            game_value args(std::vector<game_value>{
                var_name_,
                default_value_
            });
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__namespace__array__ret__any, namespace_, args));
        }

        game_value get_variable(const display & display_, const std::string & var_name_, game_value& default_value_)
        {
            game_value args(std::vector<game_value>{
                var_name_,
                default_value_
            });
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__display__string_array__ret__any, display_, args));
        }

        game_value get_variable(const control & ctrl_, const std::string & var_name_, game_value& default_value_)
        {
            game_value args(std::vector<game_value>{
                var_name_,
                default_value_
            });
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__display__string_array__ret__any, ctrl_, args));
        }

        game_value get_variable(const object & obj_, const std::string & var_name_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__object__string__ret__any, obj_, var_name_));
        }

        game_value get_variable(const object & obj_, const std::string & var_name_, game_value& default_value_)
        {
            game_value args(std::vector<game_value>{
                var_name_,
                default_value_
            });
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__object__array__ret__any, obj_, args));
        }

        game_value get_variable(const group & group_, const std::string & var_name_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__group__string__ret__any, group_, var_name_));
        }

        game_value get_variable(const group & group_, const std::string & var_name_, game_value& default_value_)
        {
            game_value args(std::vector<game_value>{
                var_name_,
                default_value_
            });
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__group__array__ret__any, group_, args));
        }

        game_value get_variable(const team_member & team_member_, const std::string & var_name_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__team_member__string__ret__any, team_member_, var_name_));
        }

        game_value get_variable(const team_member & team_member_, const std::string & var_name_, game_value& default_value_)
        {
            game_value args(std::vector<game_value>{
                var_name_,
                default_value_
            });
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__team_member__array__ret__any, team_member_, args));
        }

        game_value get_variable(const task & task_, const std::string & var_name_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__task__string__ret__any, task_, var_name_));
        }

        game_value get_variable(const location & loc_, const std::string & var_name_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getvariable__location__string__ret__any, loc_, var_name_));
        }


        vector3 model_to_world_visual(const object & model_, const vector3 & model_pos_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__modeltoworldvisual__object__array__ret__array, model_, model_pos_));
        }

        vector2 world_to_screen(const vector3 & pos_agl_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__worldtoscreen__array__ret__array, pos_agl_));
        }

        vector2 world_to_screen(const vector3 & pos_agl_, bool & in_screen_)
        {
            rv_game_value result = host::functions.invoke_raw_unary(client::__sqf::unary__worldtoscreen__array__ret__array, pos_agl_);
            if (((game_data_array *)result.data)->length == 2)
                in_screen_ = true;
            else
                in_screen_ = false;
            return game_value(result);
        }

        void ctrl_set_position(const control & ctrl_, float x_, float y_, float width_, float height_)
        {
            game_value args(std::vector<game_value>{
                x_,
                y_,
                width_,
                height_
            });
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetposition__control__array__ret__nothing, ctrl_, args);
        }

        void ctrl_map_anim_add(const control & ctrl_, float time_, float zoom_, vector2 pos_)
        {
            game_value args({
                time_,
                zoom_,
                pos_
            });
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlmapanimadd__control__array__ret__nothing, ctrl_, args);
        }

        vector2 ctrl_map_screen_to_world(const control & ctrl_, const vector2 & screen_pos_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__ctrlmapscreentoworld__control__array__ret__array, ctrl_, screen_pos_));
        }

        std::vector<object> near_entities(const vector3 & pos_agl_, const std::vector<std::string>& types_, float range_)
        {
            std::vector<game_value> types;
            for (auto type : types_)
                types.push_back(type);
            game_value args(std::vector<game_value>{
                types,
                range_
            });

            game_value ret = host::functions.invoke_raw_binary(__sqf::binary__nearentities__object_array__scalar_array__ret__array, pos_agl_, args);
            std::vector<object> ret_objects;
            for (uint32_t i = 0; i < ret.length(); ++i)
                ret_objects.push_back(object(ret[i].rv_data));
            return ret_objects;
        }

        void set_vector_dir(const object & obj_, const vector3 & vec_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__setvectordir__object__array__ret__nothing, obj_, vec_);
        }

        void set_velocity(const object & obj_, const vector3 & vel_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__setvelocity__object__array__ret__nothing, obj_, vel_);
        }

        object create_vehicle_local(const std::string & type_, const vector3 & pos_atl_)
        {
            return object(host::functions.invoke_raw_binary(__sqf::binary__createvehiclelocal__string__array__ret__object, type_, pos_atl_));
        }

        void draw_rectangle(const control & ctrl_, const vector2 center_pos_, float a_, float b_, float angle_, const rv_color & color_, const std::string & fill_texture_)
        {
            game_value args({
                center_pos_,
                a_,
                b_,
                angle_,
                color_,
                fill_texture_
            });
            host::functions.invoke_raw_binary(client::__sqf::binary__drawrectangle__control__array__ret__nothing, ctrl_, args);
        }

        void draw_icon(const control & ctrl_, const std::string & texture_, const rv_color & color_, const vector2 & pos_, float width_, float height_, float angle_, const std::string & text_, uint32_t shadow_, float text_size_, const std::string & font_, const std::string & align_)
        {
            game_value args({
                texture_,
                color_,
                pos_,
                width_,
                height_,
                angle_,
                text_,
                (float)shadow_,
                text_size_,
                font_,
                align_
            });
            host::functions.invoke_raw_binary(client::__sqf::binary__drawicon__control__array__ret__nothing, ctrl_, args);
        }

        void draw_icon(const control & ctrl_, const std::string & texture_, const rv_color & color_, const object & pos_, float width_, float height_, float angle_, const std::string & text_, uint32_t shadow_, float text_size_, const std::string & font_, const std::string & align_)
        {
            game_value args({
                texture_,
                color_,
                pos_,
                width_,
                height_,
                angle_,
                text_,
                (float)shadow_,
                text_size_,
                font_,
                align_
            });
            host::functions.invoke_raw_binary(client::__sqf::binary__drawicon__control__array__ret__nothing, ctrl_, args);
        }

        vector3 velocity(const object & obj_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__velocity__object__ret__array, obj_));
        }

        std::vector<std::string> action_keys(const std::string &user_action_)
        {
            game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeys__string__ret__array, user_action_);
            std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);
            return r_arr;
        }

        rv_text action_keys_images(const std::string &user_action_)
        {
            return rv_text(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysimages__string_array__ret__text, user_action_));
        }

        std::string action_keys_names(const std::string &user_action_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, user_action_));
        }

        std::string action_keys_names(const std::string &user_action_, int max_keys_)
        {
            std::vector<game_value> params{ user_action_, game_value((float)max_keys_) };
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, params));
        }
        std::string action_keys_names(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_)
        {
            game_value params({
                user_action_,
                (float)max_keys_,
                input_device_priority_
            });

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, params));
        }

        std::vector<std::string> action_keys_names_array(const std::string &user_action_)
        {
            game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, user_action_);
            std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);

            host::functions.free_value(&act_keys);
            return r_arr;
        }

        std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_)
        {
            std::vector<game_value> params{ user_action_, game_value((float)max_keys_) };

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
        }
        std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_)
        {
            game_value params({
                user_action_,
                (float)max_keys_,
                input_device_priority_
            });

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
        }

        void activate_addons(std::vector<std::string> &addons_)
        {
            std::vector<game_value> addons;
            for (auto it : addons_)
                addons.push_back(it);

            host::functions.invoke_raw_unary(client::__sqf::unary__activateaddons__array__ret__nothing, addons);
        }

        /* potential namespace: camera */
        void add_cam_shake(float power_, float duration_, float frequency_)
        {
            std::vector<game_value> params{ power_, duration_, frequency_ };

            host::functions.invoke_raw_unary(client::__sqf::unary__addcamshake__array__ret__nothing, params);
        }

        /* potential namespace: items, inventory, campaign */
        void add_item_pool(const std::string &item_name_, int item_count_)
        {
            std::vector<game_value> params{ item_name_, game_value((float)item_count_) };

            host::functions.invoke_raw_unary(client::__sqf::unary__additempool__array__ret__nothing, params);
        }

        void add_magazine_pool(const std::string &mag_name_, int mag_count_)
        {
            std::vector<game_value> params{ mag_name_, game_value((float)mag_count_) };
            host::functions.invoke_raw_unary(client::__sqf::unary__addmagazinepool__array__ret__nothing, params);
        }

        void add_backpack_cargo(const object & vehicle_, const std::string & packClassName_, int count_) {
            std::vector<game_value> args{
                packClassName_,
                (float)count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpackcargo__object__array__ret__nothing, vehicle_, args);
        }

        void add_backpack_cargo_global(const object & vehicle_, const std::string & packClassName_, int count_) {
            std::vector<game_value> args{
                packClassName_,
                (float)count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpackcargoglobal__object__array__ret__nothing, vehicle_, args);
        }

        void add_item_cargo(const object & object_, const std::string & item_, int count_) {
            std::vector<game_value> args{
                item_,
                (float)count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__additemcargo__object__array__ret__nothing, object_, args);
        }

        void add_item_cargo_global(const object & object_, const std::string & item_, int count_) {
            std::vector<game_value> args{
                item_,
                (float)count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__additemcargoglobal__object__array__ret__nothing, object_, args);
        }

        void add_to_remains_collector(std::vector<object> objects_)
        {
            std::vector<game_value> objects;
            for (auto &it : objects_)
                objects.push_back(it);
            host::functions.invoke_raw_unary(client::__sqf::unary__addtoremainscollector__array__ret__nothing, objects);
        }

        void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_)
        {
            game_value params(std::vector<game_value>{
                wounded_,
                medic_,
                medic_can_heal_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__aisfinishheal__array__ret__nothing, params);
        }

        std::vector<object> all_mission_objects(const std::string &type_)
        {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__allmissionobjects__string__ret__array, type_));
        }

        std::vector<object> assigned_cargo(const object &veh_)
        {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__assignedcargo__object__ret__array, veh_));
        }

        std::vector<std::string> assigned_items(const object &unit_)
        {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__assigneditems__object__ret__array, unit_));
        }

        object attached_object(const location &loc_)
        {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__attachedobject__location__ret__object, loc_));
        }

        std::vector<object> attached_objects(const object &obj_)
        {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__attachedobjects__object__ret__array, obj_));
        }

        object attached_to(const object &obj_)
        {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__attachedto__object__ret__array, obj_));
        }

        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_, const std::string &memPoint_) {
            std::vector<game_value> args{
                object2_,
                offset_,
                memPoint_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__attachto__object__array__ret__nothing, object1_, args);
        }

        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_) {
            std::vector<game_value> args{
                object2_,
                offset_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__attachto__object__array__ret__nothing, object1_, args);
        }

        bool attack_enabled(const object &unit_)
        {
            return __helpers::__bool_unary_object(client::__sqf::unary__attackenabled__object_group__ret__bool, unit_);
        }

        bool attack_enabled(const group &group_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__attackenabled__object_group__ret__bool, group_));
        }

        std::vector<std::string> backpack_cargo(const object &box_)
        {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackcargo__object__ret__array, box_));
        }

        std::vector<std::string> backpack_items(const object &unit_)
        {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackitems__object__ret__array, unit_));
        }

        std::vector<std::string> backpack_magazines(const object &unit_)
        {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackmagazines__object__ret__array, unit_));
        }

        sqf::rv_bounding_box bounding_box(const object &model_)
        {
            //game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__boundingbox__object__ret__array, model_);
            //game_data_array* array_value = ((game_data_array *)input.data);

            //sqf::rv_bounding_box bb;

            //float x_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[0].data)->number;
            //float y_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[1].data)->number;
            //float z_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[2].data)->number;
            //bb.min = vector3(x_min, y_min, z_min);

            //float x_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[0].data)->number;
            //float y_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[1].data)->number;
            //float z_max  = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[2].data)->number;
            //bb.min = vector3(x_max, y_max, z_max);

            //host::functions.free_value(&input);
            //return bb;
            throw 713; // TODO
        }

        sqf::rv_bounding_box bounding_box_real(const object &model_)
        {
            //game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__boundingboxreal__object__ret__array, model_);
            //game_data_array* array_value = ((game_data_array *)input.data);

            //sqf::rv_bounding_box bb;

            //float x_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[0].data)->number;
            //float y_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[1].data)->number;
            //float z_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[2].data)->number;
            //bb.min = vector3(x_min, y_min, z_min);

            //float x_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[0].data)->number;
            //float y_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[1].data)->number;
            //float z_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[2].data)->number;
            //bb.min = vector3(x_max, y_max, z_max);

            //host::functions.free_value(&input);
            //return bb;
            throw 713; // TODO
        }

        vector3 bounding_center(const object &obj_)
        {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(client::__sqf::unary__boundingcenter__object__ret__array, obj_));
        }

        void button_set_action(int control_id_, const std::string &code_)
        {
            game_value params({
                (float)control_id_,
                code_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__buttonsetaction__array__ret__nothing, params);
        }

        void button_set_action(const control &control_, const std::string &code_)
        {
            game_value params({
                control_,
                code_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__buttonsetaction__array__ret__nothing, params);
        }

        // What a confusing command name.
        std::string class_name(const location &loc_)
        {
            return game_value( host::functions.invoke_raw_unary(client::__sqf::unary__classname__location__ret__string, loc_) );
        }

        std::string combat_mode(const group &grp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__combatmode__object_group__ret__string, grp_));
        }

        std::string combat_mode(const object &unit_)
        {
            return __helpers::__string_unary_object(client::__sqf::unary__combatmode__object_group__ret__string, unit_);
        }

        void command_get_out(const object &unit_)
        {
            return __helpers::__empty_unary_object(client::__sqf::unary__commandgetout__object_array__ret__nothing, unit_);
        }

        void command_get_out(std::vector<object> units_)
        {
            //std::vector<game_value> units;
            //for (auto it : units)
            //    units.push_back(it);

            //__helpers::__empty_unary_object(client::__sqf::unary__commandgetout__object_array__ret__nothing, units);
            //TODO Implement command_get_out
            throw 713;
        }

        void command_stop(const object &unit_)
        {
            return __helpers::__empty_unary_object(client::__sqf::unary__commandstop__object_array__ret__nothing, unit_);
        }
        void command_stop(std::vector<object> units_)
        {
            throw 713; // TODO Implement command_stop
            //return __helpers::__empty_unary_object(client::__sqf::unary__commandstop__object_array__ret__nothing, unit_);
        }

        object create_agent(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ /* = {}*/, float placement_ /*= 0.0f*/, const std::string &special_ /*= "NONE"*/)
        {
            std::vector<game_value> markers;
            for (auto &it : markers_)
                markers.push_back(it);

            game_value args({
                type_,
                pos_,
                markers,
                placement_,
                special_
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createagent__array__ret__object, args));

        }

        void create_gear_dialog(const object &unit_, const std::string &resource_)
        {
            game_value params({
                unit_,
                resource_
            });

            host::functions.invoke_raw_unary(__sqf::unary__creategeardialog__array__ret__nothing, params);
        }

        void create_guarded_point(const side &side_, const vector3 &pos_, float idstatic_, const object &veh_)
        {
            game_value params({
                side_,
                pos_,
                idstatic_,
                veh_
            });

            host::functions.invoke_raw_unary(__sqf::unary__createguardedpoint__array__ret__nothing, params);
        }

        void action(const object & unit_, const std::vector<game_value>& action_array_) {
            host::functions.invoke_raw_binary(__sqf::binary__action__object__array__ret__nothing, unit_, action_array_);
        }

        float add_event_handler(const object & object_, const std::string & type_, const code & command_) {
            std::vector<game_value> args{
                type_,
                command_
            };

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addeventhandler__object__array__ret__nothing_scalar, object_, args));
        }

        float add_event_handler(const object & object_, const std::string & type_, const std::string & command_) {
            std::vector<game_value> args{
                type_,
                command_
            };

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addeventhandler__object__array__ret__nothing_scalar, object_, args));
        }

        location create_location(const std::string &classname_, const vector3 &pos_, float size_x_, float size_y_)
        {
            game_value params({
                classname_,
                pos_,
                size_x_,
                size_y_
            });

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }

        location create_location(const std::string &classname_, vector2 pos_, float size_x_, float size_y_)
        {
            game_value params({
                classname_,
                pos_,
                size_x_,
                size_y_
            });

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }
        location create_location(const std::string &classname_, const object &obj_, float size_x_, float size_y_)
        {
            game_value params({
                classname_,
                obj_,
                size_x_,
                size_y_
            });

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }

        object create_mine(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_/* = {}*/, float placement_/* = 0.0f*/)
        {
            std::vector<game_value> markers;
            for (auto &it : markers_)
                markers.push_back(it);

            game_value args({
                type_,
                pos_,
                markers,
                placement_,
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createmine__array__ret__object, args));
        }

        object create_sound_source(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_/* = {}*/, float placement_/* = 0.0f*/)
        {
            std::vector<game_value> markers;
            for (auto it : markers_)
                markers.push_back(it);

            game_value args({
                type_,
                pos_,
                markers,
                placement_,
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createsoundsource__array__ret__object, args));
        }

        team_member create_team(const std::string &type_, const std::string &name_)
        {
            game_value args({
                (type_),
                (name_),
            });

            return team_member(host::functions.invoke_raw_unary(__sqf::unary__createteam__array__ret__team_member, args));
        }

        object create_trigger(const std::string &type_, const vector3 &pos_, bool make_global_/* = true*/)
        {
            game_value args({
                (type_),
                (pos_),
                (make_global_)
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
        }

        object create_trigger(const std::string &type_, const object &pos_, bool make_global_ /*= true*/)
        {
            game_value args({
                (type_),
                pos_,
                (make_global_)
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
        }

        std::vector<object> crew(object _veh)
        {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__crew__object__ret__array, _veh));
        }

        std::string current_magazine_detail(const object &veh_)
        {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmagazinedetail__object__ret__array, veh_);
        }

        std::vector<task> current_tasks(const team_member &team_member_)
        {
            game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__currenttasks__team_member__ret__array, team_member_);

            std::vector<task> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(task(input[i].rv_data));
            }

            return output;
        }

        void cut_obj(const std::string &name_, const std::string &type_, float speed_)
        {
            game_value args({
                (name_),
                (type_),
                (speed_)
            });

            host::functions.invoke_raw_unary(__sqf::unary__cutobj__array__ret__nothing, args);
        }

        void cut_rsc(const std::string &name_, const std::string &type_, float speed_, bool show_on_map_)
        {
            game_value args({
                (name_),
                (type_),
                (speed_),
                (show_on_map_)
            });

            host::functions.invoke_raw_unary(__sqf::unary__cutrsc__array__ret__nothing, args);
        }

        void cut_text(const std::string &name_, const std::string &type_, float speed_, bool show_on_map_)
        {
            game_value args({
                (name_),
                (type_),
                (speed_),
                (show_on_map_)
            });

            host::functions.invoke_raw_unary(__sqf::unary__cuttext__array__ret__nothing, args);
        }

        void enable_debriefing_stats(float left_, float top_, float width_, float height_)
        {
            //game_value args({
            //    (left_),
            //    (top_),
            //    (width_),
            //    (height_)
            //});

            //host::functions.invoke_raw_unary(__sqf::unary__enabledebriefingstats__array__ret__nothing, args);
        }

        float add_action(const object &object_, const std::string &title_, const std::string &script_, const std::vector<game_value> &arguments_, float priority_, bool show_window_, bool hide_on_use_, const std::string &shortcut_, const std::string &condition_) {
            std::vector<game_value> args{
                title_,
                script_,
                arguments_,
                priority_,
                show_window_,
                hide_on_use_,
                shortcut_,
                condition_
            };

            return game_value(host::functions.invoke_raw_binary(__sqf::binary__addaction__object__array__ret__nothing_scalar, object_, args));
        }

        float add_action(const object &object_, const std::string &title_, const code &script_, const std::vector<game_value> &arguments_, float priority_, bool show_window_, bool hide_on_use_, const std::string &shortcut_, const std::string &condition_) {
            std::vector<game_value> args{
                title_,
                script_,
                arguments_,
                priority_,
                show_window_,
                hide_on_use_,
                shortcut_,
                condition_
            };

            return game_value(host::functions.invoke_raw_binary(__sqf::binary__addaction__object__array__ret__nothing_scalar, object_, args));
        }

        void enable_saving(bool enable_)
        {
            enable_saving(enable_, !enable_);
        }

        void enable_saving(bool enable_, bool autosave_)
        {
            //game_value args({
            //    (enable_),
            //    (autosave_)
            //});

            //host::functions.invoke_raw_unary(__sqf::unary__enablesaving__bool_array__ret__nothing, args);
        }

        std::string formation(const object &leader_)
        {
            return game_value(host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, leader_));
        }

        std::string formation(const group &group_)
        {
            return game_value(host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, group_));
        }

        std::vector<object> formation_members(const object &unit_)
        {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__formationmembers__object__ret__array, unit_));
        }

        vector3 formation_position(const object &unit_)
        {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__formationposition__object__ret__array, unit_));
        }

        std::vector<rv_crew_member> full_crew(const object &veh_, const std::string & filter_)
        {
            //game_value crew_list;

            //if (filter_ == "")
            //{
            //    crew_list = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__object__ret__array, veh_);
            //}
            //else
            //{
            //    game_value args({
            //        veh_,
            //        (filter_)
            //    });

            //    crew_list = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__array__ret__array, args);
            //}

            //game_data_array* gd_array = ((game_data_array *)crew_list.data);
            //std::vector<rv_crew_member> output;
            //for (uint32_t i = 0; i < gd_array->length; ++i) {

            //    rv_crew_member crew_m;

            //    crew_m.unit = object(((game_data_array *)gd_array->data[i].data)->data[0]);
            //    crew_m.role = ((game_data_string *)((game_data_array *)gd_array->data[i].data)->data[1].data)->get_string();
            //    crew_m.cargo_index = ((game_data_number *)((game_data_array *)gd_array->data[i].data)->data[2].data)->number;
            //    // Turret path
            //    crew_m.person_turret = ((game_data_bool *)((game_data_array *)gd_array->data[i].data)->data[4].data)->value;
            //    output.push_back(crew_m);
            //}

            //host::functions.free_value(&crew_list);
            //return output;

            throw 713; // TODO re-implement full_crew
        }

        std::vector<std::string> get_artillery_ammo(const std::vector<object>& units_)
        {
            std::vector<game_value> units;
            for (auto &it : units_)
                units.push_back(it);

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__getartilleryammo__array__ret__array, units));
        }

        vector3 get_center_of_mass(const object &obj_)
        {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(client::__sqf::unary__getcenterofmass__object__ret__array, obj_));
        }

        std::vector<float> get_dlcs(float filter_)
        {
            return __helpers::__convert_to_numbers_vector(host::functions.invoke_raw_unary(client::__sqf::unary__getdlcs__scalar__ret__array, filter_));
        }

#pragma region listbox
        /****************************************************************************** LISTBOX ***************************************************************************/
        float lb_add(int control_id_, const std::string &text_)
        {
            game_value args({
                (float)(control_id_),
                (text_)
            });

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbadd__array__ret__scalar, args));
        }

        float lb_add(const control &control_, const std::string &text_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbadd__control__string__ret__scalar, control_, text_));
        }

        float lb_color(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbcolor__array__ret__array, args));
        }

        float lb_color(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbcolor__control__scalar__ret__array, control_, (float)index_));
        }

        float lb_color_right(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbcolorright__array__ret__array, args));
        }

        float lb_color_right(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbcolorright__control__scalar__ret__array, control_, (float)index_));
        }

        std::string lb_data(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbdata__array__ret__string, args));
        }

        std::string lb_data(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbdata__control__scalar__ret__string, control_, (float)index_));
        }

        void lb_delete(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            host::functions.invoke_raw_unary(client::__sqf::unary__lbdelete__array__ret__nothing, args);
        }

        void lb_delete(const control &control_, int index_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__lbdelete__control__scalar__ret__nothing, control_, (float)index_);
        }

        std::string lb_picture(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbpicture__array__ret__string, args));
        }

        std::string lb_picture(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpicture__control__scalar__ret__string, control_, (float)index_));
        }

        std::string lb_picture_right(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbpictureright__array__ret__string, args));
        }

        std::string lb_picture_right(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpictureright__control__scalar__ret__string, control_, (float)index_));
        }

        // TODO std::vector<float> lb_selection(const control &control_) { ... }; // USE lb_cur_sel IN A3 https://community.bistudio.com/wiki/lbSelection

        void lb_set_color(int control_id_, int index_, rv_color color_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcolor__array__ret__nothing, args);
        }

        void lb_set_color(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcolor__control__array__ret__nothing, control_, args);
        }

        void lb_set_color_right(int control_id_, int index_, rv_color color_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcolorright__array__ret__nothing, args);
        }

        void lb_set_color_right(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcolorright__control__array__ret__nothing, control_, args);
        }

        void lb_set_cur_sel(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };
            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcursel__array__ret__nothing, args);
        }

        void lb_set_cur_sel(const control &control_, int index_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcursel__control__scalar__ret__nothing, control_, (float)index_);
        }

        void lb_set_data(int control_id_, int index_, const std::string &data_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                data_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetdata__array__ret__nothing, args);
        }


        void lb_set_data(const control &control_, int index_, const std::string &data_)
        {
            game_value args({
                (float)(index_),
                (data_)
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetdata__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture(int control_id_, int index_, const std::string &name_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                name_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicture__array__ret__nothing, args);
        }

        void lb_set_picture(const control &control_, int index_, const std::string &name_)
        {
            game_value args({
                (float)(index_),
                (name_)
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicture__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_right(int control_id_, int index_, const std::string &name_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                name_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpictureright__array__ret__nothing, args);
        }

        void lb_set_picture_right(const control &control_, int index_, const std::string &name_)
        {
            game_value args({
                (float)(index_),
                (name_)
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpictureright__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_color(int control_id_, int index_, rv_color color_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolor__array__ret__nothing, args);
        }


        void lb_set_picture_color(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolor__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_color_disabled(int control_id_, int index_, rv_color color_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolordisabled__array__ret__nothing, args);
        }

        void lb_set_picture_color_disabled(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolordisabled__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_color_selected(int control_id_, int index_, rv_color color_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolorselected__array__ret__nothing, args);
        }

        void lb_set_picture_color_selected(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolorselected__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_right_color(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturerightcolor__control__array__ret__nothing, control_, args);
        }

        void lb_set_picture_right_color_disabled(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturerightcolordisabled__control__array__ret__nothing, control_, args);
        }


        void lb_set_picture_right_color_selected(const control &control_, int index_, rv_color color_)
        {
            game_value args({
                (float)(index_),
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturerightcolorselected__control__array__ret__nothing, control_, args);
        }



        void lb_set_tooltip(int control_id_, int index_, const std::string &tooltip_)
        {
            game_value args({
                (float)(control_id_),
                (float)(index_),
                tooltip_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsettooltip__array__ret__nothing, args);
        }

        void lb_set_tooltip(const control &control_, int index_, const std::string &tooltip_)
        {
            game_value args({
                (float)(index_),
                (tooltip_)
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsettooltip__control__array__ret__nothing, control_, args);
        }

        void lb_set_value(int control_id_, int index_, float val_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_), val_ };

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetvalue__array__ret__nothing, args);
        }

        void lb_set_value(const control &control_, int index_, float val_)
        {
            std::vector<game_value> args{game_value((float)index_), val_ };

            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetvalue__control__array__ret__nothing, control_, args);
        }

        void lb_sort(const control &control_)
        {
            host::functions.invoke_raw_unary(client::__sqf::unary__lbsort__control__ret__scalar, control_);
        }

        void lb_sort(const control &control_, const std::string &sort_order_)
        {
            game_value args({
                control_,
                (sort_order_)
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsort__array__ret__scalar, args);
        }

        std::string lb_text(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbtext__array__ret__string, args));
        }

        std::string lb_text(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtext__control__scalar__ret__string, control_, (float)index_));
        }

        std::string lb_text_right(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbtextright__array__ret__string, args));
        }

        std::string lb_text_right(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtextright__control__scalar__ret__string, control_, (float)index_));
        }

        float lb_value(int control_id_, int index_)
        {
            std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbvalue__array__ret__scalar, args));
        }

        float lb_value(const control &control_, int index_)
        {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbvalue__control__scalar__ret__scalar, control_, (float)index_));
        }

        void lb_set_select_color(int idc_, int index_, rv_color &color_)
        {
            game_value params({
                (float)idc_,
                (float)index_,
                (color_)
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetselectcolor__array__ret__nothing, params);
            // Alt syntax binary__lbsetselectcolor__control__array__ret__nothing
        }

        void lb_set_select_color_right(int idc_, int index_, rv_color &color_)
        {
            game_value params({
                (float)idc_,
                (float)index_,
                color_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__lbsetselectcolorright__array__ret__nothing, params);
            // Alt syntax binary__lbsetselectcolorright__control__array__ret__nothing
        }

        /*************************************************************** LISTBOX END *****************************************************************************/
#pragma endregion listbox

        /* 3den */
        std::string current3denoperation() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__current3denoperation__ret__string);
        }
        object get3dencamera() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__get3dencamera__ret__object);
        }

        bool get3deniconsvisible() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__get3deniconsvisible__ret__bool);
        }

        bool get3denlinesvisible() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__get3denlinesvisible__ret__bool);
        }

        bool is3den() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3den__ret__bool);
        }

        bool is3denmultiplayer() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3denmultiplayer__ret__bool);
        }
        float get_3den_action_state(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__get3denactionstate__string__ret__scalar, value_);
        }
        void edit_3den_mission_attributes(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__edit3denmissionattributes__string__ret__nothing, value_);
        }
        bool remove_3den_layer(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__remove3denlayer__scalar__ret__bool, value_);
        }

        void remove_all_3den_eventhandlers(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__removeall3deneventhandlers__string__ret__nothing, value_);
        }

        float add_3den_layer(float value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__add3denlayer__scalar__string__ret__scalar, value0_, value1_));
        }

        /* Chat */
        namespace __helpers {
            void chat_message(binary_function fnc_, const object & obj_, const std::string &message_) {
                host::functions.invoke_raw_binary(fnc_, obj_, message_);
            }
        }

        void side_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(client::__sqf::binary__sidechat__object_array__string__ret__nothing, obj_, message_);
        }

        void global_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(client::__sqf::binary__globalchat__object__string__ret__nothing, obj_, message_);
        }

        void group_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(client::__sqf::binary__groupchat__object__string__ret__nothing, obj_, message_);
        }

        void vehicle_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(client::__sqf::binary__vehiclechat__object__string__ret__nothing, obj_, message_);
        }

        void command_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(client::__sqf::binary__commandchat__object_array__string__ret__nothing, obj_, message_);
        }

        void system_chat(const std::string &message_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__systemchat__string__ret__nothing, message_);
        }

        void custom_chat(const object & obj_, uint32_t channel_id_, const std::string &message_) {
            game_value args = game_value({ ((float)channel_id_), message_ });
            host::functions.invoke_raw_binary(client::__sqf::binary__customchat__object__array__ret__nothing, obj_, args);
        }

        /* Config */

        std::vector<config> config_hierarchy(const config &config_entry_) {
            game_value output = host::functions.invoke_raw_unary(client::__sqf::unary__confighierarchy__config__ret__array, config_entry_);
            return __helpers::__convert_to_configs_vector(output);
        }

        std::string config_name(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__configname__config__ret__string, config_entry_));
        }

        std::vector<config> config_properties(const config &config_entry, const std::string& condition_, bool inherit) {
            game_value array_entry({
                config_entry,
                condition_,
                inherit
            });
            game_value output = host::functions.invoke_raw_unary(client::__sqf::unary__configproperties__array__ret__array, array_entry);
            return __helpers::__convert_to_configs_vector(output);
        }

        std::string config_source_mod(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__configsourcemod__config__ret__string, config_entry_));
        }

        std::vector<std::string> config_source_mod_list(const config &config_entry_) {
            game_value output = host::functions.invoke_raw_unary(client::__sqf::unary__configsourcemodlist__config__ret__array, config_entry_);
            return __helpers::__convert_to_strings_vector(output);
        }

        float count(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__count__config__ret__scalar, config_entry_));
        }

        //std::vector<game_value> get_array(const config &config_entry_) {
        // TODO implement get_array
        //}

            config get_mission_config(const std::string& value_) {
            return config(host::functions.invoke_raw_unary(client::__sqf::unary__getmissionconfig__string__ret__config, value_));
        }

        float get_number(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__getnumber__config__ret__scalar, config_entry_));
        }

        std::string get_text(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__gettext__config__ret__string, config_entry_));
        }

        config inherits_from(const config &config_entry_) {
            return config(host::functions.invoke_raw_unary(client::__sqf::unary__inheritsfrom__config__ret__config, config_entry_));
        }

        bool is_array(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isarray__config__ret__bool, config_entry_));
        }

        bool is_class(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isclass__config__ret__bool, config_entry_));
        }

        bool is_null(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__config__ret__bool, config_entry_));
        }

        bool is_number(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnumber__config__ret__bool, config_entry_));
        }

        bool is_text(const config &config_entry_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__istext__config__ret__bool, config_entry_));
        }

        std::vector<std::string> config_classes(const std::string& value_, config a_config_) {
            game_value output = host::functions.invoke_raw_binary(client::__sqf::binary__configclasses__string__config__ret__array, value_, a_config_);
            return __helpers::__convert_to_strings_vector(output);
        }

        void load_overlay(const control &a_control_, config a_config_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__loadoverlay__control__config__ret__nothing, a_control_, a_config_);
        }

        void new_overlay(const control &a_control_, config a_config_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__newoverlay__control__config__ret__nothing, a_control_, a_config_);
        }

        config select(const config &a_config_, float a_number_) {
            return config(host::functions.invoke_raw_binary(client::__sqf::binary__select__config__scalar__ret__config, a_config_, a_number_));
        }

        config campaign_config_file() {
            return config(host::functions.invoke_raw_nular(client::__sqf::nular__campaignconfigfile__ret__config));
        }

        config config_file() {
            return config(host::functions.invoke_raw_nular(client::__sqf::nular__configfile__ret__config));
        }

        config config_null() {
            return config(host::functions.invoke_raw_nular(client::__sqf::nular__confignull__ret__config));
        }

        config mission_config_file() {
            return config(host::functions.invoke_raw_nular(client::__sqf::nular__missionconfigfile__ret__config));
        }

        /* Core */
                object player() {
            return object(host::functions.invoke_raw_nular(client::__sqf::nular__player__ret__object));
        }

        object create_vehicle(const std::string &type_, const vector3 &pos_)
        {
            return object(host::functions.invoke_raw_binary(__sqf::binary__createvehicle__string__array__ret__object, type_, pos_));
        }

        object create_vehicle(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_, const std::string &special_) {
            std::vector<game_value> markers;
            for (auto it : markers_) {
                markers.push_back(it);
            }
            game_value args({
                type_,
                pos_,
                markers,
                placement_,
                special_
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createvehicle__array__ret__object, args));
        }

        void delete_vehicle(const object &obj_)
        {
            host::functions.invoke_raw_unary(__sqf::unary__deletevehicle__object__ret__nothing, obj_);
        }

        std::vector<object> all_3den_entities() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__all3denentities__ret__array));
        }

        std::vector<object> all_curators() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allcurators__ret__array));
        }

        std::vector<object> all_dead() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__alldead__ret__array));
        }

        std::vector<object> all_deadmen() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__alldeadmen__ret__array));
        }

        std::vector<display> all_displays() {
            return __helpers::__convert_to_displays_vector(host::functions.invoke_raw_nular(client::__sqf::nular__alldisplays__ret__array));
        }

        std::vector<group> all_groups() {
            return __helpers::__convert_to_groups_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allgroups__ret__array));
        }

        std::vector<marker> all_map_markers() {
            return __helpers::__convert_to_markers_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allmapmarkers__ret__array));
        }

        std::vector<object> all_mines() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allmines__ret__array));
        }

        std::vector<object> all_players() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allplayers__ret__array));
        }

        std::vector<object> all_units() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allunits__ret__array));
        }

        std::vector<object> all_units_uav() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allunitsuav__ret__array));
        }

        float server_time() {
            return game_value(host::functions.invoke_raw_nular(client::__sqf::nular__servertime__ret__scalar));
        }

        std::string server_name() {
            return game_value(host::functions.invoke_raw_nular(client::__sqf::nular__servername__ret__string));
        }

        bool is_null(const object &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__object__ret__bool, value_));
        }

        bool is_null(const group &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__group__ret__bool, value_));
        }

        bool is_null(const control &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__control__ret__bool, value_));
        }

        bool is_null(const display &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__display__ret__bool, value_));
        }

        bool is_null(const script &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__script__ret__bool, value_));
        }

        bool is_null(const task &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__task__ret__bool, value_));
        }

        script script_null() {
            return script(host::functions.invoke_raw_nular(client::__sqf::nular__scriptnull__ret__script));
        }

        task task_null() {
            return task(host::functions.invoke_raw_nular(client::__sqf::nular__tasknull__ret__task));
        }

        rv_namespace ui_namespace() {
            return rv_namespace(host::functions.invoke_raw_nular(client::__sqf::nular__uinamespace__ret__namespace));
        }

        std::vector<script> diag_active_mission_fsms() {
            game_value input = host::functions.invoke_raw_nular(client::__sqf::nular__diag_activemissionfsms__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(script(input[i].rv_data));
            }
            return output;
        }

        std::vector<script> diag_active_sqf_scripts() {
            game_value input = host::functions.invoke_raw_nular(client::__sqf::nular__diag_activesqfscripts__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(script(input[i].rv_data));
            }
            return output;
        }

        std::vector<script> diag_active_sqs_scripts() {
            game_value input = host::functions.invoke_raw_nular(client::__sqf::nular__diag_activesqsscripts__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(script(input[i].rv_data));
            }
            return output;
        }

        bool __sqfassert(bool test_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isnull__script__ret__bool, test_));
        }

        std::vector<control> all_controls(const display &display_) {
            game_value input__ = host::functions.invoke_raw_unary(client::__sqf::unary__allcontrols__display__ret__array, display_);
            std::vector<control> output;
            for (uint32_t i = 0; i < input__.length(); ++i) {
                output.push_back(control(input__[i].rv_data));
            }
            return output;
        }

        std::vector<std::string> all_turrets(const object &vehicle_, bool person_turrets_) {
            game_value array_input(std::vector<game_value>{
                vehicle_,
                person_turrets_
            });

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allturrets__array__ret__array, array_input));
        }

        std::vector<std::string> all_turrets(const object &vehicle_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allturrets__object__ret__array, vehicle_));
        }

        std::vector<std::string> all_variables(const object &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allvariables__object__ret__array, value_));
        }
        std::vector<std::string> all_variables(const control &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allvariables__control__ret__array, value_));
        }
        std::vector<std::string> all_variables(const team_member &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allvariables__team_member__ret__array, value_));
        }
        std::vector<std::string> all_variables(rv_namespace value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allvariables__namespace__ret__array, value_));
        }
        std::vector<std::string> all_variables(const group &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allvariables__group__ret__array, value_));
        }
        std::vector<std::string> all_variables(const task &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allvariables__task__ret__array, value_));
        }
        std::vector<std::string> all_variables(const location &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                client::__sqf::unary__allvariables__location__ret__array, value_));
        }

        /* Ctrl */
                void ctrl_activate(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__ctrlactivate__control__ret__nothing, value_);
        }

        float ctrl_auto_scroll_delay(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrlautoscrolldelay__control__ret__scalar, value_);
        }

        bool ctrl_auto_scroll_rewind(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrlautoscrollrewind__control__ret__bool, value_);
        }

        float ctrl_auto_scroll_speed(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrlautoscrollspeed__control__ret__scalar, value_);
        }

        bool ctrl_checked(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrlchecked__control__ret__bool, value_);
        }

        std::string ctrl_class_name(const control &value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__ctrlclassname__control__ret__string, value_);
        }

        bool ctrl_committed(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrlcommitted__control__ret__bool, value_);
        }

        bool ctrl_delete(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrldelete__control__ret__bool, value_);
        }

        bool ctrl_enabled(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrlenabled__control__ret__bool, value_);
        }

        bool ctrl_enabled(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__ctrlenabled__scalar__ret__bool, value_);
        }

        float ctrl_fade(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrlfade__control__ret__scalar, value_);
        }

        bool ctrl_htmlloaded(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrlhtmlloaded__control__ret__bool, value_);
        }

        float ctrl_idc(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrlidc__control__ret__scalar, value_);
        }

        float ctrl_idd(const display &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__ctrlidd__display__ret__scalar, value_));
        }

        void ctrl_map_anim_clear(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__ctrlmapanimclear__control__ret__nothing, value_);
        }

        void ctrl_map_anim_commit(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__ctrlmapanimcommit__control__ret__nothing, value_);
        }

        bool ctrl_map_anim_done(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrlmapanimdone__control__ret__bool, value_);
        }

        float ctrl_map_scale(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrlmapscale__control__ret__scalar, value_);
        }

        std::string ctrl_model(const control &value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__ctrlmodel__control__ret__string, value_);
        }

        float ctrl_model_scale(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrlmodelscale__control__ret__scalar, value_);
        }

        display ctrl_parent(const control &value_) {
            return display(host::functions.invoke_raw_unary(client::__sqf::unary__ctrlparent__control__ret__display, value_));
        }

        control ctrl_parent_controls_group(const control &value_) {
            return control(host::functions.invoke_raw_unary(client::__sqf::unary__ctrlparentcontrolsgroup__control__ret__control, value_));
        }

        float ctrl_scale(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrlscale__control__ret__scalar, value_);
        }

        void ctrl_set_focus(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__ctrlsetfocus__control__ret__nothing, value_);
        }

        bool ctrl_shown(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__ctrlshown__control__ret__bool, value_);
        }

        std::string ctrl_text(const control &value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__ctrltext__control__ret__string, value_);
        }

        std::string ctrl_text(float value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__ctrltext__scalar__ret__string, value_));
        }

        float ctrl_text_height(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrltextheight__control__ret__scalar, value_);
        }

        std::string ctrl_text_secondary(const control &value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__ctrltextsecondary__control__ret__string, value_);
        }

        float ctrl_type(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__ctrltype__control__ret__scalar, value_);
        }

        bool ctrl_visible(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__ctrlvisible__scalar__ret__bool, value_);
        }

        void ctrl_commit(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlcommit__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_enable(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlenable__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_enable(int control_id_, bool enable_) {
            game_value params(std::vector<game_value>{
                (float)control_id_,
                    enable_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__ctrlenable__array__ret__nothing, params);
        }

        void ctrl_remove_all_event_handlers(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlremovealleventhandlers__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_auto_scroll_delay(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetautoscrolldelay__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_auto_scroll_rewind(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetautoscrollrewind__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_set_auto_scroll_speed(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetautoscrollspeed__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_checked(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetchecked__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_set_fade(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfade__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfont__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h1(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth1__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h1b(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth1b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h2(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth2__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h2b(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth2b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h3(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth3__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h3b(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth3b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h4(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth4__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h4b(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth4b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h5(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth5__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h5b(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth5b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h6(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth6__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_h6b(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfonth6b__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheight__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h1(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth1__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h2(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth2__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h3(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth3__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h4(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth4__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h5(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth5__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_h6(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheighth6__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_height_secondary(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontheightsecondary__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_p(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontp__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_p(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontp__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_pb(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontpb__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_font_secondary(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetfontsecondary__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_model(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetmodel__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_model_scale(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetmodelscale__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_scale(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetscale__control__scalar__ret__nothing, value0_, value1_);
        }

        void ctrl_set_structured_text(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsetstructuredtext__control__text__ret__nothing, value0_, value1_);
        }

        void ctrl_set_text(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsettext__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_text(int control_id_, const std::string &text_) {
            game_value params({
                (float)control_id_,
                text_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__ctrlsettext__array__ret__nothing, params);
        }

        void ctrl_set_text_secondary(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsettextsecondary__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_set_tooltip(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlsettooltip__control__string__ret__nothing, value0_, value1_);
        }

        void ctrl_show(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ctrlshow__control__bool__ret__nothing, value0_, value1_);
        }

        void ctrl_show(int control_id_, bool show_)
        {
            game_value params(std::vector<game_value>{
                (float)control_id_,
                show_
            });
            host::functions.invoke_raw_unary(client::__sqf::unary__ctrlshow__array__ret__nothing, params);
        }

        /* Curator */
                object curatorcamera() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__curatorcamera__ret__object);
        }

        object curatormouseover() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__curatormouseover__ret__object);
        }

        std::vector<object> curatorselected() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__curatorselected__ret__array));
        }

        void opencuratorinterface() {
            __helpers::__empty_nular(client::__sqf::nular__opencuratorinterface__ret__nothing);
        }

        bool shown_curatorcompass() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__showncuratorcompass__ret__bool);
        }

        float curator_camera_area_ceiling(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__curatorcameraareaceiling__object__ret__scalar, value_);
        }

        bool curator_editing_area_type(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__curatoreditingareatype__object__ret__bool, value_);
        }

        float curator_points(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__curatorpoints__object__ret__scalar, value_);
        }

        float curator_waypoint_cost(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__curatorwaypointcost__object__ret__scalar, value_);
        }

        object get_assigned_curator_logic(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getassignedcuratorlogic__object__ret__object, value_);
        }

        object get_assigned_curator_unit(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getassignedcuratorunit__object__ret__object, value_);
        }

        void remove_all_curator_addons(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcuratoraddons__object__ret__nothing, value_);
        }

        void remove_all_curator_camera_areas(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcuratorcameraareas__object__ret__nothing, value_);
        }

        void remove_all_curator_editing_areas(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcuratoreditingareas__object__ret__nothing, value_);
        }

        void show_curator_compass(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showcuratorcompass__bool__ret__nothing, value_);
        }

        void unassign_curator(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__unassigncurator__object__ret__nothing, value_);
        }

        void add_curator_points(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addcuratorpoints__object__scalar__ret__nothing, value0_, value1_);
        }

        void allow_curator_logic_ignore_areas(const object &value1_, bool value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__allowcuratorlogicignoreareas__object__bool__ret__nothing, value0_, value1_);
        }
        float curator_coef(const object &value0_, const std::string &value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__curatorcoef__object__string__ret__scalar, value0_, value1_));
        }

        void remove_curator_camera_area(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removecuratorcameraarea__object__scalar__ret__nothing, value0_, value1_);
        }

        void remove_curator_editing_area(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removecuratoreditingarea__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_curator_camera_area_ceiling(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcuratorcameraareaceiling__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_curator_editing_area_type(const object &value1_, bool value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcuratoreditingareatype__object__bool__ret__nothing, value0_, value1_);
        }

        void set_curator_waypoint_cost(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcuratorwaypointcost__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_curator_addons(const object & curator_object_, const std::vector<std::string>& addons_) {
            std::vector<game_value> addons;
            for (std::string addon : addons_) {
                addons.push_back(game_value(addon));
            }
            host::functions.invoke_raw_binary(client::__sqf::binary__addcuratoraddons__object__array__ret__nothing, curator_object_, addons);
        }

        void add_curator_camera_area(const object & curator_object_, int camera_area_id_, const vector2 & position_, float radius_) {
            std::vector<game_value> args{
                (float)camera_area_id_,
                position_,
                radius_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addcuratorcameraarea__object__array__ret__nothing, curator_object_, args);
        }

        void add_curator_camera_area(const object & curator_object_, int camera_area_id_, const vector3 & position_, float radius_) {
            std::vector<game_value> args{
                (float)camera_area_id_,
                position_,
                radius_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addcuratorcameraarea__object__array__ret__nothing, curator_object_, args);
        }

        void add_curator_editable_object(const object & curator_object_, const std::vector<object>& objects_, bool add_crew_) {
            std::vector<game_value> objects;
            for (object cobject : objects_) {
                objects.push_back(game_value(cobject));
            }
            std::vector<game_value> args{
                objects,
                add_crew_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addcuratoreditableobjects__object__array__ret__nothing, curator_object_, args);
        }

        void add_curator_editing_area(const object & curator_object_, int edit_area_id_, const vector2 & position_, float radius_) {
            std::vector<game_value> args{
                (float)edit_area_id_,
                position_,
                radius_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addcuratoreditingarea__object__array__ret__nothing, curator_object_, args);
        }

        std::vector<std::string> curator_addons(const object &curator_module_)
        {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__curatoraddons__object__ret__array, curator_module_));
        }

        std::vector<object> curator_editable_objects(const object &curator_module_)
        {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__curatoreditableobjects__object__ret__array, curator_module_));
        }

        /* Group */
                bool group_icon_selectable() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__groupiconselectable__ret__bool);
        }

        // TODO std::array<bool, 2> group_icons_visible();

        group grp_null() {
            return __helpers::__retrieve_nular_group(client::__sqf::nular__grpnull__ret__group);
        }

        void clear_group_icons(const group &value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__cleargroupicons__group__ret__nothing, value_);
        }

        group create_group(const side &value_) {
            return group(host::functions.invoke_raw_unary(client::__sqf::unary__creategroup__side__ret__group, value_));
        }

        void delete_group(const group &value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__deletegroup__group__ret__nothing, value_);
        }

        group group_from_net_id(const std::string& value_) {
            return group(host::functions.invoke_raw_unary(client::__sqf::unary__groupfromnetid__string__ret__group, value_));
        }

        std::string group_id(const group &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__groupid__group__ret__string, value_));
        }

        float group_owner(const group &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__groupowner__group__ret__scalar, value_));
        }

        bool set_group_owner(const group &value1_, float value0_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__setgroupowner__group__scalar__ret__bool, value0_, value1_));
        }

        object leader(const group &value_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__leader__group__ret__object, value_));
        }

        void group_radio(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__groupradio__object__string__ret__nothing, value0_, value1_);
        }

        void remove_group_icon(const group &value1_, float value0_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removegroupicon__group__scalar__ret__nothing, value0_, value1_);
        }

        void select_leader(const object &value0_, const group &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__selectleader__group__object__ret__nothing, value1_, value0_);
        }

        float current_waypoint(const group &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__currentwaypoint__group__ret__scalar, value_));
        }

        void set_group_icons_selectable(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__setgroupiconsselectable__bool__ret__nothing, value_);
        }

        /* Marker */
                void delete_marker(const std::string& value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarker__string__ret__nothing, value_);
        }

        void delete_marker_local(const std::string& value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarkerlocal__string__ret__nothing, value_);
        }

        float marker_alpha(const std::string& value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markeralpha__string__ret__scalar, value_);
        }

        std::string marker_brush(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markerbrush__string__ret__string, value_);
        }

        std::string marker_color(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markercolor__string__ret__string, value_);
        }

        float marker_dir(const std::string& value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markerdir__string__ret__scalar, value_);
        }

        std::string marker_shape(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markershape__string__ret__string, value_);
        }

        std::string marker_text(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markertext__string__ret__string, value_);
        }

        std::string marker_type(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markertype__string__ret__string, value_);
        }

        void set_marker_type(const std::string& marker_, const std::string& type_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertype__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_type_local(const std::string& marker_, const std::string& type_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertypelocal__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_text(const std::string& marker_, const std::string& text_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertext__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_text_local(const std::string& marker_, const std::string& text_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertextlocal__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_size(const std::string& marker_, const vector2& size_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkersize__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_size_local(const std::string& marker_, const vector2& size_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkersizelocal__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_shape(const std::string& marker_, const std::string& shape_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkershape__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_shape_local(const std::string& marker_, const std::string& shape_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkershapelocal__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_pos(const std::string& marker_, const vector3& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerpos__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(const std::string& marker_, const vector3& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerposlocal__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos(const std::string& marker_, const vector2& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerpos__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(const std::string& marker_, const vector2& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerposlocal__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_brush(const std::string& marker_, const std::string& brush_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerbrush__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_brush_local(const std::string& marker_, const std::string& brush_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerbrushlocal__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_color(const std::string& marker_, const std::string& color_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkercolor__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_color_local(const std::string& marker_, const std::string& color_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkercolorlocal__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_alpha(const std::string& marker_, float alpha_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralpha__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_alpha_local(const std::string& marker_, float alpha_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralphalocal__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_dir(const std::string& marker_, float dir_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdir__string__scalar__ret__nothing, marker_, dir_);
        }

        void set_marker_dir_local(const std::string& marker_, float dir_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdirlocal__string__scalar__ret__nothing, marker_, dir_);
        }

        std::string get_marker_color(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkercolor__string__ret__string, value_);
        }

        std::string get_marker_type(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkertype__string__ret__string, value_);
        }

        vector3 get_marker_pos(const std::string& value_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__getmarkerpos__string__ret__array, value_));
            // Identical: unary__markerpos__string__ret__array
        }

        vector2 get_marker_size(const std::string& value_) {
            game_value function_return_array = host::functions.invoke_raw_unary(__sqf::unary__getmarkersize__string__ret__array, value_);
            return vector2(function_return_array[0], function_return_array[1]);
            // Identical: unary__markersize__string__ret__array
        }

        std::string create_marker(const std::string &name_, const vector2 &pos_)
        {
            game_value params({
                name_,
                pos_
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
        }

        std::string create_marker(const std::string &name_, const vector3 &pos_)
        {
            game_value params({
                name_,
                pos_
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
        }

        std::string create_marker(const std::string &name_, const object &pos_)
        {
            game_value params({
                name_,
                pos_
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
        }

        std::string create_marker_local(const std::string &name_, const vector2 &pos_)
        {
            game_value params({
                name_,
                pos_,
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
        }

        std::string create_marker_local(const std::string &name_, const vector3 &pos_)
        {
            game_value params({
                name_,
                pos_,
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
        }

        std::string create_marker_local(const std::string &name_, const object &pos_)
        {
            game_value params({
                name_,
                pos_,
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
        }

        /* Misc */
                float acc_time() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__acctime__ret__scalar);
        }

        object agent(const team_member &value_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__agent__team_member__ret__object, value_));
        }

        std::vector<std::string> activated_addons() {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_nular(client::__sqf::nular__activatedaddons__ret__array));
        }

        std::vector<team_member> agents() {
            return __helpers::__convert_to_team_members_vector(host::functions.invoke_raw_nular(client::__sqf::nular__agents__ret__array));
        }

        float armorypoints() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__armorypoints__ret__scalar);
        }

        float benchmark() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__benchmark__ret__scalar);
        }

        side blufor() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__blufor__ret__side);
        }

        std::string briefingname() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__briefingname__ret__string);
        }

        bool cadetmode() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__cadetmode__ret__bool);
        }

        object cameraon() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__cameraon__ret__object);
        }

        std::string cameraview() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__cameraview__ret__string);
        }

        config campaignconfigfile() {
            return __helpers::__retrieve_nular_config(client::__sqf::nular__campaignconfigfile__ret__config);
        }

        bool cheatsenabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__cheatsenabled__ret__bool);
        }

        side civilian() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__civilian__ret__side);
        }

        void clearforcesrtd() {
            __helpers::__empty_nular(client::__sqf::nular__clearforcesrtd__ret__nothing);
        }

        void clearitempool() {
            __helpers::__empty_nular(client::__sqf::nular__clearitempool__ret__nothing);
        }

        void clearmagazinepool() {
            __helpers::__empty_nular(client::__sqf::nular__clearmagazinepool__ret__nothing);
        }

        void clearradio() {
            __helpers::__empty_nular(client::__sqf::nular__clearradio__ret__nothing);
        }

        void clearweaponpool() {
            __helpers::__empty_nular(client::__sqf::nular__clearweaponpool__ret__nothing);
        }

        float clientowner() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__clientowner__ret__scalar);
        }

        std::string commandingmenu() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__commandingmenu__ret__string);
        }

        config configfile() {
            return __helpers::__retrieve_nular_config(client::__sqf::nular__configfile__ret__config);
        }

        config confignull() {
            return __helpers::__retrieve_nular_config(client::__sqf::nular__confignull__ret__config);
        }

        control controlnull() {
            return __helpers::__retrieve_nular_control(client::__sqf::nular__controlnull__ret__control);
        }

        std::string copyfromclipboard() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__copyfromclipboard__ret__string);
        }

        float currentchannel() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__currentchannel__ret__scalar);
        }

        rv_namespace currentnamespace() {
            return __helpers::__retrieve_nular_namespace(client::__sqf::nular__currentnamespace__ret__namespace);
        }

        object cursortarget() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__cursortarget__ret__object);
        }

        float daytime() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__daytime__ret__scalar);
        }

        bool dialog() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__dialog__ret__bool);
        }

        float difficulty() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__difficulty__ret__scalar);
        }

        bool difficulty_enabled_rtd() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__difficultyenabledrtd__ret__bool);
        }

        void disable_debriefing_stats() {
            __helpers::__empty_nular(client::__sqf::nular__disabledebriefingstats__ret__nothing);
        }

        void disable_serialization() {
            __helpers::__empty_nular(client::__sqf::nular__disableserialization__ret__nothing);
        }

        display display_null() {
            return __helpers::__retrieve_nular_display(client::__sqf::nular__displaynull__ret__display);
        }

        float distribution_region() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__distributionregion__ret__scalar);
        }

        side east() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__east__ret__side);
        }

        void enable_end_dialog() {
            __helpers::__empty_nular(client::__sqf::nular__enableenddialog__ret__nothing);
        }

        void end_loading_screen() {
            __helpers::__empty_nular(client::__sqf::nular__endloadingscreen__ret__nothing);
        }

        float estimated_end_server_time() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__estimatedendservertime__ret__scalar);
        }

        void exit() {
            __helpers::__empty_nular(client::__sqf::nular__exit__ret__nothing);
        }

        void finish_mission_init() {
            __helpers::__empty_nular(client::__sqf::nular__finishmissioninit__ret__nothing);
        }

        bool fog() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__fog__ret__scalar);
        }

        float fog_forecast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__fogforecast__ret__scalar);
        }

        // TODO std::vector<float> fog_params();

        void force_end() {
            __helpers::__empty_nular(client::__sqf::nular__forceend__ret__nothing);
        }

        void force_weather_change() {
            __helpers::__empty_nular(client::__sqf::nular__forceweatherchange__ret__nothing);
        }

        bool free_look() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__freelook__ret__bool);
        }



        std::string getclientstate() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__getclientstate__ret__string);
        }

        float getelevationoffset() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__getelevationoffset__ret__scalar);
        }

        // TODO std::array<float, 2> get_mouse_position();
        // TODO std::array<float, 2> get_object_view_distance();

        bool get_remote_sensors_disabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__getremotesensorsdisabled__ret__bool);
        }

        // TODO std::array<float, 6> get_resolution();
        float get_shadow_distance() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__getshadowdistance__ret__scalar);
        }

        float get_total_dlc_usage_time() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__gettotaldlcusagetime__ret__scalar);
        }

        float gusts() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__gusts__ret__scalar);
        }

        void halt() {
            __helpers::__empty_nular(client::__sqf::nular__halt__ret__nothing);
        }

        bool has_interface() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__hasinterface__ret__bool);
        }

        bool hc_shown_bar() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__hcshownbar__ret__bool);
        }

        float humidity() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__humidity__ret__scalar);
        }

        side independent() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__independent__ret__side);
        }

        void init_ambient_life() {
            __helpers::__empty_nular(client::__sqf::nular__initambientlife__ret__nothing);
        }

        bool is_autotest() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isautotest__ret__bool);
        }

        bool is_filepatching_enabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isfilepatchingenabled__ret__bool);
        }

        bool is_instructor_figure_enabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isinstructorfigureenabled__ret__bool);
        }

        bool is_pip_enabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__ispipenabled__ret__bool);
        }

        bool is_steam_mission() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__issteammission__ret__bool);
        }

        bool is_stream_friendly_ui_enabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isstreamfriendlyuienabled__ret__bool);
        }

        bool is_stress_damage_enabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isstressdamageenabled__ret__bool);
        }

        bool is_tut_hints_enabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__istuthintsenabled__ret__bool);
        }

        std::string language() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__language__ret__string);
        }

        // TODO std::vector<std::array<std::string, 2>> library_credits();
        std::vector<rv_credit> library_credits() {
            game_value input = host::functions.invoke_raw_nular(client::__sqf::nular__librarycredits__ret__array);

            std::vector<rv_credit> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(input[i]);
            }
            return output;
        }

        std::vector<std::string> library_disclaimers() {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_nular(client::__sqf::nular__librarydisclaimers__ret__array));
        }

        float lightnings() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__lightnings__ret__scalar);
        }

        std::string line_break() {
            return game_value(host::functions.invoke_raw_nular(client::__sqf::nular__linebreak__ret__text));
        }

        void load_game() {
            __helpers::__empty_nular(client::__sqf::nular__loadgame__ret__nothing);
        }

        location location_null() {
            return __helpers::__retrieve_nular_location(client::__sqf::nular__locationnull__ret__location);
        }

        void log_entities() {
            __helpers::__empty_nular(client::__sqf::nular__logentities__ret__nothing);
        }

        void map_anim_clear() {
            __helpers::__empty_nular(client::__sqf::nular__mapanimclear__ret__nothing);
        }

        void map_anim_commit() {
            __helpers::__empty_nular(client::__sqf::nular__mapanimcommit__ret__nothing);
        }

        bool map_anim_done() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__mapanimdone__ret__bool);
        }

        bool mark_as_finished_on_steam() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__markasfinishedonsteam__ret__bool);
        }

        float mission_difficulty() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__missiondifficulty__ret__scalar);
        }

        std::string mission_name() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__missionname__ret__string);
        }

        rv_namespace mission_namespace() {
            return __helpers::__retrieve_nular_namespace(client::__sqf::nular__missionnamespace__ret__namespace);
        }

        // TODO std::array<float, 6> mission_start();

        float moon_intensity() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__moonintensity__ret__scalar);
        }

        float music_volume() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__musicvolume__ret__scalar);
        }

        float next_weather_change() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__nextweatherchange__ret__scalar);
        }

        object obj_null() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__objnull__ret__object);
        }

        side opfor() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__opfor__ret__side);
        }

        float overcast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__overcast__ret__scalar);
        }

        float overcast_forecast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__overcastforecast__ret__scalar);
        }

        rv_namespace parsing_namespace() {
            return __helpers::__retrieve_nular_namespace(client::__sqf::nular__parsingnamespace__ret__namespace);
        }

        float particles_quality() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__particlesquality__ret__scalar);
        }

        float pi() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__pi__ret__scalar);
        }

        float pixel_h() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__pixelh__ret__scalar);
        }

        float pixel_w() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__pixelw__ret__scalar);
        }

        std::vector<object> playable_units() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__playableunits__ret__array));
        }

        float player_respawn_time() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__playerrespawntime__ret__scalar);
        }

        side player_side() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__playerside__ret__side);
        }

        std::string profile_name() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__profilename__ret__string);
        }
        rv_namespace profile_namespace() {
            return __helpers::__retrieve_nular_namespace(client::__sqf::nular__profilenamespace__ret__namespace);
        }

        std::string profile_namesteam() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__profilenamesteam__ret__string);
        }

        float rain() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__rain__ret__scalar);
        }

        float rainbow() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__rainbow__ret__scalar);
        }

        void reset_cam_shake() {
            __helpers::__empty_nular(client::__sqf::nular__resetcamshake__ret__nothing);
        }

        side resistance() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__resistance__ret__side);
        }

        bool reversed_mouse_y() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__reversedmousey__ret__bool);
        }

        void run_init_script() {
            __helpers::__empty_nular(client::__sqf::nular__runinitscript__ret__nothing);
        }

        float safe_zone_x() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezonex__ret__scalar);
        }
        float safe_zone_y() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezoney__ret__scalar);
        }
        float safe_zone_h() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezoneh__ret__scalar);
        }
        float safe_zone_w() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezonew__ret__scalar);
        }
        float safe_zone_x_abs() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezonexabs__ret__scalar);
        }
        float safe_zone_w_abs() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezonewabs__ret__scalar);
        }

        float diag_fps() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__diag_fps__ret__scalar);
        }
        float diag_fpsmin() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__diag_fpsmin__ret__scalar);
        }
        float diag_frameno() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__diag_frameno__ret__scalar);
        }
        float diag_ticktime() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__diag_ticktime__ret__scalar);
        }

        bool shown_artillerycomputer() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownartillerycomputer__ret__bool);
        }
        bool shown_chat() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownchat__ret__bool);
        }
        bool shown_compass() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__showncompass__ret__bool);
        }
        bool shown_hud() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownhud__ret__array);
        }
        bool shown_gps() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__showngps__ret__bool);
        }
        bool shown_map() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownmap__ret__bool);
        }
        bool shown_pad() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownpad__ret__bool);
        }
        bool shown_radio() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownradio__ret__bool);
        }
        bool shown_uavfeed() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownuavfeed__ret__bool);
        }
        bool shown_warrant() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownwarrant__ret__bool);
        }
        bool shown_watch() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownwatch__ret__bool);
        }

        bool visible_watch() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblewatch__ret__bool);
        }

        bool visible_map() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblemap__ret__bool);
        }

        bool visible_gps() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblegps__ret__bool);
        }

        bool visible_compass() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblecompass__ret__bool);
        }

        float view_distance() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__viewdistance__ret__scalar);
        }

        bool team_switch_enabled()
        {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__teamswitchenabled__ret__bool);
        }

        void team_switch()
        {
            __helpers::__empty_nular(client::__sqf::nular__teamswitch__ret__nothing);
        }

        float system_of_units()
        {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__systemofunits__ret__scalar);
        }

        std::vector<object> switchable_units() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__switchableunits__ret__array));
        }

        float sun_or_moon()
        {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__sunormoon__ret__scalar);
        }

        float sound_volume()
        {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__soundvolume__ret__scalar);
        }

        bool sling_load_assistant_shown()
        {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__slingloadassistantshown__ret__bool);
        }

        void simul_weather_sync()
        {
            __helpers::__empty_nular(client::__sqf::nular__simulweathersync__ret__nothing);
        }

        void select_no_player()
        {
            __helpers::__empty_nular(client::__sqf::nular__selectnoplayer__ret__nothing);
        }

        bool saving_enabled()
        {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__savingenabled__ret__bool);
        }

        void save_profile_namespace()
        {
            __helpers::__empty_nular(client::__sqf::nular__saveprofilenamespace__ret__nothing);
        }

        std::string action_name(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__actionname__string__ret__string, value_);
        }

        void activate_key(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__activatekey__string__ret__nothing, value_);
        }

        void add_switchable_unit(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__addswitchableunit__object__ret__nothing, value_);
        }

        float air_density_rtd(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__airdensityrtd__scalar__ret__scalar, value_);
        }

        void airport_side(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__airportside__scalar__ret__nothing, value_);
        }

        bool alive(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__alive__object__ret__bool, value_);
        }

        std::string animation_state(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__animationstate__object__ret__string, value_);
        }

        object assigned_commander(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedcommander__object__ret__object, value_);
        }

        object assigned_driver(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assigneddriver__object__ret__object, value_);
        }

        object assigned_gunner(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedgunner__object__ret__object, value_);
        }

        object assigned_target(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedtarget__object__ret__object, value_);
        }

        std::string assigned_team(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__assignedteam__object__ret__string, value_);
        }

        object assigned_vehicle(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedvehicle__object__ret__object, value_);
        }

        std::string backpack(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__backpack__object__ret__string, value_);
        }

        object backpack_container(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__backpackcontainer__object__ret__object, value_);
        }

        std::string behaviour(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__behaviour__object__ret__string, value_);
        }

        std::string binocular(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__binocular__object__ret__string, value_);
        }

        void break_out(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__breakout__string__ret__nothing, value_);
        }

        void break_to(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__breakto__string__ret__nothing, value_);
        }

        void buldozer(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__buldozer_enableroaddiag__bool__ret__nothing, value_);
        }

        bool buldozer(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__buldozer_loadnewroads__string__ret__bool, value_);
        }

        std::string button_action(const control &value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__buttonaction__control__ret__string, value_);
        }

        std::string button_action(float value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__buttonaction__scalar__ret__string, value_));
        }

        bool cam_committed(const object &camera_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__camcommitted__object__ret__bool, camera_);
        }

        void cam_destroy(const object &camera_) {
            __helpers::__empty_unary_object(client::__sqf::unary__camdestroy__object__ret__nothing, camera_);
        }

        bool cam_preloaded(const object &camera_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__campreloaded__object__ret__bool, camera_);
        }

        object cam_target(const object &camera_) {
            return __helpers::__object_unary_object(client::__sqf::unary__camtarget__object__ret__object, camera_);
        }

        void cam_use_nvg(bool use_nvg_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__camusenvg__bool__ret__nothing, use_nvg_);
        }

        void camera_effect_enable_hud(bool enable_hud_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__cameraeffectenablehud__bool__ret__nothing, enable_hud_);
        }

        float camera_interest(const object &entity_) {
            return __helpers::__number_unary_object(client::__sqf::unary__camerainterest__object__ret__scalar, entity_);
        }

        void cam_constuction_set_params(const object &camera_, const vector3 & position_, float radius_, float max_above_land_) {
            std::vector<game_value> args{
                position_,
                radius_,
                max_above_land_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__camconstuctionsetparams__object__array__ret__nothing, camera_, args);
        }

        object cam_create(const std::string & type_, const vector3 & position_) {
            return host::functions.invoke_raw_binary(client::__sqf::binary__camcreate__string__array__ret__object, type_, position_);
        }

        void camera_effect(const object & camera_, const std::string & name_, const std::string & position_) {
            std::vector<game_value> args{
                name_,
                position_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__cameraeffect__object__array__ret__nothing, camera_, args);
        }

        void camera_effect(const object & camera_, const std::string & name_, const std::string & position_, const std::string & rtt_) {
            std::vector<game_value> args{
                name_,
                position_,
                rtt_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__cameraeffect__object__array__ret__nothing, camera_, args);
        }

        void cam_prepare_focus(const object & camera_, float distance_, float blur_) {
            std::vector<game_value> args{
                distance_,
                blur_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparefocus__object__array__ret__nothing, camera_, args);
        }

        void cam_prepare_fov_range(const object & camera_, float min_, float max_) {
            std::vector<game_value> args{
                min_,
                max_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparefovrange__object__array__ret__nothing, camera_, args);
        }

        void cam_prepare_pos(const object & camera_, const vector3 & position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparepos__object__array__ret__nothing, camera_, position_);
        }

        void cam_prepare_rel_pos(const object & camera_, const vector3 & relative_position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparerelpos__object__array__ret__nothing, camera_, relative_position_);
        }

        void cam_prepare_target(const object & camera_, const object & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparetarget__object__object__ret__nothing, camera_, target_);
        }

        void cam_prepare_target(const object & camera_, const vector3 & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparetarget__object__array__ret__nothing, camera_, target_);
        }

        void cam_set_focus(const object & camera_, float distance_, float blur_) {
            std::vector<game_value> args{
                distance_,
                blur_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetfocus__object__array__ret__nothing, camera_, args);
        }

        void cam_set_fov_range(const object & camera_, float min_, float max_) {
            std::vector<game_value> args{
                min_,
                max_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetfovrange__object__array__ret__nothing, camera_, args);
        }

        void cam_set_pos(const object & camera_, const vector3 & position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetpos__object__array__ret__nothing, camera_, position_);
        }

        void cam_set_relative_pos(const object & camera_, const vector3 & relative_position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetrelpos__object__array__ret__nothing, camera_, relative_position_);
        }

        void cam_set_target(const object & camera_, const object & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsettarget__object__object__ret__nothing, camera_, target_);
        }

        void cam_set_target(const object & camera_, const vector3 & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsettarget__object__array__ret__nothing, camera_, target_);
        }

        bool can_fire(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canfire__object__ret__bool, value_);
        }

        bool can_move(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canmove__object__ret__bool, value_);
        }

        bool can_stand(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canstand__object__ret__bool, value_);
        }

        bool can_unload_in_combat(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canunloadincombat__object__ret__bool, value_);
        }

        bool captive(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__captive__object__ret__bool, value_);
        }

        float captive_num(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__captivenum__object__ret__scalar, value_);
        }

        bool cb_checked(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__cbchecked__control__ret__bool, value_);
        }

        bool channel_enabled(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__channelenabled__scalar__ret__bool, value_);
        }

        bool check_aifeature(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__checkaifeature__string__ret__bool, value_);
        }

        void clear_all_items_from_backpack(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearallitemsfrombackpack__object__ret__nothing, value_);
        }

        void clear_backpack_cargo(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearbackpackcargo__object__ret__nothing, value_);
        }

        void clear_backpack_cargo_global(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearbackpackcargoglobal__object__ret__nothing, value_);
        }

        void clear_item_cargo(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearitemcargo__object__ret__nothing, value_);
        }

        void clear_item_cargo_global(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearitemcargoglobal__object__ret__nothing, value_);
        }

        void clear_magazine_cargo(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearmagazinecargo__object__ret__nothing, value_);
        }

        void clear_magazine_cargo_global(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearmagazinecargoglobal__object__ret__nothing, value_);
        }

        void clear_overlay(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__clearoverlay__control__ret__nothing, value_);
        }

        void clear_weapon_cargo(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearweaponcargo__object__ret__nothing, value_);
        }

        void clear_weapon_cargo_global(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearweaponcargoglobal__object__ret__nothing, value_);
        }

        void close_dialog(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__closedialog__scalar__ret__nothing, value_);
        }

        void close_overlay(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__closeoverlay__control__ret__nothing, value_);
        }

        void collapse_object_tree(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__collapseobjecttree__control__ret__nothing, value_);
        }

        float collective_rtd(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__collectivertd__object__ret__scalar, value_);
        }

        object commander(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__commander__object__ret__object, value_);
        }

        void comment(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__comment__string__ret__nothing, value_);
        }

        void commit_overlay(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__commitoverlay__control__ret__nothing, value_);
        }

        bool completed_fsm(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__completedfsm__scalar__ret__bool, value_);
        }

        void copy_to_clipboard(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__copytoclipboard__string__ret__nothing, value_);
        }

        float count(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__count__string__ret__scalar, value_);
        }

        bool create_dialog(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__createdialog__string__ret__bool, value_);
        }

        void create_vehicle_crew(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__createvehiclecrew__object__ret__nothing, value_);
        }

        std::string current_command(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentcommand__object__ret__string, value_);
        }

        std::string current_magazine(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmagazine__object__ret__string, value_);
        }

        std::string current_muzzle(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmuzzle__object__ret__string, value_);
        }

        float current_vision_mode(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__currentvisionmode__object__ret__scalar, value_);
        }

        std::string current_weapon(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentweapon__object__ret__string, value_);
        }

        std::string current_weapon_mode(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentweaponmode__object__ret__string, value_);
        }

        float current_zeroing(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__currentzeroing__object__ret__scalar, value_);
        }

        float damage(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__damage__object__ret__scalar, value_);
        }

        void de_activate_key(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deactivatekey__string__ret__nothing, value_);
        }

        float debriefing_text(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__debriefingtext__string__ret__scalar, value_);
        }

        void delete_collection(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__deletecollection__object__ret__nothing, value_);
        }

        bool delete_identity(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__deleteidentity__string__ret__bool, value_);
        }

        void delete_site(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__deletesite__object__ret__nothing, value_);
        }

        bool delete_status(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__deletestatus__string__ret__bool, value_);
        }

        void detach(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__detach__object__ret__nothing, value_);
        }

        bool did_jipowner(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__didjipowner__object__ret__bool, value_);
        }

        bool difficulty_enabled(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__difficultyenabled__string__ret__bool, value_);
        }

        float direction(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__direction__object__ret__scalar, value_);
        }

        float direction(const location &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__direction__location__ret__scalar, value_);
        }

        void disable_remote_sensors(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__disableremotesensors__bool__ret__nothing, value_);
        }

        void disable_user_input(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__disableuserinput__bool__ret__nothing, value_);
        }

        void dissolve_team(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__dissolveteam__string__ret__nothing, value_);
        }

        object driver(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__driver__object__ret__object, value_);
        }

        void echo(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__echo__string__ret__nothing, value_);
        }

        object effective_commander(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__effectivecommander__object__ret__object, value_);
        }

        void enable_cam_shake(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enablecamshake__bool__ret__nothing, value_);
        }

        void enable_caustics(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enablecaustics__bool__ret__nothing, value_);
        }

        void enable_diag_legend(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enablediaglegend__bool__ret__nothing, value_);
        }

        void enable_engine_artillery(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enableengineartillery__bool__ret__nothing, value_);
        }

        void enable_environment(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enableenvironment__bool__ret__nothing, value_);
        }

        void enable_radio(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enableradio__bool__ret__nothing, value_);
        }

        void enable_sat_normal_on_detail(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enablesatnormalondetail__bool__ret__nothing, value_);
        }

        void enable_sentences(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enablesentences__bool__ret__nothing, value_);
        }

        void enable_stress_damage(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enablestressdamage__bool__ret__nothing, value_);
        }

        void enable_team_switch(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enableteamswitch__bool__ret__nothing, value_);
        }

        void enable_traffic(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enabletraffic__bool__ret__nothing, value_);
        }

        void end_mission(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__endmission__string__ret__nothing, value_);
        }

        void estimated_time_left(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__estimatedtimeleft__scalar__ret__nothing, value_);
        }

        float exec_fsm(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__execfsm__string__ret__scalar, value_);
        }

        void export_jipmessages(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__exportjipmessages__string__ret__nothing, value_);
        }

        std::string face(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__face__object__ret__string, value_);
        }

        std::string faction(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__faction__object__ret__string, value_);
        }

        void fail_mission(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__failmission__string__ret__nothing, value_);
        }

        void fill_weapons_from_pool(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__fillweaponsfrompool__object__ret__nothing, value_);
        }

        bool finite(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__finite__scalar_nan__ret__bool, value_);
        }

        object first_backpack(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__firstbackpack__object__ret__object, value_);
        }

        object flag(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__flag__object__ret__object, value_);
        }

        object flag_owner(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__flagowner__object__ret__object, value_);
        }

        std::string flag_texture(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__flagtexture__object__ret__string, value_);
        }

        bool fleeing(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__fleeing__object__ret__bool, value_);
        }

        void force_map(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__forcemap__bool__ret__nothing, value_);
        }

        void force_respawn(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__forcerespawn__object__ret__nothing, value_);
        }

        object form_leader(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__formleader__object__ret__object, value_);
        }

        float formation_direction(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__formationdirection__object__ret__scalar, value_);
        }

        object formation_leader(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__formationleader__object__ret__object, value_);
        }

        std::string formation_task(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__formationtask__object__ret__string, value_);
        }

        float fuel(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__fuel__object__ret__scalar, value_);
        }

        float gear_idcammo_count(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__gearidcammocount__scalar__ret__scalar, value_);
        }

        float gear_slot_ammo_count(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__gearslotammocount__control__ret__scalar, value_);
        }

        std::string gear_slot_data(const control &value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__gearslotdata__control__ret__string, value_);
        }

        float get_aiming_coef(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getaimingcoef__object__ret__scalar, value_);
        }

        float get_ammo_cargo(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getammocargo__object__ret__scalar, value_);
        }

        float get_anim_aim_precision(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getanimaimprecision__object__ret__scalar, value_);
        }

        float get_anim_speed_coef(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getanimspeedcoef__object__ret__scalar, value_);
        }

        float get_bleeding_remaining(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getbleedingremaining__object__ret__scalar, value_);
        }

        float get_burning_value(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getburningvalue__object__ret__scalar, value_);
        }

        object get_connected_uav(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getconnecteduav__object__ret__object, value_);
        }

        float get_custom_aim_coef(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getcustomaimcoef__object__ret__scalar, value_);
        }

        float get_dlcusage_time(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__getdlcusagetime__scalar__ret__scalar, value_);
        }

        float get_dammage(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getdammage__object__ret__scalar, value_);
        }

        float get_dir(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getdir__object__ret__scalar, value_);
        }

        float get_dir_visual(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getdirvisual__object__ret__scalar, value_);
        }

        std::string get_editor_mode(const control &value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__geteditormode__control__ret__string, value_);
        }

        float get_fatigue(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getfatigue__object__ret__scalar, value_);
        }

        float get_fuel_cargo(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getfuelcargo__object__ret__scalar, value_);
        }

        float get_mass(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getmass__object__ret__scalar, value_);
        }

        float get_object_dlc(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getobjectdlc__object__ret__scalar, value_);
        }

        float get_object_type(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getobjecttype__object__ret__scalar, value_);
        }

        float get_oxygen_remaining(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getoxygenremaining__object__ret__scalar, value_);
        }

        float get_player_channel(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getplayerchannel__object__ret__scalar, value_);
        }

        std::string get_player_uid(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__getplayeruid__object__ret__string, value_);
        }

        float get_repair_cargo(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getrepaircargo__object__ret__scalar, value_);
        }

        float get_rotor_brake_rtd(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getrotorbrakertd__object__ret__scalar, value_);
        }

        object get_sling_load(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getslingload__object__ret__object, value_);
        }

        float get_stamina(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getstamina__object__ret__scalar, value_);
        }

        float get_stat_value(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__getstatvalue__string__ret__scalar, value_);
        }

        float get_suppression(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getsuppression__object__ret__scalar, value_);
        }

        float get_weapon_sway(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getweaponsway__object__ret__scalar, value_);
        }

        float get_wings_orientation_rtd(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getwingsorientationrtd__object__ret__scalar, value_);
        }

        float get_wings_position_rtd(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getwingspositionrtd__object__ret__scalar, value_);
        }

        std::string goggles(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__goggles__object__ret__string, value_);
        }

        object gunner(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__gunner__object__ret__object, value_);
        }

        std::string handgun_magazine(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__handgunmagazine__object__ret__string, value_);
        }

        std::string handgun_weapon(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__handgunweapon__object__ret__string, value_);
        }

        float hands_hit(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__handshit__object__ret__scalar, value_);
        }

        void hc_remove_all_groups(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hcremoveallgroups__object__ret__nothing, value_);
        }

        void hc_show_bar(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__hcshowbar__bool__ret__nothing, value_);
        }

        std::string headgear(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__headgear__object__ret__string, value_);
        }

        void hide_body(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hidebody__object__ret__nothing, value_);
        }

        void hide_object(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hideobject__object__ret__nothing, value_);
        }

        void hide_object_global(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hideobjectglobal__object__ret__nothing, value_);
        }

        void hint_c(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__hintc__string__ret__nothing, value_);
        }

        std::string hmd(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__hmd__object__ret__string, value_);
        }

        void import_all_groups(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__importallgroups__control__ret__nothing, value_);
        }

        std::string incapacitated_state(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__incapacitatedstate__object__ret__string, value_);
        }

        bool inflamed(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__inflamed__object__ret__bool, value_);
        }

        float input_action(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__inputaction__string__ret__scalar, value_);
        }

        bool is_able_to_breathe(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isabletobreathe__object__ret__bool, value_);
        }

        bool is_aim_precision_enabled(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isaimprecisionenabled__object__ret__bool, value_);
        }

        bool is_auto_hover_on(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isautohoveron__object__ret__bool, value_);
        }

        bool is_auto_trim_on_rtd(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isautotrimonrtd__object__ret__bool, value_);
        }

        bool is_autonomous(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isautonomous__object__ret__bool, value_);
        }

        bool is_bleeding(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isbleeding__object__ret__bool, value_);
        }

        bool is_burning(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isburning__object__ret__bool, value_);
        }

        bool is_collision_light_on(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__iscollisionlighton__object__ret__bool, value_);
        }

        bool is_copilot_enabled(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__iscopilotenabled__object__ret__bool, value_);
        }

        bool is_dlcavailable(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__isdlcavailable__scalar__ret__bool, value_);
        }

        bool is_engine_on(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isengineon__object__ret__bool, value_);
        }

        bool is_forced_walk(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isforcedwalk__object__ret__bool, value_);
        }

        bool is_formation_leader(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isformationleader__object__ret__bool, value_);
        }

        bool is_hidden(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ishidden__object__ret__bool, value_);
        }

        bool is_in_remains_collector(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isinremainscollector__object__ret__bool, value_);
        }

        bool is_key_active(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__iskeyactive__string__ret__bool, value_);
        }

        bool is_light_on(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__islighton__object__ret__bool, value_);
        }

        bool is_localized(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__islocalized__string__ret__bool, value_);
        }

        bool is_manual_fire(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ismanualfire__object__ret__bool, value_);
        }

        bool is_marked_for_collection(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ismarkedforcollection__object__ret__bool, value_);
        }

        bool is_object_hidden(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isobjecthidden__object__ret__bool, value_);
        }

        bool is_object_rtd(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isobjectrtd__object__ret__bool, value_);
        }

        bool is_player(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isplayer__object__ret__bool, value_);
        }

        bool is_real_time(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__isrealtime__control__ret__bool, value_);
        }

        bool is_showing(const control &value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__isshowing3dicons__control__ret__bool, value_);
        }

        bool is_sprint_allowed(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__issprintallowed__object__ret__bool, value_);
        }

        bool is_stamina_enabled(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isstaminaenabled__object__ret__bool, value_);
        }

        bool is_touching_ground(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__istouchingground__object__ret__bool, value_);
        }

        bool is_turned_out(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isturnedout__object__ret__bool, value_);
        }

        bool is_uavconnected(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isuavconnected__object__ret__bool, value_);
        }

        bool is_walking(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__iswalking__object__ret__bool, value_);
        }

        bool is_weapon_deployed(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isweapondeployed__object__ret__bool, value_);
        }

        bool is_weapon_rested(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isweaponrested__object__ret__bool, value_);
        }

        std::string land_result(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__landresult__object__ret__string, value_);
        }

        object laser_target(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__lasertarget__object__ret__object, value_);
        }

        void lb_clear(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__lbclear__control__ret__nothing, value_);
        }

        void lb_clear(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__lbclear__scalar__ret__nothing, value_);
        }

        float lb_cur_sel(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lbcursel__control__ret__scalar, value_);
        }

        float lb_cur_sel(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__lbcursel__scalar__ret__scalar, value_);
        }

        float lb_size(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lbsize__control__ret__scalar, value_);
        }

        float lb_size(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__lbsize__scalar__ret__scalar, value_);
        }

        float lb_sort_by_value(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lbsortbyvalue__control__ret__scalar, value_);
        }

        object leader(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__leader__object__ret__object, value_);
        }

        bool leaderboard_de_init(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__leaderboarddeinit__string__ret__bool, value_);
        }

        bool leaderboard_init(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__leaderboardinit__string__ret__bool, value_);
        }

        bool leaderboard_request_rows_friends(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__leaderboardrequestrowsfriends__string__ret__bool, value_);
        }

        float leaderboard_state(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__leaderboardstate__string__ret__scalar, value_);
        }

        std::string life_state(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__lifestate__object__ret__string, value_);
        }

        void light_detach_object(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__lightdetachobject__object__ret__nothing, value_);
        }

        std::string light_is_on(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__lightison__object__ret__string, value_);
        }

        void lnb_clear(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__lnbclear__control__ret__nothing, value_);
        }

        void lnb_clear(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__lnbclear__scalar__ret__nothing, value_);
        }

        float lnb_cur_sel_row(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lnbcurselrow__control__ret__scalar, value_);
        }

        float lnb_cur_sel_row(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__lnbcurselrow__scalar__ret__scalar, value_);
        }

        float load(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__load__object__ret__scalar, value_);
        }

        float load_abs(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loadabs__object__ret__scalar, value_);
        }

        float load_backpack(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loadbackpack__object__ret__scalar, value_);
        }

        std::string load_file(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__loadfile__string__ret__string, value_);
        }

        float load_uniform(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loaduniform__object__ret__scalar, value_);
        }

        float load_vest(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loadvest__object__ret__scalar, value_);
        }

        std::string localize(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__localize__string__ret__string, value_);
        }

        bool lock_identity(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__lockidentity__object__ret__bool, value_);
        }

        float locked(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__locked__object__ret__scalar, value_);
        }

        bool locked_driver(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__lockeddriver__object__ret__bool, value_);
        }

        bool mine_active(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__mineactive__object__ret__bool, value_);
        }

        float morale(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__morale__object__ret__scalar, value_);
        }

        void move_out(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__moveout__object__ret__nothing, value_);
        }

        float move_time(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__movetime__object__ret__scalar, value_);
        }

        bool move_to_completed(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__movetocompleted__object__ret__bool, value_);
        }

        bool move_to_failed(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__movetofailed__object__ret__bool, value_);
        }

        std::string name(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__name__object__ret__string, value_);
        }

        std::string name(const location &loc_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__name__location__ret__string, loc_));
        }

        std::string name_sound(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__namesound__object__ret__string, value_);
        }

        object nearest_building(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__nearestbuilding__object__ret__object, value_);
        }

        object nearest_building(const vector3 &value_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__nearestbuilding__array__ret__object, value_));
        }

        float need_reload(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__needreload__object__ret__scalar, value_);
        }

        std::string net_id(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__netid__object__ret__string, value_);
        }

        float next_menu_item_index(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__nextmenuitemindex__control__ret__scalar, value_);
        }

        float number_of_engines_rtd(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__numberofenginesrtd__object__ret__scalar, value_);
        }

        object object_parent(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__objectparent__object__ret__object, value_);
        }

        void on_briefing_group(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefinggroup__string__ret__nothing, value_);
        }

        void on_briefing_notes(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefingnotes__string__ret__nothing, value_);
        }

        void on_briefing_plan(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefingplan__string__ret__nothing, value_);
        }

        void on_briefing_team_switch(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefingteamswitch__string__ret__nothing, value_);
        }

        bool open_dlc_page(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__opendlcpage__scalar__ret__bool, value_);
        }

        bool open_youtube_video(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__openyoutubevideo__string__ret__bool, value_);
        }

        float owner(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__owner__object__ret__scalar, value_);
        }

        float parse_number(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__parsenumber__string__ret__scalar, value_);
        }

        void pick_weapon_pool(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__pickweaponpool__object__ret__nothing, value_);
        }

        std::string pitch(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__pitch__object__ret__string, value_);
        }

        void play_music(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__playmusic__string__ret__nothing, value_);
        }

        void play_sound(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__playsound__string__ret__nothing, value_);
        }

        bool pp_effect_committed(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__ppeffectcommitted__string__ret__bool, value_);
        }

        bool pp_effect_committed(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__ppeffectcommitted__scalar__ret__bool, value_);
        }

        void pp_effect_destroy(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__ppeffectdestroy__scalar__ret__nothing, value_);
        }

        bool pp_effect_enabled(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__ppeffectenabled__scalar__ret__bool, value_);
        }

        float precision(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__precision__object__ret__scalar, value_);
        }

        bool preload_sound(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__preloadsound__string__ret__bool, value_);
        }

        std::string preprocess_file(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__preprocessfile__string__ret__string, value_);
        }

        std::string preprocess_file_line_numbers(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__preprocessfilelinenumbers__string__ret__string, value_);
        }

        std::string primary_weapon(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__primaryweapon__object__ret__string, value_);
        }

        void process_diary_link(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__processdiarylink__string__ret__nothing, value_);
        }

        void progress_loading_screen(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__progressloadingscreen__scalar__ret__nothing, value_);
        }

        float progress_position(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__progressposition__control__ret__scalar, value_);
        }

        void public_variable(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__publicvariable__string__ret__nothing, value_);
        }

        void public_variable_server(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__publicvariableserver__string__ret__nothing, value_);
        }

        void put_weapon_pool(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__putweaponpool__object__ret__nothing, value_);
        }

        float query_items_pool(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__queryitemspool__string__ret__scalar, value_);
        }

        float query_magazine_pool(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__querymagazinepool__string__ret__scalar, value_);
        }

        float query_weapon_pool(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__queryweaponpool__string__ret__scalar, value_);
        }

        std::string rank(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__rank__object__ret__string, value_);
        }

        float rank_id(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__rankid__object__ret__scalar, value_);
        }

        float rating(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__rating__object__ret__scalar, value_);
        }

        void reload(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__reload__object__ret__nothing, value_);
        }

        bool reload_enabled(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__reloadenabled__object__ret__bool, value_);
        }

        void remove_all_actions(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallactions__object__ret__nothing, value_);
        }

        void remove_all_assigned_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallassigneditems__object__ret__nothing, value_);
        }

        void remove_all_containers(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcontainers__object__ret__nothing, value_);
        }

        void remove_all_handgun_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallhandgunitems__object__ret__nothing, value_);
        }

        void remove_all_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallitems__object__ret__nothing, value_);
        }

        void remove_all_items_with_magazines(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallitemswithmagazines__object__ret__nothing, value_);
        }

        void remove_all_mission_event_handlers(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__removeallmissioneventhandlers__string__ret__nothing, value_);
        }

        void remove_all_music_event_handlers(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__removeallmusiceventhandlers__string__ret__nothing, value_);
        }

        void remove_all_primary_weapon_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallprimaryweaponitems__object__ret__nothing, value_);
        }

        void remove_all_weapons(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallweapons__object__ret__nothing, value_);
        }

        void remove_backpack(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removebackpack__object__ret__nothing, value_);
        }

        void remove_backpack_global(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removebackpackglobal__object__ret__nothing, value_);
        }

        void remove_goggles(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removegoggles__object__ret__nothing, value_);
        }

        void remove_headgear(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeheadgear__object__ret__nothing, value_);
        }

        void remove_switchable_unit(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeswitchableunit__object__ret__nothing, value_);
        }

        void remove_uniform(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeuniform__object__ret__nothing, value_);
        }

        void remove_vest(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removevest__object__ret__nothing, value_);
        }

        bool required_version(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__requiredversion__string__ret__bool, value_);
        }

        void reset_subgroup_direction(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__resetsubgroupdirection__object__ret__nothing, value_);
        }

        void restart_editor_camera(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__restarteditorcamera__control__ret__nothing, value_);
        }

        std::string role_description(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__roledescription__object__ret__string, value_);
        }

        bool rope_attach_enabled(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ropeattachenabled__object__ret__bool, value_);
        }

        object rope_attached_to(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__ropeattachedto__object__ret__object, value_);
        }

        void rope_destroy(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__ropedestroy__object__ret__nothing, value_);
        }

        float rope_length(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__ropelength__object__ret__scalar, value_);
        }

        bool rope_unwound(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ropeunwound__object__ret__bool, value_);
        }

        void save_overlay(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__saveoverlay__control__ret__nothing, value_);
        }

        void save_var(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__savevar__string__ret__nothing, value_);
        }

        void scope_name(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__scopename__string__ret__nothing, value_);
        }

        float score(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__score__object__ret__scalar, value_);
        }

        void script_name(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__scriptname__string__ret__nothing, value_);
        }

        float scud_state(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__scudstate__object__ret__scalar, value_);
        }

        std::string secondary_weapon(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__secondaryweapon__object__ret__string, value_);
        }

        void select_player(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__selectplayer__object__ret__nothing, value_);
        }

        void selected_editor_objects(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__selectededitorobjects__control__ret__nothing, value_);
        }

        bool server_command(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__servercommand__string__ret__bool, value_);
        }

        bool server_command_available(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__servercommandavailable__string__ret__bool, value_);
        }

        bool server_command_executable(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__servercommandexecutable__string__ret__bool, value_);
        }

        void set_acc_time(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setacctime__scalar__ret__nothing, value_);
        }

        void set_aperture(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setaperture__scalar__ret__nothing, value_);
        }

        void set_armory_points(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setarmorypoints__scalar__ret__nothing, value_);
        }

        bool set_current_channel(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__setcurrentchannel__scalar__ret__bool, value_);
        }

        void set_horizon_parallax_coef(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__sethorizonparallaxcoef__scalar__ret__nothing, value_);
        }

        void set_object_view_distance(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setobjectviewdistance__scalar__ret__nothing, value_);
        }

        void set_playable(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__setplayable__object__ret__nothing, value_);
        }

        void set_player_respawn_time(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setplayerrespawntime__scalar__ret__nothing, value_);
        }

        void set_shadow_distance(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setshadowdistance__scalar__ret__nothing, value_);
        }

        void set_simul_weather_layers(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setsimulweatherlayers__scalar__ret__nothing, value_);
        }

        void set_stamina_scheme(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__setstaminascheme__string__ret__nothing, value_);
        }

        void set_system_of_units(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setsystemofunits__scalar__ret__nothing, value_);
        }

        void set_terrain_grid(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setterraingrid__scalar__ret__nothing, value_);
        }

        void set_time_multiplier(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__settimemultiplier__scalar__ret__nothing, value_);
        }

        void set_traffic_distance(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__settrafficdistance__scalar__ret__nothing, value_);
        }

        void set_view_distance(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setviewdistance__scalar__ret__nothing, value_);
        }

        void show_chat(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showchat__bool__ret__nothing, value_);
        }

        void show_cinema_border(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showcinemaborder__bool__ret__nothing, value_);
        }

        void show_commanding_menu(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__showcommandingmenu__string__ret__nothing, value_);
        }

        void show_compass(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showcompass__bool__ret__nothing, value_);
        }

        void show_gps(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showgps__bool__ret__nothing, value_);
        }

        void show_hud(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showhud__bool__ret__nothing, value_);
        }

        void show_map(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showmap__bool__ret__nothing, value_);
        }

        void show_pad(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showpad__bool__ret__nothing, value_);
        }

        void show_radio(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showradio__bool__ret__nothing, value_);
        }

        void show_uavfeed(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showuavfeed__bool__ret__nothing, value_);
        }

        void show_warrant(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showwarrant__bool__ret__nothing, value_);
        }

        void show_watch(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showwatch__bool__ret__nothing, value_);
        }

        bool simulation_enabled(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__simulationenabled__object__ret__bool, value_);
        }

        float size_of(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__sizeof__string__ret__scalar, value_);
        }

        float skill(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__skill__object__ret__scalar, value_);
        }

        void skip_time(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__skiptime__scalar__ret__nothing, value_);
        }

        void sleep(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__sleep__scalar__ret__nothing, value_);
        }

        float slider_position(const control &value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__sliderposition__control__ret__scalar, value_);
        }

        float slider_position(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__sliderposition__scalar__ret__scalar, value_);
        }

        bool some_ammo(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__someammo__object__ret__bool, value_);
        }

        std::string speaker(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__speaker__object__ret__string, value_);
        }

        float speed(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__speed__object__ret__scalar, value_);
        }

        std::string stance(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__stance__object__ret__string, value_);
        }

        void stop_engine_rtd(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__stopenginertd__object__ret__nothing, value_);
        }

        bool stopped(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__stopped__object__ret__bool, value_);
        }

        std::string text(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__text__location__ret__string, value_);
        }

        void title_fade_out(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__titlefadeout__scalar__ret__nothing, value_);
        }

        std::string to_lower(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__tolower__string__ret__string, value_);
        }

        std::string to_upper(const std::string &value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__toupper__string__ret__string, value_);
        }

        bool trigger_activated(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__triggeractivated__object__ret__bool, value_);
        }

        object trigger_attached_vehicle(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__triggerattachedvehicle__object__ret__object, value_);
        }

        std::string trigger_text(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__triggertext__object__ret__string, value_);
        }

        float trigger_timeout_current(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__triggertimeoutcurrent__object__ret__scalar, value_);
        }

        std::string trigger_type(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__triggertype__object__ret__string, value_);
        }

        void tv_clear(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__tvclear__scalar__ret__nothing, value_);
        }

        void tv_clear(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__tvclear__control__ret__nothing, value_);
        }

        std::string type_of(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__typeof__object__ret__string, value_);
        }

        void uisleep(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__uisleep__scalar__ret__nothing, value_);
        }

        void unassign_team(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__unassignteam__object__ret__nothing, value_);
        }

        void unassign_vehicle(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__unassignvehicle__object__ret__nothing, value_);
        }

        bool underwater(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__underwater__object__ret__bool, value_);
        }

        std::string uniform(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__uniform__object__ret__string, value_);
        }

        object uniform_container(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__uniformcontainer__object__ret__object, value_);
        }

        object unit_backpack(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__unitbackpack__object__ret__object, value_);
        }

        std::string unit_pos(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__unitpos__object__ret__string, value_);
        }

        float unit_recoil_coefficient(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__unitrecoilcoefficient__object__ret__scalar, value_);
        }

        bool unlock_achievement(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__unlockachievement__string__ret__bool, value_);
        }

        void update_object_tree(const control &value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__updateobjecttree__control__ret__nothing, value_);
        }

        object vehicle(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__vehicle__object__ret__object, value_);
        }

        std::string vehicle_var_name(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__vehiclevarname__object__ret__string, value_);
        }

        bool verify_signature(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__verifysignature__string__ret__bool, value_);
        }

        std::string vest(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__vest__object__ret__string, value_);
        }

        object vest_container(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__vestcontainer__object__ret__object, value_);
        }

        bool waypoints_enabled_uav(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__waypointsenableduav__object__ret__bool, value_);
        }

        bool weapon_lowered(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__weaponlowered__object__ret__bool, value_);
        }

        // BINARY FUNCTIONS

        void add_backpack(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpack__object__string__ret__nothing, value0_, value1_);
        }

        void add_backpack_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpackglobal__object__string__ret__nothing, value0_, value1_);
        }

        void add_goggles(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addgoggles__object__string__ret__nothing, value0_, value1_);
        }

        void add_handgun_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addhandgunitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_headgear(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addheadgear__object__string__ret__nothing, value0_, value1_);
        }

        void add_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additem__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_backpack(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additemtobackpack__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_uniform(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additemtouniform__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_vest(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additemtovest__object__string__ret__nothing, value0_, value1_);
        }

        void add_live_stats(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addlivestats__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_magazine(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazine__object__string__ret__nothing, value0_, value1_);
        }

        void add_magazine_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazineglobal__object__string__ret__nothing, value0_, value1_);
        }

        void add_primary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addprimaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_rating(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addrating__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_score(const object &value0_,float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addscore__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_score_side(const side &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addscoreside__side__scalar__ret__nothing, value0_, value1_);
        }

        void add_secondary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addsecondaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_uniform(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__adduniform__object__string__ret__nothing, value0_, value1_);
        }

        void add_vehicle(const group &value0_, const object &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addvehicle__group__object__ret__nothing, value0_, value1_);
        }

        void add_vest(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addvest__object__string__ret__nothing, value0_, value1_);
        }

        void add_weapon(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addweapon__object__string__ret__nothing, value0_, value1_);
        }

        void add_weapon_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponglobal__object__string__ret__nothing, value0_, value1_);
        }

        void allow3dmode(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__allow3dmode__control__bool__ret__nothing, value0_, value1_);
        }

        void allow_crew_in_immobile(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__allowcrewinimmobile__object__bool__ret__nothing, value0_, value1_);
        }

        void allow_damage(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__allowdamage__object__bool__ret__nothing, value0_, value1_);
        }

        void allow_dammage(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__allowdammage__object__bool__ret__nothing, value0_, value1_);
        }

        void allow_file_operations(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__allowfileoperations__control__bool__ret__nothing, value0_, value1_);
        }

        void allow_sprint(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__allowsprint__object__bool__ret__nothing, value0_, value1_);
        }

        float ammo(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__ammo__object__string__ret__scalar, value0_, value1_));
        }

        float animation_phase(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__animationphase__object__string__ret__scalar, value0_, value1_));
        }

        void assign_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__assignitem__object__string__ret__nothing, value0_, value1_);
        }

        void assign_team(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__assignteam__object__string__ret__nothing, value0_, value1_);
        }

        void assign_to_airport(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__assigntoairport__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_command(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camcommand__object__string__ret__nothing, value0_, value1_);
        }

        void cam_commit(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camcommit__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_commit_prepared(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camcommitprepared__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_preload(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreload__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_bank(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparebank__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_dir(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparedir__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_dive(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparedive__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_fov(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparefov__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_set_bank(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetbank__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_set_dive(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetdive__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_set_fov(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetfov__object__scalar__ret__nothing, value0_, value1_);
        }

        void cb_set_checked(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__cbsetchecked__control__bool__ret__nothing, value0_, value1_);
        }

        void close_display(float value0_, const display &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__closedisplay__display__scalar__ret__nothing, value0_, value1_);
        }

        control controls_group_ctrl(const control &value0_, float value1_) {
            return control(host::functions.invoke_raw_binary(client::__sqf::binary__controlsgroupctrl__control__scalar__ret__control, value0_, value1_));
        }

        display create_display(const std::string& value0_, const display &value1_) {
            return display(host::functions.invoke_raw_binary(client::__sqf::binary__createdisplay__display__string__ret__display, value0_, value1_));
        }

        void create_menu(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__createmenu__control__scalar__ret__nothing, value0_, value1_);
        }

        display create_mission_display(const std::string& value0_, const display &value1_) {
            return display(host::functions.invoke_raw_binary(client::__sqf::binary__createmissiondisplay__display__string__ret__display, value0_, value1_));
        }

        void debug_fsm(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__debugfsm__scalar__bool__ret__nothing, value0_, value1_);
        }

        bool diary_subject_exists(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__diarysubjectexists__object__string__ret__bool, value0_, value1_));
        }

        void direct_say(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__directsay__object__string__ret__nothing, value0_, value1_);
        }

        void disable_ai(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__disableai__object__string__ret__nothing, value0_, value1_);
        }

        void disable_conversation(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__disableconversation__object__bool__ret__nothing, value0_, value1_);
        }

        void disable_nvgequipment(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__disablenvgequipment__object__bool__ret__nothing, value0_, value1_);
        }

        void disable_tiequipment(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__disabletiequipment__object__bool__ret__nothing, value0_, value1_);
        }

        control display_ctrl(float value0_, const display &value1_) {
            return control(host::functions.invoke_raw_binary(client::__sqf::binary__displayctrl__display__scalar__ret__control, value0_, value1_));
        }

        void display_remove_all_event_handlers(const std::string& value0_, const display &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__displayremovealleventhandlers__display__string__ret__nothing, value0_, value1_);
        }

        float door_phase(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__doorphase__object__string__ret__scalar, value0_, value1_));
        }

        float empty_positions(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__emptypositions__object__string__ret__scalar, value0_, value1_));
        }

        void enable_ai(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enableai__object__string__ret__nothing, value0_, value1_);
        }

        void enable_aifeature(bool value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enableaifeature__string__bool__ret__nothing, value0_, value1_);
        }

        void enable_aim_precision(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enableaimprecision__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_auto_start_up_rtd(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enableautostartuprtd__object__bool__ret__nothing, value0_, value1_);
        }

        bool enable_auto_trim_rtd(const object &value0_, bool value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__enableautotrimrtd__object__bool__ret__bool, value0_, value1_));
        }

        void enable_channel(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablechannel__scalar__bool__ret__nothing, value0_, value1_);
        }

        void enable_copilot(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablecopilot__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_fatigue(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablefatigue__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_mimics(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablemimics__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_reload(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablereload__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_rope_attach(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enableropeattach__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_simulation(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablesimulation__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_simulation_global(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablesimulationglobal__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_stamina(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablestamina__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_uavwaypoints(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enableuavwaypoints__object__bool__ret__nothing, value0_, value1_);
        }

        void engine_on(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__engineon__object__bool__ret__nothing, value0_, value1_);
        }

        void fire(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__fire__object__string__ret__nothing, value0_, value1_);
        }

        void fly_in_height(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__flyinheight__object__scalar__ret__nothing, value0_, value1_);
        }

        void force_add_uniform(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__forceadduniform__object__string__ret__nothing, value0_, value1_);
        }

        void force_speed(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__forcespeed__object__scalar__ret__nothing, value0_, value1_);
        }

        void force_walk(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__forcewalk__object__bool__ret__nothing, value0_, value1_);
        }

        std::string get_editor_object_scope(const control &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__geteditorobjectscope__control__string__ret__string, value0_, value1_));
        }

        float get_hit(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__gethit__object__string__ret__scalar, value0_, value1_));
        }

        float get_hit_index(const object &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__gethitindex__object__scalar__ret__scalar, value0_, value1_));
        }

        float get_hit_point_damage(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__gethitpointdamage__object__string__ret__scalar, value0_, value1_));
        }

        object get_object_proxy(const control &value0_, const std::string& value1_) {
            return object(host::functions.invoke_raw_binary(client::__sqf::binary__getobjectproxy__control__string__ret__object, value0_, value1_));
        }

        float get_speed(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__getspeed__object__string__ret__scalar, value0_, value1_));
        }

        void global_radio(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__globalradio__object__string__ret__nothing, value0_, value1_);
        }

        bool has_weapon(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__hasweapon__object__string__ret__bool, value0_, value1_));
        }

        void hc_remove_group(const object &value0_, const group &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__hcremovegroup__object__group__ret__nothing, value0_, value1_);
        }

        void hide_object(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__hideobject__object__bool__ret__nothing, value0_, value1_);
        }

        void hide_object_global(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__hideobjectglobal__object__bool__ret__nothing, value0_, value1_);
        }

        void hint_c(const std::string& value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__hintc__string__text__ret__nothing, value0_, value1_);
            // Identical from intercept's side: binary__hintc__string__string__ret__nothing
        }

        void html_load(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__htmlload__control__string__ret__nothing, value0_, value1_);
        }

        void inflame(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__inflame__object__bool__ret__nothing, value0_, value1_);
        }

        bool is_flashlight_on(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__isflashlighton__object__string__ret__bool, value0_, value1_));
        }

        bool is_irlaser_on(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__isirlaseron__object__string__ret__bool, value0_, value1_));
        }

        bool is_kind_of(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__iskindof__object__string__ret__bool, value0_, value1_));
        }

        bool is_uniform_allowed(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__isuniformallowed__object__string__ret__bool, value0_, value1_));
        }

        bool kb_add_database(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__kbadddatabase__object__string__ret__bool, value0_, value1_));
        }

        bool kb_add_database_targets(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__kbadddatabasetargets__object__string__ret__bool, value0_, value1_));
        }

        bool kb_has_topic(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__kbhastopic__object__string__ret__bool, value0_, value1_));
        }

        void kb_remove_topic(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__kbremovetopic__object__string__ret__nothing, value0_, value1_);
        }

        float knows_about(const object &value0_, const side &value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__knowsabout__side__object__ret__scalar, value0_, value1_));
        }

        void land(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__land__object__string__ret__nothing, value0_, value1_);
        }

        void land_at(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__landat__object__scalar__ret__nothing, value0_, value1_);
        }

        std::string lb_data(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbdata__control__scalar__ret__string, value0_, value1_));
        }

        void lb_delete(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lbdelete__control__scalar__ret__nothing, value0_, value1_);
        }

        bool lb_is_selected(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbisselected__control__scalar__ret__bool, value0_, value1_));
        }

        std::string lb_picture(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpicture__control__scalar__ret__string, value0_, value1_));
        }

        std::string lb_picture_right(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpictureright__control__scalar__ret__string, value0_, value1_));
        }

        void lb_set_cur_sel(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcursel__control__scalar__ret__nothing, value0_, value1_);
        }

        std::string lb_text(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtext__control__scalar__ret__string, value0_, value1_));
        }

        std::string lb_text_right(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtextright__control__scalar__ret__string, value0_, value1_));
        }

        float lb_value(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbvalue__control__scalar__ret__scalar, value0_, value1_));
        }

        void leave_vehicle(const object &value0_, const group &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__leavevehicle__group__object__ret__nothing, value0_, value1_);
        }

        void limit_speed(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__limitspeed__object__scalar__ret__nothing, value0_, value1_);
        }

        void link_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__linkitem__object__string__ret__nothing, value0_, value1_);
        }

        float lnb_add_column(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lnbaddcolumn__control__scalar__ret__scalar, value0_, value1_));
        }

        void lnb_delete_column(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lnbdeletecolumn__control__scalar__ret__nothing, value0_, value1_);
        }

        void lnb_delete_row(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lnbdeleterow__control__scalar__ret__nothing, value0_, value1_);
        }

        void lnb_set_cur_sel_row(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lnbsetcurselrow__control__scalar__ret__nothing, value0_, value1_);
        }

        bool load_identity(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__loadidentity__object__string__ret__bool, value0_, value1_));
        }

        bool load_status(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__loadstatus__object__string__ret__bool, value0_, value1_));
        }

        void lock(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lock__object__bool__ret__nothing, value0_, value1_);
        }

        void lock(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lock__object__scalar__ret__nothing, value0_, value1_);
        }

        void lock_cargo(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lockcargo__object__bool__ret__nothing, value0_, value1_);
        }

        void lock_driver(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__lockdriver__object__bool__ret__nothing, value0_, value1_);
        }

        bool locked_cargo(const object &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lockedcargo__object__scalar__ret__bool, value0_, value1_));
        }

        void map_center_on_camera(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__mapcenteroncamera__control__bool__ret__nothing, value0_, value1_);
        }

        bool mine_detected_by(const object &value0_, const side &value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__minedetectedby__object__side__ret__bool, value0_, value1_));
        }

        void move_object_to_end(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__moveobjecttoend__control__string__ret__nothing, value0_, value1_);
        }

        void play_action(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__playaction__object__string__ret__nothing, value0_, value1_);
        }

        void play_action_now(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__playactionnow__object__string__ret__nothing, value0_, value1_);
        }

        void play_gesture(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__playgesture__object__string__ret__nothing, value0_, value1_);
        }

        void play_move(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__playmove__object__string__ret__nothing, value0_, value1_);
        }

        void play_move_now(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__playmovenow__object__string__ret__nothing, value0_, value1_);
        }

        void pp_effect_commit(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectcommit__string__scalar__ret__nothing, value0_, value1_);
        }

        void pp_effect_enable(bool value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectenable__string__bool__ret__nothing, value0_, value1_);
        }

        void pp_effect_enable(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectenable__scalar__bool__ret__nothing, value0_, value1_);
        }

        void pp_effect_force_in_nvg(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectforceinnvg__scalar__bool__ret__nothing, value0_, value1_);
        }

        void progress_set_position(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__progresssetposition__control__scalar__ret__nothing, value0_, value1_);
        }

        void public_variable_client(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__publicvariableclient__scalar__string__ret__nothing, value0_, value1_);
        }

        void radio_channel_set_call_sign(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__radiochannelsetcallsign__scalar__string__ret__nothing, value0_, value1_);
        }

        void radio_channel_set_label(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__radiochannelsetlabel__scalar__string__ret__nothing, value0_, value1_);
        }

        bool register_task(const team_member &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__registertask__team_member__string__ret__bool, value0_, value1_));
        }

        void remove_action(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeaction__object__scalar__ret__nothing, value0_, value1_);
        }

        void remove_all_event_handlers(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removealleventhandlers__object__string__ret__nothing, value0_, value1_);
        }

        void remove_all_mpevent_handlers(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeallmpeventhandlers__object__string__ret__nothing, value0_, value1_);
        }

        void remove_handgun_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removehandgunitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_backpack(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitemfrombackpack__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_uniform(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitemfromuniform__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_vest(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitemfromvest__object__string__ret__nothing, value0_, value1_);
        }

        void remove_items(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitems__object__string__ret__nothing, value0_, value1_);
        }

        void remove_magazine_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removemagazineglobal__object__string__ret__nothing, value0_, value1_);
        }

        void remove_magazines(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removemagazines__object__string__ret__nothing, value0_, value1_);
        }

        void remove_menu_item(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removemenuitem__control__scalar__ret__nothing, value0_, value1_);
        }

        void remove_menu_item(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removemenuitem__control__string__ret__nothing, value0_, value1_);
        }

        void remove_primary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeprimaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_secondary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removesecondaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_weapon(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeweapon__object__string__ret__nothing, value0_, value1_);
        }

        void remove_weapon_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeweaponglobal__object__string__ret__nothing, value0_, value1_);
        }

        void reveal_mine(const object &value0_, const side &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__revealmine__side__object__ret__nothing, value0_, value1_);
        }

        bool save_identity(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__saveidentity__object__string__ret__bool, value0_, value1_));
        }

        bool save_status(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__savestatus__object__string__ret__bool, value0_, value1_));
        }

        void select_diary_subject(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__selectdiarysubject__object__string__ret__nothing, value0_, value1_);
        }

        void select_weapon(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__selectweapon__object__string__ret__nothing, value0_, value1_);
        }

        void send_simple_command(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__sendsimplecommand__object__string__ret__nothing, value0_, value1_);
        }

        void set_actual_collective_rtd(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setactualcollectivertd__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_airport_side(float value0_, const side &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setairportside__scalar__side__ret__nothing, value0_, value1_);
        }

        void set_ammo_cargo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setammocargo__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_anim_speed_coef(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setanimspeedcoef__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_autonomous(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setautonomous__object__bool__ret__nothing, value0_, value1_);
        }

        void set_bleeding_remaining(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setbleedingremaining__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_cam_use_ti(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcamuseti__bool__scalar__ret__nothing, value0_, value1_);
        }

        void set_camera_interest(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcamerainterest__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_collision_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcollisionlight__object__bool__ret__nothing, value0_, value1_);
        }

        void set_combat_mode(const team_member &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcombatmode__team_member__string__ret__nothing, value0_, value1_);
        }

        void set_custom_aim_coef(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcustomaimcoef__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_custom_weight_rtd(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcustomweightrtd__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_damage(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setdamage__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_dammage(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setdammage__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_dir(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setdir__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_drop_interval(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setdropinterval__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_editor_mode(const control &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__seteditormode__control__string__ret__nothing, value0_, value1_);
        }

        void set_face(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setface__object__string__ret__nothing, value0_, value1_);
        }

        void set_faceanimation(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setfaceanimation__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_fatigue(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setfatigue__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_flag_side(const object &value0_, const side &value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setflagside__object__side__ret__nothing, value0_, value1_);
        }

        void set_flag_texture(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setflagtexture__object__string__ret__nothing, value0_, value1_);
        }

        void set_formation(const team_member &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setformation__team_member__string__ret__nothing, value0_, value1_);
        }

        void set_formation_task(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setformationtask__object__string__ret__nothing, value0_, value1_);
        }

        void set_from_editor(const team_member &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setfromeditor__team_member__bool__ret__nothing, value0_, value1_);
        }

        void set_fuel(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setfuel__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_fuel_cargo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setfuelcargo__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_identity(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setidentity__object__string__ret__nothing, value0_, value1_);
        }

        void set_light_brightness(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setlightbrightness__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_day_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setlightdaylight__object__bool__ret__nothing, value0_, value1_);
        }

        void set_light_flare_max_distance(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setlightflaremaxdistance__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_flare_size(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setlightflaresize__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_intensity(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setlightintensity__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_use_flare(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setlightuseflare__object__bool__ret__nothing, value0_, value1_);
        }

        void set_mimic(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmimic__object__string__ret__nothing, value0_, value1_);
        }

        void set_name(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setname__object__string__ret__nothing, value0_, value1_);
        }

        void set_name_sound(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setnamesound__object__string__ret__nothing, value0_, value1_);
        }

        bool set_owner(const object &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__setowner__object__scalar__ret__bool, value0_, value1_));
        }

        void set_oxygen_remaining(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setoxygenremaining__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_particle_class(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setparticleclass__object__string__ret__nothing, value0_, value1_);
        }

        void set_pilot_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setpilotlight__object__bool__ret__nothing, value0_, value1_);
        }

        void set_pitch(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setpitch__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_radio_msg(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setradiomsg__scalar__string__ret__nothing, value0_, value1_);
        }

        void set_random_lip(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setrandomlip__object__bool__ret__nothing, value0_, value1_);
        }

        void set_rank(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setrank__object__string__ret__nothing, value0_, value1_);
        }

        void set_repair_cargo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setrepaircargo__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_rotor_brake_rtd(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setrotorbrakertd__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_skill(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setskill__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_speaker(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setspeaker__object__string__ret__nothing, value0_, value1_);
        }

        void set_stamina(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setstamina__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_suppression(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setsuppression__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_target_age(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__settargetage__object__string__ret__nothing, value0_, value1_);
        }

        void set_trigger_text(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__settriggertext__object__string__ret__nothing, value0_, value1_);
        }

        void set_trigger_type(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__settriggertype__object__string__ret__nothing, value0_, value1_);
        }

        void set_unconscious(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setunconscious__object__bool__ret__nothing, value0_, value1_);
        }

        void set_unit_ability(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setunitability__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_unit_pos(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setunitpos__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_pos_weak(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setunitposweak__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_rank(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setunitrank__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_recoil_coefficient(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setunitrecoilcoefficient__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_ammo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setvehicleammo__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_ammo_def(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setvehicleammodef__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_armor(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setvehiclearmor__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_id(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setvehicleid__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_lock(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setvehiclelock__object__string__ret__nothing, value0_, value1_);
        }

        void set_vehicle_var_name(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setvehiclevarname__object__string__ret__nothing, value0_, value1_);
        }

        void show3dicons(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__show3dicons__control__bool__ret__nothing, value0_, value1_);
        }

        void show_legend(const control &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__showlegend__control__bool__ret__nothing, value0_, value1_);
        }

        float skill(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__skill__object__string__ret__scalar, value0_, value1_));
        }

        float skill_final(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__skillfinal__object__string__ret__scalar, value0_, value1_));
        }

        void slider_set_position(float value0_, float value1_) {
            game_value args(std::vector<game_value>{
                value0_,
                value1_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__slidersetposition__array__ret__nothing, args);
        }

        void slider_set_position(const control &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__slidersetposition__control__scalar__ret__nothing, value0_, value1_);
        }

        void stop(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__stop__object__bool__ret__nothing, value0_, value1_);
        }

        void suppress_for(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__suppressfor__object__scalar__ret__nothing, value0_, value1_);
        }

        void switch_action(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__switchaction__object__string__ret__nothing, value0_, value1_);
        }

        void switch_camera(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__switchcamera__object__string__ret__nothing, value0_, value1_);
        }

        void switch_gesture(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__switchgesture__object__string__ret__nothing, value0_, value1_);
        }

        void switch_light(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__switchlight__object__string__ret__nothing, value0_, value1_);
        }

        void switch_move(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__switchmove__object__string__ret__nothing, value0_, value1_);
        }

        void trigger_attach_object(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__triggerattachobject__object__scalar__ret__nothing, value0_, value1_);
        }

        std::string tv_tooltip(const control &value0_, float value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvtooltip__control__scalar__ret__string, value0_, value1_));
        }

        void unassign_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__unassignitem__object__string__ret__nothing, value0_, value1_);
        }

        void unlink_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__unlinkitem__object__string__ret__nothing, value0_, value1_);
        }

        bool unregister_task(const team_member &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__unregistertask__team_member__string__ret__bool, value0_, value1_));
        }

        void use_audio_time_for_moves(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__useaudiotimeformoves__object__bool__ret__nothing, value0_, value1_);
        }

        void vehicle_radio(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__vehicleradio__object__string__ret__nothing, value0_, value1_);
        }

        side create_center(const side &value_) {
            return side(host::functions.invoke_raw_unary(client::__sqf::unary__createcenter__side__ret__side, value_));
        }

        void delete_center(const side &value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__deletecenter__side__ret__nothing, value_);
        }

        void delete_team(const team_member &value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__deleteteam__team_member__ret__nothing, value_);
        }

        void do3denaction(const std::string& value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__do3denaction__string__ret__nothing, value_);
        }

        display find_display(float value_) {
            return display(host::functions.invoke_raw_unary(client::__sqf::unary__finddisplay__scalar__ret__display, value_));
        }

        side flag_side(const object &value_) {
            return side(host::functions.invoke_raw_unary(client::__sqf::unary__flagside__object__ret__side, value_));
        }

        std::string formation(const team_member &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__formation__team_member__ret__string, value_));
        }

        bool from_editor(const team_member &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__fromeditor__team_member__ret__bool, value_));
        }

        void get3dengrid(const std::string& value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__get3dengrid__string__ret__nothing, value_);
        }

        object get_editor_camera(const control &value_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__geteditorcamera__control__ret__object, value_));
        }

        object hc_leader(const group &value_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__hcleader__group__ret__object, value_));
        }

        std::string image(const std::string& value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__image__string__ret__text, value_));
        }

        bool is_agent(const team_member &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__isagent__team_member__ret__bool, value_));
        }

        std::string key_image(float value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__keyimage__scalar__ret__text, value_));
        }

        std::string key_name(float value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__keyname__scalar__ret__string, value_));
        }

        team_member leader(const team_member &value_) {
            return team_member(host::functions.invoke_raw_unary(client::__sqf::unary__leader__team_member__ret__team_member, value_));
        }

        std::string net_id(const group &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__netid__group__ret__string, value_));
        }

        object object_from_net_id(const std::string& value_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__objectfromnetid__string__ret__object, value_));
        }

        bool open_map(bool value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__openmap__bool__ret__bool, value_));
        }

        float parse_number(bool value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__parsenumber__bool__ret__scalar, value_));
        }

        std::string parse_text(const std::string& value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__parsetext__string__ret__text, value_));
        }

        float playable_slots_number(const side &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__playableslotsnumber__side__ret__scalar, value_));
        }

        float players_number(const side &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__playersnumber__side__ret__scalar, value_));
        }

        float score_side(const side &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__scoreside__side__ret__scalar, value_));
        }

        bool show_subtitles(bool value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__showsubtitles__bool__ret__bool, value_));
        }

        std::string team_name(const team_member &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__teamname__team_member__ret__string, value_));
        }

        std::string team_type(const team_member &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__teamtype__team_member__ret__string, value_));
        }

        float waypoint_timeout_current(const group &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointtimeoutcurrent__group__ret__scalar, value_));
        }

        float radio_volume() {
            return game_value(host::functions.invoke_raw_nular(client::__sqf::nular__radiovolume__ret__scalar));
        }

        void save_game() {
            host::functions.invoke_raw_nular(client::__sqf::nular__savegame__ret__nothing);
        }

        void save_joysticks() {
            host::functions.invoke_raw_nular(client::__sqf::nular__savejoysticks__ret__nothing);
        }

        side side_enemy() {
            return side(host::functions.invoke_raw_nular(client::__sqf::nular__sideenemy__ret__side));
        }

        side side_friendly() {
            return side(host::functions.invoke_raw_nular(client::__sqf::nular__sidefriendly__ret__side));
        }

        side side_logic() {
            return side(host::functions.invoke_raw_nular(client::__sqf::nular__sidelogic__ret__side));
        }

        side side_unknown() {
            return side(host::functions.invoke_raw_nular(client::__sqf::nular__sideunknown__ret__side));
        }

        team_member team_member_null() {
            game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__teammembernull__ret__team_member);
            return team_member(host::functions.invoke_raw_nular(client::__sqf::nular__teammembernull__ret__team_member));
        }

        side west() {
            return side(host::functions.invoke_raw_nular(client::__sqf::nular__west__ret__side));
        }

        bool buldozer_is_enabled_road_diag() {
            return game_value(host::functions.invoke_raw_nular(client::__sqf::nular__buldozer_isenabledroaddiag__ret__bool));
        }

        void buldozer_reload_oper_map() {
            host::functions.invoke_raw_nular(client::__sqf::nular__buldozer_reloadopermap__ret__nothing);
        }

        void cancel_simple_task_destination(task value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__cancelsimpletaskdestination__task__ret__nothing, value_);
        }

        task current_task(const object &value_) {
            return task(host::functions.invoke_raw_unary(client::__sqf::unary__currenttask__object__ret__task, value_));
        }

        script exec_vm(const std::string& value_) {
            return script(host::functions.invoke_raw_unary(client::__sqf::unary__execvm__string__ret__script, value_));
        }

        float priority(task value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__priority__task__ret__scalar, value_));
        }

        bool script_done(script value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__scriptdone__script__ret__bool, value_));
        }

        bool task_completed(task value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__taskcompleted__task__ret__bool, value_));
        }

        task task_parent(task value_) {
            return task(host::functions.invoke_raw_unary(client::__sqf::unary__taskparent__task__ret__task, value_));
        }

        std::string task_state(task value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__taskstate__task__ret__string, value_));
        }

        void terminate(script value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__terminate__script__ret__nothing, value_);
        }

        std::string type(task value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__type__task__ret__string, value_));
        }

        /* Multiplayer */
                bool local(const object &value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__local__object__ret__bool, value_);
        }

        bool local(const group &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__local__group__ret__bool, value_));
        }

        bool is_server() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isserver__ret__bool);
        }

        bool is_multiplayer() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__ismultiplayer__ret__bool);
        }

        bool is_dedicated() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isdedicated__ret__bool);
        }

        bool did_jip() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__didjip__ret__bool);
        }

        /* Position */
        namespace __helpers {
            vector3 get_pos_obj(unary_function fnc_, const object & obj_)
            {
                return game_value(host::functions.invoke_raw_unary(fnc_, obj_));
            }
            vector3 get_pos_loc(unary_function fnc_, const location & loc_)
            {
                return game_value(host::functions.invoke_raw_unary(fnc_, loc_));
            }
        }

        vector3 get_pos(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__getpos__object__ret__array, obj_);
        }

        vector3 get_pos(const location & loc_)
        {
            return __helpers::get_pos_loc(__sqf::unary__getpos__location__ret__array, loc_);
        }

        vector3 get_pos_asl(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__getposasl__object__ret__array, obj_);
        }

        vector3 get_pos_atl(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__getposatl__object__ret__array, obj_);
        }

        vector3 get_pos_aslw(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__getposaslw__object__ret__array, obj_);
        }

        vector3 visible_position(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__visibleposition__object__ret__array, obj_);
        }

        vector3 visible_position_asl(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__visiblepositionasl__object__ret__array, obj_);
        }

        vector3 position(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__position__object__ret__array, obj_);
        }

        vector3 get_pos_visual(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__getposvisual__object__ret__array, obj_);
        }
        vector3 get_pos_asl_visual(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__getposaslvisual__object__ret__array, obj_);
        }

        vector3 get_pos_atl_visual(const object & obj_)
        {
            return __helpers::get_pos_obj(__sqf::unary__getposatlvisual__object__ret__array, obj_);
        }

        vector3 aim_pos(const object & obj_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__aimpos__object__ret__array, obj_));
        }

        void set_pos(const object & obj_, const vector3 & pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__setpos__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_asl(const object & obj_, const vector3 & pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__setposasl__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_asl2(const object & obj_, const vector3 & pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__setposasl2__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_aslw(const object & obj_, const vector3 & pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__setposaslw__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_atl(const object & obj_, const vector3 & pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__setposatl__object__array__ret__nothing, obj_, pos_);
        }

        vector3 agl_to_asl(const vector3 & agl_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__agltoasl__array__ret__array, agl_));
        }

        vector3 asl_to_agl(const vector3 & asl_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__asltoagl__array__ret__array, asl_));
        }

        vector3 atl_to_asl(const vector3 & atl_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__atltoasl__array__ret__array, atl_));
        }
        vector3 asl_to_atl(const vector3 & asl_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__asltoatl__array__ret__array, asl_));
        }

        /* Waypoint */
                object waypoint_attached_object(waypoint &wp_)
        {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__waypointattachedobject__array__ret__object, wp_.__to_gv()));
        }

        object waypoint_attached_vehicle(waypoint & wp_)
        {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__waypointattachedvehicle__array__ret__object, wp_.__to_gv()));
        }

        waypoint::behaviour waypoint_behaviour(waypoint & wp_)
        {
            return waypoint::__parse_behaviour(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointbehaviour__array__ret__string, wp_.__to_gv())));
        }

        waypoint::combat_mode waypoint_combat_mode(waypoint & wp_)
        {
            return waypoint::__parse_combat_mode(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointcombatmode__array__ret__string, wp_.__to_gv())));
        }

        float waypoint_completeion_radius(waypoint & wp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointcompletionradius__array__ret__scalar, wp_.__to_gv()));
        }

        std::string waypoint_description(waypoint & wp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointdescription__array__ret__string, wp_.__to_gv()));
        }

        waypoint::formation waypoint_formation(waypoint & wp_)
        {
            return waypoint::__parse_formation( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointformation__array__ret__string, wp_.__to_gv())) );
        }

        float waypoint_house_position(waypoint & wp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointhouseposition__array__ret__scalar, wp_.__to_gv()));
        }

        float waypoint_loiter_radius(waypoint & wp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointloiterradius__array__ret__scalar, wp_.__to_gv()));
        }

        waypoint::loiter_type waypoint_loiter_type(waypoint & wp_)
        {
            return waypoint::__parse_loiter_type(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointloitertype__array__ret__string, wp_.__to_gv())));
        }

        std::string waypoint_name(waypoint & wp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointname__array__ret__string, wp_.__to_gv()));
        }
        vector3 waypoint_position(waypoint & wp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointposition__array__ret__array, wp_.__to_gv()));
        }
        std::vector<waypoint> waypoints(group & gp_)
        {
            // TODO return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypoints__object_group__ret__array, gp_));
            throw 713;
        }
        std::string waypoint_script(waypoint & wp_)
        {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointscript__array__ret__string, wp_.__to_gv()));
        }
        waypoint::show waypoint_show(waypoint & wp_)
        {
            return waypoint::__parse_show( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointshow__array__ret__string, wp_.__to_gv())) );
        }
        waypoint::speed waypoint_speed(waypoint & wp_)
        {
            return waypoint::__parse_speed( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointspeed__array__ret__string, wp_.__to_gv())) );
        }
        waypoint::type waypoint_type(waypoint & wp_)
        {
            return waypoint::__parse_type( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointtype__array__ret__string, wp_.__to_gv())) );
        }
        bool waypoint_visible(waypoint & wp_)
        {
            // TODO THIS CAN RETURN 0, CHECK FOR 0 AND RETURN FALSE.
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointvisible__array__ret__scalar, wp_.__to_gv()));
        }

        bool waypoint_exists(waypoint & wp_)
        {
            // TODO THIS CAN RETURN 0, CHECK FOR 0 AND RETURN FALSE.
            //if (game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointvisible__array__ret__scalar, wp_.__to_gv())).type == "number") return false;
            throw 713;
        }

        waypoint add_waypoint(group& gp_, const vector3& center_, float radius_, int index_, const std::string& name_)
        {
            game_value args({
                center_,
                radius_,
                (float)index_,
                name_
            });

            return waypoint(game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
        }

        waypoint add_waypoint(group & gp_, const object & center_, float radius_, int index_, const std::string & name_)
        {
            game_value args({
                center_,
                radius_,
                (float)index_,
                name_
            });

            return waypoint(game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
        }

        void delete_waypoint(waypoint & wp_)
        {
            host::functions.invoke_raw_unary(client::__sqf::unary__deletewaypoint__array__ret__nothing, wp_.__to_gv());
        }

        void copy_waypoints(group & to_, group & from_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__copywaypoints__group__group__ret__nothing, to_, from_);
        }

        std::vector<waypoint> synchronized_waypoints(waypoint & wp_)
        {
            game_value rv_ret_vals(host::functions.invoke_raw_unary(client::__sqf::unary__synchronizedwaypoints__array__ret__array, wp_.__to_gv()));

            // TODO test for logic.
            std::vector<waypoint> waypoints;
            for (uint32_t i = 0; i < rv_ret_vals.length() - 1; i++)
                waypoints.push_back(waypoint(rv_ret_vals[i]));

            return waypoints;
        }
        std::vector<waypoint> synchronized_waypoints(object & obj_)
        {
            game_value rv_ret_vals(host::functions.invoke_raw_unary(client::__sqf::unary__synchronizedwaypoints__object__ret__array, obj_));

            // TODO test for logic.
            std::vector<waypoint> waypoints;
            for (uint32_t i = 0; i < rv_ret_vals.length() - 1; i++)
                waypoints.push_back(waypoint(rv_ret_vals[i]));

            return waypoints;
        }

        void set_current_waypoint(group & gp_, waypoint & wp_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcurrentwaypoint__group__array__ret__nothing, gp_, wp_.__to_gv());
        }

        void set_waypoint_behaviour(waypoint & wp_, waypoint::behaviour mode_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointbehaviour__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_combat_mode(waypoint & wp_, waypoint::combat_mode mode_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointcombatmode__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_completion_radius(waypoint & wp_, float radius_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointcompletionradius__array__scalar__ret__nothing, wp_.__to_gv(), radius_);
        }
        void set_waypoint_description(waypoint & wp_, std::string text_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointdescription__array__string__ret__nothing, wp_.__to_gv(), text_);
        }
        void set_waypoint_formation(waypoint & wp_, waypoint::formation formation_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointformation__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(formation_));
        }
        void set_waypoint_house_position(waypoint & wp_, float house_pos_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointhouseposition__array__scalar__ret__nothing, wp_.__to_gv(), house_pos_);
        }
        void set_waypoint_loiter_radius(waypoint & wp_, float radius_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointloiterradius__array__scalar__ret__nothing, wp_.__to_gv(), radius_);
        }
        void set_waypoint_loiter_type(waypoint & wp_, waypoint::loiter_type type_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointloitertype__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(type_));
        }
        void set_waypoint_name(waypoint & wp_, std::string name_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointname__array__string__ret__nothing, wp_.__to_gv(), name_);
        }
        void set_waypoint_position(waypoint & wp_, vector3 & pos_, float radius_)
        {
            game_value args({ pos_, radius_});
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointposition__array__array__ret__nothing, wp_.__to_gv(), args);
        }
        void set_waypoint_script(waypoint & wp_, std::string command_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointscript__array__string__ret__nothing, wp_.__to_gv(), command_);
        }
        void set_waypoint_speed(waypoint& wp_, waypoint::speed mode_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointspeed__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_statements(waypoint& wp_, std::string condition_, std::string statement_)
        {
            game_value args({ condition_, statement_ });
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointstatements__array__array__ret__nothing, wp_.__to_gv(), args);
        }
        void set_waypoint_timeout(waypoint& wp_, float min_, float mid_, float max_)
        {
            game_value args({ std::vector<game_value> { min_, mid_, max_ } });
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointtimeout__array__array__ret__nothing, wp_.__to_gv(), args);
        }
        void set_waypoint_type(waypoint& wp_, waypoint::type type_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointtype__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(type_));
        }
        void set_waypoint_visible(waypoint& wp_, bool visibility_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointvisible__array__bool__ret__nothing, wp_.__to_gv(), visibility_);
        }

        void show_waypoint(waypoint& wp_, std::string show_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__showwaypoint__array__string__ret__nothing, wp_.__to_gv(), show_);
        }

        void synchronize_waypoint(waypoint& wp_, std::vector<waypoint> others_)
        {
            std::vector<game_value> waypoints;
            for (auto it : others_)
                waypoints.push_back(it.__to_gv());

            host::functions.invoke_raw_binary(client::__sqf::binary__synchronizewaypoint__array__array__ret__nothing, wp_.__to_gv(), waypoints);
        }
        void synchronize_waypoint(object& trigger_, std::vector<waypoint> others_)
        {
            std::vector<game_value> waypoints;
            for (auto it : others_)
                waypoints.push_back(it.__to_gv());

            host::functions.invoke_raw_binary(client::__sqf::binary__synchronizewaypoint__object__array__ret__nothing, trigger_, waypoints);
        }

        void waypoint_attach_object(waypoint& wp_, int obj_id_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_.__to_gv(), (float)obj_id_);
        }

        void waypoint_attach_object(waypoint& wp_, object obj_)
        {
            host::functions.invoke_raw_binary(client::__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_.__to_gv(), obj_);
        }


        float current_waypoint(group gp_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__currentwaypoint__group__ret__scalar, gp_));
        }

        bool waypoints_enabled_uav(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__waypointsenableduav__object__ret__bool, value_);
        }

        void enable_uavwaypoints(bool value0_, object value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enableuavwaypoints__object__bool__ret__nothing, value0_, value1_);
        }

        /* World */
        float world_size() {
            return sqf::__helpers::__retrieve_nular_number(client::__sqf::nular__worldsize__ret__scalar);
        }

        std::string world_name()
        {
            return game_value(host::functions.invoke_raw_nular(client::__sqf::nular__worldname__ret__string));
        }

        float wind_str() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__windstr__ret__scalar);
        }

        float wind_dir() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__winddir__ret__scalar);
        }

        vector3 wind() {
            return __helpers::__retrieve_nular_vector3(client::__sqf::nular__wind__ret__array);
        }

        float waves() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__waves__ret__scalar);
        }

        float time() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__time__ret__scalar);
        }

        float time_multiplier() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__timemultiplier__ret__scalar);
        }

        float date_to_number(rv_date date_) {
            //game_value date_array({
            //    (date_.year),
            //    (date_.month),
            //    (date_.day),
            //    (date_.hour),
            //    (date_.minute)
            //})

            throw 713; // TODO reimplement day_to_number
        }

        std::vector<object> near_objects(const vector3 &pos_, const float &radius_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, pos_, radius_));
        }

        std::vector<object> near_objects(const object &object_, const float &radius_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, object_, radius_));
        }

        std::vector<object> near_objects(const vector3 &pos_, const std::string &type_, const float &radius_) {
            game_value args(std::vector<game_value>{
                type_,
                radius_
            });

            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, pos_, args));
        }

        std::vector<object> near_objects(const object &object_, const std::string &type_, const float &radius_) {
            game_value args(std::vector<game_value>{
                type_,
                radius_
            });

            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, object_, args));
        }

        void hint(const std::string &text_) {
            __helpers::__empty_unary_string(client::__sqf::unary__hint__text_string__ret__nothing, text_);
        }

        void hint_cadet(const std::string &text_) {
            __helpers::__empty_unary_string(client::__sqf::unary__hintcadet__text_string__ret__nothing, text_);
        }

        void hint_silent(const std::string &text_) {
            __helpers::__empty_unary_string(client::__sqf::unary__hintsilent__text_string__ret__nothing, text_);
        }

        float importance(const location &loc_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__importance__location__ret__scalar, loc_));
        }

        void set_importance(const location &loc_, const float &value_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setimportance__location__scalar__ret__nothing, loc_, value_);
        }

        std::string map_grid_position(const object &obj_) {
            return __helpers::__string_unary_object(client::__sqf::unary__mapgridposition__object_array__ret__string, obj_);
        }

        std::string map_grid_position(const vector2 &pos_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__mapgridposition__object_array__ret__string, pos_));
        }

        std::vector<object> roads_connected_to(const object &obj_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__roadsconnectedto__object__ret__array, obj_));
        }

        std::vector<object> rope_attached_objects(const object &obj_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__ropeattachedobjects__object__ret__array, obj_));
        }

        std::vector<object> ropes(const object &obj_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__ropes__object__ret__array, obj_));
        }

        vector3 screen_to_world(const vector2 &pos_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__screentoworld__array__ret__array, pos_));
        }

        vector2 size(const location &loc_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__size__location__ret__array, loc_));
        }

        vector2 slider_range(const float &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__sliderrange__scalar__ret__array, value_));
        }

        vector2 slider_range(const control &ctrl_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__sliderrange__control__ret__array, ctrl_));
        }

        void slider_set_range(float value0_, float value1_, float value2_) {
            game_value args(std::vector<game_value>{
                value0_,
                value1_,
                value2_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__slidersetrange__array__ret__nothing, args);
        }

        void slider_set_range(const control &value0_, float value1_, float value2_) {
            game_value args(std::vector<game_value>{
                value0_,
                value1_,
                value2_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__slidersetrange__array__ret__nothing, args);
        }

        vector2 slider_speed(const float &value_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__sliderspeed__scalar__ret__array, value_));
        }

        vector2 slider_speed(const control &ctrl_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__sliderspeed__control__ret__array, ctrl_));
        }

        void slider_set_speed(float value0_, float value1_, float value2_) {
            game_value args(std::vector<game_value>{
                value0_,
                value1_,
                value2_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__slidersetspeed__array__ret__nothing, args);
        }

        void slider_set_speed(const control &value0_, float value1_, float value2_) {
            game_value args(std::vector<game_value>{
                value0_,
                value1_,
                value2_
            });

            host::functions.invoke_raw_unary(client::__sqf::unary__slidersetspeed__array__ret__nothing, args);
        }

        std::string speed_mode(const object &obj_) {
            return __helpers::__string_unary_object(client::__sqf::unary__speedmode__object_group__ret__string, obj_);
        }

        std::string speed_mode(const group &grp_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__speedmode__object_group__ret__string, grp_));
        }

        game_value get_mission_config_value(const std::string& attribute_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__getmissionconfigvalue__any__ret__any, attribute_));
        }

        game_value get_mission_config_value(const std::string& attribute_, game_value default_value_) {
            game_value args(std::vector<game_value>{
                attribute_,
                    default_value_
            });
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__getmissionconfigvalue__any__ret__any, args));
        }

        void move(const object& unit_, const vector3& pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__move__object_group__array__ret__nothing, unit_, pos_);
        }

        void move(const group& group_, const vector3& pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__move__object_group__array__ret__nothing, group_, pos_);
        }

        bool move_in_any(const object& unit_, const object& vehicle_)
        {
            return game_value(host::functions.invoke_raw_binary(__sqf::binary__moveinany__object__object__ret__bool, unit_, vehicle_));
        }

        void move_in_cargo(const object& unit_, const object& vehicle_, int cargo_index_)
        {
            if (cargo_index_ == -1)
            {
                host::functions.invoke_raw_binary(__sqf::binary__moveincargo__object__object__ret__nothing, unit_, vehicle_);
            }
            else
            {
                game_value params(std::vector<game_value> {
                    vehicle_,
                    (float)cargo_index_
                });

                host::functions.invoke_raw_binary(__sqf::binary__moveincargo__object__array__ret__nothing, unit_, params);
            }
        }

        void move_in_commander(const object& unit_, const object& vehicle_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__moveincommander__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_driver(const object& unit_, const object& vehicle_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__moveindriver__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_gunner(const object &unit_, const object &vehicle_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__moveingunner__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_turret(const object& unit_, const object& vehicle_, const std::vector<int> turret_path_)
        {
            std::vector<game_value> path;
            for (int item : turret_path_)
                path.push_back(game_value((float)item));

            game_value params(std::vector<game_value> {
                vehicle_,
                path
            });

            host::functions.invoke_raw_binary(__sqf::binary__moveinturret__object__array__ret__nothing, unit_, params);
        }

        void move_to(const object& unit_, const vector3& pos_)
        {
            host::functions.invoke_raw_binary(__sqf::binary__moveto__object__array__ret__nothing, unit_, pos_);
        }

        rv_date date() {
            return rv_date::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__date__ret__array)));
        }

        rv_fog_parameters fog_params() {
            return rv_fog_parameters::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__fogparams__ret__array)));
        }

        rv_rendering_distances get_object_view_distance() {
            return rv_rendering_distances::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__getobjectviewdistance__ret__array)));
        }

        rv_resolution get_resolution() {
            return rv_resolution::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__getresolution__ret__array)));
        }

        rv_date mission_start() {
            return rv_date::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__missionstart__ret__array)));
        }

        std::vector<object> vehicles() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__vehicles__ret__array));
        }

        int tv_add(const control& ctrl_, const std::vector<int>& path_, const std::string& text_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                text_
            });

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvadd__control__array__ret__scalar, ctrl_, params));
        }

        void tv_collapse(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            host::functions.invoke_raw_binary(client::__sqf::binary__tvcollapse__control__array__ret__nothing, ctrl_, path);
        }

        int tv_count(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvcount__control__array__ret__scalar, ctrl_, path));
        }

        std::string tv_data(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvdata__control__array__ret__string, ctrl_, path));
        }

        void tv_delete(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            host::functions.invoke_raw_binary(client::__sqf::binary__tvdelete__control__array__ret__nothing, ctrl_, path);
        }

        void tv_expand(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            host::functions.invoke_raw_binary(client::__sqf::binary__tvexpand__control__array__ret__nothing, ctrl_, path);
        }

        std::string tv_picture(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvpicture__control__array__ret__string, ctrl_, path));
        }

        std::string tv_picture_right(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvpictureright__control__array__ret__string, ctrl_, path));
        }

        void tv_set_cur_sel(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsetcursel__control__array__ret__nothing, ctrl_, path);
        }

        void tv_set_data(const control& ctrl_, const std::vector<int>& path_, const std::string& data_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                data_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsetdata__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture(const control& ctrl_, const std::vector<int>& path_, const std::string& name_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                name_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsetpicture__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture_right(const control& ctrl_, const std::vector<int>& path_, const std::string& name_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                name_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsetpictureright__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture_color(const control& ctrl_, const std::vector<int>& path_, const rv_color& color_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsetpicturecolor__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_picture_color_right(const control& ctrl_, const std::vector<int>& path_, const rv_color& color_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                color_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsetpicturecolorright__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_tooltip(const control& ctrl_, const std::vector<int>& path_, const std::string& text_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                text_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsettooltip__control__array__ret__nothing, ctrl_, params);
        }

        void tv_set_value(const control& ctrl_, const std::vector<int>& path_, float value_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                value_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsetvalue__control__array__ret__nothing, ctrl_, params);
        }

        void tv_sort(const control& ctrl_, const std::vector<int>& path_, bool reversed_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                reversed_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsort__control__array__ret__nothing, ctrl_, params);
        }

        void tv_sort_by_value(const control& ctrl_, const std::vector<int>& path_, bool reversed_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            game_value params({
                path,
                reversed_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__tvsortbyvalue__control__array__ret__nothing, ctrl_, params);
        }

        std::string tv_text(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvtext__control__array__ret__string, ctrl_, path));
        }

        float tv_value(const control& ctrl_, const std::vector<int>& path_) {
            std::vector<game_value> path;
            for (int item : path_) {
                path.push_back(game_value((float)item));
            }

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__tvvalue__control__array__ret__scalar, ctrl_, path));
        }

        vector3 eye_pos(const object &object_) {
            return vector3(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__eyepos__object__ret__array, object_)));
        }

        rv_eden_mouse_over get_eden_mouse_over() {
            return rv_eden_mouse_over(host::functions.invoke_raw_nular(client::__sqf::nular__get3denmouseover__ret__array));
        }

        rv_artillery_computer_settings get_artillery_computer_settings() {
            return rv_artillery_computer_settings(host::functions.invoke_raw_nular(client::__sqf::nular__getartillerycomputersettings__ret__array));
        }

        rv_product_version product_version() {
            return rv_product_version(host::functions.invoke_raw_nular(client::__sqf::nular__productversion__ret__array));
        }
    }
}
