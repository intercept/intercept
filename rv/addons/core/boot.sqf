//boot.sqf
diag_log text format["_________________________________________Doing Intercept Boot Load"];
_res = "intercept" callExtension "init:";
diag_log text format["Initiated: %1", _res];
_res = "intercept" callExtension "init_patch:"; // find a patch
if(_res == "ceil") then {
    diag_log text format["Found: %1", _res];
    ceil 9.5; // this did our patch... probably. :)
    _res = "intercept" callExtension "remove_patch:"; // clear the patch
};
diag_log text format["_________________________________________Intercept Res: %1", _res];