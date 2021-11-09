#pragma once
#include "Component.h"
#include "ComponentArray.h"
#include "Entity.h"
#include <string>
#include <unordered_map>
#include <algorithm>

/**
 * The component manager is in charge of adding or removing components from their specific
 * component arrays that are held in the component managers.
 */

class ComponentManager final
{
public:
    ComponentManager();
    ~ComponentManager();

    // Registeres the given component type and creates a component array for the given type
    template<typename T>
    void RegisterComponent();

    // Unregisters the given component type and removes the component array for the given type
    template<typename T>
    void UnRegisterComponent();

    // Returns the component type signature mask of the given component
    template<typename T>
    ComponentType GetComponentType() const;

    // Adds the component to the given entity
    template <typename T>
    void AddComponent(Entity EntityIndex, T Component);

    // Removes the component if the given entity has that component type in its signature
    template <typename T>
    void RemoveComponent(Entity EntityIndex);

    // Returns a reference to the component if the given entity has that component type in its signature 
    template <typename T>
    T& GetComponent(Entity EntityIndex) const;
    
    // Function that notifies all component arrays that the given entity has been removed
    void EntityRemoved(Entity EntityRemoved);

private:
    // Name of the component type.
    // Compare to the string to get the index and use that index for getting data from ComponentTypes and ComponentArrays.
    std::vector<std::string> HeldComponentTypeNames;

    // Get index from HeldComponentTypeNames to get data out of this vector
    std::vector<ComponentType> ComponentTypes;

    // Get index from HeldComponentTypeNames to get data out of this vector
    std::vector<IComponentArray*> ComponentArrays;

    // The type to be assigned to next registered component.
    ComponentType NextComponentType;

    // Returns the component array of the given component type
    template <typename T>
    ComponentArray<T>* GetComponentArray() const;
};

template<typename T>
inline void ComponentManager::RegisterComponent()
{
    // TODO: Error when NextComponentType == MaxComponents

    std::string TypeName = typeid(T).name();

    auto It = std::find(HeldComponentTypeNames.cbegin(), HeldComponentTypeNames.cend(), TypeName);
    // TODO: Error when It != HeldComponentTypeNames.cend()

    // Add the type name, component type and component type array to their respective containers
    HeldComponentTypeNames.push_back(TypeName);
    ComponentTypes.push_back(NextComponentType);
    ComponentArrays.push_back(new ComponentArray<T>());

    // Finally increment the next component type variable
    ++NextComponentType;
}

template<typename T>
inline void ComponentManager::UnRegisterComponent()
{
    std::string TypeName = typeid(T).name();

    auto It = std::find(HeldComponentTypeNames.cbegin(), HeldComponentTypeNames.cend(), TypeName);
    // TODO: Error when It == HeldComponentTypeNames.cend()

    // Decrementing next component type as we are removing a component and can use this decremented value later on here
    --NextComponentType;
    // Get the index that is equal to the to be un registered component in all 3 vectors
    size_t Index = It - HeldComponentTypeNames.cbegin();

    // Cleaning up the component array pointer
    delete(ComponentArrays[Index]);
    ComponentArrays[Index] = nullptr;

    // Swapping the data at the end of the vectors so we keep all existing data packed
    std::swap(HeldComponentTypeNames[Index], HeldComponentTypeNames[NextComponentType]);
    std::swap(ComponentTypes[Index], ComponentTypes[NextComponentType]);
    std::swap(ComponentArrays[Index], ComponentArrays[NextComponentType]);

    // Removing the duplicate data at the end of our vector
    HeldComponentTypeNames.pop_back();
    ComponentTypes.pop_back();
    ComponentArrays.pop_back();
}

template<typename T>
inline ComponentType ComponentManager::GetComponentType() const
{
    std::string TypeName = typeid(T).name();

    auto It = std::find(HeldComponentTypeNames.cbegin(), HeldComponentTypeNames.cend(), TypeName);
    // TODO: Error when It == HeldComponentTypeNames.cend()

    // Get the index for the given class to get the component type;
    size_t Index = It - HeldComponentTypeNames.cbegin();

    return ComponentTypes[Index];
}

template<typename T>
inline void ComponentManager::AddComponent(Entity EntityIndex, T Component)
{
    // Add given component for the given entity to the correct component array
    GetComponentArray<T>()->AddComponent(EntityIndex, Component);
}

template<typename T>
inline void ComponentManager::RemoveComponent(Entity EntityIndex)
{
    // Remove given component for the given entity to the correct component array
    GetComponentArray<T>()->RemoveComponent(EntityIndex);
}

template<typename T>
inline T& ComponentManager::GetComponent(Entity EntityIndex) const
{
    // Remove given component for the given entity to the correct component array
    return GetComponentArray<T>()->GetComponent(EntityIndex);
}

template<typename T>
inline ComponentArray<T>* ComponentManager::GetComponentArray() const
{
    std::string TypeName = typeid(T).name();

    auto It = std::find(HeldComponentTypeNames.cbegin(), HeldComponentTypeNames.cend(), TypeName);
    // TODO: Error when It != HeldComponentTypeNames.cend()

    size_t Index = It - HeldComponentTypeNames.cbegin();

    return static_cast<ComponentArray<T>*>(ComponentArrays[Index]);
}
