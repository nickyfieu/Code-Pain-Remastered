#pragma once
#include <type_traits>

/**
 * The entity in this case is simple just an identifier.
 */

// Entity has to be unsigned since negative indexing just does not make sense
using Entity = unsigned short;      // can be any unsigned integral type
const Entity MaxEntities = 16384;   // Doubt I would ever require more


// To avoid unexpected behavior
#if defined(Entity_Short) && defined(Entity_Long)
#error Defining both 'Entity_Short' and 'Entity_Long' could have unexpected bahavior!
#endif
