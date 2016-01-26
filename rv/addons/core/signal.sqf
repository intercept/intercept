/*
 * Author: esteldunedain
 * Sends a signal to an Intercept extension
 *
 * Arguments:
 * 0: extension name <STRING>
 * 1: Parameters <ANY>
 *
 * Return value:
 * Success <BOOL>
 *
 * Example:
 * ["example_frag", myParameters] call intercept_fnc_signal
 *
 * Public: No
 */
params ["_extensionName", "_parameters"];

if !(intercept_invoker_ok) exitWith {false};

intercept_signal_params = +_parameters;
"intercept" callExtension format ["signal:%1",_extensionName];
