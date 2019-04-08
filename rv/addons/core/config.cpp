//config.cpp
class CfgPatches {
    class Intercept_Core {
        name = "Intercept - Core";
        units[] = {};
        weapons[] = {};
        requiredVersion = 1.88;
        requiredAddons[] = {
            "A3_Data_F_Loadorder",
            "A3_Data_F_Curator_Loadorder",
            "A3_Data_F_Kart_Loadorder",
            "A3_Data_F_Bootcamp_Loadorder",
            "A3_Data_F_Heli_Loadorder",
            "A3_Data_F_Mark_Loadorder",
            "A3_Data_F_Exp_A_Loadorder",
            "A3_Data_F_Exp_B_Loadorder",
            "A3_Data_F_Exp_Loadorder",
            "A3_Data_F_Jets_Loadorder",
            "A3_Data_F_Argo_Loadorder",
            "A3_Data_F_Patrol_Loadorder",
            "A3_Data_F_Orange_Loadorder",
            // CBA
            "cba_xeh"
        };
        version = 0.1;
    };
};

class CfgFunctions {
	init = "z\intercept\rv\addons\core\initFunctionsWrapper.sqf";
	//init = "A3\functions_f\initFunctions.sqf";
};

#define QUOTE(var1) #var1
#define ARR_2(ARG1,ARG2) ARG1, ARG2
#define EVENT_ARGS(x) rv_event:##x
#define EH_CLASS_DEF(x,y) class Extended_##y##_EventHandlers { \
    class All { \
        class Intercept { \
            y = QUOTE([ARR_2('x', _this)] call (uiNamespace getVariable 'intercept_fnc_event');); \
        }; \
    }; \
}

EH_CLASS_DEF(anim_changed,animChanged);
EH_CLASS_DEF(anim_done,animDone);
EH_CLASS_DEF(anim_state_changed,animStateChanged);
EH_CLASS_DEF(container_closed,containerClosed);
EH_CLASS_DEF(container_opened,containerOpened);
EH_CLASS_DEF(controls_shifted,controlsShifted);
EH_CLASS_DEF(dammaged,dammaged);
EH_CLASS_DEF(engine,engine);
EH_CLASS_DEF(epe_contact,epeContact);
EH_CLASS_DEF(epe_contact_end,epeContactEnd);
EH_CLASS_DEF(epe_contact_start,epeContactStart);
EH_CLASS_DEF(explosion,explosion);
EH_CLASS_DEF(fired,firedBIS);
EH_CLASS_DEF(fired_near,firedNear);
EH_CLASS_DEF(fuel,fuel);
EH_CLASS_DEF(gear,gear);
EH_CLASS_DEF(get_in,getIn);
EH_CLASS_DEF(get_out,getOut);
EH_CLASS_DEF(handle_heal,handleHeal);
EH_CLASS_DEF(hit,hit);
EH_CLASS_DEF(hit_part,hitPart);
EH_CLASS_DEF(init,init);
EH_CLASS_DEF(incoming_missile,incomingMissile);
EH_CLASS_DEF(inventory_closed,inventoryClosed);
EH_CLASS_DEF(inventory_opened,inventoryOpened);
EH_CLASS_DEF(killed,killed);
EH_CLASS_DEF(landed_touch_down,landedTouchDown);
EH_CLASS_DEF(landed_stopped,landedStopped);
EH_CLASS_DEF(local,local);
EH_CLASS_DEF(put,put);
EH_CLASS_DEF(respawn,respawn);
EH_CLASS_DEF(seat_switched,seatSwitched);
EH_CLASS_DEF(sound_played,soundPlayed);
EH_CLASS_DEF(take,take);
EH_CLASS_DEF(weapon_assembled,weaponAssembled);
EH_CLASS_DEF(weapon_disassembled,weaponDisassembled);

// These events don't have XEH on CBA yet
//EH_CLASS_DEF(handle_damage,handleDamage);
//EH_CLASS_DEF(handle_rating,handleRating);
//EH_CLASS_DEF(handle_score,handleScore);
//EH_CLASS_DEF(post_reset,postReset);
//EH_CLASS_DEF(rope_attach,ropeAttach);
//EH_CLASS_DEF(rope_break,ropeBreak);
//EH_CLASS_DEF(task_set_as_current,taskSetAsCurrent);
//EH_CLASS_DEF(weapon_deployed,weaponDeployed);
//EH_CLASS_DEF(weapon_rested,weaponRested);
/*
class Intercept {
    class example_dll_project {
        class example_dll_module {
            pluginName = "example_dll";
        };
    };
};
*/

class Extended_PreStart_EventHandlers {
    class Intercept_Core {
        init = "['post_start', _this] call (uiNamespace getVariable 'intercept_fnc_event');";
    };
};

class Extended_PreInit_EventHandlers {
    class Intercept_Core {
        init = "['pre_init',[]] call (uiNamespace getVariable 'intercept_fnc_event');";
    };
};


class Extended_PostInit_EventHandlers {
    class Intercept_Core {
        init = "call compile preprocessFileLineNumbers '\z\intercept\rv\addons\core\post_init.sqf';";
    };
};

class Extended_DisplayUnload_EventHandlers {
    class RscDisplayMission {
        Intercept_MissionEnded = "['mission_ended', []] call (uiNamespace getVariable 'intercept_fnc_event');";
    };
};
