#pragma once
#include <cstdint>

/**
 * Components are just structs that contain data and no functionality!
 * Each component type has a unique identifier given to them.
 */

using ComponentType = std::uint8_t;
const ComponentType MaxComponents = 32; // Keep this number in a multiple of 8
