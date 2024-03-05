/*!
@file
@author Dedmen (dedmen@dedmen.de)

@brief Helper stuff for Binding Callbacks to Eventhandlers on Objects and alike.

https://github.com/NouberNou/intercept

@defgroup eh_bind Eventhandlers with direct Callbacks
Provides the ability to assign Eventhandlers without going through SQF
*/
#pragma once

#if _WIN64 || __X86_64__
#pragma comment(linker, "/include:client_eventhandlers_clear")
#else
#pragma comment(linker, "/include:_client_eventhandlers_clear")
#endif

#include "../shared/client_types.hpp"

#ifndef INTERCEPT_NO_SQF
#include <functional>
#include <vector>
namespace intercept::client {

    enum class loaded_saveType {
        save,         ///< custom save, achieved by pressing SAVE button in the pause menu
        autosave,     ///< automatic checkpoint, saved using saveGame command
        continuesave  ///< saved when leaving a mission to the main menu
    };
    
    /// @private
    struct EHIdentifier {
        int32_t internal_id;
        int arma_eh_id;
        uint32_t EHIteration;
        uint8_t EHType;
        bool already_deleted = false;
        bool operator==(const EHIdentifier& other) const {
            return internal_id == other.internal_id && arma_eh_id == other.arma_eh_id && EHType == other.EHType;
        }


    };


    /// @private
    struct EHIdentifier_hasher {
        size_t operator()(const intercept::client::EHIdentifier& x) const {
            using intercept::types::__internal::pairhash;
            return pairhash(pairhash(x.internal_id, x.arma_eh_id), x.EHType);
        }
    };


    
    /**
     * @brief 
     * @ingroup eh_bind
     */
    class EHIdentifierHandle {
    public:
        constexpr EHIdentifierHandle() = default;
        EHIdentifierHandle(EHIdentifier ident, std::function<void(EHIdentifier&)> onDelete) : handle(std::make_shared<impl>(std::move(ident), std::move(onDelete))) {}
        EHIdentifierHandle& operator=(const EHIdentifierHandle& other){
            //This is extra protection against deleting already deleted EHs.
            //EHIteration already protects against this so this is just optional extra
            //Performance impact is minimal so I don't really care if this is useless
            if (other.handle && handle && handle!=other.handle) {
                auto& myIdent = handle->ident;
                auto& otherIdent = other.handle->ident;
                if (otherIdent.internal_id != myIdent.internal_id
                    && otherIdent.EHType == myIdent.EHType
                    && otherIdent.arma_eh_id == myIdent.arma_eh_id) //We were replaced by a EH with same ID and type. Which can only happen if the old one doesn't exist.
                    other.handle->ident.already_deleted = true;
            }
            handle = other.handle;
            return *this;
        }

    private:
        class impl {
        public:
            impl(EHIdentifier&& ident_, std::function<void(EHIdentifier&)>&& onDelete_) : ident(ident_), onDelete(onDelete_) {}
            EHIdentifier ident;
            std::function<void(EHIdentifier&)> onDelete;
            ~impl();
        };
        std::shared_ptr<impl> handle;
    };

    enum class eventhandler_type {
        mission,
        object,
        display,
        ctrl,
        mp,
        group,
        ammo,
        custom
    };

#pragma region Mission Eventhandlers

#define EH_Func_Args_Mission_Draw3D
#define EH_Func_Args_Mission_Ended types::r_string end_type
#define EH_Func_Args_Mission_MPEnded
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
#define EH_Func_Args_Mission_ControlsShifted types::object newController, types::object oldController, types::object vehicle, bool copilotEnabled, bool controlsUnlocked
#define EH_Func_Args_Mission_ExtensionCallback types::r_string name, types::r_string function, types::r_string data
#define EH_Func_Args_Mission_HandleAccTime float currentTimeAcc, float prevTimeAcc, bool messageSuppressed
#define EH_Func_Args_Mission_HandleChatMessage int channel, int owner, types::r_string from, types::r_string text, types::object person, types::r_string name, types::r_string strID, bool forcedDisplay, bool isPlayerMessage, int sentenceType, int chatMessageType
#define EH_Func_Args_Mission_MarkerCreated types::r_string marker, int channelNumber, types::object owner, bool local
#define EH_Func_Args_Mission_MarkerDeleted types::r_string marker, bool local
#define EH_Func_Args_Mission_MarkerUpdated types::r_string marker, bool local
#define EH_Func_Ret_Mission_HandleChatMessage std::optional<std::variant<bool, types::sqf_string, types::auto_array<types::sqf_string>>>
    //Name,Function return value, Function Arguments

#define EHDEF_MISSION(XX)                                                                                \
    XX(BuildingChanged, void, EH_Func_Args_Mission_BuildingChanged)                                      \
    XX(CommandModeChanged, void, EH_Func_Args_Mission_CommandModeChanged)                                \
    XX(ControlsShifted, void, EH_Func_Args_Mission_ControlsShifted)                                      \
    XX(Draw3D, void, EH_Func_Args_Mission_Draw3D)                                                        \
    XX(EachFrame, void, EH_Func_Args_Mission_EachFrame)                                                  \
    XX(Ended, void, EH_Func_Args_Mission_Ended)                                                          \
    XX(MPEnded, void, EH_Func_Args_Mission_MPEnded)                                                      \
    XX(EntityKilled, void, EH_Func_Args_Mission_EntityKilled)                                            \
    XX(EntityRespawned, void, EH_Func_Args_Mission_EntityRespawned)                                      \
    XX(ExtensionCallback, void, EH_Func_Args_Mission_ExtensionCallback)                                  \
    XX(GroupIconClick, void, EH_Func_Args_Mission_GroupIconClick)                                        \
    XX(GroupIconOverEnter, void, EH_Func_Args_Mission_GroupIconOverEnter)                                \
    XX(GroupIconOverLeave, void, EH_Func_Args_Mission_GroupIconOverLeave)                                \
    XX(HandleAccTime, std::optional<bool>, EH_Func_Args_Mission_HandleAccTime)                           \
    XX(HandleChatMessage, EH_Func_Ret_Mission_HandleChatMessage, EH_Func_Args_Mission_HandleChatMessage) \
    XX(HandleDisconnect, std::optional<bool>, EH_Func_Args_Mission_HandleDisconnect)                     \
    XX(HCGroupSelectionChanged, void, EH_Func_Args_Mission_HCGroupSelectionChanged)                      \
    XX(Loaded, void, EH_Func_Args_Mission_Loaded)                                                        \
    XX(Map, void, EH_Func_Args_Mission_Map)                                                              \
    XX(MapSingleClick, void, EH_Func_Args_Mission_MapSingleClick)                                        \
    XX(MarkerCreated, void, EH_Func_Args_Mission_MarkerCreated)                                          \
    XX(MarkerDeleted, void, EH_Func_Args_Mission_MarkerDeleted)                                          \
    XX(MarkerUpdated, void, EH_Func_Args_Mission_MarkerUpdated)                                          \
    XX(PlayerConnected, void, EH_Func_Args_Mission_PlayerConnected)                                      \
    XX(PlayerDisconnected, void, EH_Func_Args_Mission_PlayerDisconnected)                                \
    XX(PlayerViewChanged, void, EH_Func_Args_Mission_PlayerViewChanged)                                  \
    XX(PreloadStarted, void, EH_Func_Args_Mission_PreloadStarted)                                        \
    XX(PreloadFinished, void, EH_Func_Args_Mission_PreloadFinished)                                      \
    XX(TeamSwitch, void, EH_Func_Args_Mission_TeamSwitch)

#define COMPILETIME_CHECK_ENUM_MISSION(name, retVal, funcArg) static_assert(eventhandlers_mission::name >= eventhandlers_mission::BuildingChanged);
    //DOC https://stackoverflow.com/a/25235815
    /** @enum eventhandlers_mission
@brief Mission event handlers are specific EHs that are anchored to the running mission and automatically removed when mission is over.
*/
    enum class eventhandlers_mission {
        BuildingChanged,                 ///< <a href=https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#BuildingChanged">See the wiki</a>
        CommandModeChanged,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#CommandModeChanged">See the wiki</a>
        ControlsShifted,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#ControlsShifted">See the wiki</a>
        Draw3D,                          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Draw3D">See the wiki</a>
        EachFrame,                       ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#EachFrame">See the wiki</a>
        Ended,                           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Ended">See the wiki</a>
        MPEnded,                         ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#MPEnded">See the wiki</a>
        EntityKilled,                    ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#EntityKilled">See the wiki</a>
        EntityRespawned,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#EntityRespawned">See the wiki</a>
        ExtensionCallback,               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#ExtensionCallback">See the wiki</a>
        GroupIconClick,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#GroupIconClick">See the wiki</a>
        GroupIconOverEnter,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#GroupIconOverEnter">See the wiki</a>
        GroupIconOverLeave,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#GroupIconOverLeave">See the wiki</a>
        HandleAccTime,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#HandleAccTime">See the wiki</a>
        HandleChatMessage,               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#HandleChatMessage">See the wiki</a>
        HandleDisconnect,                ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#HandleDisconnect">See the wiki</a>
        HCGroupSelectionChanged,         ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#HCGroupSelectionChanged">See the wiki</a>
        Loaded,                          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Loaded">See the wiki</a>
        Map,                             ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Map">See the wiki</a>
        MapSingleClick,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#MapSingleClick">See the wiki</a>
        MarkerCreated,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#MarkerCreated">See the wiki</a>
        MarkerDeleted,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#MarkerDeleted">See the wiki</a>
        MarkerUpdated,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#MarkerUpdated">See the wiki</a>
        PlayerConnected,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PlayerConnected">See the wiki</a>
        PlayerDisconnected,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PlayerDisconnected">See the wiki</a>
        PlayerViewChanged,               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PlayerViewChanged">See the wiki</a>
        PreloadStarted,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PreloadStarted">See the wiki</a>
        PreloadFinished,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PreloadFinished">See the wiki</a>
        TeamSwitch                       ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#TeamSwitch">See the wiki</a>
    };
    /*
    @var eventhandlers_mission::Loaded
    @brief Game loading from save event
    @remark "Loaded" event handler should be added BEFORE the mission is loaded from save.Placing it in a function with preInit = 1; usually does the trick.
    */
    EHDEF_MISSION(COMPILETIME_CHECK_ENUM_MISSION)

