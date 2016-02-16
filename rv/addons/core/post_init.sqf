//post_init.sqf

if(intercept_invoker_ok) then {
    diag_log text format["Intercept Post-Init..."];
    _res = "intercept" callExtension "rv_event:post_init";
    diag_log text format["Intercept Post-Init Finished..."];
    [] spawn {
        waitUntil {!isNull (findDisplay 46)};
        (findDisplay 46) displayAddEventHandler ["unload", { 
            _res = "intercept" callExtension "rv_event:mission_stopped";
        }];
    };
    addMissionEventHandler ["Ended", {
        diag_log text format["ENDED!"];
        _res = "intercept" callExtension "rv_event:mission_ended";
    }];
};