#include "TestingClass.h"
#include "Source/ECS/EntityManager.h"
#include "Source/ECS/ComponentArray.h"
#include <iostream>

TestingClass::TestingClass()
{

}

void TestingClass::Test()
{

    EntityManager* Manager = new EntityManager{};

    Entity A = Manager->GenerateEntity();
    Entity B = Manager->GenerateEntity();
    Entity C = Manager->GenerateEntity();
    Entity D = Manager->GenerateEntity();
    Entity E = Manager->GenerateEntity();

    struct HumanFlagdata{};
    ComponentArray<HumanFlagdata>* TestArray = new ComponentArray<HumanFlagdata>();

    HumanFlagdata FlagA;
    HumanFlagdata FlagB;
    HumanFlagdata FlagC;
    HumanFlagdata FlagD;
    HumanFlagdata FlagE;
    TestArray->AddComponent(A, FlagA);
    TestArray->DebugPrint();
    TestArray->AddComponent(B, FlagB);
    TestArray->DebugPrint();
    TestArray->AddComponent(C, FlagC);
    TestArray->DebugPrint();
    TestArray->AddComponent(D, FlagD);
    TestArray->DebugPrint();

    Manager->RemoveEntity(B);
    TestArray->EntityRemoved(B);
    TestArray->DebugPrint();

    Manager->RemoveEntity(D);
    TestArray->EntityRemoved(D);
    TestArray->DebugPrint();

    TestArray->AddComponent(E, FlagE);
    TestArray->DebugPrint();
}