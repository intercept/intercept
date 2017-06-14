#include "eventhandlers.hpp"
#include <random>
#include "sqf.hpp"

namespace intercept::client {

    intercept::types::game_value client_eventhandler(int ehType, uint32_t uid, float handle, game_value args) {
        switch (static_cast<eventhandler_type>(ehType)) {
        case eventhandler_type::mission: {
            auto found = funcMapMissionEH.find({ uid,handle });
            if (found != funcMapMissionEH.end())
                return callEHHandler(found->second.first, args, found->second.second);
        }break;
        case eventhandler_type::generic: break;
        case eventhandler_type::display: break;
        default:;
        }
        return {};
    }

#pragma region Mission Eventhandlers
    std::unordered_map<EHIdentifier, std::pair<eventhandlers_mission, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMissionEH;

    EHIdentifier addScriptEH(eventhandlers_mission type) {
        std::default_random_engine rng(std::random_device{}());
        std::uniform_int_distribution<uint32_t> dist;

        r_string typeStr;
        //#TODO eachFrame is just redirector to InvokePeriod.
        switch (type) {
        case eventhandlers_mission::Draw3D: typeStr = "Draw3D"; break;
        case eventhandlers_mission::Ended: typeStr = "Ended"; break;
        case eventhandlers_mission::Loaded: typeStr = "Loaded"; break;
        case eventhandlers_mission::Map: typeStr = "Map"; break;
        case eventhandlers_mission::HandleDisconnect: typeStr = "HandleDisconnect"; break;
        case eventhandlers_mission::EntityRespawned: typeStr = "EntityRespawned"; break;
        case eventhandlers_mission::EntityKilled: typeStr = "EntityKilled"; break;
        case eventhandlers_mission::EachFrame: typeStr = "EachFrame"; break;
        case eventhandlers_mission::MapSingleClick: typeStr = "MapSingleClick"; break;
        case eventhandlers_mission::HCGroupSelectionChanged:  typeStr = "HCGroupSelectionChanged"; break;
        case eventhandlers_mission::CommandModeChanged: typeStr = "CommandModeChanged"; break;
        case eventhandlers_mission::GroupIconClick: typeStr = "GroupIconClick"; break;
        case eventhandlers_mission::GroupIconOverEnter: typeStr = "GroupIconOverEnter"; break;
        case eventhandlers_mission::GroupIconOverLeave: typeStr = "GroupIconOverLeave"; break;
        case eventhandlers_mission::PlayerConnected: typeStr = "PlayerConnected"; break;
        case eventhandlers_mission::PlayerDisconnected: typeStr = "PlayerDisconnected"; break;
        case eventhandlers_mission::TeamSwitch: typeStr = "TeamSwitch"; break;
        case eventhandlers_mission::PreloadStarted: typeStr = "PreloadStarted"; break;
        case eventhandlers_mission::PreloadFinished: typeStr = "PreloadFinished"; break;
        case eventhandlers_mission::PlayerViewChanged: typeStr = "PlayerViewChanged"; break;
        case eventhandlers_mission::BuildingChanged: typeStr = "BuildingChanged"; break;
        default:;
        }

        auto uid = dist(rng);
        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\"")
            + intercept::client::host::module_name.data() + "\","
            + std::to_string(static_cast<uint32_t>(eventhandler_type::mission)) + ","
            + std::to_string(uid) + ","
            + "_thisEventHandler"
            + "]"
            + " InterceptClientEvent _this";
        float ehid = intercept::sqf::add_mission_event_handler(static_cast<sqf_string>(typeStr), command);

        return { uid, ehid };
    }

//#define EH_Add_Mission_definition(name,retVal,fncArg)\
//template<> \
//[[nodiscard]] EHIdentifier addMissionEventHandler<eventhandlers_mission::name, std::function<retVal(fncArg)>>(std::function<retVal(fncArg)> function) {\
//    auto ident = addScriptEH(eventhandlers_mission::name);\
//    funcMapMissionEH[ident] = {eventhandlers_mission::name,std::make_shared < std::function<void()> >(*reinterpret_cast<std::function<void()>*>(&function))};\
//    return ident;\
//}
//
//EHDEF_MISSION(EH_Add_Mission_definition)

#pragma endregion
}
