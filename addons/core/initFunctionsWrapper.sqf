if (!call (uiNamespace getVariable ["INTERCEPT_BOOT_DONE",{false}])) then {
    #include "\z\intercept\rv\addons\core\boot.sqf";
    uiNamespace setVariable ['INTERCEPT_BOOT_DONE', compileFinal 'true'];
};

if (!isNil {_this}) then  {
    _this call compile preProcessFileLineNumbers "\A3\functions_f\initFunctions.sqf";
} else {
    call compile preprocessFileLineNumbers '\z\intercept\rv\addons\core\lib.sqf';
    call compile preProcessFileLineNumbers "\A3\functions_f\initFunctions.sqf";
};
