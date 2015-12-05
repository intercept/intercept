#include "chat.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        float random(float max_) {
            game_value rand_val = host::functions.invoke_raw_unary(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, game_value_number(max_));
            float rand = ((game_data_number *)rand_val.data)->number;
            host::functions.free_value(&rand_val);
            return rand;
        }

        float acc_time() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__acctime__ret__scalar);
        }

        std::vector<std::string> activated_addons() {
            return __helpers::_nular_strings(client::__sqf::nular__activatedaddons__ret__array);
        }

        std::vector<team_member> agents() {
            return __helpers::_nular_team_members(client::__sqf::nular__agents__ret__array);
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

        object curatorcamera() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__curatorcamera__ret__object);
        }

        object curatormouseover() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__curatormouseover__ret__object);
        }

        std::vector<object> curatorselected() {
            return __helpers::all_objects(client::__sqf::nular__curatorselected__ret__array);
        }

        std::string current3denoperation() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__current3denoperation__ret__string);
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

        bool didjip() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__didjip__ret__bool);
        }

        float difficulty() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__difficulty__ret__scalar);
        }

        bool difficultyenabledrtd() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__difficultyenabledrtd__ret__bool);
        }

        void disabledebriefingstats() {
            __helpers::__empty_nular(client::__sqf::nular__disabledebriefingstats__ret__nothing);
        }

        void disableserialization() {
            __helpers::__empty_nular(client::__sqf::nular__disableserialization__ret__nothing);
        }

        display displaynull() {
            return __helpers::__retrieve_nular_display(client::__sqf::nular__displaynull__ret__display);
        }

        float distributionregion() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__distributionregion__ret__scalar);
        }

        side east() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__east__ret__side);
        }

        void enableenddialog() {
            __helpers::__empty_nular(client::__sqf::nular__enableenddialog__ret__nothing);
        }

        void endloadingscreen() {
            __helpers::__empty_nular(client::__sqf::nular__endloadingscreen__ret__nothing);
        }

        float estimatedendservertime() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__estimatedendservertime__ret__scalar);
        }

        void exit() {
            __helpers::__empty_nular(client::__sqf::nular__exit__ret__nothing);
        }

        void finishmissioninit() {
            __helpers::__empty_nular(client::__sqf::nular__finishmissioninit__ret__nothing);
        }

        bool fog() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__fog__ret__scalar);
        }

        float fogforecast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__fogforecast__ret__scalar);
        }

        // TODO std::vector<float> fogparams();

        void forceend() {
            __helpers::__empty_nular(client::__sqf::nular__forceend__ret__nothing);
        }

        void forceweatherchange() {
            __helpers::__empty_nular(client::__sqf::nular__forceweatherchange__ret__nothing);
        }

        bool freelook() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__freelook__ret__bool);
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

        std::string getclientstate() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__getclientstate__ret__string);
        }

        float getelevationoffset() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__getelevationoffset__ret__scalar);
        }

        // TODO std::array<float, 2> getmouseposition();
        // TODO std::array<float, 2> getobjectviewdistance();

        bool getremotesensorsdisabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__getremotesensorsdisabled__ret__bool);
        }

        // TODO std::array<float, 6> getresolution();
        float getshadowdistance() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__getshadowdistance__ret__scalar);
        }

        float gettotaldlcusagetime() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__gettotaldlcusagetime__ret__scalar);
        }

        bool groupiconselectable() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__groupiconselectable__ret__bool);
        }

        // TODO std::array<bool, 2> groupiconsvisible();

        group grpnull() {
            return __helpers::__retrieve_nular_group(client::__sqf::nular__grpnull__ret__group);
        }

        float gusts() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__gusts__ret__scalar);
        }

        void halt() {
            __helpers::__empty_nular(client::__sqf::nular__halt__ret__nothing);
        }

        bool hasinterface() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__hasinterface__ret__bool);
        }

        bool hcshownbar() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__hcshownbar__ret__bool);
        }

        float humidity() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__humidity__ret__scalar);
        }

        side independent() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__independent__ret__side);
        }

        void initambientlife() {
            __helpers::__empty_nular(client::__sqf::nular__initambientlife__ret__nothing);
        }

        bool is3den() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3den__ret__bool);
        }

        bool is3denmultiplayer() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3denmultiplayer__ret__bool);
        }

        bool isautotest() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isautotest__ret__bool);
        }

        bool isdedicated() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isdedicated__ret__bool);
        }

        bool isfilepatchingenabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isfilepatchingenabled__ret__bool);
        }

        bool isinstructorfigureenabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isinstructorfigureenabled__ret__bool);
        }

        bool ismultiplayer() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__ismultiplayer__ret__bool);
        }

        bool ispipenabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__ispipenabled__ret__bool);
        }

        bool isserver() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isserver__ret__bool);
        }

        bool issteammission() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__issteammission__ret__bool);
        }

        bool isstreamfriendlyuienabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isstreamfriendlyuienabled__ret__bool);
        }

        bool isstressdamageenabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__isstressdamageenabled__ret__bool);
        }

        bool istuthintsenabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__istuthintsenabled__ret__bool);
        }

        std::string language() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__language__ret__string);
        }

        // TODO std::vector<std::array<std::string, 2>> librarycredits();

        std::vector<std::string> librarydisclaimers() {
            return __helpers::_nular_strings(client::__sqf::nular__librarydisclaimers__ret__array);
        }

        float lightnings() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__lightnings__ret__scalar);
        }

        text linebreak() {
            return __helpers::__retrieve_nular_text(client::__sqf::nular__linebreak__ret__text);
        }

        void loadgame() {
            __helpers::__empty_nular(client::__sqf::nular__loadgame__ret__nothing);
        }

        location locationnull() {
            return __helpers::__retrieve_nular_location(client::__sqf::nular__locationnull__ret__location);
        }

        void logentities() {
            __helpers::__empty_nular(client::__sqf::nular__logentities__ret__nothing);
        }

        void mapanimclear() {
            __helpers::__empty_nular(client::__sqf::nular__mapanimclear__ret__nothing);
        }

        void mapanimcommit() {
            __helpers::__empty_nular(client::__sqf::nular__mapanimcommit__ret__nothing);
        }

        bool mapanimdone() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__mapanimdone__ret__bool);
        }

        bool markasfinishedonsteam() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__markasfinishedonsteam__ret__bool);
        }

        config missionconfigfile() {
            return __helpers::__retrieve_nular_config(client::__sqf::nular__missionconfigfile__ret__config);
        }

        float missiondifficulty() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__missiondifficulty__ret__scalar);
        }

        std::string missionname() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__missionname__ret__string);
        }

        rv_namespace missionnamespace() {
            return __helpers::__retrieve_nular_namespace(client::__sqf::nular__missionnamespace__ret__namespace);
        }

        // TODO std::array<float, 6> missionstart();

        float moonintensity() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__moonintensity__ret__scalar);
        }

        float musicvolume() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__musicvolume__ret__scalar);
        }

        float nextweatherchange() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__nextweatherchange__ret__scalar);
        }

        object objnull() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__objnull__ret__object);
        }

        void opencuratorinterface() {
            __helpers::__empty_nular(client::__sqf::nular__opencuratorinterface__ret__nothing);
        }

        side opfor() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__opfor__ret__side);
        }

        float overcast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__overcast__ret__scalar);
        }

        float overcastforecast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__overcastforecast__ret__scalar);
        }

        rv_namespace parsingnamespace() {
            return __helpers::__retrieve_nular_namespace(client::__sqf::nular__parsingnamespace__ret__namespace);
        }

        float particlesquality() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__particlesquality__ret__scalar);
        }

        float pi() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__pi__ret__scalar);
        }

        float pixelh() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__pixelh__ret__scalar);
        }

        float pixelw() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__pixelw__ret__scalar);
        }

        std::vector<object> playableunits() {
            return __helpers::all_objects(client::__sqf::nular__playableunits__ret__array);
        }

        float playerrespawntime() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__playerrespawntime__ret__scalar);
        }

        side playerside() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__playerside__ret__side);
        }

        std::string profilename() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__profilename__ret__string);
        }
        rv_namespace profilenamespace() {
            return __helpers::__retrieve_nular_namespace(client::__sqf::nular__profilenamespace__ret__namespace);
        }

        std::string profilenamesteam() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__profilenamesteam__ret__string);
        }

        float radiovolume() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__shownradio__ret__bool);
        }

        float rain() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__rain__ret__scalar);
        }

        float rainbow() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__rainbow__ret__scalar);
        }

        void resetcamshake() {
            __helpers::__empty_nular(client::__sqf::nular__resetcamshake__ret__nothing);
        }

        side resistance() {
            return __helpers::__retrieve_nular_side(client::__sqf::nular__resistance__ret__side);
        }

        bool reversedmousey() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__reversedmousey__ret__bool);
        }

        void runinitscript() {
            __helpers::__empty_nular(client::__sqf::nular__runinitscript__ret__nothing);
        }

        float save_zone_x() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezonex__ret__scalar);
        }
        float save_zone_y() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezoney__ret__scalar);
        }
        float save_zone_h() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezoneh__ret__scalar);
        }
        float save_zone_w() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezonew__ret__scalar);
        }
        float save_zone_x_abs() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__safezonexabs__ret__scalar);
        }
        float save_zone_w_abs() {
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
        bool shown_curatorcompass() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__showncuratorcompass__ret__bool);
        }
        bool shown_hud() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownhud__ret__array);
        }
        bool shown_gps() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__showngps__ret__bool);
        }
        bool shown_hud__ret__array() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownhud__ret__array);
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

        std::vector<object> switchable_units()
        {
            return __helpers::all_objects(client::__sqf::nular__switchableunits__ret__array);
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

        float abs(float value_) {
            return __number_unary_number(unary__abs__scalar_nan__ret__scalar_nan, value_);
        }

        float acos(float value_) {
            return __number_unary_number(unary__acos__scalar_nan__ret__scalar_nan, value_);
        }

        std::string action_name(std::string value_) {
            return __string_unary_string(unary__actionname__string__ret__string, value_);
        }

        void activate_key(std::string value_) {
            __empty_unary_string(unary__activatekey__string__ret__nothing, value_);
        }

        void add_switchable_unit(object value_) {
            __empty_unary_object(unary__addswitchableunit__object__ret__nothing, value_);
        }

        float air_density_rtd(float value_) {
            return __number_unary_number(unary__airdensityrtd__scalar__ret__scalar, value_);
        }

        void airport_side(float value_) {
            __empty_unary_number(unary__airportside__scalar__ret__nothing, value_);
        }

        bool alive(object value_) {
            return __bool_unary_object(unary__alive__object__ret__bool, value_);
        }

        std::string animation_state(object value_) {
            return __string_unary_object(unary__animationstate__object__ret__string, value_);
        }

        float asin(float value_) {
            return __number_unary_number(unary__asin__scalar_nan__ret__scalar_nan, value_);
        }

        bool assert(bool value_) {
            return __bool_unary_bool(unary__assert__bool__ret__bool, value_);
        }

        object assigned_commander(object value_) {
            return __object_unary_object(unary__assignedcommander__object__ret__object, value_);
        }

        object assigned_driver(object value_) {
            return __object_unary_object(unary__assigneddriver__object__ret__object, value_);
        }

        object assigned_gunner(object value_) {
            return __object_unary_object(unary__assignedgunner__object__ret__object, value_);
        }

        object assigned_target(object value_) {
            return __object_unary_object(unary__assignedtarget__object__ret__object, value_);
        }

        std::string assigned_team(object value_) {
            return __string_unary_object(unary__assignedteam__object__ret__string, value_);
        }

        object assigned_vehicle(object value_) {
            return __object_unary_object(unary__assignedvehicle__object__ret__object, value_);
        }

        float atan(float value_) {
            return __number_unary_number(unary__atan__scalar_nan__ret__scalar_nan, value_);
        }

        float atg(float value_) {
            return __number_unary_number(unary__atg__scalar_nan__ret__scalar_nan, value_);
        }

        std::string backpack(object value_) {
            return __string_unary_object(unary__backpack__object__ret__string, value_);
        }

        object backpack_container(object value_) {
            return __object_unary_object(unary__backpackcontainer__object__ret__object, value_);
        }

        std::string behaviour(object value_) {
            return __string_unary_object(unary__behaviour__object__ret__string, value_);
        }

        std::string binocular(object value_) {
            return __string_unary_object(unary__binocular__object__ret__string, value_);
        }

        void break_out(std::string value_) {
            __empty_unary_string(unary__breakout__string__ret__nothing, value_);
        }

        void break_to(std::string value_) {
            __empty_unary_string(unary__breakto__string__ret__nothing, value_);
        }

        void buldozer(bool value_) {
            __empty_unary_bool(unary__buldozer_enableroaddiag__bool__ret__nothing, value_);
        }

        bool buldozer(std::string value_) {
            return __bool_unary_string(unary__buldozer_loadnewroads__string__ret__bool, value_);
        }

        std::string button_action(control value_) {
            return __string_unary_control(unary__buttonaction__control__ret__string, value_);
        }

        std::string button_action(float value_) {
            return __string_unary_number(unary__buttonaction__scalar__ret__string, value_);
        }

        bool cam_committed(object value_) {
            return __bool_unary_object(unary__camcommitted__object__ret__bool, value_);
        }

        void cam_destroy(object value_) {
            __empty_unary_object(unary__camdestroy__object__ret__nothing, value_);
        }

        bool cam_preloaded(object value_) {
            return __bool_unary_object(unary__campreloaded__object__ret__bool, value_);
        }

        object cam_target(object value_) {
            return __object_unary_object(unary__camtarget__object__ret__object, value_);
        }

        void cam_use_nvg(bool value_) {
            __empty_unary_bool(unary__camusenvg__bool__ret__nothing, value_);
        }

        void camera_effect_enable_hud(bool value_) {
            __empty_unary_bool(unary__cameraeffectenablehud__bool__ret__nothing, value_);
        }

        float camera_interest(object value_) {
            return __number_unary_object(unary__camerainterest__object__ret__scalar, value_);
        }

        bool can_fire(object value_) {
            return __bool_unary_object(unary__canfire__object__ret__bool, value_);
        }

        bool can_move(object value_) {
            return __bool_unary_object(unary__canmove__object__ret__bool, value_);
        }

        bool can_stand(object value_) {
            return __bool_unary_object(unary__canstand__object__ret__bool, value_);
        }

        bool can_unload_in_combat(object value_) {
            return __bool_unary_object(unary__canunloadincombat__object__ret__bool, value_);
        }

        bool captive(object value_) {
            return __bool_unary_object(unary__captive__object__ret__bool, value_);
        }

        float captive_num(object value_) {
            return __number_unary_object(unary__captivenum__object__ret__scalar, value_);
        }

        bool cb_checked(control value_) {
            return __bool_unary_control(unary__cbchecked__control__ret__bool, value_);
        }

        float ceil(float value_) {
            return __number_unary_number(unary__ceil__scalar_nan__ret__scalar_nan, value_);
        }

        bool channel_enabled(float value_) {
            return __bool_unary_number(unary__channelenabled__scalar__ret__bool, value_);
        }

        bool check_aifeature(std::string value_) {
            return __bool_unary_string(unary__checkaifeature__string__ret__bool, value_);
        }

        void clear_all_items_from_backpack(object value_) {
            __empty_unary_object(unary__clearallitemsfrombackpack__object__ret__nothing, value_);
        }

        void clear_backpack_cargo(object value_) {
            __empty_unary_object(unary__clearbackpackcargo__object__ret__nothing, value_);
        }

        void clear_backpack_cargo_global(object value_) {
            __empty_unary_object(unary__clearbackpackcargoglobal__object__ret__nothing, value_);
        }

        void clear_group_icons(group value_) {
            __empty_unary_group(unary__cleargroupicons__group__ret__nothing, value_);
        }

        void clear_item_cargo(object value_) {
            __empty_unary_object(unary__clearitemcargo__object__ret__nothing, value_);
        }

        void clear_item_cargo_global(object value_) {
            __empty_unary_object(unary__clearitemcargoglobal__object__ret__nothing, value_);
        }

        void clear_magazine_cargo(object value_) {
            __empty_unary_object(unary__clearmagazinecargo__object__ret__nothing, value_);
        }

        void clear_magazine_cargo_global(object value_) {
            __empty_unary_object(unary__clearmagazinecargoglobal__object__ret__nothing, value_);
        }

        void clear_overlay(control value_) {
            __empty_unary_control(unary__clearoverlay__control__ret__nothing, value_);
        }

        void clear_weapon_cargo(object value_) {
            __empty_unary_object(unary__clearweaponcargo__object__ret__nothing, value_);
        }

        void clear_weapon_cargo_global(object value_) {
            __empty_unary_object(unary__clearweaponcargoglobal__object__ret__nothing, value_);
        }

        void close_dialog(float value_) {
            __empty_unary_number(unary__closedialog__scalar__ret__nothing, value_);
        }

        void close_overlay(control value_) {
            __empty_unary_control(unary__closeoverlay__control__ret__nothing, value_);
        }

        void collapse_object_tree(control value_) {
            __empty_unary_control(unary__collapseobjecttree__control__ret__nothing, value_);
        }

        float collective_rtd(object value_) {
            return __number_unary_object(unary__collectivertd__object__ret__scalar, value_);
        }

        object commander(object value_) {
            return __object_unary_object(unary__commander__object__ret__object, value_);
        }

        void comment(std::string value_) {
            __empty_unary_string(unary__comment__string__ret__nothing, value_);
        }

        void commit_overlay(control value_) {
            __empty_unary_control(unary__commitoverlay__control__ret__nothing, value_);
        }

        bool completed_fsm(float value_) {
            return __bool_unary_number(unary__completedfsm__scalar__ret__bool, value_);
        }

        void copy_to_clipboard(std::string value_) {
            __empty_unary_string(unary__copytoclipboard__string__ret__nothing, value_);
        }

        float cos(float value_) {
            return __number_unary_number(unary__cos__scalar_nan__ret__scalar_nan, value_);
        }

        float count(std::string value_) {
            return __number_unary_string(unary__count__string__ret__scalar, value_);
        }

        side create_center(side value_) {
            return __side_unary_side(unary__createcenter__side__ret__side, value_);
        }

        bool create_dialog(std::string value_) {
            return __bool_unary_string(unary__createdialog__string__ret__bool, value_);
        }

        group create_group(side value_) {
            return __group_unary_side(unary__creategroup__side__ret__group, value_);
        }

        void create_vehicle_crew(object value_) {
            __empty_unary_object(unary__createvehiclecrew__object__ret__nothing, value_);
        }

        void ctrl_activate(control value_) {
            __empty_unary_control(unary__ctrlactivate__control__ret__nothing, value_);
        }

        float ctrl_auto_scroll_delay(control value_) {
            return __number_unary_control(unary__ctrlautoscrolldelay__control__ret__scalar, value_);
        }

        bool ctrl_auto_scroll_rewind(control value_) {
            return __bool_unary_control(unary__ctrlautoscrollrewind__control__ret__bool, value_);
        }

        float ctrl_auto_scroll_speed(control value_) {
            return __number_unary_control(unary__ctrlautoscrollspeed__control__ret__scalar, value_);
        }

        bool ctrl_checked(control value_) {
            return __bool_unary_control(unary__ctrlchecked__control__ret__bool, value_);
        }

        std::string ctrl_class_name(control value_) {
            return __string_unary_control(unary__ctrlclassname__control__ret__string, value_);
        }

        bool ctrl_committed(control value_) {
            return __bool_unary_control(unary__ctrlcommitted__control__ret__bool, value_);
        }

        bool ctrl_delete(control value_) {
            return __bool_unary_control(unary__ctrldelete__control__ret__bool, value_);
        }

        bool ctrl_enabled(control value_) {
            return __bool_unary_control(unary__ctrlenabled__control__ret__bool, value_);
        }

        bool ctrl_enabled(float value_) {
            return __bool_unary_number(unary__ctrlenabled__scalar__ret__bool, value_);
        }

        float ctrl_fade(control value_) {
            return __number_unary_control(unary__ctrlfade__control__ret__scalar, value_);
        }

        bool ctrl_htmlloaded(control value_) {
            return __bool_unary_control(unary__ctrlhtmlloaded__control__ret__bool, value_);
        }

        float ctrl_idc(control value_) {
            return __number_unary_control(unary__ctrlidc__control__ret__scalar, value_);
        }

        float ctrl_idd(display value_) {
            return __number_unary_display(unary__ctrlidd__display__ret__scalar, value_);
        }

        void ctrl_map_anim_clear(control value_) {
            __empty_unary_control(unary__ctrlmapanimclear__control__ret__nothing, value_);
        }

        void ctrl_map_anim_commit(control value_) {
            __empty_unary_control(unary__ctrlmapanimcommit__control__ret__nothing, value_);
        }

        bool ctrl_map_anim_done(control value_) {
            return __bool_unary_control(unary__ctrlmapanimdone__control__ret__bool, value_);
        }

        float ctrl_map_scale(control value_) {
            return __number_unary_control(unary__ctrlmapscale__control__ret__scalar, value_);
        }

        std::string ctrl_model(control value_) {
            return __string_unary_control(unary__ctrlmodel__control__ret__string, value_);
        }

        float ctrl_model_scale(control value_) {
            return __number_unary_control(unary__ctrlmodelscale__control__ret__scalar, value_);
        }

        display ctrl_parent(control value_) {
            return __display_unary_control(unary__ctrlparent__control__ret__display, value_);
        }

        control ctrl_parent_controls_group(control value_) {
            return __control_unary_control(unary__ctrlparentcontrolsgroup__control__ret__control, value_);
        }

        float ctrl_scale(control value_) {
            return __number_unary_control(unary__ctrlscale__control__ret__scalar, value_);
        }

        void ctrl_set_focus(control value_) {
            __empty_unary_control(unary__ctrlsetfocus__control__ret__nothing, value_);
        }

        bool ctrl_shown(control value_) {
            return __bool_unary_control(unary__ctrlshown__control__ret__bool, value_);
        }

        std::string ctrl_text(control value_) {
            return __string_unary_control(unary__ctrltext__control__ret__string, value_);
        }

        std::string ctrl_text(float value_) {
            return __string_unary_number(unary__ctrltext__scalar__ret__string, value_);
        }

        float ctrl_text_height(control value_) {
            return __number_unary_control(unary__ctrltextheight__control__ret__scalar, value_);
        }

        std::string ctrl_text_secondary(control value_) {
            return __string_unary_control(unary__ctrltextsecondary__control__ret__string, value_);
        }

        float ctrl_type(control value_) {
            return __number_unary_control(unary__ctrltype__control__ret__scalar, value_);
        }

        bool ctrl_visible(float value_) {
            return __bool_unary_number(unary__ctrlvisible__scalar__ret__bool, value_);
        }

        float curator_camera_area_ceiling(object value_) {
            return __number_unary_object(unary__curatorcameraareaceiling__object__ret__scalar, value_);
        }

        bool curator_editing_area_type(object value_) {
            return __bool_unary_object(unary__curatoreditingareatype__object__ret__bool, value_);
        }

        float curator_points(object value_) {
            return __number_unary_object(unary__curatorpoints__object__ret__scalar, value_);
        }

        float curator_waypoint_cost(object value_) {
            return __number_unary_object(unary__curatorwaypointcost__object__ret__scalar, value_);
        }

        std::string current_command(object value_) {
            return __string_unary_object(unary__currentcommand__object__ret__string, value_);
        }

        std::string current_magazine(object value_) {
            return __string_unary_object(unary__currentmagazine__object__ret__string, value_);
        }

        std::string current_muzzle(object value_) {
            return __string_unary_object(unary__currentmuzzle__object__ret__string, value_);
        }

        float current_vision_mode(object value_) {
            return __number_unary_object(unary__currentvisionmode__object__ret__scalar, value_);
        }

        float current_waypoint(group value_) {
            return __number_unary_group(unary__currentwaypoint__group__ret__scalar, value_);
        }

        std::string current_weapon(object value_) {
            return __string_unary_object(unary__currentweapon__object__ret__string, value_);
        }

        std::string current_weapon_mode(object value_) {
            return __string_unary_object(unary__currentweaponmode__object__ret__string, value_);
        }

        float current_zeroing(object value_) {
            return __number_unary_object(unary__currentzeroing__object__ret__scalar, value_);
        }

        float damage(object value_) {
            return __number_unary_object(unary__damage__object__ret__scalar, value_);
        }

        void de_activate_key(std::string value_) {
            __empty_unary_string(unary__deactivatekey__string__ret__nothing, value_);
        }

        float debriefing_text(std::string value_) {
            return __number_unary_string(unary__debriefingtext__string__ret__scalar, value_);
        }

        float deg(float value_) {
            return __number_unary_number(unary__deg__scalar_nan__ret__scalar_nan, value_);
        }

        void delete_center(side value_) {
            __empty_unary_side(unary__deletecenter__side__ret__nothing, value_);
        }

        void delete_collection(object value_) {
            __empty_unary_object(unary__deletecollection__object__ret__nothing, value_);
        }

        void delete_group(group value_) {
            __empty_unary_group(unary__deletegroup__group__ret__nothing, value_);
        }

        bool delete_identity(std::string value_) {
            return __bool_unary_string(unary__deleteidentity__string__ret__bool, value_);
        }

        void delete_marker(std::string value_) {
            __empty_unary_string(unary__deletemarker__string__ret__nothing, value_);
        }

        void delete_marker_local(std::string value_) {
            __empty_unary_string(unary__deletemarkerlocal__string__ret__nothing, value_);
        }

        void delete_site(object value_) {
            __empty_unary_object(unary__deletesite__object__ret__nothing, value_);
        }

        bool delete_status(std::string value_) {
            return __bool_unary_string(unary__deletestatus__string__ret__bool, value_);
        }

        void delete_vehicle(object value_) {
            __empty_unary_object(unary__deletevehicle__object__ret__nothing, value_);
        }

        void detach(object value_) {
            __empty_unary_object(unary__detach__object__ret__nothing, value_);
        }

        bool did_jipowner(object value_) {
            return __bool_unary_object(unary__didjipowner__object__ret__bool, value_);
        }

        bool difficulty_enabled(std::string value_) {
            return __bool_unary_string(unary__difficultyenabled__string__ret__bool, value_);
        }

        float direction(object value_) {
            return __number_unary_object(unary__direction__object__ret__scalar, value_);
        }

        void disable_remote_sensors(bool value_) {
            __empty_unary_bool(unary__disableremotesensors__bool__ret__nothing, value_);
        }

        void disable_user_input(bool value_) {
            __empty_unary_bool(unary__disableuserinput__bool__ret__nothing, value_);
        }

        void dissolve_team(std::string value_) {
            __empty_unary_string(unary__dissolveteam__string__ret__nothing, value_);
        }

        void do(std::string value_) {
            __empty_unary_string(unary__do3denaction__string__ret__nothing, value_);
        }

        object driver(object value_) {
            return __object_unary_object(unary__driver__object__ret__object, value_);
        }

        void echo(std::string value_) {
            __empty_unary_string(unary__echo__string__ret__nothing, value_);
        }

        void edit(std::string value_) {
            __empty_unary_string(unary__edit3denmissionattributes__string__ret__nothing, value_);
        }

        object effective_commander(object value_) {
            return __object_unary_object(unary__effectivecommander__object__ret__object, value_);
        }

        void enable_cam_shake(bool value_) {
            __empty_unary_bool(unary__enablecamshake__bool__ret__nothing, value_);
        }

        void enable_caustics(bool value_) {
            __empty_unary_bool(unary__enablecaustics__bool__ret__nothing, value_);
        }

        void enable_diag_legend(bool value_) {
            __empty_unary_bool(unary__enablediaglegend__bool__ret__nothing, value_);
        }

        void enable_engine_artillery(bool value_) {
            __empty_unary_bool(unary__enableengineartillery__bool__ret__nothing, value_);
        }

        void enable_environment(bool value_) {
            __empty_unary_bool(unary__enableenvironment__bool__ret__nothing, value_);
        }

        void enable_radio(bool value_) {
            __empty_unary_bool(unary__enableradio__bool__ret__nothing, value_);
        }

        void enable_sat_normal_on_detail(bool value_) {
            __empty_unary_bool(unary__enablesatnormalondetail__bool__ret__nothing, value_);
        }

        void enable_sentences(bool value_) {
            __empty_unary_bool(unary__enablesentences__bool__ret__nothing, value_);
        }

        void enable_stress_damage(bool value_) {
            __empty_unary_bool(unary__enablestressdamage__bool__ret__nothing, value_);
        }

        void enable_team_switch(bool value_) {
            __empty_unary_bool(unary__enableteamswitch__bool__ret__nothing, value_);
        }

        void enable_traffic(bool value_) {
            __empty_unary_bool(unary__enabletraffic__bool__ret__nothing, value_);
        }

        void end_mission(std::string value_) {
            __empty_unary_string(unary__endmission__string__ret__nothing, value_);
        }

        void estimated_time_left(float value_) {
            __empty_unary_number(unary__estimatedtimeleft__scalar__ret__nothing, value_);
        }

        float exec_fsm(std::string value_) {
            return __number_unary_string(unary__execfsm__string__ret__scalar, value_);
        }

        float exp(float value_) {
            return __number_unary_number(unary__exp__scalar_nan__ret__scalar_nan, value_);
        }

        void export_jipmessages(std::string value_) {
            __empty_unary_string(unary__exportjipmessages__string__ret__nothing, value_);
        }

        std::string face(object value_) {
            return __string_unary_object(unary__face__object__ret__string, value_);
        }

        std::string faction(object value_) {
            return __string_unary_object(unary__faction__object__ret__string, value_);
        }

        void fail_mission(std::string value_) {
            __empty_unary_string(unary__failmission__string__ret__nothing, value_);
        }

        void fill_weapons_from_pool(object value_) {
            __empty_unary_object(unary__fillweaponsfrompool__object__ret__nothing, value_);
        }

        display find_display(float value_) {
            return __display_unary_number(unary__finddisplay__scalar__ret__display, value_);
        }

        bool finite(float value_) {
            return __bool_unary_number(unary__finite__scalar_nan__ret__bool, value_);
        }

        object first_backpack(object value_) {
            return __object_unary_object(unary__firstbackpack__object__ret__object, value_);
        }

        object flag(object value_) {
            return __object_unary_object(unary__flag__object__ret__object, value_);
        }

        object flag_owner(object value_) {
            return __object_unary_object(unary__flagowner__object__ret__object, value_);
        }

        side flag_side(object value_) {
            return __side_unary_object(unary__flagside__object__ret__side, value_);
        }

        std::string flag_texture(object value_) {
            return __string_unary_object(unary__flagtexture__object__ret__string, value_);
        }

        bool fleeing(object value_) {
            return __bool_unary_object(unary__fleeing__object__ret__bool, value_);
        }

        float floor(float value_) {
            return __number_unary_number(unary__floor__scalar_nan__ret__scalar_nan, value_);
        }

        void force_map(bool value_) {
            __empty_unary_bool(unary__forcemap__bool__ret__nothing, value_);
        }

        void force_respawn(object value_) {
            __empty_unary_object(unary__forcerespawn__object__ret__nothing, value_);
        }

        object form_leader(object value_) {
            return __object_unary_object(unary__formleader__object__ret__object, value_);
        }

        float formation_direction(object value_) {
            return __number_unary_object(unary__formationdirection__object__ret__scalar, value_);
        }

        object formation_leader(object value_) {
            return __object_unary_object(unary__formationleader__object__ret__object, value_);
        }

        std::string formation_task(object value_) {
            return __string_unary_object(unary__formationtask__object__ret__string, value_);
        }

        float fuel(object value_) {
            return __number_unary_object(unary__fuel__object__ret__scalar, value_);
        }

        float gear_idcammo_count(float value_) {
            return __number_unary_number(unary__gearidcammocount__scalar__ret__scalar, value_);
        }

        float gear_slot_ammo_count(control value_) {
            return __number_unary_control(unary__gearslotammocount__control__ret__scalar, value_);
        }

        std::string gear_slot_data(control value_) {
            return __string_unary_control(unary__gearslotdata__control__ret__string, value_);
        }

        float get(std::string value_) {
            return __number_unary_string(unary__get3denactionstate__string__ret__scalar, value_);
        }

        void get(std::string value_) {
            __empty_unary_string(unary__get3dengrid__string__ret__nothing, value_);
        }

        float get_aiming_coef(object value_) {
            return __number_unary_object(unary__getaimingcoef__object__ret__scalar, value_);
        }

        float get_ammo_cargo(object value_) {
            return __number_unary_object(unary__getammocargo__object__ret__scalar, value_);
        }

        float get_anim_aim_precision(object value_) {
            return __number_unary_object(unary__getanimaimprecision__object__ret__scalar, value_);
        }

        float get_anim_speed_coef(object value_) {
            return __number_unary_object(unary__getanimspeedcoef__object__ret__scalar, value_);
        }

        object get_assigned_curator_logic(object value_) {
            return __object_unary_object(unary__getassignedcuratorlogic__object__ret__object, value_);
        }

        object get_assigned_curator_unit(object value_) {
            return __object_unary_object(unary__getassignedcuratorunit__object__ret__object, value_);
        }

        float get_bleeding_remaining(object value_) {
            return __number_unary_object(unary__getbleedingremaining__object__ret__scalar, value_);
        }

        float get_burning_value(object value_) {
            return __number_unary_object(unary__getburningvalue__object__ret__scalar, value_);
        }

        object get_connected_uav(object value_) {
            return __object_unary_object(unary__getconnecteduav__object__ret__object, value_);
        }

        float get_custom_aim_coef(object value_) {
            return __number_unary_object(unary__getcustomaimcoef__object__ret__scalar, value_);
        }

        float get_dlcusage_time(float value_) {
            return __number_unary_number(unary__getdlcusagetime__scalar__ret__scalar, value_);
        }

        float get_dammage(object value_) {
            return __number_unary_object(unary__getdammage__object__ret__scalar, value_);
        }

        float get_dir(object value_) {
            return __number_unary_object(unary__getdir__object__ret__scalar, value_);
        }

        float get_dir_visual(object value_) {
            return __number_unary_object(unary__getdirvisual__object__ret__scalar, value_);
        }

        object get_editor_camera(control value_) {
            return __object_unary_control(unary__geteditorcamera__control__ret__object, value_);
        }

        std::string get_editor_mode(control value_) {
            return __string_unary_control(unary__geteditormode__control__ret__string, value_);
        }

        float get_fatigue(object value_) {
            return __number_unary_object(unary__getfatigue__object__ret__scalar, value_);
        }

        float get_fuel_cargo(object value_) {
            return __number_unary_object(unary__getfuelcargo__object__ret__scalar, value_);
        }

        std::string get_marker_color(std::string value_) {
            return __string_unary_string(unary__getmarkercolor__string__ret__string, value_);
        }

        std::string get_marker_type(std::string value_) {
            return __string_unary_string(unary__getmarkertype__string__ret__string, value_);
        }

        float get_mass(object value_) {
            return __number_unary_object(unary__getmass__object__ret__scalar, value_);
        }

        float get_object_dlc(object value_) {
            return __number_unary_object(unary__getobjectdlc__object__ret__scalar, value_);
        }

        float get_object_type(object value_) {
            return __number_unary_object(unary__getobjecttype__object__ret__scalar, value_);
        }

        float get_oxygen_remaining(object value_) {
            return __number_unary_object(unary__getoxygenremaining__object__ret__scalar, value_);
        }

        float get_player_channel(object value_) {
            return __number_unary_object(unary__getplayerchannel__object__ret__scalar, value_);
        }

        std::string get_player_uid(object value_) {
            return __string_unary_object(unary__getplayeruid__object__ret__string, value_);
        }

        float get_repair_cargo(object value_) {
            return __number_unary_object(unary__getrepaircargo__object__ret__scalar, value_);
        }

        float get_rotor_brake_rtd(object value_) {
            return __number_unary_object(unary__getrotorbrakertd__object__ret__scalar, value_);
        }

        object get_sling_load(object value_) {
            return __object_unary_object(unary__getslingload__object__ret__object, value_);
        }

        float get_stamina(object value_) {
            return __number_unary_object(unary__getstamina__object__ret__scalar, value_);
        }

        float get_stat_value(std::string value_) {
            return __number_unary_string(unary__getstatvalue__string__ret__scalar, value_);
        }

        float get_suppression(object value_) {
            return __number_unary_object(unary__getsuppression__object__ret__scalar, value_);
        }

        float get_weapon_sway(object value_) {
            return __number_unary_object(unary__getweaponsway__object__ret__scalar, value_);
        }

        float get_wings_orientation_rtd(object value_) {
            return __number_unary_object(unary__getwingsorientationrtd__object__ret__scalar, value_);
        }

        float get_wings_position_rtd(object value_) {
            return __number_unary_object(unary__getwingspositionrtd__object__ret__scalar, value_);
        }

        std::string goggles(object value_) {
            return __string_unary_object(unary__goggles__object__ret__string, value_);
        }

        void goto(std::string value_) {
            __empty_unary_string(unary__goto__string__ret__nothing, value_);
        }

        group group_from_net_id(std::string value_) {
            return __group_unary_string(unary__groupfromnetid__string__ret__group, value_);
        }

        std::string group_id(group value_) {
            return __string_unary_group(unary__groupid__group__ret__string, value_);
        }

        float group_owner(group value_) {
            return __number_unary_group(unary__groupowner__group__ret__scalar, value_);
        }

        object gunner(object value_) {
            return __object_unary_object(unary__gunner__object__ret__object, value_);
        }

        std::string handgun_magazine(object value_) {
            return __string_unary_object(unary__handgunmagazine__object__ret__string, value_);
        }

        std::string handgun_weapon(object value_) {
            return __string_unary_object(unary__handgunweapon__object__ret__string, value_);
        }

        float hands_hit(object value_) {
            return __number_unary_object(unary__handshit__object__ret__scalar, value_);
        }

        object hc_leader(group value_) {
            return __object_unary_group(unary__hcleader__group__ret__object, value_);
        }

        void hc_remove_all_groups(object value_) {
            __empty_unary_object(unary__hcremoveallgroups__object__ret__nothing, value_);
        }

        void hc_show_bar(bool value_) {
            __empty_unary_bool(unary__hcshowbar__bool__ret__nothing, value_);
        }

        std::string headgear(object value_) {
            return __string_unary_object(unary__headgear__object__ret__string, value_);
        }

        void hide_body(object value_) {
            __empty_unary_object(unary__hidebody__object__ret__nothing, value_);
        }

        void hide_object(object value_) {
            __empty_unary_object(unary__hideobject__object__ret__nothing, value_);
        }

        void hide_object_global(object value_) {
            __empty_unary_object(unary__hideobjectglobal__object__ret__nothing, value_);
        }

        void hint_c(std::string value_) {
            __empty_unary_string(unary__hintc__string__ret__nothing, value_);
        }

        std::string hmd(object value_) {
            return __string_unary_object(unary__hmd__object__ret__string, value_);
        }

        text image(std::string value_) {
            return __text_unary_string(unary__image__string__ret__text, value_);
        }

        void import_all_groups(control value_) {
            __empty_unary_control(unary__importallgroups__control__ret__nothing, value_);
        }

        std::string incapacitated_state(object value_) {
            return __string_unary_object(unary__incapacitatedstate__object__ret__string, value_);
        }

        bool inflamed(object value_) {
            return __bool_unary_object(unary__inflamed__object__ret__bool, value_);
        }

        float input_action(std::string value_) {
            return __number_unary_string(unary__inputaction__string__ret__scalar, value_);
        }

        bool is_able_to_breathe(object value_) {
            return __bool_unary_object(unary__isabletobreathe__object__ret__bool, value_);
        }

        bool is_aim_precision_enabled(object value_) {
            return __bool_unary_object(unary__isaimprecisionenabled__object__ret__bool, value_);
        }

        bool is_auto_hover_on(object value_) {
            return __bool_unary_object(unary__isautohoveron__object__ret__bool, value_);
        }

        bool is_auto_trim_on_rtd(object value_) {
            return __bool_unary_object(unary__isautotrimonrtd__object__ret__bool, value_);
        }

        bool is_autonomous(object value_) {
            return __bool_unary_object(unary__isautonomous__object__ret__bool, value_);
        }

        bool is_bleeding(object value_) {
            return __bool_unary_object(unary__isbleeding__object__ret__bool, value_);
        }

        bool is_burning(object value_) {
            return __bool_unary_object(unary__isburning__object__ret__bool, value_);
        }

        bool is_collision_light_on(object value_) {
            return __bool_unary_object(unary__iscollisionlighton__object__ret__bool, value_);
        }

        bool is_copilot_enabled(object value_) {
            return __bool_unary_object(unary__iscopilotenabled__object__ret__bool, value_);
        }

        bool is_dlcavailable(float value_) {
            return __bool_unary_number(unary__isdlcavailable__scalar__ret__bool, value_);
        }

        bool is_engine_on(object value_) {
            return __bool_unary_object(unary__isengineon__object__ret__bool, value_);
        }

        bool is_forced_walk(object value_) {
            return __bool_unary_object(unary__isforcedwalk__object__ret__bool, value_);
        }

        bool is_formation_leader(object value_) {
            return __bool_unary_object(unary__isformationleader__object__ret__bool, value_);
        }

        bool is_hidden(object value_) {
            return __bool_unary_object(unary__ishidden__object__ret__bool, value_);
        }

        bool is_in_remains_collector(object value_) {
            return __bool_unary_object(unary__isinremainscollector__object__ret__bool, value_);
        }

        bool is_key_active(std::string value_) {
            return __bool_unary_string(unary__iskeyactive__string__ret__bool, value_);
        }

        bool is_light_on(object value_) {
            return __bool_unary_object(unary__islighton__object__ret__bool, value_);
        }

        bool is_localized(std::string value_) {
            return __bool_unary_string(unary__islocalized__string__ret__bool, value_);
        }

        bool is_manual_fire(object value_) {
            return __bool_unary_object(unary__ismanualfire__object__ret__bool, value_);
        }

        bool is_marked_for_collection(object value_) {
            return __bool_unary_object(unary__ismarkedforcollection__object__ret__bool, value_);
        }

        bool is_null(object value_) {
            return __bool_unary_object(unary__isnull__object__ret__bool, value_);
        }

        bool is_null(group value_) {
            return __bool_unary_group(unary__isnull__group__ret__bool, value_);
        }

        bool is_null(control value_) {
            return __bool_unary_control(unary__isnull__control__ret__bool, value_);
        }

        bool is_null(display value_) {
            return __bool_unary_display(unary__isnull__display__ret__bool, value_);
        }

        bool is_object_hidden(object value_) {
            return __bool_unary_object(unary__isobjecthidden__object__ret__bool, value_);
        }

        bool is_object_rtd(object value_) {
            return __bool_unary_object(unary__isobjectrtd__object__ret__bool, value_);
        }

        bool is_player(object value_) {
            return __bool_unary_object(unary__isplayer__object__ret__bool, value_);
        }

        bool is_real_time(control value_) {
            return __bool_unary_control(unary__isrealtime__control__ret__bool, value_);
        }

        bool is_showing(control value_) {
            return __bool_unary_control(unary__isshowing3dicons__control__ret__bool, value_);
        }

        bool is_sprint_allowed(object value_) {
            return __bool_unary_object(unary__issprintallowed__object__ret__bool, value_);
        }

        bool is_stamina_enabled(object value_) {
            return __bool_unary_object(unary__isstaminaenabled__object__ret__bool, value_);
        }

        bool is_touching_ground(object value_) {
            return __bool_unary_object(unary__istouchingground__object__ret__bool, value_);
        }

        bool is_turned_out(object value_) {
            return __bool_unary_object(unary__isturnedout__object__ret__bool, value_);
        }

        bool is_uavconnected(object value_) {
            return __bool_unary_object(unary__isuavconnected__object__ret__bool, value_);
        }

        bool is_walking(object value_) {
            return __bool_unary_object(unary__iswalking__object__ret__bool, value_);
        }

        bool is_weapon_deployed(object value_) {
            return __bool_unary_object(unary__isweapondeployed__object__ret__bool, value_);
        }

        bool is_weapon_rested(object value_) {
            return __bool_unary_object(unary__isweaponrested__object__ret__bool, value_);
        }

        text key_image(float value_) {
            return __text_unary_number(unary__keyimage__scalar__ret__text, value_);
        }

        std::string key_name(float value_) {
            return __string_unary_number(unary__keyname__scalar__ret__string, value_);
        }

        std::string land_result(object value_) {
            return __string_unary_object(unary__landresult__object__ret__string, value_);
        }

        object laser_target(object value_) {
            return __object_unary_object(unary__lasertarget__object__ret__object, value_);
        }

        void lb_clear(control value_) {
            __empty_unary_control(unary__lbclear__control__ret__nothing, value_);
        }

        void lb_clear(float value_) {
            __empty_unary_number(unary__lbclear__scalar__ret__nothing, value_);
        }

        float lb_cur_sel(control value_) {
            return __number_unary_control(unary__lbcursel__control__ret__scalar, value_);
        }

        float lb_cur_sel(float value_) {
            return __number_unary_number(unary__lbcursel__scalar__ret__scalar, value_);
        }

        float lb_size(control value_) {
            return __number_unary_control(unary__lbsize__control__ret__scalar, value_);
        }

        float lb_size(float value_) {
            return __number_unary_number(unary__lbsize__scalar__ret__scalar, value_);
        }

        float lb_sort(control value_) {
            return __number_unary_control(unary__lbsort__control__ret__scalar, value_);
        }

        float lb_sort_by_value(control value_) {
            return __number_unary_control(unary__lbsortbyvalue__control__ret__scalar, value_);
        }

        object leader(object value_) {
            return __object_unary_object(unary__leader__object__ret__object, value_);
        }

        object leader(group value_) {
            return __object_unary_group(unary__leader__group__ret__object, value_);
        }

        bool leaderboard_de_init(std::string value_) {
            return __bool_unary_string(unary__leaderboarddeinit__string__ret__bool, value_);
        }

        bool leaderboard_init(std::string value_) {
            return __bool_unary_string(unary__leaderboardinit__string__ret__bool, value_);
        }

        bool leaderboard_request_rows_friends(std::string value_) {
            return __bool_unary_string(unary__leaderboardrequestrowsfriends__string__ret__bool, value_);
        }

        float leaderboard_state(std::string value_) {
            return __number_unary_string(unary__leaderboardstate__string__ret__scalar, value_);
        }

        std::string life_state(object value_) {
            return __string_unary_object(unary__lifestate__object__ret__string, value_);
        }

        void light_detach_object(object value_) {
            __empty_unary_object(unary__lightdetachobject__object__ret__nothing, value_);
        }

        std::string light_is_on(object value_) {
            return __string_unary_object(unary__lightison__object__ret__string, value_);
        }

        float ln(float value_) {
            return __number_unary_number(unary__ln__scalar_nan__ret__scalar_nan, value_);
        }

        void lnb_clear(control value_) {
            __empty_unary_control(unary__lnbclear__control__ret__nothing, value_);
        }

        void lnb_clear(float value_) {
            __empty_unary_number(unary__lnbclear__scalar__ret__nothing, value_);
        }

        float lnb_cur_sel_row(control value_) {
            return __number_unary_control(unary__lnbcurselrow__control__ret__scalar, value_);
        }

        float lnb_cur_sel_row(float value_) {
            return __number_unary_number(unary__lnbcurselrow__scalar__ret__scalar, value_);
        }

        float load(object value_) {
            return __number_unary_object(unary__load__object__ret__scalar, value_);
        }

        float load_abs(object value_) {
            return __number_unary_object(unary__loadabs__object__ret__scalar, value_);
        }

        float load_backpack(object value_) {
            return __number_unary_object(unary__loadbackpack__object__ret__scalar, value_);
        }

        std::string load_file(std::string value_) {
            return __string_unary_string(unary__loadfile__string__ret__string, value_);
        }

        float load_uniform(object value_) {
            return __number_unary_object(unary__loaduniform__object__ret__scalar, value_);
        }

        float load_vest(object value_) {
            return __number_unary_object(unary__loadvest__object__ret__scalar, value_);
        }

        bool local(object value_) {
            return __bool_unary_object(unary__local__object__ret__bool, value_);
        }

        bool local(group value_) {
            return __bool_unary_group(unary__local__group__ret__bool, value_);
        }

        std::string localize(std::string value_) {
            return __string_unary_string(unary__localize__string__ret__string, value_);
        }

        bool lock_identity(object value_) {
            return __bool_unary_object(unary__lockidentity__object__ret__bool, value_);
        }

        float locked(object value_) {
            return __number_unary_object(unary__locked__object__ret__scalar, value_);
        }

        bool locked_driver(object value_) {
            return __bool_unary_object(unary__lockeddriver__object__ret__bool, value_);
        }

        float log(float value_) {
            return __number_unary_number(unary__log__scalar_nan__ret__scalar_nan, value_);
        }

        float marker_alpha(std::string value_) {
            return __number_unary_string(unary__markeralpha__string__ret__scalar, value_);
        }

        std::string marker_brush(std::string value_) {
            return __string_unary_string(unary__markerbrush__string__ret__string, value_);
        }

        std::string marker_color(std::string value_) {
            return __string_unary_string(unary__markercolor__string__ret__string, value_);
        }

        float marker_dir(std::string value_) {
            return __number_unary_string(unary__markerdir__string__ret__scalar, value_);
        }

        std::string marker_shape(std::string value_) {
            return __string_unary_string(unary__markershape__string__ret__string, value_);
        }

        std::string marker_text(std::string value_) {
            return __string_unary_string(unary__markertext__string__ret__string, value_);
        }

        std::string marker_type(std::string value_) {
            return __string_unary_string(unary__markertype__string__ret__string, value_);
        }

        bool mine_active(object value_) {
            return __bool_unary_object(unary__mineactive__object__ret__bool, value_);
        }

        float morale(object value_) {
            return __number_unary_object(unary__morale__object__ret__scalar, value_);
        }

        void move_out(object value_) {
            __empty_unary_object(unary__moveout__object__ret__nothing, value_);
        }

        float move_time(object value_) {
            return __number_unary_object(unary__movetime__object__ret__scalar, value_);
        }

        bool move_to_completed(object value_) {
            return __bool_unary_object(unary__movetocompleted__object__ret__bool, value_);
        }

        bool move_to_failed(object value_) {
            return __bool_unary_object(unary__movetofailed__object__ret__bool, value_);
        }

        std::string name(object value_) {
            return __string_unary_object(unary__name__object__ret__string, value_);
        }

        std::string name_sound(object value_) {
            return __string_unary_object(unary__namesound__object__ret__string, value_);
        }

        object nearest_building(object value_) {
            return __object_unary_object(unary__nearestbuilding__object__ret__object, value_);
        }

        float need_reload(object value_) {
            return __number_unary_object(unary__needreload__object__ret__scalar, value_);
        }

        std::string net_id(object value_) {
            return __string_unary_object(unary__netid__object__ret__string, value_);
        }

        std::string net_id(group value_) {
            return __string_unary_group(unary__netid__group__ret__string, value_);
        }

        float next_menu_item_index(control value_) {
            return __number_unary_control(unary__nextmenuitemindex__control__ret__scalar, value_);
        }

        bool not(bool value_) {
            return __bool_unary_bool(unary__not__bool__ret__bool, value_);
        }

        float number_of_engines_rtd(object value_) {
            return __number_unary_object(unary__numberofenginesrtd__object__ret__scalar, value_);
        }

        object object_from_net_id(std::string value_) {
            return __object_unary_string(unary__objectfromnetid__string__ret__object, value_);
        }

        object object_parent(object value_) {
            return __object_unary_object(unary__objectparent__object__ret__object, value_);
        }

        void on_briefing_group(std::string value_) {
            __empty_unary_string(unary__onbriefinggroup__string__ret__nothing, value_);
        }

        void on_briefing_notes(std::string value_) {
            __empty_unary_string(unary__onbriefingnotes__string__ret__nothing, value_);
        }

        void on_briefing_plan(std::string value_) {
            __empty_unary_string(unary__onbriefingplan__string__ret__nothing, value_);
        }

        void on_briefing_team_switch(std::string value_) {
            __empty_unary_string(unary__onbriefingteamswitch__string__ret__nothing, value_);
        }

        bool open_dlc_page(float value_) {
            return __bool_unary_number(unary__opendlcpage__scalar__ret__bool, value_);
        }

        bool open_map(bool value_) {
            return __bool_unary_bool(unary__openmap__bool__ret__bool, value_);
        }

        bool open_youtube_video(std::string value_) {
            return __bool_unary_string(unary__openyoutubevideo__string__ret__bool, value_);
        }

        float owner(object value_) {
            return __number_unary_object(unary__owner__object__ret__scalar, value_);
        }

        float parse_number(std::string value_) {
            return __number_unary_string(unary__parsenumber__string__ret__scalar, value_);
        }

        float parse_number(bool value_) {
            return __number_unary_bool(unary__parsenumber__bool__ret__scalar, value_);
        }

        text parse_text(std::string value_) {
            return __text_unary_string(unary__parsetext__string__ret__text, value_);
        }

        void pick_weapon_pool(object value_) {
            __empty_unary_object(unary__pickweaponpool__object__ret__nothing, value_);
        }

        std::string pitch(object value_) {
            return __string_unary_object(unary__pitch__object__ret__string, value_);
        }

        void play_music(std::string value_) {
            __empty_unary_string(unary__playmusic__string__ret__nothing, value_);
        }

        void play_sound(std::string value_) {
            __empty_unary_string(unary__playsound__string__ret__nothing, value_);
        }

        float playable_slots_number(side value_) {
            return __number_unary_side(unary__playableslotsnumber__side__ret__scalar, value_);
        }

        float players_number(side value_) {
            return __number_unary_side(unary__playersnumber__side__ret__scalar, value_);
        }

        bool pp_effect_committed(std::string value_) {
            return __bool_unary_string(unary__ppeffectcommitted__string__ret__bool, value_);
        }

        bool pp_effect_committed(float value_) {
            return __bool_unary_number(unary__ppeffectcommitted__scalar__ret__bool, value_);
        }

        void pp_effect_destroy(float value_) {
            __empty_unary_number(unary__ppeffectdestroy__scalar__ret__nothing, value_);
        }

        bool pp_effect_enabled(float value_) {
            return __bool_unary_number(unary__ppeffectenabled__scalar__ret__bool, value_);
        }

        float precision(object value_) {
            return __number_unary_object(unary__precision__object__ret__scalar, value_);
        }

        bool preload_sound(std::string value_) {
            return __bool_unary_string(unary__preloadsound__string__ret__bool, value_);
        }

        std::string preprocess_file(std::string value_) {
            return __string_unary_string(unary__preprocessfile__string__ret__string, value_);
        }

        std::string preprocess_file_line_numbers(std::string value_) {
            return __string_unary_string(unary__preprocessfilelinenumbers__string__ret__string, value_);
        }

        std::string primary_weapon(object value_) {
            return __string_unary_object(unary__primaryweapon__object__ret__string, value_);
        }

        void process_diary_link(std::string value_) {
            __empty_unary_string(unary__processdiarylink__string__ret__nothing, value_);
        }

        void progress_loading_screen(float value_) {
            __empty_unary_number(unary__progressloadingscreen__scalar__ret__nothing, value_);
        }

        float progress_position(control value_) {
            return __number_unary_control(unary__progressposition__control__ret__scalar, value_);
        }

        void public_variable(std::string value_) {
            __empty_unary_string(unary__publicvariable__string__ret__nothing, value_);
        }

        void public_variable_server(std::string value_) {
            __empty_unary_string(unary__publicvariableserver__string__ret__nothing, value_);
        }

        void put_weapon_pool(object value_) {
            __empty_unary_object(unary__putweaponpool__object__ret__nothing, value_);
        }

        float query_items_pool(std::string value_) {
            return __number_unary_string(unary__queryitemspool__string__ret__scalar, value_);
        }

        float query_magazine_pool(std::string value_) {
            return __number_unary_string(unary__querymagazinepool__string__ret__scalar, value_);
        }

        float query_weapon_pool(std::string value_) {
            return __number_unary_string(unary__queryweaponpool__string__ret__scalar, value_);
        }

        float rad(float value_) {
            return __number_unary_number(unary__rad__scalar_nan__ret__scalar_nan, value_);
        }

        float random(float value_) {
            return __number_unary_number(unary__random__scalar_nan__ret__scalar_nan, value_);
        }

        std::string rank(object value_) {
            return __string_unary_object(unary__rank__object__ret__string, value_);
        }

        float rank_id(object value_) {
            return __number_unary_object(unary__rankid__object__ret__scalar, value_);
        }

        float rating(object value_) {
            return __number_unary_object(unary__rating__object__ret__scalar, value_);
        }

        void reload(object value_) {
            __empty_unary_object(unary__reload__object__ret__nothing, value_);
        }

        bool reload_enabled(object value_) {
            return __bool_unary_object(unary__reloadenabled__object__ret__bool, value_);
        }

        bool remove(float value_) {
            return __bool_unary_number(unary__remove3denlayer__scalar__ret__bool, value_);
        }

        void remove_all(std::string value_) {
            __empty_unary_string(unary__removeall3deneventhandlers__string__ret__nothing, value_);
        }

        void remove_all_actions(object value_) {
            __empty_unary_object(unary__removeallactions__object__ret__nothing, value_);
        }

        void remove_all_assigned_items(object value_) {
            __empty_unary_object(unary__removeallassigneditems__object__ret__nothing, value_);
        }

        void remove_all_containers(object value_) {
            __empty_unary_object(unary__removeallcontainers__object__ret__nothing, value_);
        }

        void remove_all_curator_addons(object value_) {
            __empty_unary_object(unary__removeallcuratoraddons__object__ret__nothing, value_);
        }

        void remove_all_curator_camera_areas(object value_) {
            __empty_unary_object(unary__removeallcuratorcameraareas__object__ret__nothing, value_);
        }

        void remove_all_curator_editing_areas(object value_) {
            __empty_unary_object(unary__removeallcuratoreditingareas__object__ret__nothing, value_);
        }

        void remove_all_handgun_items(object value_) {
            __empty_unary_object(unary__removeallhandgunitems__object__ret__nothing, value_);
        }

        void remove_all_items(object value_) {
            __empty_unary_object(unary__removeallitems__object__ret__nothing, value_);
        }

        void remove_all_items_with_magazines(object value_) {
            __empty_unary_object(unary__removeallitemswithmagazines__object__ret__nothing, value_);
        }

        void remove_all_mission_event_handlers(std::string value_) {
            __empty_unary_string(unary__removeallmissioneventhandlers__string__ret__nothing, value_);
        }

        void remove_all_music_event_handlers(std::string value_) {
            __empty_unary_string(unary__removeallmusiceventhandlers__string__ret__nothing, value_);
        }

        void remove_all_primary_weapon_items(object value_) {
            __empty_unary_object(unary__removeallprimaryweaponitems__object__ret__nothing, value_);
        }

        void remove_all_weapons(object value_) {
            __empty_unary_object(unary__removeallweapons__object__ret__nothing, value_);
        }

        void remove_backpack(object value_) {
            __empty_unary_object(unary__removebackpack__object__ret__nothing, value_);
        }

        void remove_backpack_global(object value_) {
            __empty_unary_object(unary__removebackpackglobal__object__ret__nothing, value_);
        }

        void remove_goggles(object value_) {
            __empty_unary_object(unary__removegoggles__object__ret__nothing, value_);
        }

        void remove_headgear(object value_) {
            __empty_unary_object(unary__removeheadgear__object__ret__nothing, value_);
        }

        void remove_switchable_unit(object value_) {
            __empty_unary_object(unary__removeswitchableunit__object__ret__nothing, value_);
        }

        void remove_uniform(object value_) {
            __empty_unary_object(unary__removeuniform__object__ret__nothing, value_);
        }

        void remove_vest(object value_) {
            __empty_unary_object(unary__removevest__object__ret__nothing, value_);
        }

        bool required_version(std::string value_) {
            return __bool_unary_string(unary__requiredversion__string__ret__bool, value_);
        }

        void reset_subgroup_direction(object value_) {
            __empty_unary_object(unary__resetsubgroupdirection__object__ret__nothing, value_);
        }

        void restart_editor_camera(control value_) {
            __empty_unary_control(unary__restarteditorcamera__control__ret__nothing, value_);
        }

        std::string role_description(object value_) {
            return __string_unary_object(unary__roledescription__object__ret__string, value_);
        }

        bool rope_attach_enabled(object value_) {
            return __bool_unary_object(unary__ropeattachenabled__object__ret__bool, value_);
        }

        object rope_attached_to(object value_) {
            return __object_unary_object(unary__ropeattachedto__object__ret__object, value_);
        }

        void rope_destroy(object value_) {
            __empty_unary_object(unary__ropedestroy__object__ret__nothing, value_);
        }

        float rope_length(object value_) {
            return __number_unary_object(unary__ropelength__object__ret__scalar, value_);
        }

        bool rope_unwound(object value_) {
            return __bool_unary_object(unary__ropeunwound__object__ret__bool, value_);
        }

        float round(float value_) {
            return __number_unary_number(unary__round__scalar_nan__ret__scalar_nan, value_);
        }

        void save_overlay(control value_) {
            __empty_unary_control(unary__saveoverlay__control__ret__nothing, value_);
        }

        void save_var(std::string value_) {
            __empty_unary_string(unary__savevar__string__ret__nothing, value_);
        }

        void scope_name(std::string value_) {
            __empty_unary_string(unary__scopename__string__ret__nothing, value_);
        }

        float score(object value_) {
            return __number_unary_object(unary__score__object__ret__scalar, value_);
        }

        float score_side(side value_) {
            return __number_unary_side(unary__scoreside__side__ret__scalar, value_);
        }

        void script_name(std::string value_) {
            __empty_unary_string(unary__scriptname__string__ret__nothing, value_);
        }

        float scud_state(object value_) {
            return __number_unary_object(unary__scudstate__object__ret__scalar, value_);
        }

        std::string secondary_weapon(object value_) {
            return __string_unary_object(unary__secondaryweapon__object__ret__string, value_);
        }

        void select_player(object value_) {
            __empty_unary_object(unary__selectplayer__object__ret__nothing, value_);
        }

        void selected_editor_objects(control value_) {
            __empty_unary_control(unary__selectededitorobjects__control__ret__nothing, value_);
        }

        bool server_command(std::string value_) {
            return __bool_unary_string(unary__servercommand__string__ret__bool, value_);
        }

        bool server_command_available(std::string value_) {
            return __bool_unary_string(unary__servercommandavailable__string__ret__bool, value_);
        }

        bool server_command_executable(std::string value_) {
            return __bool_unary_string(unary__servercommandexecutable__string__ret__bool, value_);
        }

        void set_acc_time(float value_) {
            __empty_unary_number(unary__setacctime__scalar__ret__nothing, value_);
        }

        void set_aperture(float value_) {
            __empty_unary_number(unary__setaperture__scalar__ret__nothing, value_);
        }

        void set_armory_points(float value_) {
            __empty_unary_number(unary__setarmorypoints__scalar__ret__nothing, value_);
        }

        bool set_current_channel(float value_) {
            return __bool_unary_number(unary__setcurrentchannel__scalar__ret__bool, value_);
        }

        void set_group_icons_selectable(bool value_) {
            __empty_unary_bool(unary__setgroupiconsselectable__bool__ret__nothing, value_);
        }

        void set_horizon_parallax_coef(float value_) {
            __empty_unary_number(unary__sethorizonparallaxcoef__scalar__ret__nothing, value_);
        }

        void set_object_view_distance(float value_) {
            __empty_unary_number(unary__setobjectviewdistance__scalar__ret__nothing, value_);
        }

        void set_playable(object value_) {
            __empty_unary_object(unary__setplayable__object__ret__nothing, value_);
        }

        void set_player_respawn_time(float value_) {
            __empty_unary_number(unary__setplayerrespawntime__scalar__ret__nothing, value_);
        }

        void set_shadow_distance(float value_) {
            __empty_unary_number(unary__setshadowdistance__scalar__ret__nothing, value_);
        }

        void set_simul_weather_layers(float value_) {
            __empty_unary_number(unary__setsimulweatherlayers__scalar__ret__nothing, value_);
        }

        void set_stamina_scheme(std::string value_) {
            __empty_unary_string(unary__setstaminascheme__string__ret__nothing, value_);
        }

        void set_system_of_units(float value_) {
            __empty_unary_number(unary__setsystemofunits__scalar__ret__nothing, value_);
        }

        void set_terrain_grid(float value_) {
            __empty_unary_number(unary__setterraingrid__scalar__ret__nothing, value_);
        }

        void set_time_multiplier(float value_) {
            __empty_unary_number(unary__settimemultiplier__scalar__ret__nothing, value_);
        }

        void set_traffic_distance(float value_) {
            __empty_unary_number(unary__settrafficdistance__scalar__ret__nothing, value_);
        }

        void set_view_distance(float value_) {
            __empty_unary_number(unary__setviewdistance__scalar__ret__nothing, value_);
        }

        void show_chat(bool value_) {
            __empty_unary_bool(unary__showchat__bool__ret__nothing, value_);
        }

        void show_cinema_border(bool value_) {
            __empty_unary_bool(unary__showcinemaborder__bool__ret__nothing, value_);
        }

        void show_commanding_menu(std::string value_) {
            __empty_unary_string(unary__showcommandingmenu__string__ret__nothing, value_);
        }

        void show_compass(bool value_) {
            __empty_unary_bool(unary__showcompass__bool__ret__nothing, value_);
        }

        void show_curator_compass(bool value_) {
            __empty_unary_bool(unary__showcuratorcompass__bool__ret__nothing, value_);
        }

        void show_gps(bool value_) {
            __empty_unary_bool(unary__showgps__bool__ret__nothing, value_);
        }

        void show_hud(bool value_) {
            __empty_unary_bool(unary__showhud__bool__ret__nothing, value_);
        }

        void show_map(bool value_) {
            __empty_unary_bool(unary__showmap__bool__ret__nothing, value_);
        }

        void show_pad(bool value_) {
            __empty_unary_bool(unary__showpad__bool__ret__nothing, value_);
        }

        void show_radio(bool value_) {
            __empty_unary_bool(unary__showradio__bool__ret__nothing, value_);
        }

        bool show_subtitles(bool value_) {
            return __bool_unary_bool(unary__showsubtitles__bool__ret__bool, value_);
        }

        void show_uavfeed(bool value_) {
            __empty_unary_bool(unary__showuavfeed__bool__ret__nothing, value_);
        }

        void show_warrant(bool value_) {
            __empty_unary_bool(unary__showwarrant__bool__ret__nothing, value_);
        }

        void show_watch(bool value_) {
            __empty_unary_bool(unary__showwatch__bool__ret__nothing, value_);
        }

        bool simulation_enabled(object value_) {
            return __bool_unary_object(unary__simulationenabled__object__ret__bool, value_);
        }

        float sin(float value_) {
            return __number_unary_number(unary__sin__scalar_nan__ret__scalar_nan, value_);
        }

        float size_of(std::string value_) {
            return __number_unary_string(unary__sizeof__string__ret__scalar, value_);
        }

        float skill(object value_) {
            return __number_unary_object(unary__skill__object__ret__scalar, value_);
        }

        void skip_time(float value_) {
            __empty_unary_number(unary__skiptime__scalar__ret__nothing, value_);
        }

        void sleep(float value_) {
            __empty_unary_number(unary__sleep__scalar__ret__nothing, value_);
        }

        float slider_position(control value_) {
            return __number_unary_control(unary__sliderposition__control__ret__scalar, value_);
        }

        float slider_position(float value_) {
            return __number_unary_number(unary__sliderposition__scalar__ret__scalar, value_);
        }

        bool some_ammo(object value_) {
            return __bool_unary_object(unary__someammo__object__ret__bool, value_);
        }

        std::string speaker(object value_) {
            return __string_unary_object(unary__speaker__object__ret__string, value_);
        }

        float speed(object value_) {
            return __number_unary_object(unary__speed__object__ret__scalar, value_);
        }

        float sqrt(float value_) {
            return __number_unary_number(unary__sqrt__scalar_nan__ret__scalar_nan, value_);
        }

        std::string stance(object value_) {
            return __string_unary_object(unary__stance__object__ret__string, value_);
        }

        void stop_engine_rtd(object value_) {
            __empty_unary_object(unary__stopenginertd__object__ret__nothing, value_);
        }

        bool stopped(object value_) {
            return __bool_unary_object(unary__stopped__object__ret__bool, value_);
        }

        void system_chat(std::string value_) {
            __empty_unary_string(unary__systemchat__string__ret__nothing, value_);
        }

        float tan(float value_) {
            return __number_unary_number(unary__tan__scalar_nan__ret__scalar_nan, value_);
        }

        std::string text(text value_) {
            return __string_unary_text(unary__text__location__ret__string, value_);
        }

        float tg(float value_) {
            return __number_unary_number(unary__tg__scalar_nan__ret__scalar_nan, value_);
        }

        void title_fade_out(float value_) {
            __empty_unary_number(unary__titlefadeout__scalar__ret__nothing, value_);
        }

        std::string to_lower(std::string value_) {
            return __string_unary_string(unary__tolower__string__ret__string, value_);
        }

        std::string to_upper(std::string value_) {
            return __string_unary_string(unary__toupper__string__ret__string, value_);
        }

        bool trigger_activated(object value_) {
            return __bool_unary_object(unary__triggeractivated__object__ret__bool, value_);
        }

        object trigger_attached_vehicle(object value_) {
            return __object_unary_object(unary__triggerattachedvehicle__object__ret__object, value_);
        }

        std::string trigger_text(object value_) {
            return __string_unary_object(unary__triggertext__object__ret__string, value_);
        }

        float trigger_timeout_current(object value_) {
            return __number_unary_object(unary__triggertimeoutcurrent__object__ret__scalar, value_);
        }

        std::string trigger_type(object value_) {
            return __string_unary_object(unary__triggertype__object__ret__string, value_);
        }

        void tv_clear(float value_) {
            __empty_unary_number(unary__tvclear__scalar__ret__nothing, value_);
        }

        void tv_clear(control value_) {
            __empty_unary_control(unary__tvclear__control__ret__nothing, value_);
        }

        std::string type_of(object value_) {
            return __string_unary_object(unary__typeof__object__ret__string, value_);
        }

        void uisleep(float value_) {
            __empty_unary_number(unary__uisleep__scalar__ret__nothing, value_);
        }

        void unassign_curator(object value_) {
            __empty_unary_object(unary__unassigncurator__object__ret__nothing, value_);
        }

        void unassign_team(object value_) {
            __empty_unary_object(unary__unassignteam__object__ret__nothing, value_);
        }

        void unassign_vehicle(object value_) {
            __empty_unary_object(unary__unassignvehicle__object__ret__nothing, value_);
        }

        bool underwater(object value_) {
            return __bool_unary_object(unary__underwater__object__ret__bool, value_);
        }

        std::string uniform(object value_) {
            return __string_unary_object(unary__uniform__object__ret__string, value_);
        }

        object uniform_container(object value_) {
            return __object_unary_object(unary__uniformcontainer__object__ret__object, value_);
        }

        object unit_backpack(object value_) {
            return __object_unary_object(unary__unitbackpack__object__ret__object, value_);
        }

        std::string unit_pos(object value_) {
            return __string_unary_object(unary__unitpos__object__ret__string, value_);
        }

        float unit_recoil_coefficient(object value_) {
            return __number_unary_object(unary__unitrecoilcoefficient__object__ret__scalar, value_);
        }

        bool unlock_achievement(std::string value_) {
            return __bool_unary_string(unary__unlockachievement__string__ret__bool, value_);
        }

        void update_object_tree(control value_) {
            __empty_unary_control(unary__updateobjecttree__control__ret__nothing, value_);
        }

        object vehicle(object value_) {
            return __object_unary_object(unary__vehicle__object__ret__object, value_);
        }

        std::string vehicle_var_name(object value_) {
            return __string_unary_object(unary__vehiclevarname__object__ret__string, value_);
        }

        bool verify_signature(std::string value_) {
            return __bool_unary_string(unary__verifysignature__string__ret__bool, value_);
        }

        std::string vest(object value_) {
            return __string_unary_object(unary__vest__object__ret__string, value_);
        }

        object vest_container(object value_) {
            return __object_unary_object(unary__vestcontainer__object__ret__object, value_);
        }

        float waypoint_timeout_current(group value_) {
            return __number_unary_group(unary__waypointtimeoutcurrent__group__ret__scalar, value_);
        }

        bool waypoints_enabled_uav(object value_) {
            return __bool_unary_object(unary__waypointsenableduav__object__ret__bool, value_);
        }

        bool weapon_lowered(object value_) {
            return __bool_unary_object(unary__weaponlowered__object__ret__bool, value_);
        }

    }
}
