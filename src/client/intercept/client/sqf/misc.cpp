#include "chat.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"
#include <memory>

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

        std::string linebreak() {
            game_value str_ret = host::functions.invoke_raw_nular(client::__sqf::nular__linebreak__ret__text);
            std::string rv = ((game_data_string *)str_ret.data)->get_string();
            host::functions.free_value(&str_ret);
            return rv;
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
            return __helpers::__number_unary_number(client::__sqf::unary__abs__scalar_nan__ret__scalar_nan, value_);
        }

        float acos(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__acos__scalar_nan__ret__scalar_nan, value_);
        }

        std::string action_name(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__actionname__string__ret__string, value_);
        }

        void activate_key(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__activatekey__string__ret__nothing, value_);
        }

        void add_switchable_unit(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__addswitchableunit__object__ret__nothing, value_);
        }

        float air_density_rtd(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__airdensityrtd__scalar__ret__scalar, value_);
        }

        void airport_side(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__airportside__scalar__ret__nothing, value_);
        }

        bool alive(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__alive__object__ret__bool, value_);
        }

        std::string animation_state(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__animationstate__object__ret__string, value_);
        }

        float asin(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__asin__scalar_nan__ret__scalar_nan, value_);
        }

        object assigned_commander(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedcommander__object__ret__object, value_);
        }

        object assigned_driver(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assigneddriver__object__ret__object, value_);
        }

        object assigned_gunner(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedgunner__object__ret__object, value_);
        }

        object assigned_target(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedtarget__object__ret__object, value_);
        }

        std::string assigned_team(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__assignedteam__object__ret__string, value_);
        }

        object assigned_vehicle(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__assignedvehicle__object__ret__object, value_);
        }

        float atan(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__atan__scalar_nan__ret__scalar_nan, value_);
        }

        float atg(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__atg__scalar_nan__ret__scalar_nan, value_);
        }

        std::string backpack(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__backpack__object__ret__string, value_);
        }

        object backpack_container(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__backpackcontainer__object__ret__object, value_);
        }

        std::string behaviour(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__behaviour__object__ret__string, value_);
        }

        std::string binocular(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__binocular__object__ret__string, value_);
        }

        void break_out(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__breakout__string__ret__nothing, value_);
        }

        void break_to(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__breakto__string__ret__nothing, value_);
        }

        void buldozer(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__buldozer_enableroaddiag__bool__ret__nothing, value_);
        }

        bool buldozer(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__buldozer_loadnewroads__string__ret__bool, value_);
        }

        std::string button_action(control value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__buttonaction__control__ret__string, value_);
        }

        std::string button_action(float value_) {
            game_value str_ret = host::functions.invoke_raw_unary(client::__sqf::unary__buttonaction__scalar__ret__string, game_value_number(value_));
            std::string rv = ((game_data_string *)str_ret.data)->get_string();
            host::functions.free_value(&str_ret);
            return rv;
        }

        bool cam_committed(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__camcommitted__object__ret__bool, value_);
        }

        void cam_destroy(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__camdestroy__object__ret__nothing, value_);
        }

        bool cam_preloaded(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__campreloaded__object__ret__bool, value_);
        }

        object cam_target(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__camtarget__object__ret__object, value_);
        }

        void cam_use_nvg(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__camusenvg__bool__ret__nothing, value_);
        }

        void camera_effect_enable_hud(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__cameraeffectenablehud__bool__ret__nothing, value_);
        }

        float camera_interest(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__camerainterest__object__ret__scalar, value_);
        }

        bool can_fire(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canfire__object__ret__bool, value_);
        }

        bool can_move(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canmove__object__ret__bool, value_);
        }

        bool can_stand(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canstand__object__ret__bool, value_);
        }

        bool can_unload_in_combat(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__canunloadincombat__object__ret__bool, value_);
        }

        bool captive(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__captive__object__ret__bool, value_);
        }

        float captive_num(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__captivenum__object__ret__scalar, value_);
        }

        bool cb_checked(control value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__cbchecked__control__ret__bool, value_);
        }

        float ceil(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__ceil__scalar_nan__ret__scalar_nan, value_);
        }

        bool channel_enabled(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__channelenabled__scalar__ret__bool, value_);
        }

        bool check_aifeature(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__checkaifeature__string__ret__bool, value_);
        }

        void clear_all_items_from_backpack(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearallitemsfrombackpack__object__ret__nothing, value_);
        }

        void clear_backpack_cargo(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearbackpackcargo__object__ret__nothing, value_);
        }

        void clear_backpack_cargo_global(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearbackpackcargoglobal__object__ret__nothing, value_);
        }

        void clear_group_icons(group value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__cleargroupicons__group__ret__nothing, *value_);
        }

        void clear_item_cargo(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearitemcargo__object__ret__nothing, value_);
        }

        void clear_item_cargo_global(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearitemcargoglobal__object__ret__nothing, value_);
        }

        void clear_magazine_cargo(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearmagazinecargo__object__ret__nothing, value_);
        }

        void clear_magazine_cargo_global(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearmagazinecargoglobal__object__ret__nothing, value_);
        }

        void clear_overlay(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__clearoverlay__control__ret__nothing, value_);
        }

        void clear_weapon_cargo(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearweaponcargo__object__ret__nothing, value_);
        }

        void clear_weapon_cargo_global(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearweaponcargoglobal__object__ret__nothing, value_);
        }

        void close_dialog(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__closedialog__scalar__ret__nothing, value_);
        }

        void close_overlay(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__closeoverlay__control__ret__nothing, value_);
        }

        void collapse_object_tree(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__collapseobjecttree__control__ret__nothing, value_);
        }

        float collective_rtd(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__collectivertd__object__ret__scalar, value_);
        }

        object commander(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__commander__object__ret__object, value_);
        }

        void comment(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__comment__string__ret__nothing, value_);
        }

        void commit_overlay(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__commitoverlay__control__ret__nothing, value_);
        }

        bool completed_fsm(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__completedfsm__scalar__ret__bool, value_);
        }

        void copy_to_clipboard(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__copytoclipboard__string__ret__nothing, value_);
        }

        float cos(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__cos__scalar_nan__ret__scalar_nan, value_);
        }

        float count(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__count__string__ret__scalar, value_);
        }

        side create_center(side value_) {
            return nullptr; // TODO implement
        }

        bool create_dialog(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__createdialog__string__ret__bool, value_);
        }

        group create_group(side value_) {
            return nullptr; // TODO implement
        }

        void create_vehicle_crew(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__createvehiclecrew__object__ret__nothing, value_);
        }

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
            return 0.0f; // TODO implement
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
            return nullptr; // TODO implement
        }

        control ctrl_parent_controls_group(control value_) {
            return nullptr; // TODO implement
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
            return nullptr; // TODO implement
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

        float curator_camera_area_ceiling(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__curatorcameraareaceiling__object__ret__scalar, value_);
        }

        bool curator_editing_area_type(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__curatoreditingareatype__object__ret__bool, value_);
        }

        float curator_points(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__curatorpoints__object__ret__scalar, value_);
        }

        float curator_waypoint_cost(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__curatorwaypointcost__object__ret__scalar, value_);
        }

        std::string current_command(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentcommand__object__ret__string, value_);
        }

        std::string current_magazine(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmagazine__object__ret__string, value_);
        }

        std::string current_muzzle(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmuzzle__object__ret__string, value_);
        }

        float current_vision_mode(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__currentvisionmode__object__ret__scalar, value_);
        }

        float current_waypoint(group value_) {
            return 0.0f; // TODO implement
        }

        std::string current_weapon(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentweapon__object__ret__string, value_);
        }

        std::string current_weapon_mode(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentweaponmode__object__ret__string, value_);
        }

        float current_zeroing(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__currentzeroing__object__ret__scalar, value_);
        }

        float damage(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__damage__object__ret__scalar, value_);
        }

        void de_activate_key(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deactivatekey__string__ret__nothing, value_);
        }

        float debriefing_text(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__debriefingtext__string__ret__scalar, value_);
        }

        float deg(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__deg__scalar_nan__ret__scalar_nan, value_);
        }

        void delete_center(side value_) {
            // TODO implement
        }

        void delete_collection(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__deletecollection__object__ret__nothing, value_);
        }

        void delete_group(group value_) {
            // TODO implement
        }

        bool delete_identity(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__deleteidentity__string__ret__bool, value_);
        }

        void delete_marker(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarker__string__ret__nothing, value_);
        }

        void delete_marker_local(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarkerlocal__string__ret__nothing, value_);
        }

        void delete_site(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__deletesite__object__ret__nothing, value_);
        }

        bool delete_status(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__deletestatus__string__ret__bool, value_);
        }

        void delete_vehicle(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__deletevehicle__object__ret__nothing, value_);
        }

        void detach(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__detach__object__ret__nothing, value_);
        }

        bool did_jipowner(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__didjipowner__object__ret__bool, value_);
        }

        bool difficulty_enabled(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__difficultyenabled__string__ret__bool, value_);
        }

        float direction(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__direction__object__ret__scalar, value_);
        }

        void disable_remote_sensors(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__disableremotesensors__bool__ret__nothing, value_);
        }

        void disable_user_input(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__disableuserinput__bool__ret__nothing, value_);
        }

        void dissolve_team(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__dissolveteam__string__ret__nothing, value_);
        }

        object driver(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__driver__object__ret__object, value_);
        }

        void echo(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__echo__string__ret__nothing, value_);
        }

        void edit(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__edit3denmissionattributes__string__ret__nothing, value_);
        }

        object effective_commander(object value_) {
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

        void end_mission(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__endmission__string__ret__nothing, value_);
        }

        void estimated_time_left(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__estimatedtimeleft__scalar__ret__nothing, value_);
        }

        float exec_fsm(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__execfsm__string__ret__scalar, value_);
        }

        float exp(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__exp__scalar_nan__ret__scalar_nan, value_);
        }

        void export_jipmessages(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__exportjipmessages__string__ret__nothing, value_);
        }

        std::string face(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__face__object__ret__string, value_);
        }

        std::string faction(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__faction__object__ret__string, value_);
        }

        void fail_mission(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__failmission__string__ret__nothing, value_);
        }

        void fill_weapons_from_pool(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__fillweaponsfrompool__object__ret__nothing, value_);
        }

        display find_display(float value_) {
            return nullptr; // TODO implement
        }

        bool finite(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__finite__scalar_nan__ret__bool, value_);
        }

        object first_backpack(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__firstbackpack__object__ret__object, value_);
        }

        object flag(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__flag__object__ret__object, value_);
        }

        object flag_owner(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__flagowner__object__ret__object, value_);
        }

        side flag_side(object value_) {
            return nullptr; // TODO implement
        }

        std::string flag_texture(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__flagtexture__object__ret__string, value_);
        }

        bool fleeing(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__fleeing__object__ret__bool, value_);
        }

        float floor(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__floor__scalar_nan__ret__scalar_nan, value_);
        }

        void force_map(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__forcemap__bool__ret__nothing, value_);
        }

        void force_respawn(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__forcerespawn__object__ret__nothing, value_);
        }

        object form_leader(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__formleader__object__ret__object, value_);
        }

        float formation_direction(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__formationdirection__object__ret__scalar, value_);
        }

        object formation_leader(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__formationleader__object__ret__object, value_);
        }

        std::string formation_task(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__formationtask__object__ret__string, value_);
        }

        float fuel(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__fuel__object__ret__scalar, value_);
        }

        float gear_idcammo_count(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__gearidcammocount__scalar__ret__scalar, value_);
        }

        float gear_slot_ammo_count(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__gearslotammocount__control__ret__scalar, value_);
        }

        std::string gear_slot_data(control value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__gearslotdata__control__ret__string, value_);
        }

        float get_3den_action_state(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__get3denactionstate__string__ret__scalar, value_);
        }

        float get_aiming_coef(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getaimingcoef__object__ret__scalar, value_);
        }

        float get_ammo_cargo(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getammocargo__object__ret__scalar, value_);
        }

        float get_anim_aim_precision(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getanimaimprecision__object__ret__scalar, value_);
        }

        float get_anim_speed_coef(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getanimspeedcoef__object__ret__scalar, value_);
        }

        object get_assigned_curator_logic(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getassignedcuratorlogic__object__ret__object, value_);
        }

        object get_assigned_curator_unit(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getassignedcuratorunit__object__ret__object, value_);
        }

        float get_bleeding_remaining(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getbleedingremaining__object__ret__scalar, value_);
        }

        float get_burning_value(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getburningvalue__object__ret__scalar, value_);
        }

        object get_connected_uav(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getconnecteduav__object__ret__object, value_);
        }

        float get_custom_aim_coef(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getcustomaimcoef__object__ret__scalar, value_);
        }

        float get_dlcusage_time(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__getdlcusagetime__scalar__ret__scalar, value_);
        }

        float get_dammage(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getdammage__object__ret__scalar, value_);
        }

        float get_dir(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getdir__object__ret__scalar, value_);
        }

        float get_dir_visual(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getdirvisual__object__ret__scalar, value_);
        }

        object get_editor_camera(control value_) {
            return nullptr; // TODO implement
        }

        std::string get_editor_mode(control value_) {
            return __helpers::__string_unary_control(client::__sqf::unary__geteditormode__control__ret__string, value_);
        }

        float get_fatigue(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getfatigue__object__ret__scalar, value_);
        }

        float get_fuel_cargo(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getfuelcargo__object__ret__scalar, value_);
        }

        std::string get_marker_color(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkercolor__string__ret__string, value_);
        }

        std::string get_marker_type(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkertype__string__ret__string, value_);
        }

        float get_mass(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getmass__object__ret__scalar, value_);
        }

        float get_object_dlc(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getobjectdlc__object__ret__scalar, value_);
        }

        float get_object_type(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getobjecttype__object__ret__scalar, value_);
        }

        float get_oxygen_remaining(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getoxygenremaining__object__ret__scalar, value_);
        }

        float get_player_channel(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getplayerchannel__object__ret__scalar, value_);
        }

        std::string get_player_uid(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__getplayeruid__object__ret__string, value_);
        }

        float get_repair_cargo(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getrepaircargo__object__ret__scalar, value_);
        }

        float get_rotor_brake_rtd(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getrotorbrakertd__object__ret__scalar, value_);
        }

        object get_sling_load(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__getslingload__object__ret__object, value_);
        }

        float get_stamina(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getstamina__object__ret__scalar, value_);
        }

        float get_stat_value(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__getstatvalue__string__ret__scalar, value_);
        }

        float get_suppression(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getsuppression__object__ret__scalar, value_);
        }

        float get_weapon_sway(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getweaponsway__object__ret__scalar, value_);
        }

        float get_wings_orientation_rtd(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getwingsorientationrtd__object__ret__scalar, value_);
        }

        float get_wings_position_rtd(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getwingspositionrtd__object__ret__scalar, value_);
        }

        std::string goggles(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__goggles__object__ret__string, value_);
        }

        group group_from_net_id(std::string value_) {
            return nullptr; // TODO implement
        }

        std::string group_id(group value_) {
            return nullptr; // TODO implement
        }

        float group_owner(group value_) {
            return 0.0f; // TODO implement
        }

        object gunner(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__gunner__object__ret__object, value_);
        }

        std::string handgun_magazine(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__handgunmagazine__object__ret__string, value_);
        }

        std::string handgun_weapon(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__handgunweapon__object__ret__string, value_);
        }

        float hands_hit(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__handshit__object__ret__scalar, value_);
        }

        object hc_leader(group value_) {
            return nullptr; // TODO implement
        }

        void hc_remove_all_groups(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hcremoveallgroups__object__ret__nothing, value_);
        }

        void hc_show_bar(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__hcshowbar__bool__ret__nothing, value_);
        }

        std::string headgear(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__headgear__object__ret__string, value_);
        }

        void hide_body(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hidebody__object__ret__nothing, value_);
        }

        void hide_object(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hideobject__object__ret__nothing, value_);
        }

        void hide_object_global(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__hideobjectglobal__object__ret__nothing, value_);
        }

        void hint_c(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__hintc__string__ret__nothing, value_);
        }

        std::string hmd(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__hmd__object__ret__string, value_);
        }

        std::string image(std::string value_) {
            return nullptr; // TODO implement
        }

        void import_all_groups(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__importallgroups__control__ret__nothing, value_);
        }

        std::string incapacitated_state(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__incapacitatedstate__object__ret__string, value_);
        }

        bool inflamed(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__inflamed__object__ret__bool, value_);
        }

        float input_action(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__inputaction__string__ret__scalar, value_);
        }

        bool is_able_to_breathe(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isabletobreathe__object__ret__bool, value_);
        }

        bool is_aim_precision_enabled(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isaimprecisionenabled__object__ret__bool, value_);
        }

        bool is_auto_hover_on(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isautohoveron__object__ret__bool, value_);
        }

        bool is_auto_trim_on_rtd(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isautotrimonrtd__object__ret__bool, value_);
        }

        bool is_autonomous(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isautonomous__object__ret__bool, value_);
        }

        bool is_bleeding(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isbleeding__object__ret__bool, value_);
        }

        bool is_burning(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isburning__object__ret__bool, value_);
        }

        bool is_collision_light_on(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__iscollisionlighton__object__ret__bool, value_);
        }

        bool is_copilot_enabled(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__iscopilotenabled__object__ret__bool, value_);
        }

        bool is_dlcavailable(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__isdlcavailable__scalar__ret__bool, value_);
        }

        bool is_engine_on(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isengineon__object__ret__bool, value_);
        }

        bool is_forced_walk(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isforcedwalk__object__ret__bool, value_);
        }

        bool is_formation_leader(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isformationleader__object__ret__bool, value_);
        }

        bool is_hidden(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ishidden__object__ret__bool, value_);
        }

        bool is_in_remains_collector(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isinremainscollector__object__ret__bool, value_);
        }

        bool is_key_active(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__iskeyactive__string__ret__bool, value_);
        }

        bool is_light_on(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__islighton__object__ret__bool, value_);
        }

        bool is_localized(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__islocalized__string__ret__bool, value_);
        }

        bool is_manual_fire(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ismanualfire__object__ret__bool, value_);
        }

        bool is_marked_for_collection(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ismarkedforcollection__object__ret__bool, value_);
        }

        bool is_null(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isnull__object__ret__bool, value_);
        }

        bool is_null(group value_) {
            return true; // TODO implement
        }

        bool is_null(control value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__isnull__control__ret__bool, value_);
        }

        bool is_null(display value_) {
            return nullptr; // TODO implement
        }

        bool is_object_hidden(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isobjecthidden__object__ret__bool, value_);
        }

        bool is_object_rtd(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isobjectrtd__object__ret__bool, value_);
        }

        bool is_player(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isplayer__object__ret__bool, value_);
        }

        bool is_real_time(control value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__isrealtime__control__ret__bool, value_);
        }

        bool is_showing(control value_) {
            return __helpers::__bool_unary_control(client::__sqf::unary__isshowing3dicons__control__ret__bool, value_);
        }

        bool is_sprint_allowed(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__issprintallowed__object__ret__bool, value_);
        }

        bool is_stamina_enabled(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isstaminaenabled__object__ret__bool, value_);
        }

        bool is_touching_ground(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__istouchingground__object__ret__bool, value_);
        }

        bool is_turned_out(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isturnedout__object__ret__bool, value_);
        }

        bool is_uavconnected(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isuavconnected__object__ret__bool, value_);
        }

        bool is_walking(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__iswalking__object__ret__bool, value_);
        }

        bool is_weapon_deployed(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isweapondeployed__object__ret__bool, value_);
        }

        bool is_weapon_rested(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__isweaponrested__object__ret__bool, value_);
        }

        std::string key_image(float value_) {
            return nullptr; // TODO implement
        }

        std::string key_name(float value_) {
            return ""; // TODO implement
        }

        std::string land_result(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__landresult__object__ret__string, value_);
        }

        object laser_target(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__lasertarget__object__ret__object, value_);
        }

        void lb_clear(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__lbclear__control__ret__nothing, value_);
        }

        void lb_clear(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__lbclear__scalar__ret__nothing, value_);
        }

        float lb_cur_sel(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lbcursel__control__ret__scalar, value_);
        }

        float lb_cur_sel(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__lbcursel__scalar__ret__scalar, value_);
        }

        float lb_size(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lbsize__control__ret__scalar, value_);
        }

        float lb_size(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__lbsize__scalar__ret__scalar, value_);
        }

        float lb_sort(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lbsort__control__ret__scalar, value_);
        }

        float lb_sort_by_value(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lbsortbyvalue__control__ret__scalar, value_);
        }

        object leader(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__leader__object__ret__object, value_);
        }

        object leader(group value_) {
            return nullptr; // TODO implement
        }

        bool leaderboard_de_init(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__leaderboarddeinit__string__ret__bool, value_);
        }

        bool leaderboard_init(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__leaderboardinit__string__ret__bool, value_);
        }

        bool leaderboard_request_rows_friends(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__leaderboardrequestrowsfriends__string__ret__bool, value_);
        }

        float leaderboard_state(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__leaderboardstate__string__ret__scalar, value_);
        }

        std::string life_state(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__lifestate__object__ret__string, value_);
        }

        void light_detach_object(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__lightdetachobject__object__ret__nothing, value_);
        }

        std::string light_is_on(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__lightison__object__ret__string, value_);
        }

        float ln(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__ln__scalar_nan__ret__scalar_nan, value_);
        }

        void lnb_clear(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__lnbclear__control__ret__nothing, value_);
        }

        void lnb_clear(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__lnbclear__scalar__ret__nothing, value_);
        }

        float lnb_cur_sel_row(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__lnbcurselrow__control__ret__scalar, value_);
        }

        float lnb_cur_sel_row(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__lnbcurselrow__scalar__ret__scalar, value_);
        }

        float load(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__load__object__ret__scalar, value_);
        }

        float load_abs(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loadabs__object__ret__scalar, value_);
        }

        float load_backpack(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loadbackpack__object__ret__scalar, value_);
        }

        std::string load_file(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__loadfile__string__ret__string, value_);
        }

        float load_uniform(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loaduniform__object__ret__scalar, value_);
        }

        float load_vest(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__loadvest__object__ret__scalar, value_);
        }

        bool local(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__local__object__ret__bool, value_);
        }

        bool local(group value_) {
            return nullptr; // TODO implement
        }

        std::string localize(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__localize__string__ret__string, value_);
        }

        bool lock_identity(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__lockidentity__object__ret__bool, value_);
        }

        float locked(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__locked__object__ret__scalar, value_);
        }

        bool locked_driver(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__lockeddriver__object__ret__bool, value_);
        }

        float log(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__log__scalar_nan__ret__scalar_nan, value_);
        }

        float marker_alpha(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markeralpha__string__ret__scalar, value_);
        }

        std::string marker_brush(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markerbrush__string__ret__string, value_);
        }

        std::string marker_color(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markercolor__string__ret__string, value_);
        }

        float marker_dir(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markerdir__string__ret__scalar, value_);
        }

        std::string marker_shape(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markershape__string__ret__string, value_);
        }

        std::string marker_text(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markertext__string__ret__string, value_);
        }

        std::string marker_type(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markertype__string__ret__string, value_);
        }

        bool mine_active(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__mineactive__object__ret__bool, value_);
        }

        float morale(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__morale__object__ret__scalar, value_);
        }

        void move_out(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__moveout__object__ret__nothing, value_);
        }

        float move_time(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__movetime__object__ret__scalar, value_);
        }

        bool move_to_completed(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__movetocompleted__object__ret__bool, value_);
        }

        bool move_to_failed(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__movetofailed__object__ret__bool, value_);
        }

        std::string name(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__name__object__ret__string, value_);
        }

        std::string name_sound(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__namesound__object__ret__string, value_);
        }

        object nearest_building(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__nearestbuilding__object__ret__object, value_);
        }

        float need_reload(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__needreload__object__ret__scalar, value_);
        }

        std::string net_id(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__netid__object__ret__string, value_);
        }

        std::string net_id(group value_) {
            return ""; // TODO implement
        }

        float next_menu_item_index(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__nextmenuitemindex__control__ret__scalar, value_);
        }

        float number_of_engines_rtd(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__numberofenginesrtd__object__ret__scalar, value_);
        }

        object object_from_net_id(std::string value_) {
            return nullptr; // TODO implement
        }

        object object_parent(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__objectparent__object__ret__object, value_);
        }

        void on_briefing_group(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefinggroup__string__ret__nothing, value_);
        }

        void on_briefing_notes(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefingnotes__string__ret__nothing, value_);
        }

        void on_briefing_plan(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefingplan__string__ret__nothing, value_);
        }

        void on_briefing_team_switch(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__onbriefingteamswitch__string__ret__nothing, value_);
        }

        bool open_dlc_page(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__opendlcpage__scalar__ret__bool, value_);
        }

        bool open_map(bool value_) {
            return false; // TODO implement
        }

        bool open_youtube_video(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__openyoutubevideo__string__ret__bool, value_);
        }

        float owner(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__owner__object__ret__scalar, value_);
        }

        float parse_number(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__parsenumber__string__ret__scalar, value_);
        }

        float parse_number(bool value_) {
            return 0.0f; // TODO implement
        }

        std::string parse_text(std::string value_) {
            return ""; // TODO implement
        }

        void pick_weapon_pool(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__pickweaponpool__object__ret__nothing, value_);
        }

        std::string pitch(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__pitch__object__ret__string, value_);
        }

        void play_music(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__playmusic__string__ret__nothing, value_);
        }

        void play_sound(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__playsound__string__ret__nothing, value_);
        }

        float playable_slots_number(side value_) {
            return 0.0f; // TODO implement
        }

        float players_number(side value_) {
            return 0.0f; // TODO implement
        }

        bool pp_effect_committed(std::string value_) {
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

        float precision(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__precision__object__ret__scalar, value_);
        }

        bool preload_sound(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__preloadsound__string__ret__bool, value_);
        }

        std::string preprocess_file(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__preprocessfile__string__ret__string, value_);
        }

        std::string preprocess_file_line_numbers(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__preprocessfilelinenumbers__string__ret__string, value_);
        }

        std::string primary_weapon(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__primaryweapon__object__ret__string, value_);
        }

        void process_diary_link(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__processdiarylink__string__ret__nothing, value_);
        }

        void progress_loading_screen(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__progressloadingscreen__scalar__ret__nothing, value_);
        }

        float progress_position(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__progressposition__control__ret__scalar, value_);
        }

        void public_variable(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__publicvariable__string__ret__nothing, value_);
        }

        void public_variable_server(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__publicvariableserver__string__ret__nothing, value_);
        }

        void put_weapon_pool(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__putweaponpool__object__ret__nothing, value_);
        }

        float query_items_pool(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__queryitemspool__string__ret__scalar, value_);
        }

        float query_magazine_pool(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__querymagazinepool__string__ret__scalar, value_);
        }

        float query_weapon_pool(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__queryweaponpool__string__ret__scalar, value_);
        }

        float rad(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__rad__scalar_nan__ret__scalar_nan, value_);
        }

        float random(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, value_);
        }

        std::string rank(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__rank__object__ret__string, value_);
        }

        float rank_id(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__rankid__object__ret__scalar, value_);
        }

        float rating(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__rating__object__ret__scalar, value_);
        }

        void reload(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__reload__object__ret__nothing, value_);
        }

        bool reload_enabled(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__reloadenabled__object__ret__bool, value_);
        }

        bool remove(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__remove3denlayer__scalar__ret__bool, value_);
        }

        void remove_all(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__removeall3deneventhandlers__string__ret__nothing, value_);
        }

        void remove_all_actions(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallactions__object__ret__nothing, value_);
        }

        void remove_all_assigned_items(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallassigneditems__object__ret__nothing, value_);
        }

        void remove_all_containers(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcontainers__object__ret__nothing, value_);
        }

        void remove_all_curator_addons(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcuratoraddons__object__ret__nothing, value_);
        }

        void remove_all_curator_camera_areas(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcuratorcameraareas__object__ret__nothing, value_);
        }

        void remove_all_curator_editing_areas(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcuratoreditingareas__object__ret__nothing, value_);
        }

        void remove_all_handgun_items(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallhandgunitems__object__ret__nothing, value_);
        }

        void remove_all_items(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallitems__object__ret__nothing, value_);
        }

        void remove_all_items_with_magazines(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallitemswithmagazines__object__ret__nothing, value_);
        }

        void remove_all_mission_event_handlers(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__removeallmissioneventhandlers__string__ret__nothing, value_);
        }

        void remove_all_music_event_handlers(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__removeallmusiceventhandlers__string__ret__nothing, value_);
        }

        void remove_all_primary_weapon_items(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallprimaryweaponitems__object__ret__nothing, value_);
        }

        void remove_all_weapons(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallweapons__object__ret__nothing, value_);
        }

        void remove_backpack(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removebackpack__object__ret__nothing, value_);
        }

        void remove_backpack_global(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removebackpackglobal__object__ret__nothing, value_);
        }

        void remove_goggles(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removegoggles__object__ret__nothing, value_);
        }

        void remove_headgear(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeheadgear__object__ret__nothing, value_);
        }

        void remove_switchable_unit(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeswitchableunit__object__ret__nothing, value_);
        }

        void remove_uniform(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeuniform__object__ret__nothing, value_);
        }

        void remove_vest(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removevest__object__ret__nothing, value_);
        }

        bool required_version(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__requiredversion__string__ret__bool, value_);
        }

        void reset_subgroup_direction(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__resetsubgroupdirection__object__ret__nothing, value_);
        }

        void restart_editor_camera(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__restarteditorcamera__control__ret__nothing, value_);
        }

        std::string role_description(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__roledescription__object__ret__string, value_);
        }

        bool rope_attach_enabled(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ropeattachenabled__object__ret__bool, value_);
        }

        object rope_attached_to(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__ropeattachedto__object__ret__object, value_);
        }

        void rope_destroy(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__ropedestroy__object__ret__nothing, value_);
        }

        float rope_length(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__ropelength__object__ret__scalar, value_);
        }

        bool rope_unwound(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__ropeunwound__object__ret__bool, value_);
        }

        float round(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__round__scalar_nan__ret__scalar_nan, value_);
        }

        void save_overlay(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__saveoverlay__control__ret__nothing, value_);
        }

        void save_var(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__savevar__string__ret__nothing, value_);
        }

        void scope_name(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__scopename__string__ret__nothing, value_);
        }

        float score(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__score__object__ret__scalar, value_);
        }

        float score_side(side value_) {
            return 0.0f; // TODO implement
        }

        void script_name(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__scriptname__string__ret__nothing, value_);
        }

        float scud_state(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__scudstate__object__ret__scalar, value_);
        }

        std::string secondary_weapon(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__secondaryweapon__object__ret__string, value_);
        }

        void select_player(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__selectplayer__object__ret__nothing, value_);
        }

        void selected_editor_objects(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__selectededitorobjects__control__ret__nothing, value_);
        }

        bool server_command(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__servercommand__string__ret__bool, value_);
        }

        bool server_command_available(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__servercommandavailable__string__ret__bool, value_);
        }

        bool server_command_executable(std::string value_) {
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

        void set_group_icons_selectable(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__setgroupiconsselectable__bool__ret__nothing, value_);
        }

        void set_horizon_parallax_coef(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__sethorizonparallaxcoef__scalar__ret__nothing, value_);
        }

        void set_object_view_distance(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setobjectviewdistance__scalar__ret__nothing, value_);
        }

        void set_playable(object value_) {
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

        void set_stamina_scheme(std::string value_) {
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

        void show_commanding_menu(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__showcommandingmenu__string__ret__nothing, value_);
        }

        void show_compass(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showcompass__bool__ret__nothing, value_);
        }

        void show_curator_compass(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showcuratorcompass__bool__ret__nothing, value_);
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

        bool show_subtitles(bool value_) {
            return false; // TODO implement
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

        bool simulation_enabled(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__simulationenabled__object__ret__bool, value_);
        }

        float sin(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__sin__scalar_nan__ret__scalar_nan, value_);
        }

        float size_of(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__sizeof__string__ret__scalar, value_);
        }

        float skill(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__skill__object__ret__scalar, value_);
        }

        void skip_time(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__skiptime__scalar__ret__nothing, value_);
        }

        void sleep(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__sleep__scalar__ret__nothing, value_);
        }

        float slider_position(control value_) {
            return __helpers::__number_unary_control(client::__sqf::unary__sliderposition__control__ret__scalar, value_);
        }

        float slider_position(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__sliderposition__scalar__ret__scalar, value_);
        }

        bool some_ammo(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__someammo__object__ret__bool, value_);
        }

        std::string speaker(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__speaker__object__ret__string, value_);
        }

        float speed(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__speed__object__ret__scalar, value_);
        }

        float sqrt(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__sqrt__scalar_nan__ret__scalar_nan, value_);
        }

        std::string stance(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__stance__object__ret__string, value_);
        }

        void stop_engine_rtd(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__stopenginertd__object__ret__nothing, value_);
        }

        bool stopped(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__stopped__object__ret__bool, value_);
        }

        void system_chat(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__systemchat__string__ret__nothing, value_);
        }

        float tan(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__tan__scalar_nan__ret__scalar_nan, value_);
        }

        std::string text(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__text__location__ret__string, value_);
        }

        float tg(float value_) {
            return __helpers::__number_unary_number(client::__sqf::unary__tg__scalar_nan__ret__scalar_nan, value_);
        }

        void title_fade_out(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__titlefadeout__scalar__ret__nothing, value_);
        }

        std::string to_lower(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__tolower__string__ret__string, value_);
        }

        std::string to_upper(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__toupper__string__ret__string, value_);
        }

        bool trigger_activated(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__triggeractivated__object__ret__bool, value_);
        }

        object trigger_attached_vehicle(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__triggerattachedvehicle__object__ret__object, value_);
        }

        std::string trigger_text(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__triggertext__object__ret__string, value_);
        }

        float trigger_timeout_current(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__triggertimeoutcurrent__object__ret__scalar, value_);
        }

        std::string trigger_type(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__triggertype__object__ret__string, value_);
        }

        void tv_clear(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__tvclear__scalar__ret__nothing, value_);
        }

        void tv_clear(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__tvclear__control__ret__nothing, value_);
        }

        std::string type_of(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__typeof__object__ret__string, value_);
        }

        void uisleep(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__uisleep__scalar__ret__nothing, value_);
        }

        void unassign_curator(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__unassigncurator__object__ret__nothing, value_);
        }

        void unassign_team(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__unassignteam__object__ret__nothing, value_);
        }

        void unassign_vehicle(object value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__unassignvehicle__object__ret__nothing, value_);
        }

        bool underwater(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__underwater__object__ret__bool, value_);
        }

        std::string uniform(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__uniform__object__ret__string, value_);
        }

        object uniform_container(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__uniformcontainer__object__ret__object, value_);
        }

        object unit_backpack(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__unitbackpack__object__ret__object, value_);
        }

        std::string unit_pos(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__unitpos__object__ret__string, value_);
        }

        float unit_recoil_coefficient(object value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__unitrecoilcoefficient__object__ret__scalar, value_);
        }

        bool unlock_achievement(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__unlockachievement__string__ret__bool, value_);
        }

        void update_object_tree(control value_) {
            __helpers::__empty_unary_control(client::__sqf::unary__updateobjecttree__control__ret__nothing, value_);
        }

        object vehicle(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__vehicle__object__ret__object, value_);
        }

        std::string vehicle_var_name(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__vehiclevarname__object__ret__string, value_);
        }

        bool verify_signature(std::string value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__verifysignature__string__ret__bool, value_);
        }

        std::string vest(object value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__vest__object__ret__string, value_);
        }

        object vest_container(object value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__vestcontainer__object__ret__object, value_);
        }

        float waypoint_timeout_current(group value_) {
            return 0.0f; // TODO implement
        }

        bool waypoints_enabled_uav(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__waypointsenableduav__object__ret__bool, value_);
        }

        bool weapon_lowered(object value_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__weaponlowered__object__ret__bool, value_);
        }


    }
}
