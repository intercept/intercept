#include <random>
#include "eventhandlers.hpp"
#ifndef INTERCEPT_NO_SQF
#include "sqf.hpp"
#endif

namespace intercept::types {
    extern bool exiting;
};
namespace intercept::client {

    /// @private
    uint32_t EHIteration = 0; //How often the EH's have been cleared yet. Used to detect invalid removeEH calls

    //Not in header because these are Internal functions that shall not be messed with
    /// @private
    extern "C" DLLEXPORT void CDECL client_eventhandler(intercept::types::game_value& retVal, uint8_t ehType, int32_t uid, int handle, intercept::types::game_value args);
    /// @private
    extern "C" DLLEXPORT void CDECL client_eventhandlers_clear();
    /// @private
    void client_eventhandler(intercept::types::game_value& retVal, uint8_t ehType, int32_t uid, int handle, intercept::types::game_value args) {
#ifndef INTERCEPT_NO_SQF
        switch (static_cast<eventhandler_type>(ehType)) {
            case eventhandler_type::mission: {
                auto found = funcMapMissionEH.find({uid, handle, EHIteration, ehType });
                if (found != funcMapMissionEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;

			case eventhandler_type::object: {
                auto found = funcMapObjectEH.find({uid, handle, EHIteration, ehType });
                if (found != funcMapObjectEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;

			case eventhandler_type::ctrl: {
                auto found = funcMapCtrlEH.find({uid, handle, EHIteration, ehType });
                if (found != funcMapCtrlEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;

			case eventhandler_type::mp: {
                auto found = funcMapMPEH.find({ uid, handle, EHIteration, ehType });
                if (found != funcMapMPEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;

			case eventhandler_type::display: {
                auto found = funcMapDisplayEH.find({ uid, handle, EHIteration, ehType });
                if (found != funcMapDisplayEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;

			case eventhandler_type::custom: {
                auto found = customCallbackMap.find({ uid, handle, 0 });
                if (found != customCallbackMap.end())
                    retVal = (*found->second)(args);
            } break;
            default:;
        }
#endif
        return;
    }
    /// @private
    void client_eventhandlers_clear() {
#ifndef INTERCEPT_NO_SQF
        funcMapMissionEH.clear();
        funcMapObjectEH.clear();
        funcMapCtrlEH.clear();
        funcMapMPEH.clear();
        funcMapDisplayEH.clear();
#endif
        EHIteration++;
    }

#ifndef INTERCEPT_NO_SQF
#pragma region Mission Eventhandlers
    std::unordered_map<EHIdentifier, std::pair<eventhandlers_mission, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMissionEH;

    EHIdentifierHandle::impl::~impl() {
        if (!exiting)
            onDelete(ident);
    }

    intercept::types::game_value callEHHandler(eventhandlers_mission ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {
            case eventhandlers_mission::PreloadStarted: //[[fallthrough]]
            case eventhandlers_mission::PreloadFinished: //[[fallthrough]]
            case eventhandlers_mission::EachFrame: //[[fallthrough]]
            case eventhandlers_mission::MPEnded: //[[fallthrough]]
            case eventhandlers_mission::Draw3D: {
                (*func)();
            } break;

            case eventhandlers_mission::Ended: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_Ended)>*>(func.get()))(args[0]);
            } break;

            case eventhandlers_mission::Loaded: {
                auto type = static_cast<intercept::types::r_string>(args[0]);
                loaded_saveType type_ = {};
                if (type == "save"sv)
                    type_ = loaded_saveType::save;
                else if (type == "autosave"sv)
                    type_ = loaded_saveType::autosave;
                else if (type == "continue"sv)
                    type_ = loaded_saveType::continuesave;
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_Loaded)>*>(func.get()))(type_);
            } break;

            case eventhandlers_mission::Map: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_Map)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_mission::HandleDisconnect: {
                auto ret = (*reinterpret_cast<std::function<std::optional<bool>(EH_Func_Args_Mission_HandleDisconnect)>*>(func.get()))(args[0], args[1], args[2], args[3]);
                if (ret) return *ret;
            } break;

            case eventhandlers_mission::EntityRespawned: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_EntityRespawned)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_mission::EntityKilled: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_EntityKilled)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

            case eventhandlers_mission::MapSingleClick: {
                auto& arr = args[0].to_array();
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_MapSingleClick)>*>(func.get()))(intercept::types::auto_array<intercept::types::object>(arr.begin(), arr.end()), args[1], args[2], args[3]);
            } break;

            case eventhandlers_mission::HCGroupSelectionChanged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_HCGroupSelectionChanged)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_mission::CommandModeChanged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_CommandModeChanged)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_mission::GroupIconClick: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_GroupIconClick)>*>(func.get()))(args[0], args[1], args[2], args[3], {args[4], args[5]}, args[6], args[7], args[8]);
            } break;

            case eventhandlers_mission::GroupIconOverEnter: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_GroupIconOverEnter)>*>(func.get()))(args[0], args[1], args[2], args[3], {args[4], args[5]}, args[6], args[7], args[8]);
            } break;

            case eventhandlers_mission::GroupIconOverLeave: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_GroupIconOverLeave)>*>(func.get()))(args[0], args[1], args[2], args[3], {args[4], args[5]}, args[6], args[7], args[8]);
            } break;

            case eventhandlers_mission::PlayerConnected: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_PlayerConnected)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

            case eventhandlers_mission::PlayerDisconnected: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_PlayerDisconnected)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

            case eventhandlers_mission::TeamSwitch: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_TeamSwitch)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_mission::PlayerViewChanged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_PlayerViewChanged)>*>(func.get()))(args[0], args[1], args[1], args[2], args[3], args[4]);
            } break;

            case eventhandlers_mission::BuildingChanged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_BuildingChanged)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_mission::ControlsShifted: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_ControlsShifted)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

            case eventhandlers_mission::ExtensionCallback: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_ExtensionCallback)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_mission::HandleAccTime : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_HandleAccTime)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_mission::HandleChatMessage : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_HandleChatMessage)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10]);
            } break;

            case eventhandlers_mission::MarkerCreated : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_MarkerCreated)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

            case eventhandlers_mission::MarkerDeleted : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_MarkerDeleted)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_mission::MarkerUpdated : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_MarkerUpdated)>*>(func.get()))(args[0], args[1]);
            } break;

            default: ;
        }
        return {};
    }

    EHIdentifier addScriptEH(eventhandlers_mission type) {
        r_string typeStr;
        //#TODO eachFrame is just redirector to InvokePeriod.
        switch (type) {
#define EHMISS_CASE(name, retVal, args) \
    case eventhandlers_mission::name: typeStr = #name##sv; break;
            EHDEF_MISSION(EHMISS_CASE)
            default:;
        }

        //16'777'216 is the maximum float that can be cast "accurately" to an int;
        //In addition, 2^32 (max unsigned int) is divisible by that number and thus wrap-around is safe (no collisions)
        static unsigned int uid_mission = 0;
        int uid = (int)((uid_mission++) % 33'554'432) - 16'777'216;

        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\""sv)
                              + intercept::client::host::module_name.data() + "\"," //modulename
                              + std::to_string(static_cast<uint32_t>(eventhandler_type::mission)) + "," //EHType
                              + std::to_string(uid) + "," //UID
                              + "_thisEventHandler] InterceptClientEvent [_this]";
        int ehid = intercept::sqf::add_mission_event_handler(static_cast<sqf_string_const_ref>(typeStr), command);

        return {uid, ehid, EHIteration, static_cast<uint8_t>(eventhandler_type::mission)};
    }

    void delScriptEH(eventhandlers_mission type, EHIdentifier& handle) {
        if (handle.EHIteration != EHIteration || handle.already_deleted) return;//Handle not valid anymore
        r_string typeStr;
        switch (type) {
            EHDEF_MISSION(EHMISS_CASE)
            default:;
        }
        sqf::remove_mission_event_handler(static_cast<sqf_string_const_ref>(typeStr), handle.arma_eh_id);
    }

