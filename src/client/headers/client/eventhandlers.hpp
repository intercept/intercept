/*!
@file
@author Dedmen (dedmen@dedmen.de)

@brief Helper stuff for Binding Callbacks to Eventhandlers on Objects and alike.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "../shared/client_types.hpp"
#include <functional>
namespace intercept::client {

    enum class loaded_saveType {
        save,         ///< custom save, achieved by pressing SAVE button in the pause menu
        autosave,     ///< automatic checkpoint, saved using saveGame command
        continuesave  ///< saved when leaving a mission to the main menu
    };

    using EHIdentifier = std::pair<int32_t, float>;

    struct EHIdentifier_hasher {
        size_t operator()(const intercept::client::EHIdentifier& x) const {
            return intercept::types::__internal::pairhash(x.first, x.second);
        }
    };

    class EHIdentifierHandle {
    public:
        EHIdentifierHandle(EHIdentifier ident, std::function<void(EHIdentifier&)> onDelete) : handle(std::make_shared<impl>(std::move(ident), std::move(onDelete))) {}

    private:
        class impl {
        public:
            impl(EHIdentifier&& ident_, std::function<void(EHIdentifier&)>&& onDelete_) : ident(ident_), onDelete(onDelete_) {}
            EHIdentifier ident;
            std::function<void(EHIdentifier&)> onDelete;
            ~impl() {
                onDelete(ident);
            }
        };
        std::shared_ptr<impl> handle;
    };

    enum class eventhandler_type {
        mission,
        object,
        display,
        ctrl
    };

    extern "C" DLLEXPORT void CDECL client_eventhandler(intercept::types::game_value& retVal, int ehType, int32_t uid, float handle, intercept::types::game_value args);

#pragma region Mission Eventhandlers

#define EH_Func_Args_Mission_Draw3D void
#define EH_Func_Args_Mission_Ended types::r_string end_type
#define EH_Func_Args_Mission_Loaded loaded_saveType save_type
#define EH_Func_Args_Mission_Map bool mapIsOpened, bool mapIsForced
#define EH_Func_Args_Mission_HandleDisconnect types::object unit, int id, types::r_string uid, types::r_string name
#define EH_Func_Args_Mission_EntityRespawned types::object newEntity, types::object oldEntity
#define EH_Func_Args_Mission_EntityKilled types::object killed, types::object killer, types::object instigator, bool useEffects
#define EH_Func_Args_Mission_EachFrame
#define EH_Func_Args_Mission_MapSingleClick types::auto_array<types::object> units, types::vector3 pos, bool alt, bool shift
#define EH_Func_Args_Mission_HCGroupSelectionChanged types::group group, bool isSelected
#define EH_Func_Args_Mission_CommandModeChanged bool isHighCommand, bool IsForced
#define EH_Func_Args_Mission_GroupIconClick bool is3D, types::group group, int wpID, int mb, types::vector2 mousePos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Mission_GroupIconOverEnter bool is3D, types::group group, int wpID, int mb, types::vector2 mousePos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Mission_GroupIconOverLeave bool is3D, types::group group, int wpID, int mb, types::vector2 mousePos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Mission_PlayerConnected int id, types::r_string uid, types::r_string name, bool jip, int owner
#define EH_Func_Args_Mission_PlayerDisconnected int id, types::r_string uid, types::r_string name, bool jip, int owner
#define EH_Func_Args_Mission_TeamSwitch types::object from, types::object to
#define EH_Func_Args_Mission_PreloadStarted
#define EH_Func_Args_Mission_PreloadFinished
#define EH_Func_Args_Mission_PlayerViewChanged types::object oldBody, types::object newBody, types::object vehicleIn, types::object oldCameraOn, types::object newCameraOn, types::object UAV
#define EH_Func_Args_Mission_BuildingChanged types::object from, types::object to, bool isRuin

//Name,Function return value, Function Arguments

#define EHDEF_MISSION(XX)                                                            \
    XX(Draw3D, void, EH_Func_Args_Mission_Draw3D)                                    \
    XX(Ended, void, EH_Func_Args_Mission_Ended)                                      \
    XX(Loaded, void, EH_Func_Args_Mission_Loaded)                                    \
    XX(Map, void, EH_Func_Args_Mission_Map)                                          \
    XX(HandleDisconnect, std::optional<bool>, EH_Func_Args_Mission_HandleDisconnect) \
    XX(EntityRespawned, void, EH_Func_Args_Mission_EntityRespawned)                  \
    XX(EntityKilled, void, EH_Func_Args_Mission_EntityKilled)                        \
    XX(EachFrame, void, EH_Func_Args_Mission_EachFrame)                              \
    XX(MapSingleClick, void, EH_Func_Args_Mission_MapSingleClick)                    \
    XX(HCGroupSelectionChanged, void, EH_Func_Args_Mission_HCGroupSelectionChanged)  \
    XX(CommandModeChanged, void, EH_Func_Args_Mission_CommandModeChanged)            \
    XX(GroupIconClick, void, EH_Func_Args_Mission_GroupIconClick)                    \
    XX(GroupIconOverEnter, void, EH_Func_Args_Mission_GroupIconOverEnter)            \
    XX(GroupIconOverLeave, void, EH_Func_Args_Mission_GroupIconOverLeave)            \
    XX(PlayerConnected, void, EH_Func_Args_Mission_PlayerConnected)                  \
    XX(PlayerDisconnected, void, EH_Func_Args_Mission_PlayerDisconnected)            \
    XX(TeamSwitch, void, EH_Func_Args_Mission_TeamSwitch)                            \
    XX(PreloadStarted, void, EH_Func_Args_Mission_PreloadStarted)                    \
    XX(PreloadFinished, void, EH_Func_Args_Mission_PreloadFinished)                  \
    XX(PlayerViewChanged, void, EH_Func_Args_Mission_PlayerViewChanged)              \
    XX(BuildingChanged, void, EH_Func_Args_Mission_BuildingChanged)

#define COMPILETIME_CHECK_ENUM_MISSION(name, retVal, funcArg) static_assert(eventhandlers_mission::name >= eventhandlers_mission::Draw3D);
    //DOC https://stackoverflow.com/a/25235815
    /** @enum eventhandlers_mission
@brief Mission event handlers are specific EHs that are anchored to the running mission and automatically removed when mission is over.
*/
    enum class eventhandlers_mission {
        Draw3D,                  ///< Draw3D
        Ended,                   ///< Ended
        Loaded,                  ///< Game loading from save event
        Map,                     ///< Map open / close event
        HandleDisconnect,        /*< Player disconnect in MP event */
        EntityRespawned,         /*< Some entity respawn event */
        EntityKilled,            /*< Some entity death event */
        EachFrame,               /*< Per frame event */
        MapSingleClick,          /*< Map click event */
        HCGroupSelectionChanged, /*< High Command group select event */
        CommandModeChanged,      /*< High Command mode change event */
        GroupIconClick,          /*< High Command icon click event */
        GroupIconOverEnter,      /*< High Command icon enter event */
        GroupIconOverLeave,      /*< High Command icon leave event */
        PlayerConnected,         /*< Client joining MP mission event */
        PlayerDisconnected,      /*< Client leaving MP mission event */
        TeamSwitch,              /*< Player teamswitch event */
        PreloadStarted,          /*< Mission preload start event */
        PreloadFinished,         /*< Mission preload finish event */
        PlayerViewChanged,       /*< Player view change event */
        BuildingChanged          /*< Building model change event */
    };
    /*
    @var eventhandlers_mission::Loaded
    @brief Game loading from save event
    @remark "Loaded" event handler should be added BEFORE the mission is loaded from save.Placing it in a function with preInit = 1; usually does the trick.
    */
    EHDEF_MISSION(COMPILETIME_CHECK_ENUM_MISSION)

    inline intercept::types::game_value callEHHandler(eventhandlers_mission ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {
            case eventhandlers_mission::PreloadStarted:   //[[fallthrough]]
            case eventhandlers_mission::PreloadFinished:  //[[fallthrough]]
            case eventhandlers_mission::EachFrame:        //[[fallthrough]]
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
            default:;
        }
        return {};
    }

    EHIdentifier addScriptEH(eventhandlers_mission type);
    void delScriptEH(eventhandlers_mission type, EHIdentifier& handle);

    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_mission, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMissionEH;

    template <eventhandlers_mission Type>
    struct __addMissionEventHandler_Impl;

