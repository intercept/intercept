//post_init.sqf

if(intercept_invoker_ok) then {
    diag_log text format["Intercept Post-Init..."];
    ["post_init",[]] call (uiNamespace getVariable "intercept_fnc_event");
    diag_log text format["Intercept Post-Init Finished..."];
    [] spawn {
        waitUntil {!isNull (findDisplay 46)};
        (findDisplay 46) displayAddEventHandler ["unload", { 
             ["mission_stopped",[]] call (uiNamespace getVariable "intercept_fnc_event");
        }];
    };
    addMissionEventHandler ["Ended", {
        diag_log text format["ENDED!"];
         ["mission_ended",[]] call (uiNamespace getVariable "intercept_fnc_event");
    }];
};