#pragma endregion

#pragma region Object Eventhandlers

    std::unordered_map<EHIdentifier, std::pair<eventhandlers_object, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapObjectEH;

    intercept::types::game_value callEHHandler(eventhandlers_object ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {
            case eventhandlers_object::AnimChanged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::AnimDone: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimDone)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::AnimStateChanged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimStateChanged)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::ContainerClosed: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_ContainerClosed)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::ContainerOpened: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_ContainerOpened)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::ControlsShifted: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_ControlsShifted)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::Dammaged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Dammaged)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            } break;

            case eventhandlers_object::Deleted: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Deleted)>*>(func.get()))(args[0]);
            } break;

            case eventhandlers_object::Engine: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Engine)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::EpeContact: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_EpeContact)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

            case eventhandlers_object::EpeContactEnd: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_EpeContactEnd)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

            case eventhandlers_object::EpeContactStart: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_EpeContactStart)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

            case eventhandlers_object::Explosion: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Explosion)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::Fired: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Fired)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
            } break;

            case eventhandlers_object::FiredMan: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_FiredMan)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
            } break;

            case eventhandlers_object::FiredNear: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_FiredNear)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
            } break;

            case eventhandlers_object::Fuel: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Fuel)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::Gear: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Gear)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::GetIn: {
                types::r_string pos = args[1];
                get_in_position p{};
                if (pos == "driver"sv)
                    p = get_in_position::driver;
                else if (pos == "gunner"sv)
                    p = get_in_position::gunner;
                else if (pos == "cargo"sv)
                    p = get_in_position::cargo;
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetIn)>*>(func.get()))(args[0], p, args[2], types::rv_turret_path(args[3]));
            } break;

            case eventhandlers_object::GetInMan: {
                types::r_string pos = args[1];
                get_in_position p{};
                if (pos == "driver"sv)
                    p = get_in_position::driver;
                else if (pos == "gunner"sv)
                    p = get_in_position::gunner;
                else if (pos == "cargo"sv)
                    p = get_in_position::cargo;
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetInMan)>*>(func.get()))(args[0], p, args[2], types::rv_turret_path(args[3]));
            } break;

            case eventhandlers_object::GetOut: {
                types::r_string pos = args[1];
                get_in_position p{};
                if (pos == "driver"sv)
                    p = get_in_position::driver;
                else if (pos == "gunner"sv)
                    p = get_in_position::gunner;
                else if (pos == "cargo"sv)
                    p = get_in_position::cargo;
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetOut)>*>(func.get()))(args[0], p, args[2], types::rv_turret_path(args[3]));
            } break;

            case eventhandlers_object::GetOutMan: {
                types::r_string pos = args[1];
                get_in_position p{};
                if (pos == "driver"sv)
                    p = get_in_position::driver;
                else if (pos == "gunner"sv)
                    p = get_in_position::gunner;
                else if (pos == "cargo"sv)
                    p = get_in_position::cargo;
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetOutMan)>*>(func.get()))(args[0], p, args[2], types::rv_turret_path(args[3]));
            } break;

            case eventhandlers_object::HandleDamage: {
                auto ret = (*reinterpret_cast<std::function<std::optional<float>(EH_Func_Args_Object_HandleDamage)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
                if (ret) return *ret;
            } break;

            case eventhandlers_object::HandleHeal: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_HandleHeal)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::HandleRating: {
                auto ret = (*reinterpret_cast<std::function<std::optional<float>(EH_Func_Args_Object_HandleRating)>*>(func.get()))(args[0], args[1]);
                if (ret) return *ret;
            } break;

            case eventhandlers_object::HandleScore: {
                auto ret = (*reinterpret_cast<std::function<std::optional<bool>(EH_Func_Args_Object_HandleScore)>*>(func.get()))(args[0], args[1], args[2]);
                if (ret) return *ret;
            } break;
                
            case eventhandlers_object::Hit: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Hit)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;
                
            case eventhandlers_object::HitPart: {
                std::vector<eventhandler_hit_part_type> vec;
                for (auto& el : args.to_array()) {
                    vec.emplace_back(el);
                }

                (*reinterpret_cast<std::function<void(std::vector<eventhandler_hit_part_type>)>*>(func.get()))(std::move(vec));
            } break;
                
            case eventhandlers_object::Init: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Init)>*>(func.get()))(args[0]);
            } break;
                
            case eventhandlers_object::HandleIdentity: {
                auto ret = (*reinterpret_cast<std::function<std::optional<bool>(EH_Func_Args_Object_HandleIdentity)>*>(func.get()))(args[0]);
                if (ret) return *ret;
            } break;

            case eventhandlers_object::IncomingMissile: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_IncomingMissile)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

            case eventhandlers_object::InventoryClosed: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_InventoryClosed)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::InventoryOpened: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_InventoryOpened)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::Killed: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Killed)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

            case eventhandlers_object::LandedTouchDown: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_LandedTouchDown)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::LandedStopped: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_LandedStopped)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::Landing: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Landing)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::LandingCanceled: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_LandingCanceled)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::Local: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Local)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::PostReset: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_PostReset)>*>(func.get()))();
            } break;

            case eventhandlers_object::Put: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Put)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::Reloaded: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Reloaded)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4].to_array(), args[5].to_array());
            } break;

            case eventhandlers_object::Respawn: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Respawn)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::RopeAttach: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_RopeAttach)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

			case eventhandlers_object::RopeBreak: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_RopeBreak)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::SeatSwitched: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_SeatSwitched)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::SeatSwitchedMan: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_SeatSwitchedMan)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::SoundPlayed: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_SoundPlayed)>*>(func.get()))(args[0], static_cast<sound_played_origin>(static_cast<int>(args[1])));
            } break;

            case eventhandlers_object::Take: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Take)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::TaskSetAsCurrent: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_TaskSetAsCurrent)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::TurnIn: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_TurnIn)>*>(func.get()))(args[0], args[1], types::rv_turret_path(args[2]));
            } break;

            case eventhandlers_object::TurnOut: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_TurnOut)>*>(func.get()))(args[0], args[1], types::rv_turret_path(args[2]));
            } break;

            case eventhandlers_object::WeaponAssembled: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_WeaponAssembled)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::WeaponDisassembled: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_WeaponDisassembled)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::WeaponDeployed: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_WeaponDeployed)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::WeaponRested: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_WeaponRested)>*>(func.get()))(args[0], args[1]);
            } break;

            case eventhandlers_object::Disassembled : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Disassembled)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

            case eventhandlers_object::PathCalculated: {
                auto& arr_ = args[1].to_array();
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_PathCalculated)>*>(func.get()))(args[0], auto_array<types::vector3>(arr_.begin(), arr_.end()));
            } break;

            case eventhandlers_object::PeriscopeElevationChanged : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_PeriscopeElevationChanged)>*>(func.get()))(args[0], types::rv_turret_path(args[1]), args[2], args[3], args[4]);
            } break;

            case eventhandlers_object::Suppressed : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_Suppressed)>*>(func.get()))(args[0], args[1], args[2],args[3], args[4], args[5], args[6]);
            } break;

            default: assert(false);
        }
        return {};
    }

    EHIdentifier addScriptEH(types::object obj, eventhandlers_object type) {
        r_string typeStr;
        //#TODO eachFrame is just redirector to InvokePeriod.
        switch (type) {
#define EHOBJ_CASE(name, retVal, args) \
    case eventhandlers_object::name: typeStr = #name##sv; break;
            EHDEF_OBJECT(EHOBJ_CASE)
            case eventhandlers_object::HitPart: typeStr = "HitPart"sv; break;
            default:;
        }

        //16'777'216 is the maximum float that can be cast "accurately" to an int;
        //In addition, 2^32 (max unsigned int) is divisible by that number and thus wrap-around is safe (no collisions)
        static unsigned int uid_obj = 0;
        int uid = (int)((uid_obj++) % 33'554'432) - 16'777'216;
        
        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("['")
                              + intercept::client::host::module_name.data() + "',"
                              + std::to_string(static_cast<uint32_t>(eventhandler_type::object)) + ","
                              + std::to_string(uid) + ","
                              + "_thisEventHandler] InterceptClientEvent [_this]";
        int ehid = intercept::sqf::add_event_handler(obj, static_cast<sqf_string_const_ref>(typeStr), command);

        return {uid, ehid, EHIteration, static_cast<uint8_t>(eventhandler_type::object)};
    }

    void delScriptEH(types::object obj, eventhandlers_object type, EHIdentifier& handle) {
        if (handle.EHIteration != EHIteration || handle.already_deleted) return;//Handle not valid anymore
        r_string typeStr;
        switch (type) {
            EHDEF_OBJECT(EHOBJ_CASE)
            case eventhandlers_object::HitPart: typeStr = "HitPart"sv; break;
        default:;
        }
        sqf::remove_event_handler(obj, static_cast<sqf_string_const_ref>(typeStr), handle.arma_eh_id);
    }