    /// @private
    intercept::types::game_value callEHHandler(eventhandlers_mission ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func);

    /// @private
    EHIdentifier addScriptEH(eventhandlers_mission type);
    /// @private
    void delScriptEH(eventhandlers_mission type, EHIdentifier& handle);
    /// @private
    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_mission, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMissionEH;
    /// @private
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

    /**
    * @brief Registers a Mission Eventhandler with callback to a C++ function
    * @tparam Type is a value from intercept::client::eventhandlers_mission
    * @param fnc - The function that will get called
    * @return A wrapper that should be kept alive as long as the Eventhandler should be active
    * @ingroup eh_bind
    */
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
    enum class get_in_position {
        driver,
        gunner,
        cargo
    };
#define EH_Func_Args_Object_GetIn types::object vehicle, get_in_position position, types::object unit, types::rv_turret_path turret_path
#define EH_Func_Args_Object_GetInMan types::object vehicle, get_in_position position, types::object unit, types::rv_turret_path turret_path
#define EH_Func_Args_Object_GetOut types::object vehicle, get_in_position position, types::object unit, types::rv_turret_path turret_path
#define EH_Func_Args_Object_GetOutMan types::object vehicle, get_in_position position, types::object unit, types::rv_turret_path turret_path
#define EH_Func_Args_Object_HandleDamage types::object unit, types::r_string hitSelection, float dmage, types::object source, types::r_string projectile, float hitPartIndex, types::object instigator, types::r_string hitPoint
#define EH_Func_Args_Object_HandleHeal types::object unit, types::object healer, bool healerCanHeal
#define EH_Func_Args_Object_HandleRating types::object unit, float rating
#define EH_Func_Args_Object_HandleScore types::object unit, types::object object_, float score
#define EH_Func_Args_Object_Hit types::object unit, types::object causedBy, float damage, types::object instigator
//#TODO correct type for ammo