#define EH_Add_Mission_definition(name, retVal, fncArg)                                                                                                             \
    template <>                                                                                                                                                     \
    struct __addMissionEventHandler_Impl<eventhandlers_mission::name> {                                                                                             \
        using fncType = std::function<retVal(fncArg)>;                                                                                                              \
        [[nodiscard]] static EHIdentifier add(std::function<retVal(fncArg)> function) {                                                                             \
            auto ident = addScriptEH(eventhandlers_mission::name);                                                                                                  \
            funcMapMissionEH[ident] = {eventhandlers_mission::name, std::make_shared<std::function<void()>>(*reinterpret_cast<std::function<void()>*>(&function))}; \
            return ident;                                                                                                                                           \
        }                                                                                                                                                           \
    };

    EHDEF_MISSION(EH_Add_Mission_definition)

    template <eventhandlers_mission Type, typename Func = typename __addMissionEventHandler_Impl<Type>::fncType>
    [[nodiscard]] EHIdentifierHandle addMissionEventHandler(Func fnc) {
        return {__addMissionEventHandler_Impl<Type>::add(fnc), [type = Type](EHIdentifier& id) { funcMapMissionEH.erase(id); delScriptEH(type,id); }};
    }

#pragma endregion

#pragma region Object Eventhandlers

