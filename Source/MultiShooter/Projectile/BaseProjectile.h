// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FThisIsMyDelegate, int, param1, float, param2);

UCLASS()
class MULTISHOOTER_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnProjectileStop(const FHitResult& ImpactResult);

	FThisIsMyDelegate MyDelegate;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
