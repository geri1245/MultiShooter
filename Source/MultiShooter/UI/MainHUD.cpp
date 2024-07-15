// Fill out your copyright notice in the Description page of Project Settings.

#include "MainHUD.h"

#include "MainUserWidget.h"
#include "MultiShooter/Character/Components/WeaponComponent.h"
#include "MultiShooter/Character/MultiShooterCharacter.h"

void AMainHUD::BeginPlay()
{
	CrosshairWidget = NewObject<UMainUserWidget>(Owner->GetWorld(), WidgetClass);
	CrosshairWidget->AddToViewport();

	if (auto* controller = Cast<AController>(Owner))
	{
		if (auto* character = Cast<AMultiShooterCharacter>(controller->GetPawn()))
		{
			character->WeaponComponent->WeaponSpreadChanged.AddUObject(this, &AMainHUD::ApplyCrosshairSpread);
		}
	}
}

void AMainHUD::ApplyCrosshairSpread(double newSpread)
{
	CrosshairWidget->SetSpread(newSpread);
}