#define EH_Func_Args_Object_AnimChanged types::object unit, types::r_string anim
#define EH_Func_Args_Object_AnimDone types::object unit, types::r_string anim
#define EH_Func_Args_Object_AnimStateChanged types::object unit, types::r_string anim
#define EH_Func_Args_Object_ContainerClosed types::object container, types::object player
#define EH_Func_Args_Object_ContainerOpened types::object container, types::object player
#define EH_Func_Args_Object_ControlsShifted types::object vehicle, types::object newController, types::object oldController
#define EH_Func_Args_Object_Dammaged types::object unit, types::r_string, float damage, float hitPartIndex, types::r_string hitPoint, types::object shooter, types::object projectile
#define EH_Func_Args_Object_Deleted types::object entity
#define EH_Func_Args_Object_Engine types::object vehicle, bool engineState
#define EH_Func_Args_Object_EpeContact types::object object1, types::object object2, types::object select1, types::object select2, float force
#define EH_Func_Args_Object_EpeContactEnd types::object object1, types::object object2, types::object select1, types::object select2, float force
#define EH_Func_Args_Object_EpeContactStart types::object object1, types::object object2, types::object select1, types::object select2, float force
#define EH_Func_Args_Object_Explosion types::object vehicle, float damage
#define EH_Func_Args_Object_Fired types::object unit, types::r_string weapon, types::r_string muzzle, types::r_string mode, types::r_string ammo, types::r_string magazine, types::object projectile, types::object gunner
#define EH_Func_Args_Object_FiredMan types::object unit, types::r_string weapon, types::r_string muzzle, types::r_string mode, types::r_string ammo, types::r_string magazine, types::object projectile, types::object vehicle
#define EH_Func_Args_Object_FiredNear types::object unit, types::object vehicle, float distance, types::r_string weapon, types::r_string muzzle, types::r_string mode, types::r_string ammo, types::object gunner
#define EH_Func_Args_Object_Fuel types::object vehicle, bool fuelState
#define EH_Func_Args_Object_Gear types::object vehicle, bool gearState
    //#TODO correct type for turretPath
    enum class get_in_position {
        driver,
        gunner,
        cargo
    };
