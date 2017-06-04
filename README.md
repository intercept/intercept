![Intercept](http://i.imgur.com/J0PC0G0.png)

[![TravisCI Build Indicator](https://travis-ci.org/intercept/intercept.svg?branch=master)](https://travis-ci.org/intercept/intercept) [![Build status](https://ci.appveyor.com/api/projects/status/508laymfxfnhpbp1/branch/master?svg=true)](https://ci.appveyor.com/project/Verox-/intercept-1irnq/branch/master) [![Slack Status](http://slackin-intercept.idi-systems.com/badge.svg)](http://slackin-intercept.idi-systems.com)

Intercept is a C/C++ binding interface to the Arma 3 engine (internally referred to as the Real Virtuality or RV engine). It's goal is to provide easy to use library for addon makers to develop addons in a native language, or to develop language extensions for the Arma 3 engine.

In a nutshell, Intercept provides a full C/C++ binding system for calling the base C++ functions which are declared in RVEngine for SQF functions. All SQF functions within the RVEngine are actually native code, which is called by SQF via the function names. Intercept bypasses SQF entirely, allowing native C++ plugins to seamlessly interact with the game engine. In essence, Intercept allows for expansions of the game engine, calling internal functionality of the engine which has been exposed via SQF functions. 

Intercept works on a host/client based system, in which the host, Intercept itself, hosts client DLLs that implement the Intercept library. The Intercept host handles access to the RV engine by clients through a layer that provides thread concurrency, memory handling, and event dispatching. Client DLLs are then able to be written in a way that can safely ignore most internal nuances of handling data in the RV engine and work with standard C++ STD/STL data types, and only a few specialized objects specific to the game engine.

The Intercept library also provides raw C bindings to the C++ versions of SQF functions, so it is entirely possible to use Intercept as the basis for writing in additional scripting languages to the RV engine, such as Python or Lua.

## Installation

You can find a basic tutorial on [how to build and install Intercept on our wiki](https://github.com/intercept/intercept/wiki/Building-and-installing-Intercept-from-source).

## Technical Details

Intercept works by making direct calls to the SQF functions in the RV engine. These functions are themselves C++ functions which are then exposed to SQF for allowing interaction with the underlying game engine; Intercept completely bypasses SQF and allows C++ plugins to interact with the engine directly. User created threads can even be created and by properly using the provided thread concurrency functionality it is possible to execute game functionality safely and concurrently.

Intercept clients are able to invoke through the host these commands by provided wrapper functions that replicate and emulate the SQF command namespace (minus some unneeded functionality, like arrays or control structures). These wrapper functions take standard inputs, such as simple primitives like `float` or `bool`, and standard `std::string` arguments and convert them into the proper SQF command variables, providing a seamless layer to the clients.

An example of a very simple client that invokes `nular`, `unary`, and `binary` SQF functions (aka functions that take no arguments, a right side argument only, and both a left and right side argument respectively) is demonstrated below and a [more examples can be found here](https://github.com/intercept/intercept-examples).

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
    // get the player object and store it
    intercept::types::object player = intercept::sqf::player();

    // get the post of the player
    intercept::types::vector3 pos = intercept::sqf::get_pos(player);

    // build a string...
    std::stringstream side_chat_msg;
    side_chat_msg << "Hello Arma World, here is the player pos: " << pos.x << "," << pos.y << "," << pos.z;

    // send it to the binary SQF sideChat command
    intercept::sqf::side_chat(player, side_chat_msg.str());
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

As of now (4/06/17) Intercept is over 99% language feature complete. You can view the progress of wrapper completion [here](https://github.com/intercept/intercept/issues/13). Almost all normally used SQF functions are available to the end user, and with the added ability of writing inline SQF code, you can call any function that has not had a wrapper written for it yet (though with a small performance penalty).

## Contributions

Feel free to contribute as much as you want to this project in terms of time and code. The goal of this project is to be a tool for the community to provide better performing and more complex addons for the Arma 3 platform.

## License

Intercept is licensed under the MIT license. You can find the full license in the LICENSE file. Prior to commit  [f9fe4d5](https://github.com/intercept/intercept/commit/f9fe4d5afc65eb16ef074d9238ee8cd6e6a0ed41) the project was licensed under the GNU/GPL v2 license and continues to be for any commit prior to that.

