// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Enemy.generated.h"

UCLASS()
class MULTISHOOTER_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UFUNCTION(Server, Reliable)
	void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HealthComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAttackStarted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void OnHealthChanged_Server(float OldValue, float NewValue);
};