#define EH_Func_Args_Object_GetIn types::object vehicle, get_in_position position, types::object unit, types::auto_array<types::game_value> turretPath
//#TODO correct type for turretPath
#define EH_Func_Args_Object_GetInMan types::object vehicle, get_in_position position, types::object unit, types::auto_array<types::game_value> turretPath
//#TODO correct type for turretPath
#define EH_Func_Args_Object_GetOut types::object vehicle, get_in_position position, types::object unit, types::auto_array<types::game_value> turretPath
//#TODO correct type for turretPath
#define EH_Func_Args_Object_GetOutMan types::object vehicle, get_in_position position, types::object unit, types::auto_array<types::game_value> turretPath
#define EH_Func_Args_Object_HandleDamage types::object unit, types::r_string hitSelection, float dmage, types::object source, types::r_string projectile, float hitPartIndex, types::object instigator, types::r_string hitPoint
#define EH_Func_Args_Object_HandleHeal types::object unit, types::object healer, bool healerCanHeal
#define EH_Func_Args_Object_HandleRating types::object unit, float rating
#define EH_Func_Args_Object_HandleScore types::object unit, types::object object_, float score
#define EH_Func_Args_Object_Hit types::object unit, types::object causedBy, float damage, types::object instigator
//#TODO correct type for ammo
#define EH_Func_Args_Object_HitPart types::object target, types::object shooter, types::object bullet, types::vector3 position, types::vector3 velocity, types::auto_array<types::r_string> selection, types::auto_array<types::game_value> ammo, types::vector3 direction, float radius, types::r_string surface, bool direct
#define EH_Func_Args_Object_Init types::object unit
#define EH_Func_Args_Object_HandleIdentity types::object unit
#define EH_Func_Args_Object_IncomingMissile types::object target, types::r_string ammo, types::object vehicle, types::object instigator
#define EH_Func_Args_Object_InventoryClosed types::object unit, types::object targetContainer
#define EH_Func_Args_Object_InventoryOpened types::object unit, types::object targetContainer, types::object secondaryContainer
#define EH_Func_Args_Object_Killed types::object unit, types::object killer, types::object instigator, bool useEffects
#define EH_Func_Args_Object_LandedTouchDown types::object plane, float airportID
#define EH_Func_Args_Object_LandedStopped types::object plane, float airportID
#define EH_Func_Args_Object_Landing types::object plane, float airportID, bool isCarrier
#define EH_Func_Args_Object_LandingCanceled types::object plane, float airportID, bool isCarrier
#define EH_Func_Args_Object_Local types::object object_, bool local
#define EH_Func_Args_Object_PostReset
#define EH_Func_Args_Object_Put types::object unit, types::object container, types::r_string item
//#TODO correct type for new/oldMagazine
#define EH_Func_Args_Object_Reloaded types::object entity, types::r_string weapon, types::r_string muzzle, types::r_string, types::auto_array<types::game_value> newMagazine, types::auto_array<types::game_value> oldMagazine
#define EH_Func_Args_Object_Respawn types::object unit, types::object corpse
#define EH_Func_Args_Object_RopeAttach types::object object1, types::object rope, types::object object2
#define EH_Func_Args_Object_RopeBreak types::object object1, types::object rope, types::object object2
#define EH_Func_Args_Object_SeatSwitched types::object vehicle, types::object unit1, types::object unit2
#define EH_Func_Args_Object_SeatSwitchedMan types::object vehicle, types::object unit1, types::object unit2
    enum class sound_played_origin {
        Breath = 1,
        Breath_Injured,
        Breath_Scuba,
        Injured,
        Pulsation,
        Hit_Scream,
        Burning,
        Drowning,
        Drown,
        Gasping,
        Stabilizing,
        Healing,
        Healing_With_Medikit,
        Recovered = 14
    };
#define EH_Func_Args_Object_SoundPlayed types::object unit, sound_played_origin soundCode
#define EH_Func_Args_Object_Take types::object unit, types::object container, types::r_string item
#define EH_Func_Args_Object_TaskSetAsCurrent types::object unit, types::task task_
//#TODO correct type for turretPath
#define EH_Func_Args_Object_TurnIn types::object vehicle, types::object unit, types::auto_array<types::game_value> turretPath
//#TODO correct type for turretPath
#define EH_Func_Args_Object_TurnOut types::object vehicle, types::object unit, types::auto_array<types::game_value> turretPath
#define EH_Func_Args_Object_WeaponAssembled types::object unit, types::object weapon
#define EH_Func_Args_Object_WeaponDisassembled types::object unit, types::object primaryBag, types::object secondarybag
#define EH_Func_Args_Object_WeaponDeployed types::object unit, bool isDeployed
#define EH_Func_Args_Object_WeaponRested types::object unit, bool isRested

