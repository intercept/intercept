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

        bool cheatsenabled() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__cheatsenabled__ret__bool);
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
    }
}
