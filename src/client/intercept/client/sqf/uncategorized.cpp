﻿#include "uncategorized.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include "position.hpp" //for uses of get_pos_obj. Should be removed once they are sorted

using namespace intercept::types;

namespace intercept {
    namespace sqf {



        /////////////////////// DO NOT IMPLEMENT THESE FUNCTIONS /////////////////////////
        ///////// They are haram. Discuss on slack prior to removing from list. //////////
        // unary__abs__scalar_nan__ret__scalar_nan
        // unary__acos__scalar_nan__ret__scalar_nan
        // unary__asin__scalar_nan__ret__scalar_nan
        // unary__atan__scalar_nan__ret__scalar_nan
        // unary__atg__scalar_nan__ret__scalar_nan
        // unary__assert__bool__ret__bool
        // unary__breakout__string__ret__nothing
        // unary__breakto__string__ret__nothing
        // unary__case__any__ret__switch
        // unary__comment__string__ret__nothing
        // unary__compilefinal__string__ret__code
        // unary__count__array__ret__scalar
        // unary__count__string__ret__scalar
        // unary__ceil__scalar_nan__ret__scalar_nan
        // unary__cos__scalar_nan__ret__scalar_nan
        // unary__debuglog__any__ret__nothing
        // unary__default__code__ret__nothing
        // unary__deg__scalar_nan__ret__scalar_nan
        // unary__exp__scalar_nan__ret__scalar_nan
        // unary__floor__scalar_nan__ret__scalar_nan
        // unary__for__string__ret__for
        // unary__for__array__ret__for
        // unary__format__array__ret__string
        // unary__formattext__array__ret__text
        // unary__goto__string__ret__nothing
        // unary__if__bool__ret__if
        // unary__isnil__code_string__ret__bool
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
        // unary__text__string__ret__text
        // unary__textlog__any__ret__nothing
        // unary__textlogformat__array__ret__nothing
        // unary__tg__scalar_nan__ret__scalar_nan
        // unary__throw__any__ret__nothing
        // unary__toarray__string__ret__array
        // unary__tostring__array__ret__string
        // unary__try__code__ret__exception
        // unary__typename__any__ret__string
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
        // unary__isnull__netobject__ret__bool


        /// INVESTIGATE
        /* No documentation. */
        // binary_dynamicsimulationdistancecoef__string__scalar__ret__nothing

        /* No documentation.*/
        // unary__addforcegeneratorrtd__array__ret__scalar

        /* No documentation.*/
        // nular__airdensitycurvertd__ret__array

        /* No documentation.*/
        // unary__ctrlangle__control__ret__array

        /* No documentation for return array elements. */
        // unary__ctrlmapmouseover__control__ret__array
        // unary__curatorcameraarea__object__ret__array
        // unary__curatoreditingarea__object__ret__array

        /* No documentation.*/
        // unary__enableaudiofeature__array__ret__bool

        /* No documentation.*/
        // nular__getdlcassetsusage__ret__array

        /* No documentation.*/
        // nular__getmissiondlcs__ret__array

        /* No documentation.*/
        // nular__getmouseposition__ret__array

        /* No documentation.*/
        // unary__getpersonuseddlcs__object__ret__array
        // unary__getplayerscores__object__ret__array

        /* Last parameter can be position (x, y, z) or target, unknown what target is.*/
        // nular__hudmovementlevels__ret__array

        /* No documentation for type Team.*/
        // nular__teams__ret__array

        /* No documentation.*/
        // nular__windrtd__ret__array

        /* No documentation.*/
        // unary__resources__team_member__ret__array

        /* These functions apparently send arbatary messages across the network. They are apparently inactive.*/
        // unary__sendaumessage__array__ret__nothing
        // unary__sendudpmessage__array__ret__bool

        /* This function does _something_ to a listbox. No documentation.*/
        // binary__lbsettextright__control__array__ret__nothing

        /* This function is apparently depreciated but the functionality is different to the command which replaces it.*/
        // unary__lbselection__control__ret__array

        /* This undocumented function has the potential to be useful, my guess is it returns a float between 1 and 0 which
            corresponds to how visible a particular unit is from another unit. binary__knowsabout__object_group__object__ret__scalar*/
        // binary__checkvisibility__array__array__ret__scalar

        /* No documentation.*/
        // binary__ctrlsetangle__control__array__ret__nothing

        /* No documentation.*/
        // binary__ctrlsettextcolorsecondary__control__array__ret__nothing

        /* Poor documentation.*/
        // binary__backpackspacefor__object__string__ret__array

        /* No documentation for unary calls. If these are consistent with the other tv_* fuctions, they should take int idc_ as the first argument instead of ctrl and pass it as: ({idc_, ...}) */
        // unary__tvsort__array__ret__nothing
        // unary__tvsortbyvalue__array__ret__nothing

        /* No documentation but implemented (?) */
        // binary__tvtooltip__control__scalar__ret__string

        /* No documentation.*/
        // unary__tvtooltip__array__ret__string

        /* No documentation for this entire family of commands.*/
        // binary__menuaction__control__array__ret__string
        // binary__menuadd__control__array__ret__scalar
        // binary__menuchecked__control__array__ret__bool
        // binary__menucollapse__control__array__ret__nothing
        // binary__menudata__control__array__ret__string
        // binary__menudelete__control__array__ret__nothing
        // binary__menuenable__control__array__ret__nothing
        // binary__menuenabled__control__array__ret__bool
        // binary__menuexpand__control__array__ret__nothing
        // binary__menupicture__control__array__ret__string
        // binary__menusetaction__control__array__ret__nothing
        // binary__menusetcheck__control__array__ret__nothing
        // binary__menusetdata__control__array__ret__nothing
        // binary__menusetpicture__control__array__ret__nothing
        // binary__menusetvalue__control__array__ret__nothing
        // binary__menushortcut__control__array__ret__scalar
        // binary__menushortcuttext__control__array__ret__string
        // binary__menusize__control__array__ret__scalar
        // binary__menusort__control__array__ret__nothing
        // binary__menutext__control__array__ret__string
        // binary__menuurl__control__array__ret__string
        // binary__menuvalue__control__array__ret__scalar
        // unary__menuaction__array__ret__string
        // unary__menuadd__array__ret__scalar
        // unary__menuchecked__array__ret__bool
        // unary__menuclear__control__ret__nothing
        // unary__menuclear__scalar__ret__nothing
        // unary__menucollapse__array__ret__nothing
        // unary__menudata__array__ret__string
        // unary__menudelete__array__ret__nothing
        // unary__menuenable__array__ret__nothing
        // unary__menuenabled__array__ret__bool
        // unary__menuexpand__array__ret__nothing
        // unary__menuhover__control__ret__array
        // unary__menuhover__scalar__ret__array
        // unary__menupicture__array__ret__string
        // unary__menusetaction__array__ret__nothing
        // unary__menusetcheck__array__ret__nothing
        // unary__menusetdata__array__ret__nothing
        // unary__menusetpicture__array__ret__nothing
        // unary__menusetvalue__array__ret__nothing
        // unary__menushortcut__array__ret__scalar
        // unary__menushortcuttext__array__ret__string
        // unary__menusize__array__ret__scalar
        // unary__menusort__array__ret__nothing
        // unary__menutext__array__ret__string
        // unary__menuurl__array__ret__string
        // unary__menuvalue__array__ret__scalar

        /* No documentation.*/
        // unary__leaderboardgetrows__string__ret__array
        // unary__leaderboardrequestrowsglobal__array__ret__bool
        // unary__leaderboardrequestrowsglobalarounduser__array__ret__bool
        // unary__leaderboardsrequestuploadscore__array__ret__bool
        // unary__leaderboardsrequestuploadscorekeepbest__array__ret__bool

        /* No documentation.*/
        // unary__enginespowerrtd__object__ret__array
        // unary__forceatpositionrtd__array__ret__array
        // unary__forcegeneratorrtd__scalar__ret__array
        // unary__gettrimoffsetrtd__object__ret__array
        // unary__isautostartupenabledrtd__object__ret__array
        // binary__setforcegeneratorrtd__scalar__array__ret__nothing
        // binary__setwingforcescalertd__object__array__ret__nothing

        /* No documentation.*/
        // unary__setwinddir__array__ret__nothing

        /* No documentation.*/
        // nular__missionversion__ret__scalar
        // unary__weaponinertia__object__ret__array
        // unary__animationnames__object__ret__array
        // unary__animationselectionnames__object__ret__array
        // unary__call__code__ret__any
        // unary__clear3deninventory__array__ret__nothing
        // unary__tvpictureright__array__ret__string
        // unary__createobject__array__ret__object
        // unary__getdlcassetsusagebyname__string__ret__array
        // unary__getenginetargetrpmrtd__object__ret__array
        // unary__getfieldmanualstartpage__display__ret__array
        // unary__getunitloadout__object__ret__array
        // unary__getunitloadout__string__ret__array
        // unary__lbsettext__array__ret__string
        // unary__registerremoteexecfunc__string__ret__bool
        // unary__save3deninventory__array__ret__nothing
        // unary__set3denmodelsvisible__array__ret__nothing
        // unary__synchronizedtriggers__array__ret__array
        // binary__lnbcolorright__control__array__ret__array
        // unary__lnbcolorright__array__ret__array
        // unary__lnbpictureright__array__ret__string
        // binary__lnbpictureright__control__array__ret__string
        // unary__lnbsetcolorright__array__ret__nothing
        // binary__lnbsetcolorright__control__array__ret__nothing
        // unary__lnbsetpicturecolor__array__ret__nothing
        // binary__lnbsetpicturecolor__control__array__ret__nothing
        // unary__lnbsetpicturecolorright__array__ret__nothing
        // binary__lnbsetpicturecolorright__control__array__ret__nothing
        // unary__lnbsetpicturecolorselected__array__ret__nothing
        // binary__lnbsetpicturecolorselected__control__array__ret__nothing
        // unary__lnbsetpicturecolorselectedright__array__ret__nothing
        // binary__lnbsetpicturecolorselectedright__control__array__ret__nothing
        // unary__lnbsetpictureright__array__ret__nothing
        // binary__lnbsetpictureright__control__array__ret__nothing
        // unary__lnbsettextright__array__ret__nothing
        // binary__lnbsettextright__control__array__ret__nothing

        // unary__lnbsort__array__ret__nothing
        // binary__lnbsort__control__array__ret__nothing
        // unary__lnbsortbyvalue__array__ret__nothing
        // binary__lnbsortbyvalue__control__array__ret__nothing
        // unary__lnbtextright__array__ret__string
        // binary__lnbtextright__control__array__ret__string

        /* No documentation for return types. */
        // unary__getgroupicons__group__ret__array
        // unary__taskchildren__task__ret__array
        // unary__taskresult__task__ret__array
        // unary__triggeractivation__object__ret__array
        // unary__triggerstatements__object__ret__array
        // unary__waypointgetforcebehaviour__array__ret__string
        // unary__waypointstatements__array__ret__array
        // unary__waypointtimeout__array__ret__array

        /* Wrong documentation - seems to take Array instead of String. */
        // unary__lognetwork__array__ret__scalar

        /* Team Member things - apparently useless. */
        // unary__teammember__object__ret__team_member
        // binary__sendtask__team_member__array__ret__task 
        // binary__sendtaskresult__task__array__ret__nothing 



        /* deprecated?*/
        // binary__seteditorobjectscope__control__array__ret__nothing 
        // nular__benchmark__ret__scalar
        /////////////////////// DO NOT IMPLEMENT ABOVE FUNCTIONS /////////////////////////



        void draw_line_3d(const vector3 & pos1_, const vector3 & pos2_, const rv_color & color_) {
            game_value args({
                pos1_,
                pos2_,
                color_
            });
            host::functions.invoke_raw_unary(__sqf::unary__drawline3d__array__ret__nothing, args);
        }

        void draw_icon_3d(sqf_string_const_ref texture_, const rv_color & color_, const vector3 & pos_agl_, float width_, float height_, float angle_, sqf_string_const_ref text_, float shadow_, float text_size_, sqf_string_const_ref font_) {
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

            host::functions.invoke_raw_unary(__sqf::unary__drawicon3d__array__ret__nothing, args);
        }





        object create_vehicle_local(sqf_string_const_ref type_, const vector3 & pos_atl_) {
            return object(host::functions.invoke_raw_binary(__sqf::binary__createvehiclelocal__string__array__ret__object, type_, pos_atl_));
        }



