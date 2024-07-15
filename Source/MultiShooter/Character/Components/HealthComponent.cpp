// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	float oldHealth = Health;
	Health -= Damage;
	HealthChanged.Broadcast(oldHealth, Health);
}
