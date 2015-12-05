#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"
#include<vector>

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        float random(float max_);

        float acc_time();
        std::vector<std::string> activated_addons();
        std::vector<team_member> agents();
        //std::vector<?> airdensity_curvertd(); // no entry on the biki

        float armorypoints();
        float benchmark();
        side blufor();
        std::string briefingname();
        bool cadetmode();
        object cameraon();
        std::string cameraview();
        config campaignconfigfile();
        bool cheatsenabled();
        side civilian();
        void clearforcesrtd();
        void clearitempool();
        void clearmagazinepool();
        void clearradio();
        void clearweaponpool();
        float clientowner();
        std::string commandingmenu();
        config configfile();
        config confignull();
        control controlnull();
        std::string copyfromclipboard();
        object curatorcamera();
        object curatormouseover();
        std::vector<object> curatorselected();
        std::string current3denoperation();
        float currentchannel();
        rv_namespace currentnamespace();
        object cursortarget();
        std::vector<float> date();
        float daytime();
        std::vector<script> diag_activemissionfsms();
        std::vector<script> diag_activesqfscripts();
        std::vector<script> diag_activesqsscripts();
        float diag_fps();
        float diag_fpsmin();
        float diag_frameno();
        float diag_ticktime();

        bool dialog();
        bool didjip();
        float difficulty();
        bool difficultyenabledrtd();
        void disabledebriefingstats();
        void disableserialization();
        display displaynull();
        float distributionregion();
        side east();
        void enableenddialog();
        void endloadingscreen();
        float estimatedendservertime();
        void exit();
        void finishmissioninit();
        bool fog();
        float fogforecast();
        std::vector<float> fogparams();
        void forceend();
        void forceweatherchange();
        bool freelook();
        object get3dencamera();
        bool get3deniconsvisible();
        bool get3denlinesvisible();
        // TODO array[] get3denmouseover(); //      Array in format: [type,Eden Entity], where type can be: "Object", "Group", "Trigger", "Logic", "Waypoint" or "Marker" 
        // TODO array[] getartillerycomputersettings(); // ["Semi (medium)","HE Mortar Shells",0]
        std::string getclientstate();
        // TODO not on biki getdlcassetsusage();
        float getelevationoffset();
        // TODO not on biki std::vector<std::string> getmissiondlcs();
        std::array<float, 2> getmouseposition();
        std::array<float, 2> getobjectviewdistance();
        bool getremotesensorsdisabled();
        std::array<float,6> getresolution();
        float getshadowdistance();
        float gettotaldlcusagetime();
        bool groupiconselectable();
        std::array<bool,2> groupiconsvisible();
        group grpnull();
        float gusts();
        void halt();
        bool hasinterface();
        bool hcshownbar();
        // TODO hud_movement_levels hudmovementlevels();
        float humidity();
        side independent();
        void initambientlife();
        bool is3den();
        bool is3denmultiplayer();
        bool isautotest();
        bool isdedicated();
        bool isfilepatchingenabled();
        bool isinstructorfigureenabled();
        bool ismultiplayer();
        bool ispipenabled();
        bool isserver();
        bool issteammission();
        bool isstreamfriendlyuienabled();
        bool isstressdamageenabled();
        bool istuthintsenabled();
        std::string language();
        std::vector<std::array<std::string,2>> librarycredits();
        std::vector<std::string> librarydisclaimers();
        float lightnings();
        text linebreak();
        void loadgame();
        location locationnull();
        void logentities();
        void mapanimclear();
        void mapanimcommit();
        bool mapanimdone();
        bool markasfinishedonsteam();
        config missionconfigfile();
        float missiondifficulty();
        std::string missionname();
        rv_namespace missionnamespace();
        std::array<float, 6> missionstart();
        float moonintensity();
        float musicvolume();
        float nextweatherchange();
        object objnull();
        void opencuratorinterface();
        side opfor();
        float overcast();
        float overcastforecast();
        rv_namespace parsingnamespace();
        float particlesquality();
        float pi();
        float pixelh();
        float pixelw();
        std::vector<object> playableunits();
        object player();
        float playerrespawntime();
        side playerside();
        // TODO implement product_version productversion();
        std::string profilename();
        rv_namespace profilenamespace();
        std::string profilenamesteam();
        float radiovolume();
        float rain();
        float rainbow();
        void resetcamshake();
        side resistance();
        bool reversedmousey();
        void runinitscript();
        
		bool visible_watch();
		bool visible_map();
		bool visible_gps();
		bool visible_compass();

        float save_zone_x();
        float save_zone_y();
        float save_zone_h();
        float save_zone_w();
        float save_zone_x_abs();
        float save_zone_w_abs();

        bool shown_artillerycomputer();
        bool shown_chat();
        bool shown_compass();
        bool shown_curatorcompass();
        bool shown_gps();
        bool shown_hud();
        bool shown_map();
        bool shown_pad();
        bool shown_radio();
        bool shown_uavfeed();
        bool shown_warrant();
        bool shown_watch();

    }
}
