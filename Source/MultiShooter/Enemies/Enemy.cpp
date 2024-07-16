// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "MultiShooter/Character/Components/HealthComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->BodyInstance.SetObjectType(ECC_GameTraceChannel1);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->HealthChanged.AddDynamic(this, &AEnemy::OnHealthChanged_Server);
}

void AEnemy::Attack_Implementation()
{
	OnAttackStarted();
}

void AEnemy::OnHealthChanged_Server_Implementation(float OldValue, float NewValue)
{
	if (NewValue < 0)
	{
		HealthComponent->HealthChanged.RemoveDynamic(this, &AEnemy::OnHealthChanged_Server);
		Destroy();
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}
