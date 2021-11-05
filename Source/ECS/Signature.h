#pragma once
#include <bitset>
#include "Component.h"

/**
 * The signature is the way we track which components we care about.
 * We do a bitwise comparison on the system's signature and the entity's signature.
 * When this comparison returns a value greater than 0 it means we can execute the system on that entity.
 */

using Signature = std::bitset<MaxComponents>;