 class eventhandler_hit_part_type {
 public:
     explicit eventhandler_hit_part_type(const types::game_value& gv) :
         target(gv[0]),
         shooter(gv[1]),
         bullet(gv[2]),
         position(gv[3]),
         velocity(gv[4]),
         selection(gv[5].to_array().begin(), gv[5].to_array().end()),
         ammo(gv[6].to_array().begin(), gv[6].to_array().end()),
         direction(gv[7]),
         radius(gv[8]),
         surface(gv[9]),
         direct(gv[19]) {}
     types::object target;
     types::object shooter;
     types::object bullet;
     types::vector3 position;
     types::vector3 velocity;
     types::auto_array<types::r_string> selection;
     types::auto_array<types::game_value> ammo;
     types::vector3 direction;
     float radius;
     types::r_string surface;
     bool direct;
 };

#define EH_Func_Args_Object_HitPart std::vector<eventhandler_hit_part_type>;
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
#define EH_Func_Args_Object_TurnIn types::object vehicle, types::object unit, types::rv_turret_path turret_path
#define EH_Func_Args_Object_TurnOut types::object vehicle, types::object unit, types::rv_turret_path turret_path
#define EH_Func_Args_Object_WeaponAssembled types::object unit, types::object weapon
#define EH_Func_Args_Object_WeaponDisassembled types::object unit, types::object primaryBag, types::object secondarybag
#define EH_Func_Args_Object_WeaponDeployed types::object unit, bool isDeployed
#define EH_Func_Args_Object_WeaponRested types::object unit, bool isRested
#define EH_Func_Args_Object_Disassembled types::object entity, types::object primaryBag, types::object secondaryBag
#define EH_Func_Args_Object_PathCalculated types::object agent, types::auto_array<types::vector3> path
#define EH_Func_Args_Object_PeriscopeElevationChanged types::object vehicle, types::rv_turret_path turret, float elevation, float direction, bool userIsBlocked
#define EH_Func_Args_Object_Suppressed types::object unit, float distance, types::object shooter, types::object instigator, types::object ammoObject, types::r_string ammoClassName, types::config ammoConfig


//Name,Function return value, Function Arguments
#define EHDEF_OBJECT(XX)                                                               \
    XX(AnimChanged, void, EH_Func_Args_Object_AnimChanged)                             \
    XX(AnimDone, void, EH_Func_Args_Object_AnimDone)                                   \
    XX(AnimStateChanged, void, EH_Func_Args_Object_AnimStateChanged)                   \
    XX(ContainerClosed, void, EH_Func_Args_Object_ContainerClosed)                     \
    XX(ContainerOpened, void, EH_Func_Args_Object_ContainerOpened)                     \
    XX(ControlsShifted, void, EH_Func_Args_Object_ControlsShifted)                     \
    XX(Dammaged, void, EH_Func_Args_Object_Dammaged)                                   \
    XX(Deleted, void, EH_Func_Args_Object_Deleted)                                     \
    XX(Disassembled, void, EH_Func_Args_Object_Disassembled)                           \
    XX(Engine, void, EH_Func_Args_Object_Engine)                                       \
    XX(EpeContact, void, EH_Func_Args_Object_EpeContact)                               \
    XX(EpeContactEnd, void, EH_Func_Args_Object_EpeContactEnd)                         \
    XX(EpeContactStart, void, EH_Func_Args_Object_EpeContactStart)                     \
    XX(Explosion, void, EH_Func_Args_Object_Explosion)                                 \
    XX(Fired, void, EH_Func_Args_Object_Fired)                                         \
    XX(FiredMan, void, EH_Func_Args_Object_FiredMan)                                   \
    XX(FiredNear, void, EH_Func_Args_Object_FiredNear)                                 \
    XX(Fuel, void, EH_Func_Args_Object_Fuel)                                           \
    XX(Gear, void, EH_Func_Args_Object_Gear)                                           \
    XX(GetIn, void, EH_Func_Args_Object_GetIn)                                         \
    XX(GetInMan, void, EH_Func_Args_Object_GetInMan)                                   \
    XX(GetOut, void, EH_Func_Args_Object_GetOut)                                       \
    XX(GetOutMan, void, EH_Func_Args_Object_GetOutMan)                                 \
    XX(HandleDamage, std::optional<float>, EH_Func_Args_Object_HandleDamage)           \
    XX(HandleHeal, void, EH_Func_Args_Object_HandleHeal)                               \
    XX(HandleIdentity, std::optional<bool>, EH_Func_Args_Object_HandleIdentity)        \
    XX(HandleRating, std::optional<float>, EH_Func_Args_Object_HandleRating)           \
    XX(HandleScore, std::optional<bool>, EH_Func_Args_Object_HandleScore)              \
    XX(Hit, void, EH_Func_Args_Object_Hit)                                             \
    XX(Init, void, EH_Func_Args_Object_Init)                                           \
    XX(IncomingMissile, void, EH_Func_Args_Object_IncomingMissile)                     \
    XX(InventoryClosed, void, EH_Func_Args_Object_InventoryClosed)                     \
    XX(InventoryOpened, void, EH_Func_Args_Object_InventoryOpened)                     \
    XX(Killed, void, EH_Func_Args_Object_Killed)                                       \
    XX(LandedTouchDown, void, EH_Func_Args_Object_LandedTouchDown)                     \
    XX(LandedStopped, void, EH_Func_Args_Object_LandedStopped)                         \
    XX(Landing, void, EH_Func_Args_Object_Landing)                                     \
    XX(LandingCanceled, void, EH_Func_Args_Object_LandingCanceled)                     \
    XX(Local, void, EH_Func_Args_Object_Local)                                         \
    XX(PathCalculated, void, EH_Func_Args_Object_PathCalculated)                       \
    XX(PeriscopeElevationChanged, void, EH_Func_Args_Object_PeriscopeElevationChanged) \
    XX(PostReset, void, EH_Func_Args_Object_PostReset)                                 \
    XX(Put, void, EH_Func_Args_Object_Put)                                             \
    XX(Reloaded, void, EH_Func_Args_Object_Reloaded)                                   \
    XX(Respawn, void, EH_Func_Args_Object_Respawn)                                     \
    XX(RopeAttach, void, EH_Func_Args_Object_RopeAttach)                               \
    XX(RopeBreak, void, EH_Func_Args_Object_RopeBreak)                                 \
    XX(SeatSwitched, void, EH_Func_Args_Object_SeatSwitched)                           \
    XX(SeatSwitchedMan, void, EH_Func_Args_Object_SeatSwitchedMan)                     \
    XX(SoundPlayed, void, EH_Func_Args_Object_SoundPlayed)                             \
    XX(Suppressed, void, EH_Func_Args_Object_Suppressed)                               \
    XX(Take, void, EH_Func_Args_Object_Take)                                           \
    XX(TaskSetAsCurrent, void, EH_Func_Args_Object_TaskSetAsCurrent)                   \
    XX(TurnIn, void, EH_Func_Args_Object_TurnIn)                                       \
    XX(TurnOut, void, EH_Func_Args_Object_TurnOut)                                     \
    XX(WeaponAssembled, void, EH_Func_Args_Object_WeaponAssembled)                     \
    XX(WeaponDisassembled, void, EH_Func_Args_Object_WeaponDisassembled)               \
    XX(WeaponDeployed, void, EH_Func_Args_Object_WeaponDeployed)                       \
    XX(WeaponRested, void, EH_Func_Args_Object_WeaponRested)

// XX(HitPart, void, EH_Func_Args_Object_HitPart)

#define COMPILETIME_CHECK_ENUM_OBJECT(name, retVal, funcArg) static_assert(eventhandlers_object::name >= eventhandlers_object::AnimChanged);

