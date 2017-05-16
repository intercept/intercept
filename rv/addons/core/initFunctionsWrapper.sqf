if (!call (uiNamespace getVariable ["INTERCEPT_BOOT_DONE",{false}])) then {
	#include "\z\intercept\rv\addons\core\boot.sqf";
	uiNamespace setVariable ["INTERCEPT_BOOT_DONE", compileFinal "true"];
};

#include "\A3\functions_f\initFunctions.sqf";