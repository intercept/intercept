//boot.sqf
intercept_params_var = [];
diag_log text format["_________________________________________Doing Intercept Boot Load"];
_res = "intercept" callExtension "init:";
diag_log text format["Initiated: %1", _res];
_res = "intercept" callExtension format["init_patch:%1", (productVersion select 3)]; // find a patch
"intercept" callExtension "invoker_begin_register:";
call compile "interceptRegisterTypes parsingNamespace";
"intercept" callExtension "invoker_end_register:";
// };
//"intercept" callExtension "load_extension:example_dll";

_intercept_projects = configFile >> "Intercept";
for "_i" from 0 to (count _intercept_projects)-1 do {
    _project = _intercept_projects select _i;
    if(isClass _project) then {
        for "_x" from 0 to (count _project)-1 do {
            _module = _project select _x;
            if(isClass _module) then {
                _plugin_name = getText(_module >> "pluginName");
                if(_plugin_name != "") then {
                    diag_log text format["Intercept Loading Plugin: %1", _plugin_name];
                    "intercept" callExtension ("load_extension:" + _plugin_name);
                };
            };
        };
    };
};

uiNamespace setVariable ["intercept_fnc_event", compileFinal preprocessFileLineNumbers "\z\intercept\rv\addons\core\event.sqf"];
["pre_start",[]] call (uiNamespace getVariable "intercept_fnc_event");

//diag_log text format["_________________________________________Intercept Res: %1", _res];
