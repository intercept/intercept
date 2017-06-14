/*!
@file
@author Dedmen (dedmen@dedmen.de)

@brief Helper stuff for Binding Callbacks to Eventhandlers on Objects and alike.

https://github.com/NouberNou/intercept
*/
#pragma once
#include <type_traits>
#include <functional>
#include "../shared/client_types.hpp"
namespace intercept::client {

    enum class loaded_saveType {
        save, /// custom save, achieved by pressing SAVE button in the pause menu
        autosave, /// automatic checkpoint, saved using saveGame command
        continuesave /// saved when leaving a mission to the main menu
    };

    using EHIdentifier = std::pair<uint32_t, float>;
    enum class eventhandler_type {
        mission,
        generic,
        display
    };

    extern "C" DLLEXPORT intercept::types::game_value CDECL client_eventhandler(int ehType, uint32_t uid, float handle, intercept::types::game_value args);


#pragma region Mission Eventhandlers

#define EH_Func_Args_Mission_Draw3D void
#define EH_Func_Args_Mission_Ended intercept::types::r_string end_type
#define EH_Func_Args_Mission_Loaded loaded_saveType save_type
#define EH_Func_Args_Mission_Map bool mapIsOpened, bool mapIsForced
#define EH_Func_Args_Mission_HandleDisconnect intercept::types::object unit, int id, intercept::types::r_string uid, intercept::types::r_string name
#define EH_Func_Args_Mission_EntityRespawned intercept::types::object newEntity, intercept::types::object oldEntity
#define EH_Func_Args_Mission_EntityKilled intercept::types::object killed, intercept::types::object killer, intercept::types::object instigator, bool useEffects
#define EH_Func_Args_Mission_EachFrame
#define EH_Func_Args_Mission_MapSingleClick intercept::types::auto_array<intercept::types::object> units, intercept::types::vector3 pos, bool alt, bool shift
#define EH_Func_Args_Mission_HCGroupSelectionChanged intercept::types::group group, bool isSelected
#define EH_Func_Args_Mission_CommandModeChanged bool isHighCommand, bool IsForced
#define EH_Func_Args_Mission_GroupIconClick bool is3D, intercept::types::group group, int wpID, int mb, intercept::types::vector2 mousePos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Mission_GroupIconOverEnter bool is3D, intercept::types::group group, int wpID, int mb, intercept::types::vector2 mousePos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Mission_GroupIconOverLeave bool is3D, intercept::types::group group, int wpID, int mb, intercept::types::vector2 mousePos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Mission_PlayerConnected int id, intercept::types::r_string uid, intercept::types::r_string name, bool jip, int owner
#define EH_Func_Args_Mission_PlayerDisconnected int id, intercept::types::r_string uid, intercept::types::r_string name, bool jip, int owner
#define EH_Func_Args_Mission_TeamSwitch intercept::types::object from, intercept::types::object to
#define EH_Func_Args_Mission_PreloadStarted
#define EH_Func_Args_Mission_PreloadFinished
#define EH_Func_Args_Mission_PlayerViewChanged intercept::types::object oldBody, intercept::types::object newBody, intercept::types::object vehicleIn, intercept::types::object oldCameraOn, intercept::types::object newCameraOn, intercept::types::object UAV
#define EH_Func_Args_Mission_BuildingChanged intercept::types::object from, intercept::types::object to, bool isRuin


