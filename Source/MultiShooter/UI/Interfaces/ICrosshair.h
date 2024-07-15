// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ICrosshair.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCrosshair : public UInterface
{
	GENERATED_BODY()
};

class ICrosshair
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetSpread(float newSpread);
};
