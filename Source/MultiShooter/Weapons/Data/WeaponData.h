// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "WeaponData.generated.h"

/**
 *
 */
UCLASS()
class MULTISHOOTER_API UWeaponData : public UDataAsset
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	float MinSpread = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxSpread = 1.f;

	UPROPERTY(EditAnywhere)
	float SpreadChangePerShot = 0.1f;

	UPROPERTY(EditAnywhere)
	float TimeBetweenShots = 2.0f;

	UPROPERTY(EditAnywhere)
	float ReloadTime = 2.f;
};
