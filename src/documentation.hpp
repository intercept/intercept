#error Documentation only. DO NOT INCLUDE ONLY FOR DOXYGEN GLOBAL COMMENTS
// Namespaces

/*!
@namespace intercept
@brief The main namespace for all Intercept functionality.

All functionality of Intercept is included in this namespace and broken up into
sub-namespaces. Namespaces that are prefixed with `__` are considered private
and their classes/functions are considered internal and to not be used by anyone
using the API.
*/

/*!
@namespace sqf
@brief The parent namespace of all SQF commands available

SQF commands accessible to client plugin developers are contained within. They 
are broken up according to their functionality as best as possible in sub-namespaces.
*/

/*!
@namespace client_function_defs
@brief Contains all of the exported functions to client plugins.

These are the functions that are exported via struct to the client plugins. They
are used to interface with the host.
*/