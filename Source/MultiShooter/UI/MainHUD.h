// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "MainHUD.generated.h"

/**
 *
 */
UCLASS()
class MULTISHOOTER_API AMainHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UMainUserWidget> WidgetClass;

public:
	UPROPERTY()
	TObjectPtr<class UMainUserWidget> CrosshairWidget;

	void ApplyCrosshairSpread(double newSpread);
};
