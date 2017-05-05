//lib.sqf


intercept_invoker_ok = false;

INTERCEPT_DUMMY = [1,2,3];

intercept_fnc_test = {
    private ["_res"];
    if(isNil "_thisScript") then { // make sure this is NOT being called in the scheduler
        _res = "intercept" callExtension "test_invoker:";
        if(_res == profileNameSteam) then {
            intercept_invoker_ok = true;
        };
        diag_log text format["Intercept Invoker test result: %1 == %2", _res, profileNameSteam];
    };
    intercept_invoker_ok
};

intercept_fnc_exportOpList = {
    _version = format["%1 %2.%3 - %4", (productVersion select 0), (productVersion select 2), (productVersion select 3), (productVersion select 4)];
    "intercept" callExtension ("export_ptr_list:" + _version);
};

intercept_fnc_setVariableNamespace = {
    scopeName "main";
    params ["_namespace", "_args"];
    _namespace setVariable _args;
    INTERCEPT_DUMMY;
};

intercept_fnc_callWrapper = {
    scopeName "main";
    params ["_args", "_code"];
    _res = nil;
    if(!isNil "_args") then {
        _res = _args call _code;
    } else {
        _res = call _code;
    };
    missionNamespace setVariable ["INTERCEPT_CALL_RETURN", _res];
    INTERCEPT_DUMMY;
};

intercept_fnc_isNilWrapper = {
	(missionNamespace getVariable "INTERCEPT_CALL_ARGS") call intercept_fnc_callWrapper;
};

intercept_fnc__event = {
    params ["_type", "_eventArgs"];
};

intercept_fnc__onFrame = compileFinal "isNil {interceptOnFrame [];}";
//{
//    // _start = diag_tickTime;
//    "intercept" callExtension "do_invoke_period:";
//    // _end = diag_tickTime;
//    // diag_log text format["t: %1", (_end-_start)*1000];
//};

INTERCEPT_OUT_TEST = 999;

INVOKER_DELETE_ARRAY = [];
INVOKER_DELETE_ARRAY resize 1000;
intercept_params_var = [1];
intercept_params_var resize 2;
intercept_signal_var = [];
intercept_signal_var resize 2;
str INVOKER_DELETE_ARRAY;

diag_log text "Intercept Invoker SQF handler initializing...";
_res = "intercept" callExtension "init_invoker:";

[] call intercept_fnc_test;



//intercept_invoker_ok = true;
if(intercept_invoker_ok) then {
    ["intercept_onFrame", "onEachFrame", intercept_fnc__onFrame] call BIS_fnc_addStackedEventHandler;
    diag_log text "Intercept Invoker initialized.";
    diag_log text format["Intercept Pre-Init..."];
    ["pre_init",[]] call (uiNamespace getVariable "intercept_fnc_event");
    diag_log text format["Intercept Pre-Init Completed."];
};
