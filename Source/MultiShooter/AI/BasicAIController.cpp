// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ABasicAIController::Tick(float DeltaSeconds)
{
}

void ABasicAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		auto* firstPlayer = GetWorld()->GetFirstPlayerController();
		auto* pawn = firstPlayer->GetPawn();

		RunBehaviorTree(BehaviorTree);

		// This call must be after RunBehaviorTree, as that call will initialize our BlackBoard
		if (Blackboard)
		{
			ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			Blackboard->SetValueAsObject(FName("Player"), playerCharacter);
		}
	}
}
