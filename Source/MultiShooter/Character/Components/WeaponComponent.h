// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"

#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAimingStartedSignature);
DECLARE_EVENT_OneParam(UWeaponComponent, FCameraPositionShouldChangeForADSSignature, FVector /*newCameraLocation*/);
DECLARE_EVENT_OneParam(AMultiShooterCharacter, FWeaponSpreadChanged, double /*newSpread*/);

/**
 *
 */
UCLASS()
class MULTISHOOTER_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	UPROPERTY(Instanced, VisibleAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponData> Data;

	UFUNCTION()
	void SetWeaponData(class UWeaponData* NewData);

	UFUNCTION()
	void Fire();

	UPROPERTY(BlueprintAssignable)
	FAimingStartedSignature OnAimingStarted;

	FCameraPositionShouldChangeForADSSignature OnCameraPositionShouldChageForADS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	double WeaponSpread = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	double MaxWeaponSpread = 8;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	double MinWeaponSpread = 1;
	// Amount of time that needs to pass after a shot for the spread to start becoming smaller
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	double WeaponSpreadRegenCooldown = 2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	double WeaponSpreadRegenPerSec = 1.0;

	void SetAimingState(bool ShouldBeAiming);

	FWeaponSpreadChanged WeaponSpreadChanged;

private:
	/// <summary>
	/// Spread is a measurement in m. It says how much a shot can deviate from where we are aiming at 100 meters
	/// </summary>
	float Spread = 0.f;

	double LastFireTimestamp = 0.f;

	void UpdateSpread();

	virtual void OnAttachmentChanged() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
