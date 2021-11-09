#pragma once
#include <type_traits>

/**
 * The entity in this case is simple just an identifier.
 */

// Entity has to be unsigned since negative indexing just does not make sense
using Entity = unsigned short;      // can be any unsigned integral type
const Entity MaxEntities = 16384;   // Doubt I would ever require more