#pragma endregion

#pragma region Ctrl Eventhandlers
    std::unordered_map<EHIdentifier, std::pair<eventhandlers_ctrl, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapCtrlEH;

    intercept::types::game_value callEHHandler(eventhandlers_ctrl ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {
            case eventhandlers_ctrl::Draw : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_Draw)>*>(func.get()))(args[0]);
            } break;

			case eventhandlers_ctrl::MouseButtonDown : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_MouseButtonDown)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            } break;

			case eventhandlers_ctrl::MouseButtonUp : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_MouseButtonUp)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            } break;

			case eventhandlers_ctrl::MouseButtonClick : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_MouseButtonClick)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            } break;

			case eventhandlers_ctrl::MouseButtonDblClick : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_MouseButtonDblClick)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            } break;

			case eventhandlers_ctrl::MouseMoving : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_MouseMoving)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

			case eventhandlers_ctrl::MouseHolding : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_MouseHolding)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

			case eventhandlers_ctrl::ButtonClick : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_ButtonClick)>*>(func.get()))(args[0]);
            } break;

			case eventhandlers_ctrl::ButtonDblClick : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_ButtonDblClick)>*>(func.get()))(args[0]);
            } break;

			case eventhandlers_ctrl::ButtonDown : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_ButtonDown)>*>(func.get()))(args[0]);
            } break;

			case eventhandlers_ctrl::ButtonUp : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_ButtonUp)>*>(func.get()))(args[0]);
            } break;

			case eventhandlers_ctrl::CanDestroy : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_CanDestroy)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_ctrl::Char : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_Char)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_ctrl::CheckBoxesSelChanged : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_CheckBoxesSelChanged)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

			case eventhandlers_ctrl::CheckedChanged : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_CheckedChanged)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_ctrl::Destroy : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_Destroy)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_ctrl::HTMLLink : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_HTMLLink)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_ctrl::IMEChar : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_IMEChar)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_ctrl::IMEComposition : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_IMEComposition)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_ctrl::KeyDown : {
                return (*reinterpret_cast<std::function<bool(EH_Func_Args_Ctrl_KeyDown)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

			case eventhandlers_ctrl::KeyUp : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_KeyUp)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

			case eventhandlers_ctrl::KillFocus : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_KillFocus)>*>(func.get()))(args[0]);
            } break;

			case eventhandlers_ctrl::LBDblClick : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Ctrl_LBDblClick)>*>(func.get()))(args[0], args[1]);
            } break;
            default: assert(false);
        }
        return {};
    }

    EHIdentifier addScriptEH(types::control ctrl, eventhandlers_ctrl type) {
        r_string typeStr;
        //#TODO eachFrame is just redirector to InvokePeriod.
        switch (type) {
#define EHCTRL_CASE(name, retVal, args) \
    case eventhandlers_ctrl::name: typeStr = #name##sv; break;
            EHDEF_CTRL(EHCTRL_CASE)
            default:;
        }

        //16'777'216 is the maximum float that can be cast "accurately" to an int;
        //In addition, 2^32 (max unsigned int) is divisible by that number and thus wrap-around is safe (no collisions)
        static unsigned int uid_ctrl = 0;
        int uid = (int)((uid_ctrl++) % 33'554'432) - 16'777'216;

        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\"")
                              + intercept::client::host::module_name.data() + "\","
                              + std::to_string(static_cast<uint32_t>(eventhandler_type::ctrl)) + ","
                              + std::to_string(uid) + ","
                              + "_thisEventHandler] InterceptClientEvent [_this]";
        int ehid = intercept::sqf::ctrl_add_event_handler(ctrl, static_cast<sqf_string>(typeStr), command);

        return {uid, ehid, EHIteration, static_cast<uint8_t>(eventhandler_type::ctrl)};
    }

    void delScriptEH(types::control ctrl, eventhandlers_ctrl type, EHIdentifier& handle) {
        if (handle.EHIteration != EHIteration || handle.already_deleted) return;//Handle not valid anymore
        r_string typeStr;
        switch (type) {
            EHDEF_CTRL(EHCTRL_CASE)
        default:;
        }
        sqf::ctrl_remove_event_handler(ctrl,static_cast<sqf_string>(typeStr), handle.arma_eh_id);
    }

