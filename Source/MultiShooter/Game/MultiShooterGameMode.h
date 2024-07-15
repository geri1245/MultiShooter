// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "MultiShooterGameMode.generated.h"

/**
 *
 */
UCLASS()
class MULTISHOOTER_API AMultiShooterGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<APawn> AIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AController> AIControllerClass;

	virtual void StartPlay() override;
	virtual void Tick(float delta) override;
};