    /** @enum eventhandlers_object
@brief #TODO
*/
    //#TODO doc
    enum class eventhandlers_object {
        AnimChanged,               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#AnimChanged">see the wiki</a>
        AnimDone,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#AnimDone">see the wiki</a>
        AnimStateChanged,          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#AnimStateChanged">see the wiki</a>
        ContainerClosed,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#ContainerClosed">see the wiki</a>
        ContainerOpened,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#ContainerOpened">see the wiki</a>
        ControlsShifted,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#ControlsShifted">see the wiki</a>
        Dammaged,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Dammaged">see the wiki</a>
        Deleted,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Deleted">see the wiki</a>
        Disassembled,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Disassembled">see the wiki</a>
        Engine,                    ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Engine">see the wiki</a>
        EpeContact,                ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#EpeContact">see the wiki</a>
        EpeContactEnd,             ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#EpeContactEnd">see the wiki</a>
        EpeContactStart,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#EpeContactStart">see the wiki</a>
        Explosion,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Explosion">see the wiki</a>
        Fired,                     ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Fired">see the wiki</a>
        FiredMan,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#FiredMan">see the wiki</a>
        FiredNear,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#FiredNear">see the wiki</a>
        Fuel,                      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Fuel">see the wiki</a>
        Gear,                      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Gear">see the wiki</a>
        GetIn,                     ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#GetIn">see the wiki</a>
        GetInMan,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#GetInMan">see the wiki</a>
        GetOut,                    ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#GetOut">see the wiki</a>
        GetOutMan,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#GetOutMan">see the wiki</a>
        HandleDamage,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#HandleDamage">see the wiki</a>
        HandleHeal,                ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#HandleHeal">see the wiki</a>
        HandleIdentity,            ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#HandleIdentity">see the wiki</a>
        HandleRating,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#HandleRating">see the wiki</a>
        HandleScore,               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#HandleScore">see the wiki</a>
        Hit,                       ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Hit">see the wiki</a>
        HitPart,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#HitPart">see the wiki</a>
        Init,                      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Init">see the wiki</a>
        IncomingMissile,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#IncomingMissile">see the wiki</a>
        InventoryClosed,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#InventoryClosed">see the wiki</a>
        InventoryOpened,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#InventoryOpened">see the wiki</a>
        Killed,                    ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Killed">see the wiki</a>
        LandedTouchDown,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#LandedTouchDown">see the wiki</a>
        LandedStopped,             ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#LandedStopped">see the wiki</a>
        Landing,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Landing">see the wiki</a>
        LandingCanceled,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#LandingCanceled">see the wiki</a>
        Local,                     ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Local">see the wiki</a>
        PathCalculated,            ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#PathCalculated">see the wiki</a>
        PeriscopeElevationChanged, ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#PeriscopeElevationChanged">see the wiki</a>
        PostReset,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#PostReset">see the wiki</a>
        Put,                       ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Put">see the wiki</a>
        Reloaded,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Reloaded">see the wiki</a>
        Respawn,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Respawn">see the wiki</a>
        RopeAttach,                ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#RopeAttach">see the wiki</a>
        RopeBreak,                 ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#RopeBreak">see the wiki</a>
        SeatSwitched,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#SeatSwitched">see the wiki</a>
        SeatSwitchedMan,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#SeatSwitchedMan">see the wiki</a>
        SoundPlayed,               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#SoundPlayed">see the wiki</a>
        Suppressed,                ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Suppressed">see the wiki</a>
        Take,                      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Take">see the wiki</a>
        TaskSetAsCurrent,          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#TaskSetAsCurrent">see the wiki</a>
        TurnIn,                    ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#TurnIn">see the wiki</a>
        TurnOut,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#TurnOut">see the wiki</a>
        WeaponAssembled,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#WeaponAssembled">see the wiki</a>
        WeaponDisassembled,        ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#WeaponDisassembled">see the wiki</a>
        WeaponDeployed,            ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#WeaponDeployed">see the wiki</a>
        WeaponRested               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#WeaponRested">see the wiki</a>
    };

    EHDEF_OBJECT(COMPILETIME_CHECK_ENUM_OBJECT)
    /// @private
    intercept::types::game_value callEHHandler(eventhandlers_object ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func);
    /// @private
    EHIdentifier addScriptEH(types::object obj, eventhandlers_object type);
    /// @private
    void delScriptEH(types::object obj, eventhandlers_object type, EHIdentifier& handle);
    /// @private
    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_object, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapObjectEH;
    /// @private
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

    /// @private
    template <>
    struct __addEventHandler_Impl<eventhandlers_object::HitPart> {
        using fncType = std::function<void(std::vector<eventhandler_hit_part_type>)>;
        [[nodiscard]] static EHIdentifier add(types::object obj, std::function<void(std::vector<eventhandler_hit_part_type>)> function) {
            auto ident = addScriptEH(obj, eventhandlers_object::HitPart);
            funcMapObjectEH[ident] = { eventhandlers_object::HitPart, std::make_shared<std::function<void()>>(*reinterpret_cast<std::function<void()>*>(&function)) };
            return ident;
        }
    };



    /**
    * @brief Registers a Eventhandler with callback to a C++ function
    * @tparam Type is a value from intercept::client::eventhandlers_object
    * @param obj - the object you add this Eventhandler to.
    * @param fnc - The function that will get called
    * @return A wrapper that should be kept alive as long as the Eventhandler should be active
    * @ingroup eh_bind
    */
    template <eventhandlers_object Type, typename Func = typename __addEventHandler_Impl<Type>::fncType>
    [[nodiscard]] EHIdentifierHandle addEventHandler(types::object obj, Func fnc) {
        return { __addEventHandler_Impl<Type>::add(obj, fnc), [obj,type = Type](EHIdentifier& id) { funcMapObjectEH.erase(id); delScriptEH(obj,type,id); } };
    }

#pragma endregion

#pragma region CTRL Eventhandlers

#define EH_Func_Args_Ctrl_Draw types::control map
#define EH_Func_Args_Ctrl_MouseButtonDown types::control ctrl, int button, float x_pos, float y_pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseButtonUp types::control ctrl, int button, float x_pos, float y_pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseButtonClick types::control ctrl, int button, float x_pos, float y_pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseButtonDblClick types::control ctrl, int button, float x_pos, float y_pos, bool Shift, bool Ctrl, bool Alt
#define EH_Func_Args_Ctrl_MouseMoving types::control ctrl, float x_pos, float y_pos, bool mouse_over
#define EH_Func_Args_Ctrl_MouseHolding types::control ctrl, float x_pos, float y_pos, bool mouse_over
#define EH_Func_Args_Ctrl_ButtonClick types::control ctrl
#define EH_Func_Args_Ctrl_ButtonDblClick types::control ctrl
#define EH_Func_Args_Ctrl_ButtonDown types::control ctrl
#define EH_Func_Args_Ctrl_ButtonUp types::control ctrl
#define EH_Func_Args_Ctrl_CanDestroy types::control ctrl, float exitCode
#define EH_Func_Args_Ctrl_Char types::control ctrl, int charCode 
#define EH_Func_Args_Ctrl_CheckBoxesSelChanged types::control ctrl, int selectedIndex, int currentIndex
#define EH_Func_Args_Ctrl_CheckedChanged types::control checkBox, bool checked
#define EH_Func_Args_Ctrl_Destroy types::control ctrl, float exitCode
#define EH_Func_Args_Ctrl_HTMLLink types::control ctrl, types::r_string url
#define EH_Func_Args_Ctrl_IMEChar types::control ctrl, int char_code
#define EH_Func_Args_Ctrl_IMEComposition types::control ctrl, int char_code
#define EH_Func_Args_Ctrl_KeyDown types::control ctrl, int keyCode, bool shift_held, bool ctrl_held, bool alt_held
#define EH_Func_Args_Ctrl_KeyUp types::control ctrl, int keyCode, bool shift_held, bool ctrl_held, bool alt_held
#define EH_Func_Args_Ctrl_KillFocus types::control ctrl
#define EH_Func_Args_Ctrl_LBDblClick types::control ctrl, int selected_index
    class event_handlers_listbox_info {
    public:
        types::r_string text_lb{};
        types::r_string data_lb{};
        float value_lb{};
        explicit event_handlers_listbox_info(const types::game_value& gv) :
            text_lb(gv[0]),
            value_lb(gv[1]),
            data_lb(gv[2])
            
