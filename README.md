![Intercept](http://i.imgur.com/J0PC0G0.png)

[![TravisCI Build Indicator](https://travis-ci.org/intercept/intercept.svg?branch=master)](https://travis-ci.org/intercept/intercept) [![Build status](https://ci.appveyor.com/api/projects/status/508laymfxfnhpbp1/branch/master?svg=true)](https://ci.appveyor.com/project/Verox-/intercept-1irnq/branch/master) [![Slack Status](http://slackin-intercept.idi-systems.com/badge.svg)](http://slackin-intercept.idi-systems.com)

Intercept is a C/C++ binding interface to the Arma 3 engine (internally refered to as the Real Virtuality or RV engine). It's goal is to provide easy to use library for addon makers to develop addons in a native language, or to develope language extensions for the Arma 3 engine.

In a nutshell, Intercept provides a full C/C++ binding system for calling the base C++ functions which are declared in RVEngine for SQF functions. All SQF functions within the RVEngine are actually native code, which is called by SQF via the function names. Intercept bypasses SQF entirely, allowing native C++ plugins to seamlessly interact with the game engine. In essense, Intercept allows for expansions of the game engine, calling internal functionality of the engine which is exposed to SQF via functions. 

Intercept works on a host/client based system, in which the host, Intercept itself, hosts client DLLs that implement the Intercept library. The Intercept host handles access to the RV engine by clients through a layer that provides thread concurrency, memory handling, and event dispatching. Client DLLs are then able to be written in a way that can safely ignore most internal nuances of handling data in the RV engine and work with standard C++ STD/STL data types, and only a few specialized objects (all of which are wrapped in `std::shared_ptr` to properly handle memory releasing).

The intercept library also provides raw C bindings to the C++ versions of SQF functions, so it is entirely possible to use Intercept as the basis for writing in additional scripting languages to the RV engine, such as Python or Lua.

## [Progress](https://github.com/intercept/intercept/issues/13)

You can view the progress of wrapper completion [here](https://github.com/intercept/intercept/issues/13).

## Tutorial

You can find a basic tutorial on [how to build and install Intercept on our wiki](https://github.com/intercept/intercept/wiki/Building-and-installing-Intercept-from-source).

## Terminology 

#### RVEngine 
The underlying game engine of ArmA 3. This is the core of the game, which performs simulations and manages all objects and data within the game. 

#### SQF Functions
SQF Functions, in the specific case of Intercept, are C++ functions which are exposed within RVEngine via SQF functions. The SQF language itself is just a collection of 'functions' which map to C++ code, which then interact with the game engine itself. a SQF script is a collection of these function calls, which are parsed (lexed) to a series of C++ function calls. 

#### SQF Engine
The SQF engine can be considered the underlying parser and manager of SQF function calls. The way the engine works is actually directly parsing strings (an SQF script) and then mapping these to control flows of C++ function calls. 

#### Intercept Functions
Functions within intercept directly call SQF functions 100% in native machine code. We have identified the functions which the engine exposes, and are directly calling these via a complex method of hooking and object manipulation. For the less technically inclined, we completely bypass the SQF engine entirely - this allows for the functions to basically exist as any other C++ library. 

## Technical Details

Intercept works by making direct calls to the SQF functions in the RV engine. These functions are themselves C++ functions which are then exposed to SQF for allowing interaction with the underlying game engine; Intercept completely bypasses SQF and allows C++ plugins to interact with the engine directly. To provide concurrency with the game engine, these calls wait until the RV engine is specifically unlocked to Intercept client code, allowing an access window where commands can execute and return results. The only time that these commands are blocked is right before execution, and they unblock very quickly after, providing extremely high throughput in terms of code execution. 

Intercept clients are able to invoke through the host these commands by provided wrapper functions that replicate and emulate the SQF command namespace (minus some unneeded functionality, like arrays or control structures). These wrapper functions take standard inputs, such as simple primitives like `float` or `bool`, and standard `std::string` arguments and convert them into the proper SQF command variables, providing a seamless layer to the clients.

An example of a very simple client that invokes `nular`, `unary`, and `binary` SQF functions (aka functions that take no arguments, a right side argument only, and both a left and right side argument respectively) is demonstrated below and a [fuller example can be found here](src/client).

```c++
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <sstream>

// the Intercept library, only one include required.
#include "intercept.hpp"

// required exported function to return API version
int __cdecl intercept::api_version() {
    return 1;
}

// This function is exported and is called by the host each frame.
void __cdecl intercept::on_frame() {
    // call the SQF random implementation
    float rand_val = intercept::sqf::random(100.0f);
    
    // build a string...
    std::stringstream side_chat_msg;
    side_chat_msg << "Hello Arma World, here is some randomness: " << rand_val;
    
    // send it to the binary SQF sideChat command, using the nular function player as the
    // first argument
    intercept::sqf::side_chat(intercept::sqf::player(), side_chat_msg.str());
}

// Normal Windows DLL junk...
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
```

## Completion Status

As of now (1/7/16) Intercept is over 75% language feature complete.

## Contributions

Feel free to contribute as much as you want to this project in terms of time and code. The goal of this project is to be a tool for the community to provide better performing and more complex addons for the Arma 3 platform.

## License

Intercept is licensed under the GNU/GPL v2 license. You can find the full license in the LICENSE file.

