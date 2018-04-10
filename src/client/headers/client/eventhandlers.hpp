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
        custom
    };

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
        Draw3D,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Draw3D">Draw3D</a>
        Ended,                   ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Ended">Ended</a>
        Loaded,                  ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Loaded">Game loading from save event</a>
        Map,                     ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#Map">Map open / close event</a>
        HandleDisconnect,        ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#HandleDisconnect">Player disconnect in MP event</a>
        EntityRespawned,         ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#EntityRespawned">Some entity respawn event</a>
        EntityKilled,            ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#EntityKilled">Some entity death event</a>
        EachFrame,               ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#EachFrame">Per frame event</a>
        MapSingleClick,          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#MapSingleClick">Map click event</a>
        HCGroupSelectionChanged, ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#HCGroupSelectionChanged">High Command group select event</a>
        CommandModeChanged,      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#CommandModeChanged">High Command mode change event</a>
        GroupIconClick,          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#GroupIconClick">High Command icon click event</a>
        GroupIconOverEnter,      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#GroupIconOverEnter">High Command icon enter event</a>
        GroupIconOverLeave,      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#GroupIconOverLeave">High Command icon leave event</a>
        PlayerConnected,         ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PlayerConnected">Client joining MP mission event</a>
        PlayerDisconnected,      ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PlayerDisconnected">Client leaving MP mission event</a>
        TeamSwitch,              ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#TeamSwitch">Player teamswitch event</a>
        PreloadStarted,          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PreloadStarted">Mission preload start event</a>
        PreloadFinished,         ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PreloadFinished">Mission preload finish event</a>
        PlayerViewChanged,       ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#PlayerViewChanged">Player view change event</a>
        BuildingChanged          ///< <a href="https://community.bistudio.com/wiki/Arma_3:_Event_Handlers/addMissionEventHandler#BuildingChanged">Building model change event</a>
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

   // XX(HitPart, void, EH_Func_Args_Object_HitPart)                              \



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
#define EHDEF_MP(XX)                                                   \
    XX(MPHit, void, EH_Func_Args_MP_MPHit)                               \
    XX(MPKilled, void, EH_Func_Args_MP_MPKilled)         \
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

#define EH_Func_Args_Display_onLoad types::display disp
#define EH_Func_Args_Display_onUnload types::display disp, float exit_code
#define EH_Func_Args_Display_onChildDestroyed types::display disp, types::display closed_disp, float exit_code
#define EH_Func_Args_Display_onKeyDown types::display disp, int dik, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Display_onKeyUp types::display disp, int dik, bool shift, bool ctrl, bool alt
#define EH_Func_Args_Display_onMouseMoving types::display disp, float delta_x, float delta_y
#define EH_Func_Args_Display_onMouseZChanged types::display disp, float change

    //Name,Function return value, Function Arguments
#define EHDEF_Display(XX)                                                   \
    XX(Load, void, EH_Func_Args_Display_onLoad)                               \
    XX(Unload, void, EH_Func_Args_Display_onUnload)                           \
    XX(ChildDestroyed, void, EH_Func_Args_Display_onChildDestroyed)           \
    XX(KeyDown, bool, EH_Func_Args_Display_onKeyDown)                         \
    XX(KeyUp, void, EH_Func_Args_Display_onKeyUp)                             \
    XX(MouseMoving, void, EH_Func_Args_Display_onMouseMoving)                 \
    XX(MouseZChanged, void, EH_Func_Args_Display_onMouseZChanged)

#define COMPILETIME_CHECK_ENUM_Display(name, retVal, funcArg) static_assert(eventhandlers_display::name >= eventhandlers_display::Load);

    /** @enum eventhandlers_display
    @brief #TODO
    */
    //#TODO doc
    enum class eventhandlers_display {
        Load,
        Unload,
        ChildDestroyed,
        KeyDown,
        KeyUp,
        MouseMoving,
        MouseZChanged
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