        {
        }
    };
#define EH_Func_Args_Ctrl_LBDrag types::control ctrl, types::auto_array<event_handlers_listbox_info> listBoxInfo
#define EH_Func_Args_Ctrl_LBDragging types::control ctrl, float x_pos, float y_pos, int ctrlIDC, types::auto_array<event_handlers_listbox_info> listBoxInfo
#define EH_Func_Args_Ctrl_LBDrop types::control ctrl, float x_pos, float y_pos, int ctrlIDC, types::auto_array<event_handlers_listbox_info> listBoxInfo
#define EH_Func_Args_Ctrl_LBListSelChanged types::control ctrl, int selected_index
#define EH_Func_Args_Ctrl_LBSelChanged types::control ctrl, int selected_index
#define EH_Func_Args_Ctrl_Load types::control ctrl, types::config ctrl_config
#define EH_Func_Args_Ctrl_MenuSelected types::control ctrl, int menu_id
#define EH_Func_Args_Ctrl_MouseEnter types::control ctrl
#define EH_Func_Args_Ctrl_MouseExit types::control ctrl
#define EH_Func_Args_Ctrl_MouseZChanged types::control ctrl, float scroll_val
#define EH_Func_Args_Ctrl_ObjectMoved types::control ctrl, types::vector3 offset_vector
#define EH_Func_Args_Ctrl_SetFocus types::control ctrl
#define EH_Func_Args_Ctrl_SliderPosChanged types::control ctrl, float new_value
#define EH_Func_Args_Ctrl_ToolBoxSelChanged types::control ctrl, int selected_index
#define EH_Func_Args_Ctrl_TreeCollapsed types::control ctrl, types::auto_array<int> tree_path
#define EH_Func_Args_Ctrl_TreeDblClick types::control ctrl, types::auto_array<int> tree_path
#define EH_Func_Args_Ctrl_TreeExpanded types::control ctrl, types::auto_array<int> tree_path
#define EH_Func_Args_Ctrl_TreeLButtonDown types::control ctrl
#define EH_Func_Args_Ctrl_TreeMouseExit types::control ctrl
#define EH_Func_Args_Ctrl_TreeMouseHold types::control ctrl, types::auto_array<int> tree_path
#define EH_Func_Args_Ctrl_TreeMouseMove types::control ctrl, types::auto_array<int> tree_path
#define EH_Func_Args_Ctrl_TreeSelChanged types::control ctrl, types::auto_array<int> tree_path
#define EH_Func_Args_Ctrl_VideoStopped types::control ctrl



//Name,Function return value, Function Arguments
#define EHDEF_CTRL(XX)                                                                  \
    XX(ButtonClick, std::optional<bool>, EH_Func_Args_Ctrl_ButtonClick)                 \
    XX(ButtonDblClick, void, EH_Func_Args_Ctrl_ButtonDblClick)                          \
    XX(ButtonDown, void, EH_Func_Args_Ctrl_ButtonDown)                                  \
    XX(ButtonUp, void, EH_Func_Args_Ctrl_ButtonUp)                                      \
    XX(CanDestroy, std::optional<bool>, EH_Func_Args_Ctrl_CanDestroy)                   \
    XX(Char, void, EH_Func_Args_Ctrl_Char)                                              \
    XX(CheckBoxesSelChanged, void, EH_Func_Args_Ctrl_CheckBoxesSelChanged)              \
    XX(CheckedChanged, void, EH_Func_Args_Ctrl_CheckedChanged)                          \
    XX(Destroy, void, EH_Func_Args_Ctrl_Destroy)                                        \
    XX(Draw, void, EH_Func_Args_Ctrl_Draw)                                              \
    XX(HTMLLink, void, EH_Func_Args_Ctrl_HTMLLink)                                      \
    XX(IMEChar, void, EH_Func_Args_Ctrl_IMEChar)                                        \
    XX(IMEComposition, void, EH_Func_Args_Ctrl_IMEComposition)                          \
    XX(KeyDown, std::optional<bool>, EH_Func_Args_Ctrl_KeyDown)                         \
    XX(KeyUp, std::optional<bool>, EH_Func_Args_Ctrl_KeyUp)                             \
    XX(KillFocus, void, EH_Func_Args_Ctrl_KillFocus)                                    \
    XX(LBDblClick, void, EH_Func_Args_Ctrl_LBDblClick)                                  \
    XX(LBDrag, void, EH_Func_Args_Ctrl_LBDrag)                                          \
    XX(LBDragging, void, EH_Func_Args_Ctrl_LBDragging)                                  \
    XX(LBDrop, void, EH_Func_Args_Ctrl_LBDrop)                                          \
    XX(LBListSelChanged, void, EH_Func_Args_Ctrl_LBListSelChanged)                      \
    XX(LBSelChanged, void, EH_Func_Args_Ctrl_LBSelChanged)                              \
    XX(Load, void, EH_Func_Args_Ctrl_Load)                                              \
    XX(MenuSelected, void, EH_Func_Args_Ctrl_MenuSelected)                              \
    XX(MouseButtonClick, std::optional<bool>, EH_Func_Args_Ctrl_MouseButtonClick)       \
    XX(MouseButtonDblClick, std::optional<bool>, EH_Func_Args_Ctrl_MouseButtonDblClick) \
    XX(MouseButtonDown, std::optional<bool>, EH_Func_Args_Ctrl_MouseButtonDown)         \
    XX(MouseButtonUp, std::optional<bool>, EH_Func_Args_Ctrl_MouseButtonUp)             \
    XX(MouseEnter, void, EH_Func_Args_Ctrl_MouseEnter)                                  \
    XX(MouseExit, void, EH_Func_Args_Ctrl_MouseExit)                                    \
    XX(MouseHolding, void, EH_Func_Args_Ctrl_MouseHolding)                              \
    XX(MouseMoving, void, EH_Func_Args_Ctrl_MouseMoving)                                \
    XX(MouseZChanged, void, EH_Func_Args_Ctrl_MouseZChanged)                            \
    XX(ObjectMoved, void, EH_Func_Args_Ctrl_ObjectMoved)                                \
    XX(SetFocus, void, EH_Func_Args_Ctrl_SetFocus)                                      \
    XX(SliderPosChanged, void, EH_Func_Args_Ctrl_SliderPosChanged)                      \
    XX(ToolBoxSelChanged, void, EH_Func_Args_Ctrl_ToolBoxSelChanged)                    \
    XX(TreeCollapsed, void, EH_Func_Args_Ctrl_TreeCollapsed)                            \
    XX(TreeDblClick, void, EH_Func_Args_Ctrl_TreeDblClick)                              \
    XX(TreeExpanded, void, EH_Func_Args_Ctrl_TreeExpanded)                              \
    XX(TreeLButtonDown, void, EH_Func_Args_Ctrl_TreeLButtonDown)                        \
    XX(TreeMouseExit, void, EH_Func_Args_Ctrl_TreeMouseExit)                            \
    XX(TreeMouseHold, void, EH_Func_Args_Ctrl_TreeMouseHold)                            \
    XX(TreeMouseMove, void, EH_Func_Args_Ctrl_TreeMouseMove)                            \
    XX(TreeSelChanged, void, EH_Func_Args_Ctrl_TreeSelChanged)                          \
    XX(VideoStopped, void, EH_Func_Args_Ctrl_VideoStopped)

#define COMPILETIME_CHECK_ENUM_CTRL(name, retVal, funcArg) static_assert(eventhandlers_ctrl::name >= eventhandlers_ctrl::ButtonClick);

