#pragma once
#include "Entity.h"
#include "Signature.h"

/**
 * The entity manager is in charge of managing the entity identifiers(in use or not in use).
 */

class EntityManager final
{
public:
    EntityManager();

    // Generates a new entity and returns it.
    Entity GenerateEntity();

    // Removes the given entity and cleans up its signature.
    void RemoveEntity(Entity ToRemove);

    // Returns the signature of the given entity.
    Signature GetSignature(Entity SignatureHolder) const;

    // Sets the signature of the given entity to the given signature.
    void SetSignature(Entity SignatureHolder, Signature Signature);

private:
    const static unsigned int AvailableEntitiesSize = MaxEntities / 32 + ((MaxEntities % 32) != 0);
    // could be any number really but I chose 32 as its a power of 2
    // allows of compacting the availability into bits instead of 4 bytes per integer
    std::bitset<32> AvailableEntities[AvailableEntitiesSize];

    // Array of signatures where the index coresponds with the entity index
    Signature Signatures[MaxEntities];

    // Total number of generated entities
    unsigned int NumberOfEntities;
};