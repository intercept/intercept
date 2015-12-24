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
    
    player addEventHandler ["fired", {
        diag_log text format["f data 1: %1", _this];
        missionNamespace setVariable ["intercept_params_var", +_this];
        diag_log text format["f data 2: %1", intercept_params_var];
        _res = "intercept" callExtension "rv_event:fired,intercept_params_var";
    }];
};