#pragma endregion

#pragma region MP Eventhandlers
    std::unordered_map<EHIdentifier, std::pair<eventhandlers_mp, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMPEH;

    intercept::types::game_value callEHHandler(eventhandlers_mp ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {
            case eventhandlers_mp::MPHit: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_MP_MPHit)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

			case eventhandlers_mp::MPKilled: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_MP_MPKilled)>*>(func.get()))(args[0], args[1], args[2], args[3]);
            } break;

			case eventhandlers_mp::MPRespawn: {
                auto newPos = (*reinterpret_cast<std::function<types::vector3(EH_Func_Args_MP_MPRespawn)>*>(func.get()))(args[0], args[1]);
                return newPos;
            } break;
            default: assert(false);
        }
        return {};
    }

    EHIdentifier addScriptEH(types::object unit, eventhandlers_mp type) {
        r_string typeStr;
        switch (type) {
        #define EHMP_CASE(name, retVal, args) \
    case eventhandlers_mp::name: typeStr = #name##sv; break;
            EHDEF_MP(EHMP_CASE)
            default:;
        }

        //16'777'216 is the maximum float that can be cast "accurately" to an int;
        //In addition, 2^32 (max unsigned int) is divisible by that number and thus wrap-around is safe (no collisions)
        static unsigned int uid_mp = 0;
        int uid = (int)((uid_mp++) % 33'554'432) - 16'777'216;

        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\"")
            + intercept::client::host::module_name.data() + "\","
            + std::to_string(static_cast<uint32_t>(eventhandler_type::mp)) + ","
            + std::to_string(uid) + ","
            + "_thisEventHandler] InterceptClientEvent [_this]";
        int ehid = intercept::sqf::add_mp_event_handler(unit, static_cast<sqf_string_const_ref>(typeStr), command);

        return {uid, ehid, EHIteration, static_cast<uint8_t>(eventhandler_type::mp)};
    }

    void delScriptEH(types::object unit, eventhandlers_mp type, EHIdentifier& handle) {
        if (handle.EHIteration != EHIteration || handle.already_deleted) return;//Handle not valid anymore
        r_string typeStr;
        switch (type) {
            EHDEF_MP(EHMP_CASE)
            default:;
        }
        sqf::remove_mp_event_handler(unit, static_cast<sqf_string_const_ref>(typeStr), handle.arma_eh_id);
    }
