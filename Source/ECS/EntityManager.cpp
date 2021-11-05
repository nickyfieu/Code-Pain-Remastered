#include "EntityManager.h"

EntityManager::EntityManager()
{
    for (unsigned int i = 0; i < AvailableEntitiesSize; ++i)
    {
        AvailableEntities[i].reset(); // Defaulting to 0
    }
    NumberOfEntities = 0;
}

Entity EntityManager::GenerateEntity()
{
    // TODO: Error when NumberOfEntities >= MaxEntities

    Entity id = 0;
    const std::bitset<32> FilledWithEntities = std::move(std::bitset<32>().set());
    for (unsigned int i = 0; i < AvailableEntitiesSize; ++i)
    {
        // if the available entities bitset isnt filled with generated entities generate one
        if ((AvailableEntities[i] & FilledWithEntities) != FilledWithEntities)
        {
            Entity CheckForEntity = 0;
            // Increments CheckForEntity while the available entities bit we compare to is set
            while (AvailableEntities[i][CheckForEntity])
            {
                ++CheckForEntity;
            }
            AvailableEntities[i][CheckForEntity] = 1;
            id = i * 32 + CheckForEntity;
            ++NumberOfEntities;
            break; // at this point we have our id so we can break out of the for loop
        }
    }

    return id;
}

void EntityManager::RemoveEntity(Entity ToRemove)
{
    // TODO: Error when ToRemove >= MaxEntities

    const unsigned int Index = ToRemove / 32;
    const unsigned int ShiftAmount = ToRemove - Index * 32;

    AvailableEntities[Index][ShiftAmount] = 0;
    Signatures[ToRemove].reset();
    --NumberOfEntities;
}

Signature EntityManager::GetSignature(Entity SignatureHolder) const
{
    // TODO: Error when SignatureHolder >= MaxEntities

    return Signatures[SignatureHolder];
}

void EntityManager::SetSignature(Entity SignatureHolder, Signature Signature)
{
    // TODO: Error when SignatureHolder >= MaxEntities

    Signatures[SignatureHolder] = Signature;
}
