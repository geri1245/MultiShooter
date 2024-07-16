// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackEnemy_BTTask.h"

#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "MultiShooter/Enemies/Enemy.h"

UAttackEnemy_BTTask::UAttackEnemy_BTTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "AttackEnemy";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UAttackEnemy_BTTask, BlackboardKey), APawn::StaticClass());
}

void UAttackEnemy_BTTask::PostLoad()
{
	Super::PostLoad();
}

EBTNodeResult::Type UAttackEnemy_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UAttackEnemyBTTaskMemory* memory = CastInstanceNodeMemory<UAttackEnemyBTTaskMemory>(NodeMemory);
	const UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* controller = OwnerComp.GetAIOwner();

	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (controller && blackboard)
		{
			AEnemy* controlledPawn = Cast<AEnemy>(controller->GetPawn());
			UObject* keyValue = blackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
			APawn* targetActor = Cast<APawn>(keyValue);
			if (controlledPawn && targetActor)
			{
				FVector currentLocation = controlledPawn->GetActorLocation();
				FVector targetLocation = targetActor->GetTargetLocation();
				if (FVector::Distance(currentLocation, targetLocation) < AttackRange)
				{
					controlledPawn->Attack();
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}

void UAttackEnemy_BTTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UAttackEnemy_BTTask::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UAttackEnemy_BTTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

uint16 UAttackEnemy_BTTask::GetInstanceMemorySize() const
{
	return sizeof(UAttackEnemyBTTaskMemory);
}
