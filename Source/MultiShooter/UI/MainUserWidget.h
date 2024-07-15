// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Interfaces/ICrosshair.h"

#include "MainUserWidget.generated.h"

/**
 *
 */
UCLASS()
class MULTISHOOTER_API UMainUserWidget : public UUserWidget, public ICrosshair
{
	GENERATED_BODY()

	void NativeConstruct() override;

	UPROPERTY()
	float Spread;

public:
	void SetSpread(float NewSpread);

	UFUNCTION(BlueprintImplementableEvent)
	void NewSpreadSet(float NewSpread);
};
