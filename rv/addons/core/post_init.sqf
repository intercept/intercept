//post_init.sqf

if(intercept_invoker_ok) then {
    diag_log text format["Intercept Post-Init..."];
    _res = ["rv_event,post_init"] call intercept_fnc_callExtension;
    diag_log text format["Intercept Post-Init Completed."];
    addMissionEventHandler ["Ended", { 
        _res = ["rv_event,post_init"] call intercept_fnc_callExtension;
    }];
};