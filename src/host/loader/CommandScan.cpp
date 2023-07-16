// This is abstraction to make it easier to run multiple implementation with different data layouts

#include "loader.hpp"
#include "controller.hpp"

using namespace intercept;

#define CMDSC_TYPE Base
#define CT_VERSION 0

namespace __CTBase {
#include "CommandTypes.hpp"
}

#include "CommandTypes.hpp"
#include "CommandScan.hpp"
