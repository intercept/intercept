// xlib.sqf

parsingNamespace setVariable ["intercept_fnc_isNilWrapper", compileFinal "(parsingNamespace getVariable ""INTERCEPT_CALL_ARGS"") params [""_args"", ""_code""]; parsingNamespace setVariable [""INTERCEPT_CALL_RETURN"", if (isNil ""_args"") then {call _code} else {_args call _code}];"];
parsingNamespace setVariable ["intercept_fnc_voidWrapper", compileFinal "(parsingNamespace getVariable ""INTERCEPT_CALL_ARGS"") params [""_args"", ""_code""]; if (isNil ""_args"") then {call _code} else {_args call _code};"];

diag_log text "Intercept xlib stored to parsingNamespace.";