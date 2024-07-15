// Fill out your copyright notice in the Description page of Project Settings.

#include "DummyTask.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UDummyTask::UDummyTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "DummyTask";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UDummyTask, BlackboardKey), APawn::StaticClass());
}

void UDummyTask::PostLoad()
{
}

EBTNodeResult::Type UDummyTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	FDummyStructMemory* MyMemory = CastInstanceNodeMemory<FDummyStructMemory>(NodeMemory);

	if (controller)
	{
	}

	return EBTNodeResult::Succeeded;
}

void UDummyTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UDummyTask::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

void UDummyTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
}

uint16 UDummyTask::GetInstanceMemorySize() const
{
	return sizeof(FDummyStructMemory);
}
