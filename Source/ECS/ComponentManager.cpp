#include "ComponentManager.h"

ComponentManager::ComponentManager()
    :NextComponentType{0}
{
    HeldComponentTypeNames.reserve(MaxComponents);
    ComponentTypes.reserve(MaxComponents);
    ComponentArrays.reserve(MaxComponents);
}

ComponentManager::~ComponentManager()
{
    size_t NrOfComponentArrays = NextComponentType;
    for (size_t i = 0; i < NrOfComponentArrays; ++i)
    {
        delete(ComponentArrays[i]);
        ComponentArrays[i] = nullptr;
    }
}

void ComponentManager::EntityRemoved(Entity EntityRemoved)
{
    size_t NrOfComponentArrays = NextComponentType;
    for (size_t i = 0; i < NrOfComponentArrays; ++i)
    {
        ComponentArrays[i]->EntityRemoved(EntityRemoved);
    }
}
