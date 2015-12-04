//boot.sqf
diag_log text format["_________________________________________Doing Intercept Boot Load"];
_res = "intercept" callExtension "init:";
diag_log text format["Initiated: %1", _res];
_res = "intercept" callExtension format["init_patch:%1", (productVersion select 3)]; // find a patch
if(_res == "ceil") then {
    diag_log text format["Found: %1", _res];
    ceil 9.5; // this did our patch... probably. :)
    _res = "intercept" callExtension "remove_patch:"; // clear the patch
    
    
    "intercept" callExtension "invoker_begin_register:";
    "intercept" callExtension "invoker_register:delete_ptr";
    str [1,2,3];
    "intercept" callExtension "invoker_register:numeric_type";
    str 101;
    "intercept" callExtension "invoker_register:string_type";
    str "HEEEEEY";
    "intercept" callExtension "invoker_register:bool_type";
    str true;
    str false;
    "intercept" callExtension "invoker_register:code_type";
    _code = { player; };
    str _code;
    "intercept" callExtension "invoker_register:object_type";
    _obj = player;
    str _obj;
    "intercept" callExtension "invoker_register:group_type";
    str grpNull;
    "intercept" callExtension "invoker_register:config_type";
    str (configFile >> "CfgVehicles");
    "intercept" callExtension "invoker_register:control_type";
    str controlNull;
    "intercept" callExtension "invoker_register:display_type";
    str displayNull;
    "intercept" callExtension "invoker_register:location_type";
    str locationNull;
    "intercept" callExtension "invoker_register:script_type";
    str ([] spawn {});
    "intercept" callExtension "invoker_register:side_type";
    str west;
    "intercept" callExtension "invoker_register:text_type";
    str (text "ok");
    "intercept" callExtension "invoker_register:team_type";
    str teamMemberNull;
    "intercept" callExtension "invoker_register:namespace_type";
    str parsingNamespace;
    "intercept" callExtension "invoker_end_register:";
};
diag_log text format["_________________________________________Intercept Res: %1", _res];