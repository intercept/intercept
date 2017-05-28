if (!call (uiNamespace getVariable ["INTERCEPT_BOOT_DONE",{false}])) then {
	#include "\z\intercept\rv\addons\core\boot.sqf";
	isNil compile "uiNamespace setVariable ['INTERCEPT_BOOT_DONE', compileFinal 'true'];";
};

//THISVAR = _this;
//private _code =  str {
//	private _this = THISVAR;
//	#include "\A3\functions_f\initFunctions.sqf";
//};
//call compile (_code select [1, count _code-2]);
if (!isNil {_this}) then  {
	_this call compile preProcessFileLineNumbers "\A3\functions_f\initFunctions.sqf";
} else {
	call compile preProcessFileLineNumbers "\A3\functions_f\initFunctions.sqf";
};
