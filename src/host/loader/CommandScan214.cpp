// This is abstraction to make it easier to run multiple implementation with different data layouts

#include "loader.hpp"
#include "controller.hpp"

using namespace intercept;

#define CMDSC_TYPE 214
#define CT_VERSION 1

namespace __CT214 {
#include "CommandTypes.hpp"
}

#include "CommandTypes.hpp"
#include "CommandScan.hpp"