    /** @enum eventhandlers_object
    @brief #TODO
    */
    //#TODO doc
    enum class eventhandlers_ctrl {
        ButtonClick,          ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onButtonClick">see the wiki</a>
        ButtonDblClick,       ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onButtonDblClick">see the wiki</a>
        ButtonDown,           ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onButtonDown">see the wiki</a>
        ButtonUp,             ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onButtonUp">see the wiki</a>
        CanDestroy,           ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onCanDestroy">see the wiki</a>
        Char,                 ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onChar">see the wiki</a>
        CheckBoxesSelChanged, ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onCheckBoxesSelChanged">see the wiki</a>
        CheckedChanged,       ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onCheckedChanged">see the wiki</a>
        Destroy,              ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onDestroy">see the wiki</a>
        Draw,                 ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onDraw">see the wiki</a>
        HTMLLink,             ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onHTMLLink">see the wiki</a>
        IMEChar,              ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onIMEChar">see the wiki</a>
        IMEComposition,       ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onIMEComposition">see the wiki</a>
        KeyDown,              ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onKeyDown">see the wiki</a>
        KeyUp,                ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onKeyUp">see the wiki</a>
        KillFocus,            ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onKillFocus">see the wiki</a>
        LBDblClick,           ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLBDblClick">see the wiki</a>
        LBDrag,               ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLBDrag">see the wiki</a>
        LBDragging,           ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLBDragging">see the wiki</a>
        LBDrop,               ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLBDrop">see the wiki</a>
        LBListSelChanged,     ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLBListSelChanged">see the wiki</a>
        LBSelChanged,         ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLBSelChanged">see the wiki</a>
        Load,                 ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLoad">see the wiki</a>
        MenuSelected,         ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMenuSelected">see the wiki</a>
        MouseButtonClick,     ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseButtonClick">see the wiki</a>
        MouseButtonDblClick,  ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseButtonDblClick">see the wiki</a>
        MouseButtonDown,      ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseButtonDown">see the wiki</a>
        MouseButtonUp,        ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseButtonUp">see the wiki</a>
        MouseEnter,           ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseEnter">see the wiki</a>
        MouseExit,            ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseExit">see the wiki</a>
        MouseHolding,         ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseHolding">see the wiki</a>
        MouseMoving,          ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseMoving">see the wiki</a>
        MouseZChanged,        ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseZChanged">see the wiki</a>
        ObjectMoved,          ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onObjectMoved">see the wiki</a>
        SetFocus,             ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onSetFocus">see the wiki</a>
        SliderPosChanged,     ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onSliderPosChanged">see the wiki</a>
        ToolBoxSelChanged,    ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onToolBoxSelChanged">see the wiki</a>
        TreeCollapsed,        ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeCollapsed">see the wiki</a>
        TreeDblClick,         ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeDblClick">see the wiki</a>
        TreeExpanded,         ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeExpanded">see the wiki</a>
        TreeLButtonDown,      ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeLButtonDown">see the wiki</a>
        TreeMouseExit,        ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeMouseExit">see the wiki</a>
        TreeMouseHold,        ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeMouseHold">see the wiki</a>
        TreeMouseMove,        ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeMouseMove">see the wiki</a>
        TreeSelChanged,       ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onTreeSelChanged">see the wiki</a>
        VideoStopped          ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onVideoStopped">see the wiki</a>
    };

    EHDEF_CTRL(COMPILETIME_CHECK_ENUM_CTRL)

    /// @private
    intercept::types::game_value callEHHandler(eventhandlers_ctrl ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func);
    /// @private
    EHIdentifier addScriptEH(types::control ctrl, eventhandlers_ctrl type);
    /// @private
    void delScriptEH(types::control ctrl, eventhandlers_ctrl type, EHIdentifier& handle);
    /// @private
    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_ctrl, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapCtrlEH;
    /// @private
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

    /**
    * @brief Registers a CTRL Eventhandler with callback to a C++ function
    * @tparam Type is a value from intercept::client::eventhandlers_ctrl
    * @param ctrl - the control you add this Eventhandler to.
    * @param fnc - The function that will get called
    * @return A wrapper that should be kept alive as long as the Eventhandler should be active
    * @ingroup eh_bind
    */
    template <eventhandlers_ctrl Type, typename Func = typename __ctrlAddEventHandler_Impl<Type>::fncType>
    [[nodiscard]] EHIdentifierHandle ctrlAddEventHandler(types::control ctrl, Func fnc) {
        return {__ctrlAddEventHandler_Impl<Type>::add(ctrl, fnc), [ctrl,type = Type](EHIdentifier& id) { funcMapCtrlEH.erase(id); delScriptEH(ctrl,type,id); }};
    }
#pragma endregion

#pragma region MP Eventhandlers

#define EH_Func_Args_MP_MPHit types::object unit, types::object caused_by, float damage, types::object instigator
#define EH_Func_Args_MP_MPKilled types::object unit, types::object killer, types::object instigator, bool use_effects
#define EH_Func_Args_MP_MPRespawn types::object unit, types::object corpse

    //Name,Function return value, Function Arguments
#define EHDEF_MP(XX)                             \
    XX(MPHit, void, EH_Func_Args_MP_MPHit)       \
    XX(MPKilled, void, EH_Func_Args_MP_MPKilled) \
    XX(MPRespawn, types::vector3, EH_Func_Args_MP_MPRespawn)

#define COMPILETIME_CHECK_ENUM_MP(name, retVal, funcArg) static_assert(eventhandlers_mp::name >= eventhandlers_mp::MPHit);

    /** @enum eventhandlers_mp
    @brief #TODO
    */
    //#TODO doc
    enum class eventhandlers_mp {
        MPHit,
        MPKilled,
        MPRespawn
    };

    EHDEF_MP(COMPILETIME_CHECK_ENUM_MP)

    /// @private
    intercept::types::game_value callEHHandler(eventhandlers_mp ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func);
    /// @private
    EHIdentifier addScriptEH(types::object unit, eventhandlers_mp type);
    /// @private
    void delScriptEH(types::object unit, eventhandlers_mp type, EHIdentifier& handle);
    /// @private
    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_mp, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMPEH;
    /// @private
    template <eventhandlers_mp Type>
    struct __addMPEventHandler_Impl;

#define EH_Add_MP_definition(name, retVal, fncArg)                                                                                                          \
    template <>                                                                                                                                               \
    struct __addMPEventHandler_Impl<eventhandlers_mp::name> {                                                                                             \
        using fncType = std::function<retVal(fncArg)>;                                                                                                        \
        [[nodiscard]] static EHIdentifier add(types::object unit, std::function<retVal(fncArg)> function) {                                                  \
            auto ident = addScriptEH(unit, eventhandlers_mp::name);                                                                                         \
            funcMapMPEH[ident] = {eventhandlers_mp::name, std::make_shared<std::function<void()>>(*reinterpret_cast<std::function<void()>*>(&function))}; \
            return ident;                                                                                                                                     \
        }                                                                                                                                                     \
    };