        sqf_return_string_list action_keys(sqf_string_const_ref user_action_) {
            game_value act_keys = host::functions.invoke_raw_unary(__sqf::unary__actionkeys__string__ret__array, user_action_);
            sqf_return_string_list r_arr = __helpers::__convert_to_strings_vector(act_keys);
            return r_arr;
        }

        rv_text action_keys_images(sqf_string_const_ref user_action_) {
            return rv_text(host::functions.invoke_raw_unary(__sqf::unary__actionkeysimages__string_array__ret__text, user_action_));
        }

        sqf_return_string action_keys_names(sqf_string_const_ref user_action_) {
            return host::functions.invoke_raw_unary(__sqf::unary__actionkeysnames__string_array__ret__string, user_action_);
        }

        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_) {
            game_value params({ user_action_, static_cast<float>(max_keys_) });
            return host::functions.invoke_raw_unary(__sqf::unary__actionkeysnames__string_array__ret__string, params);
        }
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_) {
            game_value params({
                user_action_,
                static_cast<float>(max_keys_),
                input_device_priority_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__actionkeysnames__string_array__ret__string, params);
        }

        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_) {
            game_value act_keys = host::functions.invoke_raw_unary(__sqf::unary__actionkeysnamesarray__string_array__ret__array, user_action_);
            sqf_return_string_list r_arr = __helpers::__convert_to_strings_vector(act_keys);

            return r_arr;
        }

        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_) {
            game_value params({ user_action_, static_cast<float>(max_keys_) });

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
        }
        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_) {
            game_value params({
                user_action_,
                static_cast<float>(max_keys_),
                input_device_priority_
            });

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
        }

        
        

        void add_to_remains_collector(const std::vector<object> & objects_) {
            auto_array<game_value> objects(objects_.begin(), objects_.end());

            host::functions.invoke_raw_unary(__sqf::unary__addtoremainscollector__array__ret__nothing, std::move(objects));
        }

        void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_) {
            game_value params({
                wounded_,
                medic_,
                medic_can_heal_
            });

            host::functions.invoke_raw_unary(__sqf::unary__aisfinishheal__array__ret__nothing, params);
        }

        std::vector<object> all_mission_objects(sqf_string_const_ref type_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__allmissionobjects__string__ret__array, type_));
        }

        void action(const object & unit_, const std::vector<game_value>& action_array_) {
            host::functions.invoke_raw_binary(__sqf::binary__action__object__array__ret__nothing, unit_, action_array_);
        }

        float add_event_handler(const object & object_, sqf_string_const_ref type_, const code & command_) {
            game_value args({
                type_,
                command_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addeventhandler__object__array__ret__nothing_scalar, object_, args);
        }

        float add_event_handler(const object & object_, sqf_string_const_ref type_, sqf_string_const_ref command_) {
            game_value args({
                type_,
                command_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addeventhandler__object__array__ret__nothing_scalar, object_, args);
        }

        

        object create_mine(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_/* = {}*/, float placement_/* = 0.0f*/) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());

            game_value args({
                type_,
                pos_,
                std::move(markers),
                placement_,
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createmine__array__ret__object, args));
        }

        


        

        std::vector<object> crew(const object & _veh) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__crew__object__ret__array, _veh));
        }

        float add_action(const object &object_, sqf_string_const_ref title_, sqf_string_const_ref script_, const std::vector<game_value> &arguments_, float priority_, bool show_window_, bool hide_on_use_, sqf_string_const_ref shortcut_, sqf_string_const_ref condition_) {
            game_value args({
                title_,
                script_,
                arguments_,
                priority_,
                show_window_,
                hide_on_use_,
                shortcut_,
                condition_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addaction__object__array__ret__nothing_scalar, object_, args);
        }

        float add_action(const object &object_, sqf_string_const_ref title_, const code &script_, const std::vector<game_value> &arguments_, float priority_, bool show_window_, bool hide_on_use_, sqf_string_const_ref shortcut_, sqf_string_const_ref condition_) {
            game_value args({
                title_,
                script_,
                arguments_,
                priority_,
                show_window_,
                hide_on_use_,
                shortcut_,
                condition_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addaction__object__array__ret__nothing_scalar, object_, args);
        }

        

        std::vector<rv_crew_member> full_crew(const object &veh_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__object__ret__array, veh_);

            std::vector<rv_crew_member> crew_members;
            for (uint32_t i = 0; i < ret.size(); ++i) {
                std::vector<int> turret_path = __helpers::__convert_to_integers_vector(ret[i][3]);
                crew_members.push_back(rv_crew_member(ret[i][0], ret[i][1], ret[i][2], turret_path, ret[i][4]));
            }

            return crew_members;
        }

        std::vector<rv_crew_member> full_crew(const object &veh_, sqf_string_const_ref filter_, bool include_empty_) {
            game_value params({
                veh_,
                filter_,
                include_empty_
            });

            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__array__ret__array, params);

            std::vector<rv_crew_member> crew_members;
            for (uint32_t i = 0; i < ret.size(); ++i) {
                std::vector<int> turret_path = __helpers::__convert_to_integers_vector(ret[i][3]);
                crew_members.push_back(rv_crew_member(ret[i][0], ret[i][1], ret[i][2], turret_path, ret[i][4]));
            }

            return crew_members;
        }



        vector3 get_center_of_mass(const object &obj_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__getcenterofmass__object__ret__array, obj_));
        }

        /* Core */
        object player() {
            return object(host::functions.invoke_raw_nular(__sqf::nular__player__ret__object));
        }

        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_) {
            return object(host::functions.invoke_raw_binary(__sqf::binary__createvehicle__string__array__ret__object, type_, pos_));
        }

        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_, sqf_string_const_ref special_) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());
            game_value args({
                type_,
                pos_,
                std::move(markers),
                placement_,
                special_
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createvehicle__array__ret__object, args));
        }

        void delete_vehicle(const object &obj_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletevehicle__object__ret__nothing, obj_);
        }

        void create_unit(sqf_string_const_ref type_, const vector3 &pos_, const group &group_, sqf_string_const_ref init_, float skill_, sqf_string_const_ref rank_) {
            game_value args({
                pos_,
                group_,
                init_,
                skill_,
                rank_
            });

            host::functions.invoke_raw_binary(__sqf::binary__createunit__string__array__ret__nothing, type_, args);
        }

        object create_unit(const group &group_, sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_, sqf_string_const_ref special_) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());

            game_value args({
                type_,
                pos_,
                std::move(markers),
                placement_,
                special_
            });

            return object(host::functions.invoke_raw_binary(__sqf::binary__createunit__group__array__ret__object, group_, args));
        }

        std::vector<object> all_curators() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__allcurators__ret__array));
        }

        std::vector<object> all_dead() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__alldead__ret__array));
        }

        std::vector<object> all_deadmen() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__alldeadmen__ret__array));
        }

        std::vector<display> all_displays() {
            return __helpers::__convert_to_displays_vector(host::functions.invoke_raw_nular(__sqf::nular__alldisplays__ret__array));
        }

        std::vector<group> all_groups() {
            return __helpers::__convert_to_groups_vector(host::functions.invoke_raw_nular(__sqf::nular__allgroups__ret__array));
        }

        std::vector<object> all_mines() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__allmines__ret__array));
        }

        std::vector<object> all_players() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__allplayers__ret__array));
        }

        std::vector<object> all_units() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__allunits__ret__array));
        }

        std::vector<object> all_units_uav() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__allunitsuav__ret__array));
        }

        

        sqf_return_string_list all_turrets(const object &vehicle_, bool person_turrets_) {
            game_value array_input({
                vehicle_,
                person_turrets_
            });

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allturrets__array__ret__array, array_input));
        }

        sqf_return_string_list all_turrets(const object &vehicle_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allturrets__object__ret__array, vehicle_));
        }

        

        

        /* Misc */

        
        sqf_return_string_list activated_addons() {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_nular(__sqf::nular__activatedaddons__ret__array));
        }

  

        object camera_on() {
            return __helpers::__retrieve_nular_object(__sqf::nular__cameraon__ret__object);
        }



        side civilian() {
            return __helpers::__retrieve_nular_side(__sqf::nular__civilian__ret__side);
        }





        sqf_return_string commanding_menu() {
            return __helpers::__retrieve_nular_string(__sqf::nular__commandingmenu__ret__string);
        }

        object cursor_target() {
            return __helpers::__retrieve_nular_object(__sqf::nular__cursortarget__ret__object);
        }


        // TODO std::vector<float> fog_params();

        

        float getelevationoffset() {
            return __helpers::__retrieve_nular_number(__sqf::nular__getelevationoffset__ret__scalar);
        }

        // TODO std::array<float, 2> get_mouse_position();
        // TODO std::array<float, 2> get_object_view_distance();

        // TODO std::array<float, 6> get_resolution();

        

        bool has_interface() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__hasinterface__ret__bool);
        }

        
        
        // TODO std::array<float, 6> mission_start();

        float particles_quality() {
            return __helpers::__retrieve_nular_number(__sqf::nular__particlesquality__ret__scalar);
        }

        float pi() {
            return __helpers::__retrieve_nular_number(__sqf::nular__pi__ret__scalar);
        }

        

        std::vector<object> playable_units() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__playableunits__ret__array));
        }

        float player_respawn_time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__playerrespawntime__ret__scalar);
        }

        side player_side() {
            return __helpers::__retrieve_nular_side(__sqf::nular__playerside__ret__side);
        }

        bool reversed_mouse_y() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__reversedmousey__ret__bool);
        }

        

        
        std::vector<object> switchable_units() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(__sqf::nular__switchableunits__ret__array));
        }

        
        sqf_return_string action_name(sqf_string_const_ref action_) {
            return __helpers::__string_unary_string(__sqf::unary__actionname__string__ret__string, action_);
        }

        void airport_side(int id_) {
            __helpers::__empty_unary_number(__sqf::unary__airportside__object_scalar__ret__nothing, static_cast<float>(id_));
        }
        void airport_side(const object & target_) {
            __helpers::__empty_unary_number(__sqf::unary__airportside__object_scalar__ret__nothing, target_);
        }

        bool alive(const object & obj_) {
            return __helpers::__bool_unary_object(__sqf::unary__alive__object__ret__bool, obj_);
        }

        sqf_return_string animation_state(const object & unit_) {
            return __helpers::__string_unary_object(__sqf::unary__animationstate__object__ret__string, unit_);
        }

        object assigned_commander(const object & veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedcommander__object__ret__object, veh_);
        }

        object assigned_driver(const object & veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assigneddriver__object__ret__object, veh_);
        }

        object assigned_gunner(const object & veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedgunner__object__ret__object, veh_);
        }

        object assigned_target(const object & veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedtarget__object__ret__object, veh_);
        }

        sqf_return_string assigned_team(const object & unit_) {
            return __helpers::__string_unary_object(__sqf::unary__assignedteam__object__ret__string, unit_);
        }

        object assigned_vehicle(const object & unit_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedvehicle__object__ret__object, unit_);
        }

        
        void buldozer_enable_road_diag(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__buldozer_enableroaddiag__bool__ret__nothing, value_);
        }

        bool buldozer_load_new_roads(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__buldozer_loadnewroads__string__ret__bool, value_);
        }

        void set_particle_params(const object & particle_source_, const rv_particle_array & particle_array_) {
            host::functions.invoke_raw_binary(__sqf::binary__setparticlecircle__object__array__ret__nothing, particle_source_, particle_array_);
        }

        void set_particle_random(const object & particle_source_, const rv_particle_random & particle_random_) {
            host::functions.invoke_raw_binary(__sqf::binary__setparticlerandom__object__array__ret__nothing, particle_source_, particle_random_);
        }

        void set_particle_circle(const object & particle_source_, float radius_, const vector3 & velocity_) {
            game_value args({
                radius_,
                velocity_
            });
            host::functions.invoke_raw_binary(__sqf::binary__setparticlecircle__object__array__ret__nothing, particle_source_, args);
        }

        void set_particle_fire(const object & particle_source_, float core_intensity_, float core_distance_, float damage_time_) {
            game_value args({
                core_intensity_,
                core_distance_,
                damage_time_
            });
            host::functions.invoke_raw_binary(__sqf::binary__setparticlefire__object__array__ret__nothing, particle_source_, args);
        }

        void drop(const rv_particle_array & particle_array_) {
            host::functions.invoke_raw_unary(__sqf::unary__drop__array__ret__nothing, particle_array_);
        }

        

        bool can_fire(const object & unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canfire__object__ret__bool, unit_);
        }

        bool can_move(const object & unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canmove__object__ret__bool, unit_);
        }

        bool can_stand(const object & unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canstand__object__ret__bool, unit_);
        }

        bool can_unload_in_combat(const object & unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canunloadincombat__object__ret__bool, unit_);
        }

        bool captive(const object & unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__captive__object__ret__bool, unit_);
        }

        float captive_num(const object & unit_) {
            return __helpers::__number_unary_object(__sqf::unary__captivenum__object__ret__scalar, unit_);
        }





        object commander(const object & veh_) {
            return __helpers::__object_unary_object(__sqf::unary__commander__object__ret__object, veh_);
        }
        

        void create_vehicle_crew(const object & veh_) {
            __helpers::__empty_unary_object(__sqf::unary__createvehiclecrew__object__ret__nothing, veh_);
        }

        sqf_return_string current_command(const object & veh_) {
            return __helpers::__string_unary_object(__sqf::unary__currentcommand__object__ret__string, veh_);
        }

       
        int current_vision_mode(const object & unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__currentvisionmode__object__ret__scalar, unit_);
        }



        float current_zeroing(const object & gunner_) {
            return __helpers::__number_unary_object(__sqf::unary__currentzeroing__object__ret__scalar, gunner_);
        }

        float damage(const object & object_) {
            return __helpers::__number_unary_object(__sqf::unary__damage__object__ret__scalar, object_);
        }

        


        void disable_user_input(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__disableuserinput__bool__ret__nothing, value_);
        }

        object driver(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__driver__object__ret__object, value_);
        }

        void echo(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__echo__string__ret__nothing, value_);
        }

        object effective_commander(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__effectivecommander__object__ret__object, value_);
        }

        void end_mission(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__endmission__string__ret__nothing, value_);
        }

        void estimated_time_left(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__estimatedtimeleft__scalar__ret__nothing, value_);
        }

        sqf_return_string face(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__face__object__ret__string, value_);
        }

        sqf_return_string faction(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__faction__object__ret__string, value_);
        }

        void fail_mission(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__failmission__string__ret__nothing, value_);
        }

        void fill_weapons_from_pool(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__fillweaponsfrompool__object__ret__nothing, value_);
        }

        


        object flag(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__flag__object__ret__object, value_);
        }

        object flag_owner(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__flagowner__object__ret__object, value_);
        }

        sqf_return_string flag_texture(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__flagtexture__object__ret__string, value_);
        }



        void force_respawn(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__forcerespawn__object__ret__nothing, value_);
        }

        object form_leader(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__formleader__object__ret__object, value_);
        }

        float formation_direction(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__formationdirection__object__ret__scalar, value_);
        }

        object formation_leader(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__formationleader__object__ret__object, value_);
        }

        float fuel(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__fuel__object__ret__scalar, value_);
        }

 

        float get_aiming_coef(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getaimingcoef__object__ret__scalar, value_);
        }

  

        float get_anim_aim_precision(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getanimaimprecision__object__ret__scalar, value_);
        }

        float get_anim_speed_coef(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getanimspeedcoef__object__ret__scalar, value_);
        }

        float get_bleeding_remaining(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getbleedingremaining__object__ret__scalar, value_);
        }

        float get_burning_value(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getburningvalue__object__ret__scalar, value_);
        }

        object get_connected_uav(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__getconnecteduav__object__ret__object, value_);
        }

        float get_custom_aim_coef(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getcustomaimcoef__object__ret__scalar, value_);
        }

        float get_dammage(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getdammage__object__ret__scalar, value_);
        }

        float get_fatigue(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getfatigue__object__ret__scalar, value_);
        }



        float get_mass(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getmass__object__ret__scalar, value_);
        }

        float get_object_dlc(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getobjectdlc__object__ret__scalar, value_);
        }

        float get_object_type(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getobjecttype__object__ret__scalar, value_);
        }

        float get_oxygen_remaining(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getoxygenremaining__object__ret__scalar, value_);
        }

        sqf_return_string get_player_uid(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__getplayeruid__object__ret__string, value_);
        }





        float get_stamina(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getstamina__object__ret__scalar, value_);
        }

        float get_stat_value(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__getstatvalue__string__ret__scalar, value_);
        }

        float get_suppression(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getsuppression__object__ret__scalar, value_);
        }

        float get_weapon_sway(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getweaponsway__object__ret__scalar, value_);
        }





        object gunner(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__gunner__object__ret__object, value_);
        }

        float hands_hit(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__handshit__object__ret__scalar, value_);
        }



        void hide_body(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__hidebody__object__ret__nothing, value_);
        }

        void hide_object(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__hideobject__object__ret__nothing, value_);
        }

        void hide_object_global(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__hideobjectglobal__object__ret__nothing, value_);
        }


        sqf_return_string incapacitated_state(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__incapacitatedstate__object__ret__string, value_);
        }

        bool inflamed(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__inflamed__object__ret__bool, value_);
        }

        float input_action(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__inputaction__string__ret__scalar, value_);
        }

        bool is_able_to_breathe(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isabletobreathe__object__ret__bool, value_);
        }

        bool is_aim_precision_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isaimprecisionenabled__object__ret__bool, value_);
        }

        bool is_auto_hover_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isautohoveron__object__ret__bool, value_);
        }



        bool is_autonomous(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isautonomous__object__ret__bool, value_);
        }

        bool is_bleeding(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isbleeding__object__ret__bool, value_);
        }

        bool is_burning(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isburning__object__ret__bool, value_);
        }

        bool is_collision_light_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__iscollisionlighton__object__ret__bool, value_);
        }

        bool is_copilot_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__iscopilotenabled__object__ret__bool, value_);
        }

        bool is_engine_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isengineon__object__ret__bool, value_);
        }

        bool is_forced_walk(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isforcedwalk__object__ret__bool, value_);
        }

        bool is_formation_leader(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isformationleader__object__ret__bool, value_);
        }

        bool is_hidden(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ishidden__object__ret__bool, value_);
        }

        bool is_in_remains_collector(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isinremainscollector__object__ret__bool, value_);
        }

        bool is_key_active(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__iskeyactive__string__ret__bool, value_);
        }

        bool is_light_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__islighton__object__ret__bool, value_);
        }

        bool is_localized(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__islocalized__string__ret__bool, value_);
        }

        bool is_manual_fire(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ismanualfire__object__ret__bool, value_);
        }

        bool is_marked_for_collection(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ismarkedforcollection__object__ret__bool, value_);
        }

        bool is_object_hidden(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isobjecthidden__object__ret__bool, value_);
        }



        bool is_player(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isplayer__object__ret__bool, value_);
        }

        bool is_sprint_allowed(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__issprintallowed__object__ret__bool, value_);
        }

        bool is_stamina_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isstaminaenabled__object__ret__bool, value_);
        }

        bool is_touching_ground(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__istouchingground__object__ret__bool, value_);
        }

        bool is_turned_out(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isturnedout__object__ret__bool, value_);
        }

        bool is_uavconnected(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isuavconnected__object__ret__bool, value_);
        }

        bool is_walking(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__iswalking__object__ret__bool, value_);
        }

        bool is_weapon_deployed(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isweapondeployed__object__ret__bool, value_);
        }

        bool is_weapon_rested(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isweaponrested__object__ret__bool, value_);
        }



        object laser_target(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__lasertarget__object__ret__object, value_);
        }

        object leader(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__leader__object__ret__object, value_);
        }

        sqf_return_string life_state(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__lifestate__object__ret__string, value_);
        }

        sqf_return_string light_is_on(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__lightison__object__ret__string, value_);
        }

        

        

        sqf_return_string localize(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__localize__string__ret__string, value_);
        }

        bool lock_identity(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__lockidentity__object__ret__bool, value_);
        }

        float locked(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__locked__object__ret__scalar, value_);
        }

        bool locked_driver(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__lockeddriver__object__ret__bool, value_);
        }

        bool mine_active(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__mineactive__object__ret__bool, value_);
        }

        float morale(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__morale__object__ret__scalar, value_);
        }

        void move_out(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__moveout__object__ret__nothing, value_);
        }

        float move_time(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__movetime__object__ret__scalar, value_);
        }



        sqf_return_string name(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__name__object__ret__string, value_);
        }



        
        float need_reload(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__needreload__object__ret__scalar, value_);
        }



        object object_parent(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__objectparent__object__ret__object, value_);
        }

     

        float precision(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__precision__object__ret__scalar, value_);
        }





        sqf_return_string rank(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__rank__object__ret__string, value_);
        }

        float rank_id(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__rankid__object__ret__scalar, value_);
        }

        float rating(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__rating__object__ret__scalar, value_);
        }

        void reload(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__reload__object__ret__nothing, value_);
        }

        bool reload_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__reloadenabled__object__ret__bool, value_);
        }

        void remove_all_actions(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallactions__object__ret__nothing, value_);
        }



        void remove_all_mission_event_handlers(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__removeallmissioneventhandlers__string__ret__nothing, value_);
        }


        void remove_mp_event_handler(const object &object_, sqf_string_const_ref event_, int index_) {
            game_value params_right({
                event_,
                index_
            });

            host::functions.invoke_raw_binary(__sqf::binary__removempeventhandler__object__array__ret__nothing, object_, params_right);
        }


        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const code &code_) {
            host::functions.invoke_raw_binary(__sqf::binary__addpublicvariableeventhandler__string__code__ret__nothing, var_name_, code_);
        }

        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const object &target_, const code &code_) {
            game_value params_right({
                target_,
                code_
            });

            host::functions.invoke_raw_binary(__sqf::binary__addpublicvariableeventhandler__string__array__ret__nothing, var_name_, params_right);
        }



        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, sqf_string_const_ref expression_) {
            game_value params_right({
                type_,
                expression_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addmpeventhandler__object__array__ret__nothing_scalar, object_, params_right);
        }

        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, const code &expression_) {
            game_value params_right({
                type_,
                expression_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addmpeventhandler__object__array__ret__nothing_scalar, object_, params_right);
        }

        
        void remove_switchable_unit(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeswitchableunit__object__ret__nothing, value_);
        }

        bool required_version(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__requiredversion__string__ret__bool, value_);
        }

        void reset_subgroup_direction(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__resetsubgroupdirection__object__ret__nothing, value_);
        }


        void save_var(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__savevar__string__ret__nothing, value_);
        }

        void scope_name(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__scopename__string__ret__nothing, value_);
        }

        float score(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__score__object__ret__scalar, value_);
        }

        void script_name(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__scriptname__string__ret__nothing, value_);
        }

        float scud_state(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__scudstate__object__ret__scalar, value_);
        }



        void select_player(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__selectplayer__object__ret__nothing, value_);
        }


        void set_playable(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__setplayable__object__ret__nothing, value_);
        }

        void set_player_respawn_time(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setplayerrespawntime__scalar__ret__nothing, value_);
        }

        void set_stamina_scheme(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__setstaminascheme__string__ret__nothing, value_);
        }

        
        float size_of(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__sizeof__string__ret__scalar, value_);
        }



        

        bool some_ammo(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__someammo__object__ret__bool, value_);
        }

        sqf_return_string speaker(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__speaker__object__ret__string, value_);
        }

        float speed(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__speed__object__ret__scalar, value_);
        }

        sqf_return_string stance(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__stance__object__ret__string, value_);
        }



        bool stopped(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__stopped__object__ret__bool, value_);
        }

        game_value text(sqf_string_const_ref value_) {
            return  host::functions.invoke_raw_unary(__sqf::unary__text__location__ret__string, value_);
        }



        void unassign_team(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__unassignteam__object__ret__nothing, value_);
        }

        void unassign_vehicle(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__unassignvehicle__object__ret__nothing, value_);
        }

        sqf_return_string unit_pos(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__unitpos__object__ret__string, value_);
        }

        float unit_recoil_coefficient(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__unitrecoilcoefficient__object__ret__scalar, value_);
        }

        object vehicle(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__vehicle__object__ret__object, value_);
        }

        sqf_return_string vehicle_var_name(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__vehiclevarname__object__ret__string, value_);
        }

        bool verify_signature(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__verifysignature__string__ret__bool, value_);
        }

        bool weapon_lowered(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__weaponlowered__object__ret__bool, value_);
        }

        // BINARY FUNCTIONS

        

        

        void add_rating(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addrating__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_score(const object &value0_,float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addscore__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_score_side(const side &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addscoreside__side__scalar__ret__nothing, value0_, value1_);
        }

        



        


        void allow_crew_in_immobile(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowcrewinimmobile__object__bool__ret__nothing, value0_, value1_);
        }

        void allow_damage(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowdamage__object__bool__ret__nothing, value0_, value1_);
        }

        void allow_dammage(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowdammage__object__bool__ret__nothing, value0_, value1_);
        }


        void allow_sprint(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowsprint__object__bool__ret__nothing, value0_, value1_);
        }



        float animation_phase(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__animationphase__object__string__ret__scalar, value0_, value1_);
        }

        void assign_team(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__assignteam__object__string__ret__nothing, value0_, value1_);
        }

        void assign_to_airport(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__assigntoairport__object__object_scalar__ret__nothing, value0_, value1_);
        }

        void assign_to_airport(const object &value0_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__assigntoairport__object__object_scalar__ret__nothing, value0_, target_);
        }

        



        void disable_conversation(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__disableconversation__object__bool__ret__nothing, value0_, value1_);
        }

        void disable_nvgequipment(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__disablenvgequipment__object__bool__ret__nothing, value0_, value1_);
        }

        void disable_tiequipment(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__disabletiequipment__object__bool__ret__nothing, value0_, value1_);
        }

        float door_phase(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__doorphase__object__string__ret__scalar, value0_, value1_);
        }

        float empty_positions(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__emptypositions__object__string__ret__scalar, value0_, value1_);
        }



        void enable_aim_precision(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableaimprecision__object__bool__ret__nothing, value0_, value1_);
        }



        void enable_copilot(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablecopilot__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_fatigue(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablefatigue__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_mimics(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablemimics__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_reload(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablereload__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_stamina(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablestamina__object__bool__ret__nothing, value0_, value1_);
        }

        void engine_on(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__engineon__object__bool__ret__nothing, value0_, value1_);
        }

        void fire(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__fire__object__string__ret__nothing, value0_, value1_);
        }





        void force_speed(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__forcespeed__object__scalar__ret__nothing, value0_, value1_);
        }

        void force_walk(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__forcewalk__object__bool__ret__nothing, value0_, value1_);
        }


        float get_hit(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethit__object__string__ret__scalar, value0_, value1_);
        }

        float get_hit_index(const object &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethitindex__object__scalar__ret__scalar, value0_, value1_);
        }

        float get_hit_point_damage(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethitpointdamage__object__string__ret__scalar, value0_, value1_);
        }


        float get_speed(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getspeed__object__string__ret__scalar, value0_, value1_);
        }

        void hide_object(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__hideobject__object__bool__ret__nothing, value0_, value1_);
        }

        void hide_object_global(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__hideobjectglobal__object__bool__ret__nothing, value0_, value1_);
        }

        

        void inflame(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__inflame__object__bool__ret__nothing, value0_, value1_);
        }

        bool is_flashlight_on(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isflashlighton__object__string__ret__bool, value0_, value1_);
        }

        bool is_irlaser_on(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isirlaseron__object__string__ret__bool, value0_, value1_);
        }

      





        void leave_vehicle(const object &value0_, const group &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__leavevehicle__group__object__ret__nothing, value0_, value1_);
        }

        void limit_speed(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__limitspeed__object__scalar__ret__nothing, value0_, value1_);
        }

        void lock(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lock__object__bool__ret__nothing, value0_, value1_);
        }

        void lock(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lock__object__scalar__ret__nothing, value0_, value1_);
        }

        void lock_cargo(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lockcargo__object__bool__ret__nothing, value0_, value1_);
        }

        void lock_driver(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lockdriver__object__bool__ret__nothing, value0_, value1_);
        }

        bool locked_cargo(const object &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lockedcargo__object__scalar__ret__bool, value0_, value1_);
        }


        bool mine_detected_by(const object &value0_, const side &value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__minedetectedby__object__side__ret__bool, value0_, value1_);
        }


        void play_action(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__playaction__object__string__ret__nothing, value0_, value1_);
        }

        void play_action_now(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__playactionnow__object__string__ret__nothing, value0_, value1_);
        }

        void play_gesture(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__playgesture__object__string__ret__nothing, value0_, value1_);
        }

        void play_move(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__playmove__object__string__ret__nothing, value0_, value1_);
        }

        void play_move_now(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__playmovenow__object__string__ret__nothing, value0_, value1_);
        }




        void remove_action(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeaction__object__scalar__ret__nothing, value0_, value1_);
        }

        void remove_all_event_handlers(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removealleventhandlers__object__string__ret__nothing, value0_, value1_);
        }

        void remove_all_mpevent_handlers(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeallmpeventhandlers__object__string__ret__nothing, value0_, value1_);
        }

        

        void reveal_mine(const object &value0_, const side &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__revealmine__side__object__ret__nothing, value0_, value1_);
        }

        

        void set_airport_side(float value0_, const side &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setairportside__object_scalar__side__ret__nothing, value0_, value1_);
        }

        void set_airport_side(const object & target_, const side &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setairportside__object_scalar__side__ret__nothing, target_, value1_);
        }


        void set_anim_speed_coef(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setanimspeedcoef__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_autonomous(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setautonomous__object__bool__ret__nothing, value0_, value1_);
        }

        void set_bleeding_remaining(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setbleedingremaining__object__scalar__ret__nothing, value0_, value1_);
        }





        void set_collision_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcollisionlight__object__bool__ret__nothing, value0_, value1_);
        }



        void set_custom_aim_coef(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcustomaimcoef__object__scalar__ret__nothing, value0_, value1_);
        }



        void set_damage(const object &value0_, float value1_, bool use_effects_) {
            if (use_effects_)
                host::functions.invoke_raw_binary(__sqf::binary__setdamage__object__scalar_array__ret__nothing, value0_, value1_);
            else
                host::functions.invoke_raw_binary(__sqf::binary__setdamage__object__scalar_array__ret__nothing, value0_, {value1_,use_effects_});
        }

        void set_dammage(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdammage__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_drop_interval(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdropinterval__object__scalar__ret__nothing, value0_, value1_);
        }


        void set_face(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setface__object__string__ret__nothing, value0_, value1_);
        }

        void set_faceanimation(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfaceanimation__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_fatigue(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfatigue__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_flag_side(const object &value0_, const side &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflagside__object__side__ret__nothing, value0_, value1_);
        }

        void set_flag_texture(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflagtexture__object__string__ret__nothing, value0_, value1_);
        }





        void set_fuel(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfuel__object__scalar__ret__nothing, value0_, value1_);
        }



        void set_identity(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setidentity__object__string__ret__nothing, value0_, value1_);
        }

        void set_light_brightness(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightbrightness__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_day_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightdaylight__object__bool__ret__nothing, value0_, value1_);
        }

        void set_light_flare_max_distance(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightflaremaxdistance__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_flare_size(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightflaresize__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_intensity(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightintensity__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_use_flare(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightuseflare__object__bool__ret__nothing, value0_, value1_);
        }

        void set_mimic(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmimic__object__string__ret__nothing, value0_, value1_);
        }

        void set_name(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setname__object__string__ret__nothing, value0_, value1_);
        }

        
        void set_oxygen_remaining(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setoxygenremaining__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_particle_class(const object &particle_source_, sqf_string_const_ref particle_class_) {
            host::functions.invoke_raw_binary(__sqf::binary__setparticleclass__object__string__ret__nothing, particle_source_, particle_class_);
        }

        void set_pilot_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpilotlight__object__bool__ret__nothing, value0_, value1_);
        }

        void set_random_lip(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrandomlip__object__bool__ret__nothing, value0_, value1_);
        }

        void set_rank(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrank__object__string__ret__nothing, value0_, value1_);
        }





        
        void set_stamina(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setstamina__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_suppression(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsuppression__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_target_age(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__settargetage__object__string__ret__nothing, value0_, value1_);
        }



        void set_unconscious(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunconscious__object__bool__ret__nothing, value0_, value1_);
        }

        void set_unit_ability(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitability__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_unit_pos(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitpos__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_pos_weak(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitposweak__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_rank(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitrank__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_recoil_coefficient(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitrecoilcoefficient__object__scalar__ret__nothing, value0_, value1_);
        }



        void set_vehicle_armor(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclearmor__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_id(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicleid__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_lock(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclelock__object__string__ret__nothing, value0_, value1_);
        }

        void set_vehicle_var_name(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclevarname__object__string__ret__nothing, value0_, value1_);
        }


        

        void switch_action(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchaction__object__string__ret__nothing, value0_, value1_);
        }



        void switch_gesture(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchgesture__object__string__ret__nothing, value0_, value1_);
        }

        void switch_light(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchlight__object__string__ret__nothing, value0_, value1_);
        }

        void switch_move(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchmove__object__string__ret__nothing, value0_, value1_);
        }



        

        void use_audio_time_for_moves(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__useaudiotimeformoves__object__bool__ret__nothing, value0_, value1_);
        }

        side create_center(const side & side_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__createcenter__side__ret__side, side_));
        }

        void delete_center(const side & side_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletecenter__side__ret__nothing, side_);
        }



        side flag_side(const object &value_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__flagside__object__ret__side, value_));
        }

      
        sqf_return_string image(sqf_string_const_ref value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__image__string__ret__text, value_);
        }



        sqf_return_string key_image(float value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__keyimage__scalar__ret__text, value_);
        }

        sqf_return_string key_name(float value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__keyname__scalar__ret__string, value_);
        }



        

        float playable_slots_number(const side &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__playableslotsnumber__side__ret__scalar, value_);
        }

        float players_number(const side &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__playersnumber__side__ret__scalar, value_);
        }

        float score_side(const side &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__scoreside__side__ret__scalar, value_);
        }



        bool buldozer_is_enabled_road_diag() {
            return host::functions.invoke_raw_nular(__sqf::nular__buldozer_isenabledroaddiag__ret__bool);
        }

        void buldozer_reload_oper_map() {
            host::functions.invoke_raw_nular(__sqf::nular__buldozer_reloadopermap__ret__nothing);
        }

        
        



        std::vector<object> roads_connected_to(const object &obj_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__roadsconnectedto__object__ret__array, obj_));
        }







        void move(const object& unit_, const vector3& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__move__object_group__array__ret__nothing, unit_, pos_);
        }

        void move(const group& group_, const vector3& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__move__object_group__array__ret__nothing, group_, pos_);
        }

        bool move_in_any(const object& unit_, const object& vehicle_) {
            return host::functions.invoke_raw_binary(__sqf::binary__moveinany__object__object__ret__bool, unit_, vehicle_);
        }

        void move_in_cargo(const object& unit_, const object& vehicle_, int cargo_index_) {
            if (cargo_index_ == -1)
            {
                host::functions.invoke_raw_binary(__sqf::binary__moveincargo__object__object__ret__nothing, unit_, vehicle_);
            }
            else
            {
                game_value params({
                    vehicle_,
                    static_cast<float>(cargo_index_)
                });

                host::functions.invoke_raw_binary(__sqf::binary__moveincargo__object__array__ret__nothing, unit_, params);
            }
        }

        void move_in_commander(const object& unit_, const object& vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveincommander__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_driver(const object& unit_, const object& vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveindriver__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_gunner(const object &unit_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveingunner__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_turret(const object& unit_, const object& vehicle_, const std::vector<int> turret_path_) {
            auto_array<game_value> path(turret_path_.begin(), turret_path_.end());

            game_value params({
                vehicle_,
                std::move(path)
            });

            host::functions.invoke_raw_binary(__sqf::binary__moveinturret__object__array__ret__nothing, unit_, params);
        }

        side get_side(const object &object_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__side__object__ret__side, object_));
        }

        sqf_return_string wf_side_text(const object &object_) {
            return __helpers::__string_unary_object(__sqf::unary__wfsidetext__object__ret__string, object_);
        }

        sqf_return_string wf_side_text(const group &group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__wfsidetext__group__ret__string, group_);
        }

        sqf_return_string wf_side_text(const side &side_) {
            return host::functions.invoke_raw_unary(__sqf::unary__wfsidetext__side__ret__string, side_);
        }

        float count_side(const side &side_, std::vector<object> &objects_) {
            auto_array<game_value> objects(objects_.begin(), objects_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countside__side__array__ret__scalar, side_, std::move(objects));
        }

        float aimed_at_target(const object& vehicle_, const object& target_) {
            game_value params({
                target_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__aimedattarget__object__array__ret__scalar, vehicle_, params);
        }

        float aimed_at_target(const object& vehicle_, const object& target_, sqf_string_const_ref weapon_) {
            game_value params({
                target_,
                weapon_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__aimedattarget__object__array__ret__scalar, vehicle_, params);
        }

        

        void animate(const object& obj_, sqf_string_const_ref animation_name_, float phase_) {
            game_value params({
                animation_name_,
                phase_
            });

            host::functions.invoke_raw_binary(__sqf::binary__animate__object__array__ret__nothing, obj_, params);
        }

        void animate(const object& obj_, sqf_string_const_ref animation_name_, float phase_, bool instant_) {
            game_value params({
                animation_name_,
                phase_,
                instant_
            });

            host::functions.invoke_raw_binary(__sqf::binary__animate__object__array__ret__nothing, obj_, params);
        }

        void animate_door(const object& obj_, sqf_string_const_ref door_name_, float phase_, bool now_) {
            game_value params({
                door_name_,
                phase_,
                now_
            });

            host::functions.invoke_raw_binary(__sqf::binary__animatedoor__object__array__ret__nothing, obj_, params);
        }

        

        


        
        

        

        void remote_control(const object &controller_, const object &controlled_) {
            host::functions.invoke_raw_binary(__sqf::binary__remotecontrol__object__object__ret__nothing, controller_, controlled_);
        }

        void set_hit(const object &object_, sqf_string_const_ref part_, float damage_) {
            game_value params({
                part_,
                damage_
            });

            host::functions.invoke_raw_binary(__sqf::binary__sethit__object__array__ret__nothing, object_, params);
        }

        void set_hit_index(const object &object_, int part_index_, float damage_) {
            game_value params({
                static_cast<float>(part_index_),
                damage_
            });

            host::functions.invoke_raw_binary(__sqf::binary__sethitindex__object__array__ret__nothing, object_, params);
        }

        void set_hit_point_damage(const object &object_, sqf_string_const_ref hit_point_, float damage_) {
            game_value params({
                hit_point_,
                damage_
            });

            host::functions.invoke_raw_binary(__sqf::binary__sethitpointdamage__object__array__ret__nothing, object_, params);
        }



        

        bool in(const object &unit_, const object &vehicle_) {
            return host::functions.invoke_raw_binary(__sqf::binary__in__object__object__ret__bool, unit_, vehicle_);
        }



        float add_mission_event_handler(sqf_string_const_ref type_, const code &command_) {
            game_value params({
                type_,
                command_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__addmissioneventhandler__array__ret__nothing_scalar, params);
        }

        float add_mission_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_) {
            game_value params({
                type_,
                command_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__addmissioneventhandler__array__ret__nothing_scalar, params);
        }



        rv_vehicle_role assigned_vehicle_role(const object &unit_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__assignedvehiclerole__object__ret__array, unit_);

            if (ret.size() == 0) {
                return rv_vehicle_role({});
            }
            if (ret.size() == 1) {
                return rv_vehicle_role({ ret[0] });
            }
            std::vector<int> turret_path = __helpers::__convert_to_integers_vector(ret[1]);
            return rv_vehicle_role({ ret[0], turret_path });
        }

        sqf_return_string compose_text(sqf_string_list_const_ref texts_) {
            auto_array<game_value> texts(texts_.begin(), texts_.end());

            return host::functions.invoke_raw_unary(__sqf::unary__composetext__array__ret__text, std::move(texts));
        }

        group get_group(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__group__object__ret__group, unit_);
        }

        void do_stop(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__dostop__object_array__ret__nothing, unit_);
        }

        void do_stop(const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_unary(__sqf::unary__dostop__object_array__ret__nothing, std::move(units));
        }

        void do_get_out(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__dogetout__object_array__ret__nothing, unit_);
        }

        void do_get_out(const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_unary(__sqf::unary__dogetout__object_array__ret__nothing, std::move(units));
        }



        std::vector<object> detected_mines(const side &side_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__detectedmines__side__ret__array, side_));
        }



        rv_hit_points_damage get_all_hit_points_damage(const object &veh_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getallhitpointsdamage__object__ret__array, veh_);

            sqf_return_string_list hit_points = __helpers::__convert_to_strings_vector(ret[0]);
            sqf_return_string_list hit_selections = __helpers::__convert_to_strings_vector(ret[1]);
            std::vector<float> damages = __helpers::__convert_to_numbers_vector(ret[2]);

            return rv_hit_points_damage({ hit_points, hit_selections, damages });
        }

        



        

        





       

        sqf_return_string_list get_object_materials(const object &object_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__getobjectmaterials__object__ret__array, object_));
        }

        sqf_return_string_list get_object_textures(const object &object_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__getobjecttextures__object__ret__array, object_));
        }

        std::vector<object> group_selected_units(const object &unit_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__groupselectedunits__object__ret__array, unit_));
        }






        

        void on_command_mode_changed(const code &command_) {
            host::functions.invoke_raw_unary(__sqf::unary__oncommandmodechanged__code_string__ret__nothing, command_);
        }

        void on_command_mode_changed(sqf_string_const_ref command_) {
            host::functions.invoke_raw_unary(__sqf::unary__oncommandmodechanged__code_string__ret__nothing, command_);
        }

       void remove_from_remains_collector(const std::vector<object> &remains_) {
            auto_array<game_value> remains(remains_.begin(), remains_.end());

            host::functions.invoke_raw_unary(__sqf::unary__removefromremainscollector__array__ret__nothing, std::move(remains));
        }

        void remove_mission_event_handler(sqf_string_const_ref type_, float index_) {
            game_value params({
                type_,
                index_
            });

            host::functions.invoke_raw_unary(__sqf::unary__removemissioneventhandler__array__ret__nothing, params);
        }

        sqf_return_string_list squad_params(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__squadparams__object__ret__array, unit_));
        }

        sqf_return_string_list support_info(sqf_string_const_ref mask_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__supportinfo__string__ret__array, mask_));
        }

        std::vector<object> synchronized_objects(const object& obj_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__synchronizedobjects__object__ret__array, obj_));
        }

        object cursor_object() {
            return game_value(__helpers::__retrieve_nular_object(__sqf::nular__cursorobject__ret__object));
        }

        bool unit_ready(const object& unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__unitready__object_array__ret__bool, unit_);
        }

        sqf_return_string_list unit_addons(sqf_string_const_ref class_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__unitaddons__string__ret__array, class_));
        }

        rv_uav_control uav_control(const object& uav_) {
            return rv_uav_control(host::functions.invoke_raw_unary(__sqf::unary__uavcontrol__object__ret__array, uav_));
        }


        rv_model_info get_model_info(const object& object_) {
            return rv_model_info(host::functions.invoke_raw_unary(__sqf::unary__getmodelinfo__object__ret__array, object_));
        }


        sqf_return_string format(const std::vector<game_value> &params_) {
            return host::functions.invoke_raw_unary(__sqf::unary__format__array__ret__string, params_);         
        }

        //UNARY -- https://github.com/intercept/intercept/issues/13
        std::vector<float> action_ids(const object& entity_) {
            return __helpers::__convert_to_numbers_vector(host::functions.invoke_raw_unary(__sqf::unary__actionids__object__ret__array, entity_));
        }

        std::vector<object> all_simple_objects(sqf_string_list_const_ref params_) {
            auto_array<game_value> params(params_.begin(), params_.end());

            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__allsimpleobjects__array__ret__array, std::move(params)));
        }



        object create_simple_object(sqf_string_const_ref shapename_, const vector3 &positionworld_) {
            game_value params({
                shapename_,
                positionworld_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createsimpleobject__array__ret__object, params);
        }

        

        float flag_animation_phase(const object &flag_) {
            return host::functions.invoke_raw_unary(__sqf::unary__flaganimationphase__object__ret__scalar, flag_);
        }


        std::vector<object> get_all_owned_mines(const object &unit_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__getallownedmines__object__ret__array, unit_));
        }
        
        float get_container_max_load(sqf_string_const_ref containerclass_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getcontainermaxload__string__ret__scalar, containerclass_);
        }

        rv_shot_parents get_shot_parents(const object &projectile_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getshotparents__object__ret__array, projectile_);

            return rv_shot_parents({
                ret[0],
                ret[1]
            });
        }

        
        
        bool is_simple_object(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__issimpleobject__object__ret__bool, object_);
        }

        
        std::vector<game_value> parse_simple_array(sqf_string_const_ref string_array_) {
            game_value res = host::functions.invoke_raw_unary(__sqf::unary__parsesimplearray__string__ret__array, string_array_);
            
            std::vector<game_value> result; //#TODO replace by helper function
            for (size_t i = 0; i < res.size(); i++) {
                result.push_back(res[i]);
            }

            return result;
        }

        void remove_all_owned_mines(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__removeallownedmines__object__ret__nothing, unit_);
        }

        bool screen_shot(sqf_string_const_ref filename_) {
            return host::functions.invoke_raw_unary(__sqf::unary__screenshot__string__ret__bool, filename_);
        }

        sqf_return_string_list selection_names(const object &object_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__selectionnames__object__ret__array, object_));
        }

        void switch_camera(const object &target_) {
            host::functions.invoke_raw_unary(__sqf::unary__switchcamera__object__ret__nothing, target_);
        }

        bool unit_is_uav(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__unitisuav__object__ret__bool, unit_);
        }



        //NULAR -- https://github.com/intercept/intercept/issues/13
        bool user_input_disabled() {
            return host::functions.invoke_raw_nular(__sqf::nular__userinputdisabled__ret__bool);
        }

        //BINARY -- https://github.com/intercept/intercept/issues/13

        rv_action_params action_params(const object &entity_, int id_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__actionparams__object__scalar__ret__array,entity_,static_cast<float>(id_));
        
            return rv_action_params({
                res[0],
                res[1],
                res[2],
                res[3],
                res[4],
                res[5],
                res[6],
                res[7],
                res[8],
                res[9],
                res[10],
                res[11],
                res[12]
            });
        }

        sqf_return_string add_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &values_, sqf_string_const_ref subtype_class_) {
            game_value params_right({
                type_,
                values_,
                subtype_class_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addeditorobject__control__array__ret__string, map_, params_right);
        }

        int add_menu(const control &map_, sqf_string_const_ref text_, float priority_) {
            game_value params_right({
                text_,
                priority_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addmenu__control__array__ret__scalar, map_, params_right);
        }

        int add_menu_item(const control &map_, sqf_string_const_ref menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_) {
            game_value params_right({
                menu_,
                text_,
                command_,
                priority_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addmenuitem__control__array__ret__scalar, map_, params_right);
        }

        int add_menu_item(const control &map_, int menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_) {
            game_value params_right({
                static_cast<float>(menu_),
                text_,
                command_,
                priority_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__addmenuitem__control__array__ret__scalar, map_, params_right);
        }

        void add_owned_mine(const object &unit_, const object &mine_) {
            host::functions.invoke_raw_binary(__sqf::binary__addownedmine__object__object__ret__nothing, unit_, mine_);
        }

        void add_player_scores(const object &unit_, int kills_infantry_, int kills_soft_, int kills_armor_, int kills_air_, int killed_) {
            game_value params_right({
                static_cast<float>(kills_infantry_),
                static_cast<float>(kills_soft_),
                static_cast<float>(kills_armor_),
                static_cast<float>(kills_air_),
                static_cast<float>(killed_),
            });

            host::functions.invoke_raw_binary(__sqf::binary__addplayerscores__object__array__ret__nothing, unit_, params_right);
        }

       

        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, bool speed_) {
            game_value params_right({
                source_,
                phase_,
                speed_
            });

            host::functions.invoke_raw_binary(__sqf::binary__animatesource__object__array__ret__nothing, object_, params_right);
        }

        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, float speed_) {
            game_value params_right({
                source_,
                phase_,
                speed_
            });

            host::functions.invoke_raw_binary(__sqf::binary__animatesource__object__array__ret__nothing, object_, params_right);
        }

        float animation_source_phase(const object &object_, sqf_string_const_ref source_) {
            return host::functions.invoke_raw_binary(__sqf::binary__animationsourcephase__object__string__ret__scalar, object_, source_);
        }

        void assign_as_turret(const object &unit_, const object &vehicle_, const std::vector<int> &turret_path_) {
            auto_array<game_value> turret_path(turret_path_.begin(), turret_path_.end());
            
            game_value params_right({
                vehicle_,
                std::move(turret_path)
            });

            host::functions.invoke_raw_binary(__sqf::binary__assignasturret__object__array__ret__nothing, unit_, params_right);
        }



        



        bool connect_terminal_to_uav(const object &unit_, const object &uav_) {
            return host::functions.invoke_raw_binary(__sqf::binary__connectterminaltouav__object__object__ret__bool, unit_, uav_);
        }

        int count_enemy(const object &unit_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countenemy__object__array__ret__scalar, unit_, std::move(units));
        }

        int count_friendly(const object &unit_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countfriendly__object__array__ret__scalar, unit_, std::move(units));
        }

        int count_type(sqf_string_const_ref type_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__counttype__string__array__ret__scalar, type_, std::move(units));
        }

        int count_unknown(const object &unit_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countunknown__object__array__ret__scalar, unit_, std::move(units));
        }

        

        void delete_editor_object(const control &map_, sqf_string_const_ref object_) {
            host::functions.invoke_raw_binary(__sqf::binary__deleteeditorobject__control__string__ret__any, map_, object_);
        }



        void delete_vehicle_crew(const object &vehicle_, const object &unit_) {
            host::functions.invoke_raw_binary(__sqf::binary__deletevehiclecrew__object__object__ret__nothing, vehicle_, unit_);
        }

        void disable_collision_with(const object &object1_, const object &object2_) {
            host::functions.invoke_raw_binary(__sqf::binary__disablecollisionwith__object__object__ret__nothing, object1_, object2_);
        }

        void disable_uav_connectability(const object &object_, const object &uav_, bool check_all_items_) {
            game_value params_right({
                uav_,
                check_all_items_
            });

            host::functions.invoke_raw_binary(__sqf::binary__disableuavconnectability__object__array__ret__nothing, object_, params_right);
        }

        
        

        

        game_value edit_object(const control &map_, sqf_string_const_ref object_) {
            return host::functions.invoke_raw_binary(__sqf::binary__editobject__control__string__ret__any, map_, object_);
        }

        void editor_set_event_handler(const control &map_, sqf_string_const_ref event_type_, sqf_string_const_ref event_function_) {
            game_value params_right({
                event_type_,
                event_function_
            });
            
            host::functions.invoke_raw_binary(__sqf::binary__editorseteventhandler__control__array__ret__nothing, map_, params_right);
        }





        void enable_collision_with(const object &object1_, const object &object2_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablecollisionwith__object__object__ret__nothing, object1_, object2_);
        }

        void enable_gun_lights(const object &unit_, bool &enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablegunlights__object_group__string__ret__nothing, unit_, enable_);
        }

        void enable_gun_lights(const group &group_, bool &enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablegunlights__object_group__string__ret__nothing, group_, enable_);
        }

        void enable_ir_lasers(const object &unit_, bool &enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableirlasers__object_group__bool__ret__nothing, unit_, enable_);
        }

        void enable_ir_lasers(const group &group_, bool &enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableirlasers__object_group__bool__ret__nothing, group_, enable_);
        }

        void enable_person_turret(const object &vehicle_, const std::vector<int> &turrent_path_, bool enable_) {
            auto_array<game_value> turrent_path(turrent_path_.begin(), turrent_path_.end());
            
            game_value params_right({
                std::move(turrent_path),
                enable_
            });

            host::functions.invoke_raw_binary(__sqf::binary__enablepersonturret__object__array__ret__nothing, vehicle_, params_right);
        }

        void enable_uav_connect_ability(const object &unit_, const object &uav_, bool check_all_items_) {
            game_value params_right({
                uav_,
                check_all_items_
            });

            host::functions.invoke_raw_binary(__sqf::binary__enableuavconnectability__object__array__ret__nothing, unit_, params_right);
        }

        void enable_weapon_disassembly(const object &unit_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableweapondisassembly__object__bool__ret__nothing, unit_, enable_);
        }

        game_value eval_object_argument(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref argument_) {
            return host::functions.invoke_raw_binary(__sqf::binary__evalobjectargument__control__array__ret__any, map_, { object_, argument_ });
        }

        
        game_value exec_editor_script(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref script_) {
            game_value params_right({
                object_,
                script_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__execeditorscript__control__array__ret__any, map_, params_right);
        }

        object find_cover(const object &object_, const vector3 &position_, const vector3 &hide_position_, float max_dist_, std::optional<float> min_dist_, std::optional<vector3> visible_position_, std::optional<object> ignore_object_) {
            auto_array<game_value> params_right({
                position_,
                hide_position_,
                max_dist_
            });
           
            if (min_dist_.has_value()) params_right.push_back(*min_dist_);
            if (visible_position_.has_value()) params_right.push_back(*visible_position_);
            if (ignore_object_.has_value()) params_right.push_back(*ignore_object_);

            return host::functions.invoke_raw_binary(__sqf::binary__findcover__object__array__ret__object, object_, std::move(params_right));
        }

        /*             
        #TODO: Find out about the usage of this command
        binary__findeditorobject__control__array__ret__string
        binary__findeditorobject__control__any__ret__string
        
        sqf_return_string find_editor_object(const control &map_, const ) {
            return host::functions.invoke_raw_binary(__sqf::binary__findeditorobject__control__array__ret__string, object_, std::move(params_right));
        }
        */

        vector3 find_empty_position(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float min_distance_, float max_distance_, std::optional<std::string> vehicle_type_) {
            auto_array<game_value> params_right({
                min_distance_,
                max_distance_
            });

            if (vehicle_type_.has_value()) params_right.push_back(*vehicle_type_);

            if (center_.index() == 0) {
                return host::functions.invoke_raw_binary(__sqf::binary__findemptyposition__array__array__ret__array, std::get<0>(center_).get(), std::move(params_right));
            }
            return host::functions.invoke_raw_binary(__sqf::binary__findemptyposition__array__array__ret__array, std::get<1>(center_).get(), std::move(params_right));
        }



        object find_nearest_enemy(const object &unit_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_) {
            if (position_.index() == 0) {
                return host::functions.invoke_raw_binary(__sqf::binary__findnearestenemy__object__object_array__ret__object, unit_, std::get<0>(position_).get());
            }
            return host::functions.invoke_raw_binary(__sqf::binary__findnearestenemy__object__object_array__ret__object, unit_, std::get<1>(position_).get());
        }

        object find_nearest_enemy(const object &unit_,const object &object_) {
            return host::functions.invoke_raw_binary(__sqf::binary__findnearestenemy__object__object_array__ret__object, unit_, object_);
        }

        void fire(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref mode_, sqf_string_const_ref magazine_) {
            game_value params_right({
                muzzle_,
                mode_,
                magazine_
            });

            host::functions.invoke_raw_binary(__sqf::binary__fire__object__array__ret__nothing, unit_, params_right);
        }

        bool fire_at_target(const object &unit_, const object &target_, std::optional<std::string> muzzle_) {
            auto_array<game_value> params_right({
                target_
            });

            if (muzzle_.has_value()) {
                params_right.push_back(*muzzle_);
            }

            return host::functions.invoke_raw_binary(__sqf::binary__fireattarget__object__array__ret__bool, unit_, std::move(params_right));
        }

        void fly_in_height_asl(const object &aircraft_, float height_careless_safe_aware_, float height_combat_, float height_stealth_) {
            game_value params_right({
                height_careless_safe_aware_,
                height_combat_,
                height_stealth_
            });
            
            host::functions.invoke_raw_binary(__sqf::binary__flyinheightasl__object__array__ret__nothing, aircraft_, params_right);
        }

        void force_follow_road(const object &vehicle_, bool follow_) {
            host::functions.invoke_raw_binary(__sqf::binary__forcefollowroad__object__bool__ret__nothing, vehicle_, follow_);
        }

        void force_weapon_fire(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref fire_mode_) {
            game_value params_right({
                muzzle_,
                fire_mode_
            });

            host::functions.invoke_raw_binary(__sqf::binary__forceweaponfire__object__array__ret__nothing, unit_, params_right);
        }





        vector3 get_hide_from(const object &unit_, const object &enemy_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethidefrom__object__object__ret__array, unit_, enemy_);
        }

        sqf_return_string get_object_argument(const control &map_, const object &object_, sqf_string_const_ref argument_) {
            game_value params_right({
                object_,
                argument_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getobjectargument__control__array__ret__string, map_, params_right);
        }

        sqf_return_string_list get_object_children(const control &map_, sqf_string_const_ref object_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_binary(__sqf::binary__getobjectchildren__control__string__ret__array, map_, object_));
        }

        
        std::variant<bool, float> get_unit_trait(const object &unit_, sqf_string_const_ref skill_name_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__getunittrait__object__string__ret__bool_scalar, unit_, skill_name_);
        
            if (res.type() == game_data_bool::type_def) {
                return static_cast<bool>(res);
            }
            return static_cast<float>(res);
        }

        void glance_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> unit_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_) {
            game_value param_left;
            game_value param_right;
            
            if (unit_.index() == 0) {
                param_left = std::get<0>(unit_).get();
            } else {
                auto_array<game_value> units({ std::get<1>(unit_).get().begin(), std::get<1>(unit_).get().end() });

                param_left = std::move(units);
            }
            if (target_.index() == 0) {
                param_right = std::get<0>(target_).get();
            } else {
                param_right = std::get<1>(target_).get();
            }
            
            host::functions.invoke_raw_binary(__sqf::binary__glanceat__object_array__object_array__ret__nothing, param_left, param_right);
        }



        void hide_selection(const object &object_, sqf_string_const_ref selection_, bool hide_) {
            game_value params_right({
                selection_,
                hide_
            });

            host::functions.invoke_raw_binary(__sqf::binary__hideselection__object__array__ret__nothing, object_, params_right);
        }

        

        bool in_polygon(const vector3 &position_, const std::vector<vector3> &polygon_) {
            auto_array<game_value> polygon({ polygon_.begin(), polygon_.end() });

            return host::functions.invoke_raw_binary(__sqf::binary__inpolygon__array__array__ret__bool, position_, std::move(polygon));
        }

        

        sqf_return_string insert_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &value_, sqf_string_list_const_ref values_, sqf_string_const_ref sub_type_) {
            game_value params_right({
                type_,
                value_,
                std::move(auto_array<game_value>({values_.begin(), values_.end()})),
                sub_type_
            });
            
            return host::functions.invoke_raw_binary(__sqf::binary__inserteditorobject__control__array__ret__string, map_, params_right);
        }



        bool is_uav_connectable(const object &unit_, const object &uav_, bool check_all_items_) {
            game_value params_right({
                uav_,
                check_all_items_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__isuavconnectable__object__array__ret__bool, unit_, params_right);
        }

        void leave_vehicle(const object &unit_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__leavevehicle__object__object__ret__nothing, unit_, vehicle_);
        }

        

        //#TODO: Find out if the return type is correct
        sqf_return_string_list list_objects(const control &map_, sqf_string_const_ref type_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_binary(__sqf::binary__listobjects__control__string__ret__array, map_, type_));
        }

        void lock_camera_to(const object &vehicle_, const object &target_, const std::vector<int> &turret_path_) {
            game_value params_right({
                target_,
                std::move(auto_array<game_value>({turret_path_.begin(),turret_path_.end()}))
            });

            host::functions.invoke_raw_binary(__sqf::binary__lockcamerato__object__array__ret__nothing, vehicle_, params_right);
        }

        void lock_cargo(const object &vehicle_, int index_, bool lock_) {
            game_value params_right({
                index_,
                lock_
            });

            host::functions.invoke_raw_binary(__sqf::binary__lockcargo__object__array__ret__nothing, vehicle_, params_right);
        }

        bool locked_turret(const object &vehicle_, const std::vector<int> &turret_path_) {
            auto_array<game_value> turret_path({ turret_path_.begin(),turret_path_.end() });

            return host::functions.invoke_raw_binary(__sqf::binary__lockedturret__object__array__ret__bool, vehicle_, std::move(turret_path));
        }

        void lock_turret(const object &vehicle_, const std::vector<int> &turret_path_, bool lock_) {
            game_value params_right({
                std::move(auto_array<game_value>({ turret_path_.begin(),turret_path_.end() })),
                lock_
            });

            host::functions.invoke_raw_binary(__sqf::binary__lockturret__object__array__ret__nothing, vehicle_, params_right);
        }

        

        void look_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> units_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_) {
            game_value param_left;
            game_value param_right;

            switch (units_.index()) {
                case 0: param_left = std::get<0>(units_).get(); break;
                case 1: param_left = std::move(auto_array<game_value>({ std::get<1>(units_).get().begin(),std::get<1>(units_).get().end() })); break;
            }

            switch (target_.index()) {
                case 0: param_right = std::get<0>(target_).get(); break;
                case 1: param_right = std::get<1>(target_).get(); break;
            }
            
            host::functions.invoke_raw_binary(__sqf::binary__lookat__object_array__object_array__ret__nothing, param_left, param_right);
        }






        
        int nmenu_items(const control &map_, sqf_string_const_ref menu_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__nmenuitems__control__string_scalar__ret__scalar, map_, menu_name_);
        }

        int nmenu_items(const control &map_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__nmenuitems__control__string_scalar__ret__scalar, map_, index_);
        }

        game_value on_double_click(const control &map_, sqf_string_const_ref command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ondoubleclick__control__string__ret__any, map_, command_);
        }

        void on_map_single_click(const game_value &params_, std::variant<sqf_string_const_ref_wrapper, std::reference_wrapper<const code>> command_) {
            game_value param_right;
            switch (command_.index()) {
                case 0: param_right = std::get<0>(command_).get(); break;
                case 1: param_right = std::get<1>(command_).get(); break;
            }
            
            host::functions.invoke_raw_binary(__sqf::binary__onmapsingleclick__any__code_string__ret__nothing, params_, param_right);
        }

        game_value on_show_new_object(const object &control_, sqf_string_const_ref command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__onshownewobject__control__string__ret__any, control_, command_);
        }

        void order_get_in(const std::vector<object> &units_, bool order_) {
            auto_array<game_value> units({ units_.begin(),units_.end() });

            host::functions.invoke_raw_binary(__sqf::binary__ordergetin__array__bool__ret__nothing, std::move(units), order_);
        }

        //#TODO: Replace &settings_ with the right pp_effect_parameters
        

        void remove_event_handler(const object &object_, sqf_string_const_ref event_, int index_) {
            game_value params_right({
                event_,
                index_
            });

            host::functions.invoke_raw_binary(__sqf::binary__removeeventhandler__object__array__ret__nothing, object_, params_right);
        }

        void remove_owned_mine(const object &unit_, const object &mine_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeownedmine__object__object__ret__nothing, unit_, mine_);
        }



        void respawn_vehicle(const object &vehicle_, float delay_, int count_) {
            game_value params_right({
                delay_,
                count_
            });

            host::functions.invoke_raw_binary(__sqf::binary__respawnvehicle__object__array__ret__nothing, vehicle_, params_right);
        }

        void reveal(std::variant<object, group> &unit_, const object &target_) {
            game_value param_left;
            switch (unit_.index()) {
                case 0: param_left = std::move(std::get<0>(unit_)); break;
                case 1: param_left = std::move(std::get<1>(unit_)); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__reveal__object_group__object__ret__nothing, param_left, target_);
        }

        void reveal(std::variant<object, group> &unit_, const std::vector<object> &targets_) {
            auto_array<game_value> targets({ targets_.begin(),targets_.end() });
            
            game_value param_left;
            switch (unit_.index()) {
                case 0: param_left = std::move(std::get<0>(unit_)); break;
                case 1: param_left = std::move(std::get<1>(unit_)); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__reveal__object_group__array__ret__nothing, param_left, std::move(targets));
        }

        game_value select_editor_object(const control &map_, sqf_string_const_ref object_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selecteditorobject__control__string__ret__any, map_, object_);
        }

        void select_weapon_turret(const object & vec_, sqf_string_const_ref weapon_, const std::vector<int>& turretPath_) {
            auto_array<game_value> turret_path_(turretPath_.begin(), turretPath_.end());
            host::functions.invoke_raw_binary(__sqf::binary__selectweaponturret__object__array__ret__nothing, vec_, { weapon_ , std::move(turret_path_) });
        }

        rv_text set_attributes(const rv_text &text_, const std::vector<std::pair<std::string, std::variant<rv_text, sqf_string_const_ref_wrapper>>> &attributes_) {
            auto_array<game_value> attributes;

            for (auto& it : attributes_) {
                attributes.push_back(it.first);
                if (it.second.index() == 0)
                    attributes.push_back(std::get<0>(it.second));
                else
                    attributes.push_back(std::get<1>(it.second).get());
            };

            return host::functions.invoke_raw_binary(__sqf::binary__setattributes__text_string__array__ret__text, text_, std::move(attributes));
        }

        void set_behaviour(std::variant<group, object> group_, sqf_string_const_ref behaviour_) {
            if (group_.index() == 0)
                host::functions.invoke_raw_binary(__sqf::binary__setbehaviour__object_group__string__ret__nothing, std::get<0>(group_), behaviour_); return;
            host::functions.invoke_raw_binary(__sqf::binary__setbehaviour__object_group__string__ret__nothing, std::get<1>(group_), behaviour_);
        }

        void set_captive(const object & object_, bool status) {
            host::functions.invoke_raw_binary(__sqf::binary__setcaptive__object__bool_scalar__ret__nothing, object_, status);
        }

        void set_captive(const object & object_, float status) {
            host::functions.invoke_raw_binary(__sqf::binary__setcaptive__object__bool_scalar__ret__nothing, object_, status);
        }

        void set_center_of_mass(const object& object_, const vector3& offset_, float time_ /*= 0.f*/) {
            if (time_ == 0.f)
                host::functions.invoke_raw_binary(__sqf::binary__setcenterofmass__object__array__ret__nothing, object_, offset_);
            else
                host::functions.invoke_raw_binary(__sqf::binary__setcenterofmass__object__array__ret__nothing, object_, { offset_, time_ });
        }

        void set_combat_mode(std::variant<group, object> group_, sqf_string_const_ref mode_) {
            if (group_.index() == 0)
                host::functions.invoke_raw_binary(__sqf::binary__setcombatmode__object_group__string__ret__nothing, std::get<0>(group_), mode_); return;
            host::functions.invoke_raw_binary(__sqf::binary__setcombatmode__object_group__string__ret__nothing, std::get<1>(group_), mode_);
        }

        void set_formation(std::variant<group, object> group_, sqf_string_const_ref mode_) {
            if (group_.index() == 0)
                host::functions.invoke_raw_binary(__sqf::binary__setformation__object_group__string__ret__nothing, std::get<0>(group_), mode_); return;
            host::functions.invoke_raw_binary(__sqf::binary__setformation__object_group__string__ret__nothing, std::get<1>(group_), mode_);
        }

        void set_convoy_seperation(const object& object_, float distance_) {
            host::functions.invoke_raw_binary(__sqf::binary__setconvoyseparation__object__scalar__ret__nothing, object_, distance_);
        }

        
        void set_destination(const object& object_, const vector3& position_, sqf_string_const_ref planning_mode_, bool force_replan) {
            host::functions.invoke_raw_binary(__sqf::binary__setdestination__object__array__ret__nothing, object_, { position_, planning_mode_, force_replan });
        }

        void set_drive_on_path(const object& object_, const std::vector<vector3>& points_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdriveonpath__object__array__ret__nothing, object_, auto_array<game_value>(points_.begin(), points_.end()));
        }

        bool set_feature_type(const object& object_, feature_type type_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setfeaturetype__object__scalar__ret__bool, object_, static_cast<int>(type_));
        }

        float set_flag_animation_phase(const object& object_, float phase) {
            return host::functions.invoke_raw_binary(__sqf::binary__setflaganimationphase__object__scalar__ret__nothing, object_, phase);
        }

        void set_form_dir(std::variant<group, object> group_, float heading_) {
            if (group_.index() == 0)
                host::functions.invoke_raw_binary(__sqf::binary__setformdir__object_group__scalar__ret__nothing, std::get<0>(group_), heading_); return;
            host::functions.invoke_raw_binary(__sqf::binary__setformdir__object_group__scalar__ret__nothing, std::get<1>(group_), heading_);
        }


        void set_editor_object_scope(const control &map_, sqf_string_list_const_ref objects_, sqf_string_const_ref editor_type_, sqf_string_const_ref condition_, sqf_string_const_ref scope_, bool sub_ordinates_also_) {
            game_value params_right({
                std::move(auto_array<game_value>(objects_.begin(), objects_.end())),
                editor_type_,
                condition_,
                scope_,
                sub_ordinates_also_
            });
            
            host::functions.invoke_raw_binary(__sqf::binary__seteditorobjectscope__control__array__ret__nothing, map_, params_right);
        }

        bool set_feature_type(const object &object_, int type_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setfeaturetype__object__scalar__ret__bool, object_, type_);
        }

        void set_flag_animation_phase(const object &flag_, float &animation_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflaganimationphase__object__scalar__ret__nothing, flag_, animation_phase_);
        }

        void set_flag_owner(const object &flag_, const object &owner_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflagowner__object__object__ret__nothing, flag_, owner_);
        }

        

        void set_hide_behind(const object &unit_, const object &object_where_hide_, const vector3 &hide_position_) {
            host::functions.invoke_raw_binary(__sqf::binary__sethidebehind__object__array__ret__nothing, unit_, { object_where_hide_,hide_position_ });
        }



        void set_light_ambient(const object &light_, float r_, float g_, float b_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightambient__object__array__ret__nothing, light_, { r_,g_,b_ });
        }

        void set_light_attenuation(const object &light_, float start_, float constant_, float linear_, float quadratic_, float hard_limit_start_, float hard_limit_end_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightattenuation__object__array__ret__nothing, light_, { start_,start_,constant_,linear_,quadratic_,hard_limit_start_,hard_limit_end_ });
        }

        void set_light_color(const object &light_, float r_, float g_, float b_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightcolor__object__array__ret__nothing, light_, { r_,g_,b_ });
        }

        void set_mass(const object &object_, float mass_, std::optional<float> time_) {
            if(time_.has_value())
                host::functions.invoke_raw_binary(__sqf::binary__setmass__object__scalar_array__ret__nothing, object_, { mass_, *time_ });
            host::functions.invoke_raw_binary(__sqf::binary__setmass__object__scalar_array__ret__nothing, object_, mass_);
        }

        void set_name(const object &unit_, sqf_string_const_ref name_, sqf_string_const_ref first_name_, sqf_string_const_ref last_name_) {
            host::functions.invoke_raw_binary(__sqf::binary__setname__object__array__ret__nothing, unit_, { name_, first_name_, last_name_ });
        }



        game_value set_object_arguments(const control &map_, sqf_string_const_ref object_, sqf_string_list_const_ref values_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setobjectarguments__control__array__ret__any, map_, {object_, std::move(auto_array<game_value>(values_.begin(), values_.end()))});
        }

        void set_object_material(const object &object_, int index_, sqf_string_const_ref material_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjectmaterial__object__array__ret__nothing, object_, { index_, material_ });
        }

        void set_object_material_global(const object &object_, int index_, sqf_string_const_ref material_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjectmaterialglobal__object__array__ret__nothing, object_, { index_, material_ });
        }

        void set_object_proxy(const control &map_, sqf_string_const_ref object_, const object &proxy_object_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjectproxy__control__array__ret__any, map_, { object_, proxy_object_ });
        }

        void set_object_texture(const object &object_, int index_, sqf_string_const_ref texture_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjecttexture__object__array__ret__nothing, object_, { index_, texture_ });
        }

        void set_object_texture_global(const object &object_, int index_, sqf_string_const_ref texture_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjecttextureglobal__object__array__ret__nothing, object_, { index_, texture_ });
        }

        //#TODO: Implement with this massive amount of params
        void set_particle_params() {
            //host::functions.invoke_raw_binary(__sqf::binary__setparticleparams__object__array__ret__nothing, time_, overcast_value_);
        }

        void set_pilot_camera_direction(const object &vehicle_, const vector3 &direction_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpilotcameradirection__object__array__ret__nothing, vehicle_, direction_);
        }

        void set_pilot_camera_rotation(const object &vehicle_, float yaw_, float pitch_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpilotcamerarotation__object__array__ret__nothing, vehicle_, { yaw_,pitch_ });
        }

        bool set_pilot_camera_target(const object &vehicle_, std::variant<std::reference_wrapper<const object>, const vector3> target_) {
            if (target_.index() == 0)
                return host::functions.invoke_raw_binary(__sqf::binary__setpilotcameratarget__object__object_array__ret__bool, vehicle_, std::get<0>(target_));
            return host::functions.invoke_raw_binary(__sqf::binary__setpilotcameratarget__object__object_array__ret__bool, vehicle_, std::get<1>(target_));
        }



       

        void set_shot_parents(const object &projectile_, const object &vehicle_, const object &instigator_) {
            host::functions.invoke_raw_binary(__sqf::binary__setshotparents__object__array__ret__nothing, projectile_, { vehicle_, instigator_ });
        }
        
       









        //#TODO: Implement set_unit_loadout variations, I skipped it. @jonpas
        //binary__setunitloadout__object__array__ret__nothing
        //binary__setunitloadout__object__string__ret__nothing
        //binary__setunitloadout__object__config__ret__nothing

        void set_unit_trait(const object &unit_, sqf_string_const_ref skill_name_, std::variant<bool, float> value_, bool is_custom_) {
            if (value_.index() == 0)
                host::functions.invoke_raw_binary(__sqf::binary__setunittrait__object__array__ret__nothing, unit_, { skill_name_, std::get<0>(value_), is_custom_ }); return;
            host::functions.invoke_raw_binary(__sqf::binary__setunittrait__object__array__ret__nothing, unit_, { skill_name_, std::get<1>(value_), is_custom_ });
        }

        //#TODO: Find out which parameters should be on the right side of the command
        void set_unit_load_in_combat(const object &unit_, const game_value &params_right_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunloadincombat__object__array__ret__nothing, unit_, params_right_);
        }
        
        void set_user_action_text(const object &object_, int action_index_, std::variant<const std::string, const rv_text> text_menu_, std::variant<const std::string, const rv_text> text_window_background_, std::variant<const std::string, const rv_text> text_window_foreground_) {
            auto_array<game_value> params_right({
                action_index_
            });

            if (text_menu_.index() == 0) {
                params_right.push_back(std::get<0>(text_menu_));
            }
            else {
                params_right.push_back(std::get<1>(text_menu_));
            }

            if (text_window_background_.index() == 0) {
                params_right.push_back(std::get<0>(text_window_background_));
            }
            else {
                params_right.push_back(std::get<1>(text_window_background_));
            }

            if (text_window_foreground_.index() == 0) {
                params_right.push_back(std::get<0>(text_window_foreground_));
            }
            else {
                params_right.push_back(std::get<1>(text_window_foreground_));
            }
         
            
            host::functions.invoke_raw_binary(__sqf::binary__setuseractiontext__object__array__ret__nothing, object_, std::move(params_right));
        }



        //#TODO: Find out which params are to the right
        void set_vehicle_ti_parts(const object &vehicle_, const game_value &params_right_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicletipars__object__array__ret__nothing, vehicle_, params_right_);
        }

        void set_visible_if_tree_collapsed(const control &map_, sqf_string_const_ref object_, bool visible_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvisibleiftreecollapsed__control__array__ret__nothing, map_, { object_, visible_ });
        }

        void set_weapon_reloading_time(const object &vehicle_, const object &gunner_, sqf_string_const_ref muzzle_class_, float reload_time_) {
            host::functions.invoke_raw_binary(__sqf::binary__setweaponreloadingtime__object__array__ret__bool, vehicle_, { gunner_, muzzle_class_, reload_time_ });
        }

        

        //#TODO: Find out which params are to the right
        game_value shown_editor_object(const control &map_, const game_value &params_right_) {
            return host::functions.invoke_raw_binary(__sqf::binary__showneweditorobject__control__array__ret__any, map_, params_right_);
        }




        void swim_in_depth(const object &unit_, float depth_) {
            host::functions.invoke_raw_binary(__sqf::binary__swimindepth__object__scalar__ret__nothing, unit_, depth_);
        }

        void synchronize_objects_add(const object &unit_, const std::vector<object> &objects_) {
            host::functions.invoke_raw_binary(__sqf::binary__synchronizeobjectsadd__object__array__ret__nothing, unit_, std::move(auto_array<game_value>(objects_.begin(), objects_.end())));
        }

        void synchronize_objects_remove(const object &unit_, const std::vector<object> &objects_) {
            host::functions.invoke_raw_binary(__sqf::binary__synchronizeobjectsremove__object__array__ret__nothing, unit_, std::move(auto_array<game_value>(objects_.begin(), objects_.end())));
        }

        rv_target_knowledge target_knowledge(const object &unit_, const object &target_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__targetknowledge__object__object__ret__array, unit_, target_);

            return rv_target_knowledge({ res[0], res[1], res[2], res[3], res[4], res[5], res[6] });
        }

        //#TODO: Find out how this function works
        game_value targets_aggregate(const object &speaker_, const side &side_, const object &unit_, const vector3 &place_, float time_, game_value &candidates_) {
            return host::functions.invoke_raw_binary(__sqf::binary__targetsaggregate__array__array__ret__array, { speaker_, side_, unit_, place_, time_ }, candidates_);
        }

        rv_query_target targets_query(const object &unit_, const object &target_ignore_, const side &target_side, sqf_string_const_ref target_type_, const vector3 &target_position_, float target_max_age_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__targetsquery__object__array__ret__array, unit_, { target_ignore_, target_side, target_type_, target_position_, target_max_age_ });
        
            return rv_query_target({ res[0], res[1], res[2], res[3], res[4], res[5] });
        }

        object turret_unit(const object &vehicle_, const std::vector<int> &turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__turretunit__object__array__ret__object, vehicle_, std::move(auto_array<game_value>(turret_path_.begin(), turret_path_.end())));
        }

        
        void update_menu_item(const control &map_, int menu_item_index_, sqf_string_const_ref text_, sqf_string_const_ref command_) {
            host::functions.invoke_raw_binary(__sqf::binary__updatemenuitem__control__array__ret__nothing, map_, { menu_item_index_, text_ , command_ });
        }

       

        sqf_return_string_list weapons_turret(const object &vehicle_, const std::vector<int> &turret_path_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_binary(__sqf::binary__weaponsturret__object__array__ret__array, vehicle_, std::move(auto_array<game_value>(turret_path_.begin(), turret_path_.end()))));
        }






        int airplane_throttle(const object &airplane_) {
            return host::functions.invoke_raw_unary(__sqf::unary__airplanethrottle__object__ret__scalar, airplane_);
        }

        

        sqf_return_string get_forced_flag_texture(const object &flag_pole_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getforcedflagtexture__object__ret__string, flag_pole_);
        }

        sqf_return_string_list get_pylon_magazines(const object &vehicle_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__getpylonmagazines__object__ret__array, vehicle_));
        }

        bool is_damage_allowed(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isdamageallowed__object__ret__bool, object_);
        }

        void lb_sort(const control &control_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsort__control__ret__nothing, control_);
        }

        void lb_sort(const control &control_, sqf_string_const_ref sort_order_) {
            host::functions.invoke_raw_unary(__sqf::unary__lbsort__array__ret__nothing, { control_, sort_order_ });
        }



        bool vehicle_receive_remote_targets(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vehiclereceiveremotetargets__object__ret__bool, vehicle_);
        }

        bool vehicle_report_own_position(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vehiclereportownposition__object__ret__bool, vehicle_);
        }

        bool vehicle_report_remote_targets(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vehiclereportremotetargets__object__ret__bool, vehicle_);
        }

        int ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ammoonpylon__object__string_scalar__ret__scalar, vehicle_, pylon_name_);
        }

        int ammo_on_pylon(const object &vehicle_, int pylon_index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ammoonpylon__object__string_scalar__ret__scalar, vehicle_, pylon_index_);
        }

        void animate_bay(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatebay__object__array__ret__nothing, vehicle_, { pylon_name_, anim_phase_ });
        }

        void animate_bay(const object &vehicle_, int pylon_index_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatebay__object__array__ret__nothing, vehicle_, { pylon_index_, anim_phase_ });
        }

        void animate_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatepylon__object__array__ret__nothing, vehicle_, { pylon_name_, anim_phase_ });
        }

        void animate_pylon(const object &vehicle_, int pylon_index_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatepylon__object__array__ret__nothing, vehicle_, { pylon_index_, anim_phase_ });
        }

        void confirm_sensor_target(const object &vehicle_, const side &side_, bool is_confirmed_) {
            host::functions.invoke_raw_binary(__sqf::binary__confirmsensortarget__object__array__ret__nothing, vehicle_, { side_, is_confirmed_ });
        }

        

        void force_flag_texture(const object &object_, sqf_string_const_ref texture_) {
            host::functions.invoke_raw_binary(__sqf::binary__forceflagtexture__object__string__ret__nothing, object_, texture_);
        }

        void forget_target(const object &unit_, const object target_) {
            host::functions.invoke_raw_binary(__sqf::binary__forgettarget__object_group__object__ret__nothing, unit_, target_);
        }

        void forget_target(const group &group_, const object target_) {
            host::functions.invoke_raw_binary(__sqf::binary__forgettarget__object_group__object__ret__nothing, group_, target_);
        }

        bool is_sensor_target_confirmed(const object &object_, const side &side_) {
            return host::functions.invoke_raw_binary(__sqf::binary__issensortargetconfirmed__object__side__ret__bool, object_, side_);
        }



        void report_remote_target(const side &side_, const object &target_, float time_) {
            host::functions.invoke_raw_binary(__sqf::binary__reportremotetarget__side__array__ret__nothing, side_, { target_, time_ });
        }

        void set_air_plane_throttle(const object &airplane_, float throttle_) {
            host::functions.invoke_raw_binary(__sqf::binary__setairplanethrottle__object__scalar__ret__nothing, airplane_, throttle_);
        }

        void set_ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, int ammo_count_) {
            host::functions.invoke_raw_binary(__sqf::binary__setammoonpylon__object__array__ret__nothing, vehicle_, { pylon_name_, ammo_count_ });
        }

        void set_ammo_on_pylon(const object &vehicle_, int pylon_index_, int ammo_count_) {
            host::functions.invoke_raw_binary(__sqf::binary__setammoonpylon__object__array__ret__nothing, vehicle_, { pylon_index_, ammo_count_ });
        }

        //#TODO: Find out what the right parameter is
        bool set_pylon_loadout(const object &object_, game_value param_right) {
            return host::functions.invoke_raw_binary(__sqf::binary__setpylonloadout__object__array__ret__bool, object_, param_right);
        }

        void set_pylons_priority(const object &object_, const std::vector<int> &priorities_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpylonspriority__object__array__ret__nothing, object_, auto_array<game_value>(priorities_.begin(), priorities_.end()));
        }

        void set_user_mfd_value(const object &object_, int index_, float value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setusermfdvalue__object__array__ret__nothing, object_, { index_, value_ });
        }

        void set_vehicle_radar(const object &vehicle_, int rules_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicleradar__object__scalar__ret__nothing, vehicle_, rules_);
        }

        void set_vehicle_receive_remote_targets(const object &vehicle_, bool receive_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclereceiveremotetargets__object__bool__ret__nothing, vehicle_, receive_);
        }

        void set_vehicle_report_own_position(const object &vehicle_, bool report_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclereportownposition__object__bool__ret__nothing, vehicle_, report_);
        }

        void set_vehicle_report_remote_targets(const object &vehicle_, bool report_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclereportremotetargets__object__bool__ret__nothing, vehicle_, report_);
        }

        void targets(const object &unit_, std::optional<bool> enemy_only_, std::optional<float> max_distance_, std::optional<std::vector<side>> sides_, std::optional<float> max_age_, std::optional<std::variant<std::reference_wrapper<vector2>, std::reference_wrapper<vector3>>> alternate_center_) {
            auto_array<game_value> params_right;
            
            if (enemy_only_.has_value()) params_right.push_back(*enemy_only_); else params_right.push_back(game_value());
            if (max_distance_.has_value()) params_right.push_back(*max_distance_); else params_right.push_back(game_value());
            if (sides_.has_value()) params_right.push_back(auto_array<game_value>((*sides_).begin(), (*sides_).end())); else params_right.push_back(game_value());
            if (max_age_.has_value()) params_right.push_back(*max_age_); else params_right.push_back(game_value());
            if (alternate_center_.has_value()) {
                if ((*alternate_center_).index() == 0) 
                    params_right.push_back(std::get<0>(*alternate_center_).get());
                else
                    params_right.push_back(std::get<1>(*alternate_center_).get());
            }
            else params_right.push_back(game_value());

            host::functions.invoke_raw_binary(__sqf::binary__targets__object__array__ret__array, unit_, std::move(params_right));
        }

        sqf_return_string endl() {
            return host::functions.invoke_raw_nular(__sqf::nular__endl__ret__string);
        }

        rv_cursor_object_params get_cursor_object_params() {
            game_value res = host::functions.invoke_raw_nular(__sqf::nular__getcursorobjectparams__ret__array);

            return rv_cursor_object_params({ res[0], res[1], res[2] });
        }

    }
}
