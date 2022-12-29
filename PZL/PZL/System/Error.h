#pragma once

// Prints the specified message and stops execution.
#define PZL_EXIT_WITH_ERROR(...) { printf("Error: " __VA_ARGS__); exit(-1); }

namespace PZL::System
{

}