    EHDEF_MP(EH_Add_MP_definition)


    /**
    * @brief Registers a MP Eventhandler with callback to a C++ function
    * @tparam Type is a value from intercept::client::eventhandlers_mp
    * @param unit - the unit you add this Eventhandler to.
    * @param fnc - The function that will get called
    * @return A wrapper that should be kept alive as long as the Eventhandler should be active
    * @ingroup eh_bind
    */
    template <eventhandlers_mp Type, typename Func = typename __addMPEventHandler_Impl<Type>::fncType>
    [[nodiscard]] EHIdentifierHandle addMPEventHandler(types::object unit, Func fnc) {
        return { __addMPEventHandler_Impl<Type>::add(unit, fnc), [unit,type = Type](EHIdentifier& id) { funcMapMPEH.erase(id); delScriptEH(unit,type,id); } };
    }
#pragma endregion

#pragma region Display Eventhandlers

#define EH_Func_Args_Display_Load types::display disp
#define EH_Func_Args_Display_Unload types::display disp, float exit_code
#define EH_Func_Args_Display_ChildDestroyed types::display disp, types::display closed_disp, float exit_code
#define EH_Func_Args_Display_KeyDown types::display disp, int dik, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Display_KeyUp types::display disp, int dik, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Display_MouseMoving types::display disp, float delta_x, float delta_y
#define EH_Func_Args_Display_MouseZChanged types::display disp, float change
#define EH_Func_Args_Display_MouseButtonDown types::display disp, int button, float x_pos, float y_pos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Display_MouseButtonUp types::display disp, int button, float x_pos, float y_pos, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Display_MouseHolding types::display disp, float x_pos, float y_pos
#define EH_Func_Args_Display_Char types::display disp, int char_code
    

    //Name,Function return value, Function Arguments
#define EHDEF_Display(XX)                                                          \
    XX(Char, void, EH_Func_Args_Display_Char)                                      \
    XX(ChildDestroyed, void, EH_Func_Args_Display_ChildDestroyed)                  \
    XX(KeyDown, std::optional<bool>, EH_Func_Args_Display_KeyDown)                 \
    XX(KeyUp, std::optional<bool>, EH_Func_Args_Display_KeyUp)                     \
    XX(Load, void, EH_Func_Args_Display_Load)                                      \
    XX(MouseButtonDown, std::optional<bool>, EH_Func_Args_Display_MouseButtonDown) \
    XX(MouseButtonUp, std::optional<bool>, EH_Func_Args_Display_MouseButtonUp)     \
    XX(MouseHolding, void, EH_Func_Args_Display_MouseHolding)                      \
    XX(MouseMoving, void, EH_Func_Args_Display_MouseMoving)                        \
    XX(MouseZChanged, void, EH_Func_Args_Display_MouseZChanged)                    \
    XX(Unload, void, EH_Func_Args_Display_Unload)

#define COMPILETIME_CHECK_ENUM_Display(name, retVal, funcArg) static_assert(eventhandlers_display::name >= eventhandlers_display::Char);

    /** @enum eventhandlers_display
    @brief #TODO
    */
    //#TODO doc
    enum class eventhandlers_display {
        Char,            ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onChar">see the wiki</a>
        ChildDestroyed,  ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onChildDestroyed">see the wiki</a>
        KeyDown,         ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onKeyDown">see the wiki</a>
        KeyUp,           ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onKeyUp">see the wiki</a>
        Load,            ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onLoad">see the wiki</a>
        MouseButtonDown, ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseButtonDown">see the wiki</a>
        MouseButtonUp,   ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseButtonUp">see the wiki</a>
        MouseHolding,    ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseHolding">see the wiki</a>
        MouseMoving,     ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseMoving">see the wiki</a>
        MouseZChanged,   ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onMouseZChanged">see the wiki</a>
        Unload           ///< <a href="https://community.bistudio.com/wiki/User_Interface_Event_Handlers#onUnload">see the wiki</a>
    };

    EHDEF_Display(COMPILETIME_CHECK_ENUM_Display)

    /// @private
    intercept::types::game_value callEHHandler(eventhandlers_display ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func);
    /// @private
    EHIdentifier addScriptEH(types::display disp, eventhandlers_display type);
    /// @private
    void delScriptEH(types::display disp, eventhandlers_display type, EHIdentifier& handle);
    /// @private
    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_display, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapDisplayEH;
    /// @private
    template <eventhandlers_display Type>
    struct __displayAddEventHandler_Impl;

#define EH_Add_Display_definition(name, retVal, fncArg)                                                                                                          \
    template <>                                                                                                                                               \
    struct __displayAddEventHandler_Impl<eventhandlers_display::name> {                                                                                             \
        using fncType = std::function<retVal(fncArg)>;                                                                                                        \
        [[nodiscard]] static EHIdentifier add(types::display disp, std::function<retVal(fncArg)> function) {                                                  \
            auto ident = addScriptEH(disp, eventhandlers_display::name);                                                                                         \
            funcMapDisplayEH[ident] = {eventhandlers_display::name, std::make_shared<std::function<void()>>(*reinterpret_cast<std::function<void()>*>(&function))}; \
            return ident;                                                                                                                                     \
        }                                                                                                                                                     \
    };

    EHDEF_Display(EH_Add_Display_definition)


    /**
    * @brief Registers a Display Eventhandler with callback to a C++ function
    * @tparam Type is a value from intercept::client::eventhandlers_display
    * @param disp - the display you add this Eventhandler to.
    * @param fnc - The function that will get called
    * @return A wrapper that should be kept alive as long as the Eventhandler should be active
    * @ingroup eh_bind
    */
    template <eventhandlers_display Type, typename Func = typename __displayAddEventHandler_Impl<Type>::fncType>
    [[nodiscard]] EHIdentifierHandle displayAddEventHandler(types::display disp, Func fnc) {
        return { __displayAddEventHandler_Impl<Type>::add(disp, fnc), [disp,type = Type](EHIdentifier& id) { funcMapDisplayEH.erase(id); delScriptEH(disp,type,id); } };
    }
#pragma endregion

#pragma region Group EventHandlers
#define EH_Func_Args_Group_UnitJoined types::group grp, types::object newUnit
#define EH_Func_Args_Group_UnitLeft types::group grp, types::object oldUnit
#define EH_Func_Args_Group_VehicleAdded types::group grp, types::object newVehicle
#define EH_Func_Args_Group_VehicleRemoved types::group grp, types::object oldVehicle
#define EH_Func_Args_Group_Empty types::group grp
#define EH_Func_Args_Group_Deleted types::group grp
#define EH_Func_Args_Group_Local types::group grp
#define EH_Func_Args_Group_CombatModeChanged types::group grp, types::r_string newMode
#define EH_Func_Args_Group_CommandChanged types::group grp, types::r_string newCommand
#define EH_Func_Args_Group_FormationChanged types::group grp, types::r_string newFormation
#define EH_Func_Args_Group_SpeedModeChanged types::group grp, types::r_string newSpeedmode
#define EH_Func_Args_Group_EnableAttackChanged types::group grp, bool attackEnabled
#define EH_Func_Args_Group_LeaderChanged types::group grp, types::object newLeader
#define EH_Func_Args_Group_GroupIdChanged types::group grp, types::r_string newGroupID
#define EH_Func_Args_Group_KnowsAboutChanged types::group grp, types::object targetUnit, int newKnowsAbout, int oldKnowsAbout
#define EH_Func_Args_Group_WaypointComplete types::group grp, int waypointIndex
#define EH_Func_Args_Group_Fleeing types::group grp, bool fleeingNow
#define EH_Func_Args_Group_EnemyDetected types::group grp, types::object newTarget


