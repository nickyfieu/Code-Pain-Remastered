#include "TestingClass.h"
#include "Source/ECS/EntityManager.h"
#include "Source/ECS/ComponentArray.h"
#include "Source/ECS/ComponentManager.h"
#include <iostream>

TestingClass::TestingClass()
{

}

void TestingClass::TestECS()
{

    EntityManager* Manager = new EntityManager{};

    Entity A = Manager->GenerateEntity();
    Entity B = Manager->GenerateEntity();
    Entity C = Manager->GenerateEntity();
    Entity D = Manager->GenerateEntity();
    Entity E = Manager->GenerateEntity();

#pragma region TestComponentArray
#ifdef _DEBUG
    {   // Testing if component array behaves as intended
        struct HumanFlagdata {};
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

        delete TestArray;
    }
#endif
#pragma endregion

    struct TestData1
    {
        char Letter;
    };

    struct TestData2
    {
        int Integer;
    };

    struct Flag
    {
    };

    ComponentManager ComponentHandler{};

    // Testing if registering works as intended
    ComponentHandler.RegisterComponent<TestData1>();
    ComponentHandler.RegisterComponent<TestData2>();
    ComponentHandler.RegisterComponent<Flag>();

    // Testing if unregistering works as intended ( Note: uncomenting the part below will throw an error if the testing of adding components is done below )
    // ComponentHandler.UnRegisterComponent<TestData1>();

    // Testing if adding components works as intended
    TestData1 DataContainer{};
    DataContainer.Letter = 'B';
    ComponentHandler.AddComponent<TestData1>(B, DataContainer);
    DataContainer.Letter = 'A';
    ComponentHandler.AddComponent<TestData1>(A, DataContainer);
    DataContainer.Letter = 'D';
    ComponentHandler.AddComponent<TestData1>(D, DataContainer);
    DataContainer.Letter = 'C';
    ComponentHandler.AddComponent<TestData1>(C, DataContainer);

    Flag DataFlag{};
    ComponentHandler.AddComponent<Flag>(C, DataFlag);
    ComponentHandler.AddComponent<Flag>(D, DataFlag);

    // Testing if removing an entity works as intended ( Note: uncomenting the part below will throw an error if the testing of getting the componen is done below )
    //ComponentHandler.EntityRemoved(D);

    // Testing if getting the component works as intended
    TestData1 ComponentTestData = ComponentHandler.GetComponent<TestData1>(D);
    printf("\nTest Data 1 Data[%c]\n", ComponentTestData.Letter);

    // Testing if get component type works as intended
    ComponentType ComponentTestType = ComponentHandler.GetComponentType<Flag>();
    printf("\nFlag Type Index[%i]\n", ComponentTestType);

}