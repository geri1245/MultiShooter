// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CoreMinimal.h"

#include "AttackEnemy_BTTask.generated.h"

struct UAttackEnemyBTTaskMemory
{
	APawn* TargetEnemy = nullptr;
};

/**
 *
 */
UCLASS() class MULTISHOOTER_API UAttackEnemy_BTTask : public UBTTask_BlackboardBase
{
public:
	GENERATED_BODY()

	UAttackEnemy_BTTask(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual uint16 GetInstanceMemorySize() const override;

	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AttackRange = 5;
};
