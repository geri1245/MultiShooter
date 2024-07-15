// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CoreMinimal.h"

#include "DummyTask.generated.h"

struct FDummyStructMemory
{
	int SomeNumber;
};

/**
 *
 */
UCLASS() class MULTISHOOTER_API UDummyTask : public UBTTask_BlackboardBase
{
public:
	GENERATED_BODY()

	UDummyTask(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual uint16 GetInstanceMemorySize() const override;
};
