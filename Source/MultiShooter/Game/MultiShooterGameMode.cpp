// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiShooterGameMode.h"

#include "../Enemies/EnemySpawn.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMultiShooterGameMode::StartPlay()
{
	Super::StartPlay();

	// TArray<AActor*> EnemyStarts;
	// UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawn::StaticClass(), EnemyStarts);

	// if (!EnemyStarts.IsEmpty())
	//{
	//	auto& transform = EnemyStarts[0]->GetTransform();
	//	auto* spawnedActor = GetWorld()->SpawnActor(AIClass, &transform);
	//	if (auto* spawnedPawn = Cast<APawn>(spawnedActor))
	//	{
	//		spawnedPawn->AIControllerClass = AIControllerClass;
	//		spawnedPawn->SpawnDefaultController();
	//	}
	// }
}

void AMultiShooterGameMode::Tick(float delta)
{
	Super::Tick(delta);
}