    //Name,Function return value, Function Arguments
#define EHDEF_MISSION(XX) \
XX(Draw3D,void,EH_Func_Args_Mission_Draw3D)\
XX(Ended,void,EH_Func_Args_Mission_Ended)\
XX(Loaded,void,EH_Func_Args_Mission_Loaded)\
XX(Map,void,EH_Func_Args_Mission_Map)\
XX(HandleDisconnect,bool,EH_Func_Args_Mission_HandleDisconnect)\
XX(EntityRespawned,void,EH_Func_Args_Mission_EntityRespawned)\
XX(EntityKilled,void,EH_Func_Args_Mission_EntityKilled)\
XX(EachFrame,void,EH_Func_Args_Mission_EachFrame)\
XX(MapSingleClick,void,EH_Func_Args_Mission_MapSingleClick)\
XX(HCGroupSelectionChanged,void,EH_Func_Args_Mission_HCGroupSelectionChanged)\
XX(CommandModeChanged,void,EH_Func_Args_Mission_CommandModeChanged)\
XX(GroupIconClick,void,EH_Func_Args_Mission_GroupIconClick)\
XX(GroupIconOverEnter,void,EH_Func_Args_Mission_GroupIconOverEnter)\
XX(GroupIconOverLeave,void,EH_Func_Args_Mission_GroupIconOverLeave)\
XX(PlayerConnected,void,EH_Func_Args_Mission_PlayerConnected)\
XX(PlayerDisconnected,void,EH_Func_Args_Mission_PlayerDisconnected)\
XX(TeamSwitch,void,EH_Func_Args_Mission_TeamSwitch)\
XX(PreloadStarted,void,EH_Func_Args_Mission_PreloadStarted)\
XX(PreloadFinished,void,EH_Func_Args_Mission_PreloadFinished)\
XX(PlayerViewChanged,void,EH_Func_Args_Mission_PlayerViewChanged)\
XX(BuildingChanged,void,EH_Func_Args_Mission_BuildingChanged)


#define COMPILETIME_CHECK_ENUM_MISSION(name,retVal,funcArg) static_assert(eventhandlers_mission::name >= eventhandlers_mission::Draw3D);
//DOC https://stackoverflow.com/a/25235815
/** @enum eventhandlers_mission
@brief Mission event handlers are specific EHs that are anchored to the running mission and automatically removed when mission is over.
*/
    enum class eventhandlers_mission {
        /*
        @brief Draw3D
        */
        Draw3D,
        /// Ended
        Ended,
        /// Game loading from save event
        Loaded,
        /// Map open / close event
        Map,
        HandleDisconnect, /*< Player disconnect in MP event */
        EntityRespawned, /*< Some entity respawn event */
        EntityKilled, /*< Some entity death event */
        EachFrame, /*< Per frame event */
        MapSingleClick, /*< Map click event */
        HCGroupSelectionChanged, /*< High Command group select event */
        CommandModeChanged, /*< High Command mode change event */
        GroupIconClick, /*< High Command icon click event */
        GroupIconOverEnter, /*< High Command icon enter event */
        GroupIconOverLeave, /*< High Command icon leave event */
        PlayerConnected, /*< Client joining MP mission event */
        PlayerDisconnected, /*< Client leaving MP mission event */
        TeamSwitch, /*< Player teamswitch event */
        PreloadStarted, /*< Mission preload start event */
        PreloadFinished, /*< Mission preload finish event */
        PlayerViewChanged, /*< Player view change event */
        BuildingChanged /*< Building model change event */
    };
    /*
    @var eventhandlers_mission::Loaded
    @brief Game loading from save event
    @remark "Loaded" event handler should be added BEFORE the mission is loaded from save.Placing it in a function with preInit = 1; usually does the trick.
    */
    EHDEF_MISSION(COMPILETIME_CHECK_ENUM_MISSION)


