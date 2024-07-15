// Fill out your copyright notice in the Description page of Project Settings.

#include "MainUserWidget.h"

#include "Camera/CameraComponent.h"
#include "MultiShooter/Character/MultiShooterCharacter.h"

void UMainUserWidget::NativeConstruct()
{
}

void UMainUserWidget::SetSpread(float NewSpread)
{
	Spread = NewSpread;
	NewSpreadSet(NewSpread);
}
