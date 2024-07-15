// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"

#include "BasicAIController.generated.h"

/**
 *
 */
UCLASS()
class MULTISHOOTER_API ABasicAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree = nullptr;

	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
};