#pragma endregion

#pragma region Display Eventhandlers
    std::unordered_map<EHIdentifier, std::pair<eventhandlers_display, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapDisplayEH;

    intercept::types::game_value callEHHandler(eventhandlers_display ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {

            case eventhandlers_display::Load: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_Load)>*>(func.get()))(args);
            } break;

			case eventhandlers_display::Unload: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_Unload)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_display::ChildDestroyed: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_ChildDestroyed)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

			case eventhandlers_display::KeyDown: {
                return (*reinterpret_cast<std::function<bool(EH_Func_Args_Display_KeyDown)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

			case eventhandlers_display::KeyUp: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_KeyUp)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
            } break;

			case eventhandlers_display::MouseMoving: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_MouseMoving)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

			case eventhandlers_display::MouseZChanged: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_MouseZChanged)>*>(func.get()))(args[0], args[1]);
            } break;

			case eventhandlers_display::MouseButtonDown : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_MouseButtonDown)>*>(func.get()))(args[0], args[1], args[2],args[3], args[4], args[5], args[6]);
            } break;

			case eventhandlers_display::MouseButtonUp : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_MouseButtonUp)>*>(func.get()))(args[0], args[1], args[2],args[3], args[4], args[5], args[6]);
            } break;

			case eventhandlers_display::MouseHolding : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_MouseHolding)>*>(func.get()))(args[0], args[1], args[2]);
            } break;

			case eventhandlers_display::Char : {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Display_Char)>*>(func.get()))(args[0], args[1]);
            } break;
            default: assert(false);
        }
        return {};
    }

    EHIdentifier addScriptEH(types::display disp, eventhandlers_display type) {
        r_string typeStr;
        switch (type) {
        #define EHDisplay_CASE(name, retVal, args) \
    case eventhandlers_display::name: typeStr = #name##sv; break;
            EHDEF_Display(EHDisplay_CASE)
            default:;
        }

        //16'777'216 is the maximum float that can be cast "accurately" to an int;
        //In addition, 2^32 (max unsigned int) is divisible by that number and thus wrap-around is safe (no collisions)
        static unsigned int uid_disp = 0;
        int uid = (int)((uid_disp++) % 33'554'432) - 16'777'216;

        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\"")
            + intercept::client::host::module_name.data() + "\","
            + std::to_string(static_cast<uint32_t>(eventhandler_type::display)) + ","
            + std::to_string(uid) + ","
            + "_thisEventHandler] InterceptClientEvent [_this]";
        int ehid = intercept::sqf::display_add_event_handler(disp, static_cast<sqf_string_const_ref>(typeStr), command);

        return {uid, ehid, EHIteration, static_cast<uint8_t>(eventhandler_type::display)};
    }

    void delScriptEH(types::display disp, eventhandlers_display type, EHIdentifier& handle) {
        if (handle.EHIteration != EHIteration || handle.already_deleted) return;//Handle not valid anymore
        r_string typeStr;
        switch (type) {
            EHDEF_Display(EHDisplay_CASE)
            default:;
        }
        sqf::display_remove_eventhandler(disp, static_cast<sqf_string_const_ref>(typeStr), handle.arma_eh_id);
    }
