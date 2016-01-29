//config.cpp
class CfgPatches {
	class Intercept_Core {
		units[] = {""};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {};
		version = 0.1;
	};
};

#define EH_CLASS_DEF(x,y) y = "with missionNamespace do { intercept_params_var set[intercept_params_index, +_this]; 'intercept' callExtension ('rv_event:##x,' + (str intercept_params_index)); intercept_params_index = intercept_params_index + 1;}; '';"
//#define EH_CLASS_DEF(x,y) y = "missionNamespace setVariable ['intercept_params_var', +_this]; _test = missionNamespace getVariable 'intercept_params_var'; '';"

class CfgVehicles {
    class AllVehicles {
        class EventHandlers {
            class Intercept {
                EH_CLASS_DEF(anim_changed,animChanged);
                EH_CLASS_DEF(anim_done,animDone);
                EH_CLASS_DEF(anim_state_changed,animStateChanged);
                EH_CLASS_DEF(container_closed,containerClosed);
                EH_CLASS_DEF(controls_shifted,controlsShifted);
                EH_CLASS_DEF(dammaged,dammaged);
                EH_CLASS_DEF(engine,engine);
                EH_CLASS_DEF(epe_contact,epeContact);
                EH_CLASS_DEF(epe_contact_end,epeContactEnd);
                EH_CLASS_DEF(epe_contact_start,epeContactStart);
                EH_CLASS_DEF(explosion,explosion);
                EH_CLASS_DEF(fired,fired);
                EH_CLASS_DEF(fired_near,firedNear);
                EH_CLASS_DEF(fuel,fuel);
                EH_CLASS_DEF(gear,gear);
                EH_CLASS_DEF(get_in,getIn);
                EH_CLASS_DEF(get_out,getOut);
                EH_CLASS_DEF(handle_damage,handleDamage);
                EH_CLASS_DEF(handle_heal,handleHeal);
                EH_CLASS_DEF(handle_rating,handleRating);
                EH_CLASS_DEF(handle_score,handleScore);
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
                EH_CLASS_DEF(post_reset,postReset);
                EH_CLASS_DEF(put,put);
                EH_CLASS_DEF(respawn,respawn);
                EH_CLASS_DEF(rope_attach,ropeAttach);
                EH_CLASS_DEF(rope_break,ropeBreak);
                EH_CLASS_DEF(seat_switched,seatSwitched);
                EH_CLASS_DEF(sound_played,soundPlayed);
                EH_CLASS_DEF(take,take);
                EH_CLASS_DEF(task_set_as_current,taskSetAsCurrent);
                EH_CLASS_DEF(weapon_assembled,weaponAssembled);
                EH_CLASS_DEF(weapon_disassembled,weaponDisassembled);
                EH_CLASS_DEF(weapon_deployed,weaponDeployed);
                EH_CLASS_DEF(weapon_rested,weaponRested);
            };
        };
    };
};

class CfgFunctions
{
	class Intercept
	{
		class boot
		{
			class boot_loader
			{
				preStart = 1;
                file = "z\intercept\rv\addons\core\boot.sqf";
                headerType = -1;
			};
		};
        class initialization 
        {
            class lib_loader
            {
                preInit = 1;
                file = "z\intercept\rv\addons\core\lib.sqf";
                headerType = -1;
            };
            class post_init_handler
            {
                postInit = 1;
                file = "z\intercept\rv\addons\core\post_init.sqf";
                headerType = -1;
            };
        };
	};
};