//Name,Function return value, Function Arguments
#define EHDEF_OBJECT(XX)                                                        \
    XX(AnimChanged, void, EH_Func_Args_Object_AnimChanged)                      \
    XX(AnimDone, void, EH_Func_Args_Object_AnimDone)                            \
    XX(AnimStateChanged, void, EH_Func_Args_Object_AnimStateChanged)            \
    XX(ContainerClosed, void, EH_Func_Args_Object_ContainerClosed)              \
    XX(ContainerOpened, void, EH_Func_Args_Object_ContainerOpened)              \
    XX(ControlsShifted, void, EH_Func_Args_Object_ControlsShifted)              \
    XX(Dammaged, void, EH_Func_Args_Object_Dammaged)                            \
    XX(Deleted, void, EH_Func_Args_Object_Deleted)                              \
    XX(Engine, void, EH_Func_Args_Object_Engine)                                \
    XX(EpeContact, void, EH_Func_Args_Object_EpeContact)                        \
    XX(EpeContactEnd, void, EH_Func_Args_Object_EpeContactEnd)                  \
    XX(EpeContactStart, void, EH_Func_Args_Object_EpeContactStart)              \
    XX(Explosion, void, EH_Func_Args_Object_Explosion)                          \
    XX(Fired, void, EH_Func_Args_Object_Fired)                                  \
    XX(FiredMan, void, EH_Func_Args_Object_FiredMan)                            \
    XX(FiredNear, void, EH_Func_Args_Object_FiredNear)                          \
    XX(Fuel, void, EH_Func_Args_Object_Fuel)                                    \
    XX(Gear, void, EH_Func_Args_Object_Gear)                                    \
    XX(GetIn, void, EH_Func_Args_Object_GetIn)                                  \
    XX(GetInMan, void, EH_Func_Args_Object_GetInMan)                            \
    XX(GetOut, void, EH_Func_Args_Object_GetOut)                                \
    XX(GetOutMan, void, EH_Func_Args_Object_GetOutMan)                          \
    XX(HandleDamage, std::optional<float>, EH_Func_Args_Object_HandleDamage)    \
    XX(HandleHeal, void, EH_Func_Args_Object_HandleHeal)                        \
    XX(HandleRating, std::optional<float>, EH_Func_Args_Object_HandleRating)    \
    XX(HandleScore, std::optional<bool>, EH_Func_Args_Object_HandleScore)       \
    XX(Hit, void, EH_Func_Args_Object_Hit)                                      \
    XX(HitPart, void, EH_Func_Args_Object_HitPart)                              \
    XX(Init, void, EH_Func_Args_Object_Init)                                    \
    XX(HandleIdentity, std::optional<bool>, EH_Func_Args_Object_HandleIdentity) \
    XX(IncomingMissile, void, EH_Func_Args_Object_IncomingMissile)              \
    XX(InventoryClosed, void, EH_Func_Args_Object_InventoryClosed)              \
    XX(InventoryOpened, void, EH_Func_Args_Object_InventoryOpened)              \
    XX(Killed, void, EH_Func_Args_Object_Killed)                                \
    XX(LandedTouchDown, void, EH_Func_Args_Object_LandedTouchDown)              \
    XX(LandedStopped, void, EH_Func_Args_Object_LandedStopped)                  \
    XX(Landing, void, EH_Func_Args_Object_Landing)                              \
    XX(LandingCanceled, void, EH_Func_Args_Object_LandingCanceled)              \
    XX(Local, void, EH_Func_Args_Object_Local)                                  \
    XX(PostReset, void, EH_Func_Args_Object_PostReset)                          \
    XX(Put, void, EH_Func_Args_Object_Put)                                      \
    XX(Reloaded, void, EH_Func_Args_Object_Reloaded)                            \
    XX(Respawn, void, EH_Func_Args_Object_Respawn)                              \
    XX(RopeAttach, void, EH_Func_Args_Object_RopeAttach)                        \
    XX(RopeBreak, void, EH_Func_Args_Object_RopeBreak)                          \
    XX(SeatSwitched, void, EH_Func_Args_Object_SeatSwitched)                    \
    XX(SeatSwitchedMan, void, EH_Func_Args_Object_SeatSwitchedMan)              \
    XX(SoundPlayed, void, EH_Func_Args_Object_SoundPlayed)                      \
    XX(Take, void, EH_Func_Args_Object_Take)                                    \
    XX(TaskSetAsCurrent, void, EH_Func_Args_Object_TaskSetAsCurrent)            \
    XX(TurnIn, void, EH_Func_Args_Object_TurnIn)                                \
    XX(TurnOut, void, EH_Func_Args_Object_TurnOut)                              \
    XX(WeaponAssembled, void, EH_Func_Args_Object_WeaponAssembled)              \
    XX(WeaponDisassembled, void, EH_Func_Args_Object_WeaponDisassembled)        \
    XX(WeaponDeployed, void, EH_Func_Args_Object_WeaponDeployed)                \
    XX(WeaponRested, void, EH_Func_Args_Object_WeaponRested)

