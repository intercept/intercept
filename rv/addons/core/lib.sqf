//lib.sqf
// this is the SQF function the invoker has hooked to get the game state each frame
#define HOOKED_PREAMBLE cadetMode

intercept_invoker_ok = false;

intercept_fnc_test = {
    private ["_res"];
    if(isNil "_thisScript") then { // make sure this is NOT being called in the scheduler
        HOOKED_PREAMBLE; //make sure we are in a good game state
        _res = ["test_invoker"] call intercept_fnc_callExtension;
        if(_res == profileNameSteam) then {
            intercept_invoker_ok = true;
        };
        diag_log text format["Invoker test result: %1 == %2", _res, profileNameSteam];
    };
    intercept_invoker_ok
};

intercept_fnc_exportOpList = {
    _version = format["%1 %2.%3 - %4", (productVersion select 0), (productVersion select 2), (productVersion select 3), (productVersion select 4)];
    "intercept" callExtension ("export_ptr_list:" + _version);
};

// This function is a wrapper to call extension.
// It will always execute the callExtension call in
// unscheduled space, opening and closing an invoke
// period until the command is done. Be aware that
// this command also allow all other code in other
// threads to access the engine at the same time.
intercept_fnc_callExtension = {
    params ["_args"];
    private _res = "";
    if(isNil "_thisScript") then {
        _args = "block_execute:" + _args;
        HOOKED_PREAMBLE;
        _res = "intercept" callExtension _args;
    } else {
        __fnc = {
            params ["_args"];
            _args = "block_execute:" + _args;
            HOOKED_PREAMBLE;
            _res = "intercept" callExtension _args;
            _res;
        };
        // force the call to be in non-scheduled space since you need to ensure
        // that the gamestate does not change between setting it, and invoking
        // the extension call
        "_res = _this call __fnc; false;" configClasses (configfile >> "InterceptBlank"); 
    };
    _res;
};
intercept_fnc__onFrame = {
    //HOOKED_PREAMBLE;
    "intercept" callExtension "do_invoke_period:";
};

INVOKER_DELETE_ARRAY = [];
INVOKER_DELETE_ARRAY resize 1000;
str INVOKER_DELETE_ARRAY;

diag_log text "Invoker SQF handler initializing...";
_res = ["init_invoker"] call intercept_fnc_callExtension;

[] call intercept_fnc_test;



//intercept_invoker_ok = true;
if(intercept_invoker_ok) then {
    ["intercept_onFrame", "onEachFrame", intercept_fnc__onFrame] call BIS_fnc_addStackedEventHandler;
    diag_log text "Invoker initialized.";
};