    //Name,Function return value, Function Arguments
#define EHDEF_Group(XX)                                                          \
    XX(UnitJoined, void, EH_Func_Args_Group_UnitJoined)                                      \
    XX(UnitLeft, void, EH_Func_Args_Group_UnitLeft)                                      \
    XX(VehicleAdded, void, EH_Func_Args_Group_VehicleAdded)                                      \
    XX(VehicleRemoved, void, EH_Func_Args_Group_VehicleRemoved)                                      \
    XX(Empty, void, EH_Func_Args_Group_Empty)                                      \
    XX(Deleted, void, EH_Func_Args_Group_Deleted)                                      \
    XX(Local, void, EH_Func_Args_Group_Local)                                      \
    XX(CombatModeChanged, void, EH_Func_Args_Group_CombatModeChanged)                                      \
    XX(CommandChanged, void, EH_Func_Args_Group_CommandChanged)                                      \
    XX(FormationChanged, void, EH_Func_Args_Group_FormationChanged)                                      \
    XX(SpeedModeChanged, void, EH_Func_Args_Group_SpeedModeChanged)                                      \
    XX(EnableAttackChanged, void, EH_Func_Args_Group_EnableAttackChanged)                                      \
    XX(LeaderChanged, void, EH_Func_Args_Group_LeaderChanged)                                      \
    XX(GroupIdChanged, void, EH_Func_Args_Group_GroupIdChanged)                                      \
    XX(KnowsAboutChanged, void, EH_Func_Args_Group_KnowsAboutChanged)                                      \
    XX(WaypointComplete, void, EH_Func_Args_Group_WaypointComplete)                                      \
    XX(Fleeing, void, EH_Func_Args_Group_Fleeing)                                      \
    XX(EnemyDetected, void, EH_Func_Args_Group_EnemyDetected)

#define COMPILETIME_CHECK_ENUM_Group(name, retVal, funcArg) static_assert(eventhandlers_group::name >= eventhandlers_group::UnitJoined);

    /** @enum eventhandlers_group
    @brief #TODO
    */
    //#TODO doc
    enum class eventhandlers_group {
        UnitJoined,       ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#UnitJoined">see the wiki</a>
        UnitLeft,         ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#UnitLeft">see the wiki</a>
        VehicleAdded,     ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#VehicleAdded">see the wiki</a>
        VehicleRemoved,   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#VehicleRemoved">see the wiki</a>
        Empty,            ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Empty">see the wiki</a>
        Deleted,         ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Deleted">see the wiki</a>
        Local,           ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Local">see the wiki</a>
        CombatModeChanged,  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#CombatModeChanged">see the wiki</a>
        CommandChanged,     ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#CommandChanged">see the wiki</a>
        FormationChanged,   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#FormationChanged">see the wiki</a>
        SpeedModeChanged,    ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#SpeedModeChanged">see the wiki</a>
        EnableAttackChanged,  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#EnableAttackChanged">see the wiki</a>
        LeaderChanged,        ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#LeaderChanged">see the wiki</a>
        GroupIdChanged,       ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#GroupIdChanged">see the wiki</a>
        KnowsAboutChanged,    ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#KnowsAboutChanged">see the wiki</a>
        WaypointComplete,     ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#WaypointComplete">see the wiki</a>
        Fleeing,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#Fleeing">see the wiki</a>
        EnemyDetected,        ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers#EnemyDetected">see the wiki</a>
    };

    EHDEF_Group(COMPILETIME_CHECK_ENUM_Group)

    /// @private
        intercept::types::game_value callEHHandler(eventhandlers_group ehType, intercept::types::game_value args, std::shared_ptr<std::function<void()>> func);
    /// @private
    EHIdentifier addScriptEH(types::group grp, eventhandlers_group type);
    /// @private
    void delScriptEH(types::group grp, eventhandlers_group type, EHIdentifier& handle);
    /// @private
    extern std::unordered_map<EHIdentifier, std::pair<eventhandlers_group, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapGroupEH;
    /// @private
    template <eventhandlers_group Type>
    struct __groupAddEventHandler_Impl;

#define EH_Add_Group_definition(name, retVal, fncArg)                                                                                                             \
    template <>                                                                                                                                                     \
    struct __groupAddEventHandler_Impl<eventhandlers_group::name> {                                                                                             \
        using fncType = std::function<retVal(fncArg)>;                                                                                                              \
        [[nodiscard]] static EHIdentifier add(types::group grp, std::function<retVal(fncArg)> function) {                                                        \
            auto ident = addScriptEH(grp, eventhandlers_group::name);                                                                                            \
            funcMapGroupEH[ident] = {eventhandlers_group::name, std::make_shared<std::function<void()>>(*reinterpret_cast<std::function<void()>*>(&function))}; \
            return ident;                                                                                                                                           \
        }                                                                                                                                                           \
    };

    EHDEF_Group(EH_Add_Group_definition)

        /**
    * @brief Registers a Group Eventhandler with callback to a C++ function
    * @tparam Type is a value from intercept::client::eventhandlers_group
    * @param grp - the group you add this Eventhandler to.
    * @param fnc - The function that will get called
    * @return A wrapper that should be kept alive as long as the Eventhandler should be active
    * @ingroup eh_bind
    */
        template <eventhandlers_group Type, typename Func = typename __groupAddEventHandler_Impl<Type>::fncType>
        [[nodiscard]] EHIdentifierHandle addEventHandler(types::group grp, Func fnc) {
        return {__groupAddEventHandler_Impl<Type>::add(grp, fnc), [grp, type = Type](EHIdentifier& id) { funcMapGroupEH.erase(id); delScriptEH(grp,type,id); }};
    }
#pragma endregion

#pragma region Custom Callback

    /// @private
    extern std::unordered_map<EHIdentifier, std::shared_ptr<std::function<types::game_value(types::game_value_parameter)>>, EHIdentifier_hasher> customCallbackMap;


    /**
    * @brief Registers a custom callback to a C++ function
    * @param fnc - The function that will get called. It's argument is _this from where the code was called
    * @return A SQF script that, when called will call your C++ function.
    * @return A wrapper that should be kept alive as long as the Callback should be active
    * @ingroup eh_bind
    */
    [[nodiscard]] std::pair<std::string, EHIdentifierHandle> generate_custom_callback(std::function<types::game_value(types::game_value_parameter)> fnc);
#pragma endregion
}  // namespace intercept::client                                                                                    
#endif