#define COMPILETIME_CHECK_ENUM_OBJECT(name, retVal, funcArg) static_assert(eventhandlers_object::name >= eventhandlers_object::AnimChanged);

    /** @enum eventhandlers_object
@brief #TODO
*/
    //#TODO doc
    enum class eventhandlers_object {
        AnimChanged,
        AnimDone,
        AnimStateChanged,
        ContainerClosed,
        ContainerOpened,
        ControlsShifted,
        Dammaged,
        Deleted,
        Engine,
        EpeContact,
        EpeContactEnd,
        EpeContactStart,
        Explosion,
        Fired,
        FiredMan,
        FiredNear,
        Fuel,
        Gear,
        GetIn,
        GetInMan,
        GetOut,
        GetOutMan,
        HandleDamage,
        HandleHeal,
        HandleRating,
        HandleScore,
        Hit,
        HitPart,
        Init,
        HandleIdentity,
        IncomingMissile,
        InventoryClosed,
        InventoryOpened,
        Killed,
        LandedTouchDown,
        LandedStopped,
        Landing,
        LandingCanceled,
        Local,
        PostReset,
        Put,
        Reloaded,
        Respawn,
        RopeAttach,
        RopeBreak,
        SeatSwitched,
        SeatSwitchedMan,
        SoundPlayed,
        Take,
        TaskSetAsCurrent,
        TurnIn,
        TurnOut,
        WeaponAssembled,
        WeaponDisassembled,
        WeaponDeployed,
        WeaponRested
    };

    EHDEF_OBJECT(COMPILETIME_CHECK_ENUM_OBJECT)

    inline intercept::types::game_value callEHHandler(eventhandlers_object ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
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
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetIn)>*>(func.get()))(args[0], p, args[2], args[3].to_array());
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
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetInMan)>*>(func.get()))(args[0], p, args[2], args[3].to_array());
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
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetOut)>*>(func.get()))(args[0], p, args[2], args[3].to_array());
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
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_GetOutMan)>*>(func.get()))(args[0], p, args[2], args[3].to_array());
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
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_HitPart)>*>(func.get()))(args[0], args[1], args[2], args[3], args[4], types::auto_array<types::r_string>(args[5].to_array().begin(), args[5].to_array().end()), args[6].to_array(), args[7], args[8], args[9], args[10]);
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
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_TurnIn)>*>(func.get()))(args[0], args[1], args[2].to_array());
            } break;
            case eventhandlers_object::TurnOut: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_TurnOut)>*>(func.get()))(args[0], args[1], args[2].to_array());
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

            default: assert(false);
        }
        return {};
    }

    EHIdentifier addScriptEH(types::object obj, eventhandlers_object type);
    void delScriptEH(types::object obj, eventhandlers_object type, EHIdentifier& handle);

    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_object, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapObjectEH;

    template <eventhandlers_object Type>
    struct __addEventHandler_Impl;

#define EH_Add_Object_definition(name, retVal, fncArg)                                                                                                            \
    template <>                                                                                                                                                   \
    struct __addEventHandler_Impl<eventhandlers_object::name> {                                                                                                   \
        using fncType = std::function<retVal(fncArg)>;                                                                                                            \
        [[nodiscard]] static EHIdentifier add(types::object obj, std::function<retVal(fncArg)> function) {                                                        \
            auto ident = addScriptEH(obj, eventhandlers_object::name);                                                                                            \
            funcMapObjectEH[ident] = {eventhandlers_object::name, std::make_shared<std::function<void()>>(*reinterpret_cast<std::function<void()>*>(&function))}; \
            return ident;                                                                                                                                         \
        }                                                                                                                                                         \
    };

    EHDEF_OBJECT(EH_Add_Object_definition)

    template <eventhandlers_object Type, typename Func = typename __addEventHandler_Impl<Type>::fncType>
    [[nodiscard]] EHIdentifierHandle addEventHandler(types::object obj, Func fnc) {
        return { __addEventHandler_Impl<Type>::add(obj, fnc), [obj,type = Type](EHIdentifier& id) { funcMapObjectEH.erase(id); delScriptEH(obj,type,id); } };
    }

#pragma endregion

#pragma region CTRL Eventhandlers