#pragma endregion


#pragma region Custom Callback

    std::unordered_map<EHIdentifier, std::shared_ptr<std::function<types::game_value(types::game_value_parameter)>>, EHIdentifier_hasher> customCallbackMap;

    std::pair<std::string, EHIdentifierHandle> generate_custom_callback(std::function<game_value(game_value_parameter)> fnc) {
        static int ehId = -16777210;

        //16'777'216 is the maximum float that can be cast "accurately" to an int;
        //In addition, 2^32 (max unsigned int) is divisible by that number and thus wrap-around is safe (no collisions)
        static unsigned int uid_custom = 0;
        int uid = (int)((uid_custom++) % 33'554'432) - 16'777'216;

        ehId++;
        EHIdentifier ident{ uid, ehId, 0, 0 };

        customCallbackMap[ident] = std::make_shared<std::function<game_value(game_value_parameter)>>(fnc);

        std::string command = std::string("[\"")
            + intercept::client::host::module_name.data() + "\","
            + std::to_string(static_cast<uint32_t>(eventhandler_type::custom)) + ","
            + std::to_string(uid) + ","
            + std::to_string(ehId) + "] InterceptClientEvent [_this]";

        return { command, { ident, [](EHIdentifier& id) { customCallbackMap.erase(id); } } };
    }

#pragma endregion

#endif
}  // namespace intercept::client
