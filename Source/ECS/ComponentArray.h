#pragma once
#include "Component.h"
#include "Entity.h"
#include <unordered_map>

/**
 * The component array holds all components of type T
 * packed closely together in memory.
 * 
 * To get the entity to component array index we use an unordered map 
 * Same for the other way around
 * We use a unordered map cause it allows us to use find(), delete() & insert()
 */

template<typename T>
class ComponentArray final
{
public:
    // Adds the given component to the entity, do not add a component twice
    void AddComponent(Entity EntityIndex, const T& Component);

    // Removes the component of the given entity and packs the array
    void RemoveComponent(Entity EntityIndex);

    // Supposed to be called when the given entity is removed
    // Removes the component for the given entity if it exists
    void EntityRemoved(Entity EntityIndex);

    // Returns the component for the given entity
    T& GetComponent(Entity EntityIndex) const;

#ifdef _DEBUG
    void DebugPrint() const;
#endif

private:
    // Packs all the components as closely together in memory as possible
    // At most this array can be filled with MaxEntities amount of components of a single type
    T Components[MaxEntities];

    // Unordered map from an entity index to the component array index.
    std::unordered_map<Entity, unsigned int> EntityToComponentIndex;

    // Unordered map from an component array index to the entity index.
    std::unordered_map<unsigned int, Entity> ComponentToEntityIndex;

    // Total size of valid components in the array currently.
    unsigned int AmountOfComponents;
};

template<typename T>
void ComponentArray<T>::AddComponent(Entity EntityIndex, const T& Component)
{
    // TODO: Error when we find Entity in EntityToComponentIndex map

    Components[AmountOfComponents] = std::move(Component);
    EntityToComponentIndex[EntityIndex] = AmountOfComponents;
    ComponentToEntityIndex[AmountOfComponents] = EntityIndex;
    ++AmountOfComponents;
}


template<typename T>
void ComponentArray<T>::RemoveComponent(Entity EntityIndex)
{
    // TODO: Error when we cannot find Entity in EntityToComponentIndex map

    // To keep all the components packed in memory when we remove a component,
    // we will swap the component at the back with the component to be removed at the component index given the entity index
    --AmountOfComponents;
    const unsigned int BackIndex = AmountOfComponents;
    const unsigned int RemoveIndex = EntityToComponentIndex[EntityIndex];
    Components[RemoveIndex] = std::move(Components[BackIndex]);

    // Update the ComponentToEntityIndex and EntityToComponentIndex to acount for the packing
    const Entity BackEntity = ComponentToEntityIndex[BackIndex];
    EntityToComponentIndex[BackEntity] = RemoveIndex;
    ComponentToEntityIndex[RemoveIndex] = BackEntity;

    // Invalidate the deleted component and entity index in their respective maps
    EntityToComponentIndex.erase(EntityIndex);
    ComponentToEntityIndex.erase(BackIndex);
}

template<typename T>
void ComponentArray<T>::EntityRemoved(Entity EntityIndex)
{
    // Find out if the component of the given entity existed when so remove it
    if (EntityToComponentIndex.find(EntityIndex) != EntityToComponentIndex.cend())
    {
        RemoveComponent(EntityIndex);
    }
}

template<typename T>
T& ComponentArray<T>::GetComponent(Entity EntityIndex) const
{
    // TODO: Error when we cannot find Entity in EntityToComponentIndex map

    return Components[EntityToComponentIndex[EntityIndex]];
}

#ifdef _DEBUG
template<typename T>
void ComponentArray<T>::DebugPrint() const
{
    printf("\nComponents[");
    for (unsigned int i = 0; i < AmountOfComponents; ++i)
    {
        printf("%c%s", char('A' + ComponentToEntityIndex.at(i)), (i == AmountOfComponents - 1) ? "]\n" : ", ");
    }

    printf("\nEntity->Component:\n");
    for (unsigned int i = 0; i < AmountOfComponents; ++i)
    {
        Entity EntityIndex = ComponentToEntityIndex.at(i);
        printf("[%i:%i] Entity %i's data (%c) is at Component index %i\n", EntityIndex, i, EntityIndex, char('A' + EntityIndex), i);
    }

    printf("\nComponent->Entity:\n");
    for (unsigned int i = 0; i < AmountOfComponents; ++i)
    {
        Entity EntityIndex = ComponentToEntityIndex.at(i);
        printf("[%i:%i] Component %i holds Entity %i's data (%c)\n", i, EntityIndex, i, EntityIndex, char('A' + EntityIndex));
    }
    printf("\n -------------------------------------------------------------------------------------- \n ");
}
#endif