#define EH_Func_Args_Ctrl_Draw types::control map
#define EH_Func_Args_Ctrl_MouseButtonDown types::control ctrl, int button, types::vector2 pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseButtonUp types::control ctrl, int button, types::vector2 pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseButtonClick types::control ctrl, int button, types::vector2 pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseButtonDblClick types::control ctrl, int button, types::vector2 pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseMoving types::control map, types::vector2 pos
#define EH_Func_Args_Ctrl_MouseHolding types::control map, types::vector2 pos

//Name,Function return value, Function Arguments
#define EHDEF_CTRL(XX)                                                   \
    XX(Draw, void, EH_Func_Args_Ctrl_Draw)                               \
    XX(MouseButtonDown, void, EH_Func_Args_Ctrl_MouseButtonDown)         \
    XX(MouseButtonUp, void, EH_Func_Args_Ctrl_MouseButtonUp)             \
    XX(MouseButtonClick, void, EH_Func_Args_Ctrl_MouseButtonClick)       \
    XX(MouseButtonDblClick, void, EH_Func_Args_Ctrl_MouseButtonDblClick) \
    XX(MouseMoving, void, EH_Func_Args_Ctrl_MouseMoving)                 \
    XX(MouseHolding, void, EH_Func_Args_Ctrl_MouseHolding)

#define COMPILETIME_CHECK_ENUM_CTRL(name, retVal, funcArg) static_assert(eventhandlers_ctrl::name >= eventhandlers_ctrl::Draw);

    /** @enum eventhandlers_object
    @brief #TODO
    */
    //#TODO doc
    enum class eventhandlers_ctrl {
        Draw,
        MouseButtonDown,
        MouseButtonUp,
        MouseButtonClick,
        MouseButtonDblClick,
        MouseMoving,
        MouseHolding
    };

    EHDEF_CTRL(COMPILETIME_CHECK_ENUM_CTRL)

    inline intercept::types::game_value callEHHandler(eventhandlers_ctrl ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func) {
        switch (ehType) {
            case eventhandlers_ctrl::Draw: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;
            case eventhandlers_ctrl::MouseButtonDown: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;
            case eventhandlers_ctrl::MouseButtonUp: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;
            case eventhandlers_ctrl::MouseButtonClick: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;
            case eventhandlers_ctrl::MouseButtonDblClick: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;
            case eventhandlers_ctrl::MouseMoving: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;
            case eventhandlers_ctrl::MouseHolding: {
                (*reinterpret_cast<std::function<void(EH_Func_Args_Object_AnimChanged)>*>(func.get()))(args[0], args[1]);
            } break;
            default: assert(false);
        }
        return {};
    }

    EHIdentifier addScriptEH(types::control ctrl, eventhandlers_ctrl type);
    void delScriptEH(types::control ctrl, eventhandlers_ctrl type, EHIdentifier& handle);

    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_ctrl, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapCtrlEH;

    template <eventhandlers_ctrl Type>
    struct __ctrlAddEventHandler_Impl;

#define EH_Add_Ctrl_definition(name, retVal, fncArg)                                                                                                          \
    template <>                                                                                                                                               \
    struct __ctrlAddEventHandler_Impl<eventhandlers_ctrl::name> {                                                                                             \
        using fncType = std::function<retVal(fncArg)>;                                                                                                        \
        [[nodiscard]] static EHIdentifier add(types::control ctrl, std::function<retVal(fncArg)> function) {                                                  \
            auto ident = addScriptEH(ctrl, eventhandlers_ctrl::name);                                                                                         \
            funcMapCtrlEH[ident] = {eventhandlers_ctrl::name, std::make_shared<std::function<void()>>(*reinterpret_cast<std::function<void()>*>(&function))}; \
            return ident;                                                                                                                                     \
        }                                                                                                                                                     \
    };

    EHDEF_CTRL(EH_Add_Ctrl_definition)

    template <eventhandlers_ctrl Type, typename Func = typename __ctrlAddEventHandler_Impl<Type>::fncType>
    [[nodiscard]] EHIdentifierHandle ctrlAddEventHandler(types::control ctrl, Func fnc) {
        return {__ctrlAddEventHandler_Impl<Type>::add(ctrl, fnc), [ctrl,type = Type](EHIdentifier& id) { funcMapCtrlEH.erase(id); delScriptEH(ctrl,type,id); }};
    }
#pragma endregion

}  // namespace intercept::client                                                                                    
