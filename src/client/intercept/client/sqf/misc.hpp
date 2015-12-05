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


		bool visible_watch();
		bool visible_map();
		bool visible_gps();
		bool visible_compass();
		float view_distance();

        float save_zone_x();
        float save_zone_y();
        float save_zone_h();
        float save_zone_w();
        float save_zone_x_abs();
        float save_zone_w_abs();

        float diag_fps();
        float diag_fpsmin();
        float diag_frameno();
        float diag_ticktime();

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
