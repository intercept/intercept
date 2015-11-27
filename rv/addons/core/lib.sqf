//lib.sqf
// this is the SQF function the invoker has hooked to get the game state each frame
#define HOOKED_PREAMBLE cadetMode

intercept_invoker_ok = false;

intercept_fnc_test = {
    if(isNil "_thisScript") then { // make sure this is NOT being called in the scheduler
        HOOKED_PREAMBLE; //make sure we are in a good game state
        _res = "intercept" callExtension "test_invoker:";
        if(_res == profileNameSteam) then {
            intercept_invoker_ok = true;
        };
        diag_log text format["Invoker test result: %1 == %2", _res, profileNameSteam];
    };
    intercept_invoker_ok
};

intercept_fnc_callExtension = {
    params ["_extension", "_args"];
    private _res = "";
    if(isNil "_thisScript") then {
        HOOKED_PREAMBLE;
        _res = _extension callExtension _args;
    } else {
        __fnc = {
            params ["_extension", "_args"];
            HOOKED_PREAMBLE;
            _extension callExtension _args;
        };
        // force the call to be in non-scheduled space since you need to ensure
        // that the gamestate does not change between setting it, and invoking
        // the extension call
        "_res = _this call __fnc; false;" configClasses (configfile >> "InterceptBlank"); 
    };
    _res;
};

intercept_fnc__onFrame = {
    HOOKED_PREAMBLE;
    "intercept" callExtension "do_invoke_period:";
};
diag_log text "Invoker SQF handler initializing...";
//[] call intercept_fnc_test;
intercept_invoker_ok = true;
if(intercept_invoker_ok) then {
    ["intercept_onFrame", "onEachFrame", intercept_fnc__onFrame] call BIS_fnc_addStackedEventHandler;
    diag_log text "Invoker initialized.";
};