        inline intercept::types::game_value callEHHandler(eventhandlers_mission ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {
        case eventhandlers_mission::PreloadStarted: //[[fallthrough]]
        case eventhandlers_mission::PreloadFinished: //[[fallthrough]]
        case eventhandlers_mission::EachFrame: //[[fallthrough]]
        case eventhandlers_mission::Draw3D: {
            (*func)();
        }break;
        case eventhandlers_mission::Ended: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_Ended)>*>(func.get()))(args);
        }break;
        case eventhandlers_mission::Loaded: {
            auto type = static_cast<intercept::types::r_string>(args);
            loaded_saveType type_ = {};
            if (type == "save") type_ = loaded_saveType::save;
            else if (type == "autosave") type_ = loaded_saveType::autosave;
            else if (type == "continue") type_ = loaded_saveType::continuesave;
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_Loaded)>*>(func.get()))(type_);
        }break;
        case eventhandlers_mission::Map: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_Map)>*>(func.get()))(args[0], args[1]);
        }break;
        case eventhandlers_mission::HandleDisconnect: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_HandleDisconnect)>*>(func.get()))(args[0], args[1], args[2], args[3]);
        }break;
        case eventhandlers_mission::EntityRespawned: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_EntityRespawned)>*>(func.get()))(args[0], args[1]);
        }break;
        case eventhandlers_mission::EntityKilled: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_EntityKilled)>*>(func.get()))(args[0], args[1], args[2], args[3]);
        }break;
        case eventhandlers_mission::MapSingleClick: {
            auto& arr = args[0].to_array();
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_MapSingleClick)>*>(func.get()))(intercept::types::auto_array<intercept::types::object>(arr.begin(), arr.end()), args[1], args[2], args[3]);
        }break;
        case eventhandlers_mission::HCGroupSelectionChanged: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_HCGroupSelectionChanged)>*>(func.get()))(args[0], args[1]);
        }break;
        case eventhandlers_mission::CommandModeChanged: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_CommandModeChanged)>*>(func.get()))(args[0], args[1]);
        }break;
        case eventhandlers_mission::GroupIconClick: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_GroupIconClick)>*>(func.get()))(args[0], args[1], args[2], args[3], { args[4], args[5] }, args[6], args[7], args[8]);
        }break;
        case eventhandlers_mission::GroupIconOverEnter: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_GroupIconOverEnter)>*>(func.get()))(args[0], args[1], args[2], args[3], { args[4], args[5] }, args[6], args[7], args[8]);
        }break;
        case eventhandlers_mission::GroupIconOverLeave: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_GroupIconOverLeave)>*>(func.get()))(args[0], args[1], args[2], args[3], { args[4], args[5] }, args[6], args[7], args[8]);
        }break;
        case eventhandlers_mission::PlayerConnected: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_PlayerConnected)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
        }break;
        case eventhandlers_mission::PlayerDisconnected: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_PlayerDisconnected)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4]);
        }break;
        case eventhandlers_mission::TeamSwitch: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_TeamSwitch)>*>(func.get()))(args[0], args[1]);
        }break;
        case eventhandlers_mission::PlayerViewChanged: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_PlayerViewChanged)>*>(func.get()))(args[0], args[1], args[1], args[2], args[3], args[4]);
        }break;
        case eventhandlers_mission::BuildingChanged: {
            (*reinterpret_cast<std::function<void(EH_Func_Args_Mission_BuildingChanged)>*>(func.get()))(args[0], args[1], args[2]);
        }break;
        default:;
        }
        return {};
    }




    EHIdentifier addScriptEH(eventhandlers_mission type);

    struct EHIdentifier_hasher {
        size_t operator()(const intercept::client::EHIdentifier& x) const {
            return intercept::types::__internal::pairhash(x.first, x.second);
        }
    };
    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_mission, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMissionEH;

    template<eventhandlers_mission Type>
    struct __addMissionEventHandler_Impl;


#define EH_Add_Mission_definition(name,retVal,fncArg)\
template<> \
struct __addMissionEventHandler_Impl<eventhandlers_mission::name>{\
    [[nodiscard]] static EHIdentifier add(std::function<retVal(fncArg)> function) {\
            auto ident = addScriptEH(eventhandlers_mission::name); \
            funcMapMissionEH[ident] = { eventhandlers_mission::name,std::make_shared < std::function<void()> >(*reinterpret_cast<std::function<void()>*>(&function)) }; \
            return ident; \
    }\
};


#define EH_Add_Mission_declaration(name,retVal,fncArg)\
template<> \
[[nodiscard]] EHIdentifier addMissionEventHandler<eventhandlers_mission::name>(std::function<retVal(fncArg)> function);

    EHDEF_MISSION(EH_Add_Mission_definition)


    template <eventhandlers_mission Type, typename Func>
    [[nodiscard]] EHIdentifier addMissionEventHandler(Func fnc) { return __addMissionEventHandler_Impl<Type>::add(fnc); };

#pragma endregion
}
