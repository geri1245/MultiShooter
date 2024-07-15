// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"

#include "../../Weapons/Data/WeaponData.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/World.h"

namespace
{
const FName CharacterTraceTag("CharacterDebugTraceTag");
constexpr const char* AimingCircleSocketName = "AimingCircle";
constexpr const char* AimingHelperSocketName = "AimingHelper";

// The camera will be this far behind the aiming reticle while aiming
constexpr const float CameraOffsetFromAimingReticle = 5;

// https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly
FVector2D GetRandomPointInCircle(float radius)
{
	float r = radius * FMath::Sqrt(FMath::FRand());
	float theta = 2 * PI * FMath::FRand();

	return FVector2D{r * cos(theta), r * sin(theta)};
}
}	 // namespace

UWeaponComponent::UWeaponComponent()
{
	Data = CreateDefaultSubobject<UWeaponData>(TEXT("WeaponComponent"));
	Spread = Data->MinSpread;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UWeaponComponent::SetWeaponData(UWeaponData* NewData)
{
	Data = NewData;
}

void UWeaponComponent::Fire()
{
	if (auto* world = GetWorld())
	{
		auto now = world->GetTimeSeconds();

		// We eneed to wait a little bit for the next shot
		if (now - LastFireTimestamp < Data->TimeBetweenShots)
		{
			return;
		}

		auto* owningPawn = Cast<APawn>(GetOwner());
		if (owningPawn != nullptr && owningPawn->GetLocalRole() == ROLE_Authority)
		{
			if (auto* camera = owningPawn->FindComponentByClass<UCameraComponent>())
			{
				FHitResult LineTraceHitResult;
				FVector ActorLocation = camera->GetComponentLocation();
				FVector Direction = camera->GetComponentRotation().Vector();
				FVector TraceEndLocation = ActorLocation + 100000.f * Direction;
				FCollisionObjectQueryParams ObjectQueryParams(ECC_GameTraceChannel1);
				FCollisionQueryParams QueryParams(CharacterTraceTag, false, owningPawn);

				bool wasHit = world->LineTraceSingleByObjectType(LineTraceHitResult, ActorLocation, TraceEndLocation, ObjectQueryParams, QueryParams);

				if (wasHit)
				{
					DrawDebugLine(GetWorld(), ActorLocation, LineTraceHitResult.ImpactPoint, FColor::Blue, false, 5.f, 0, 1.f);
					if (AActor* hitActor = LineTraceHitResult.GetActor())
					{
						hitActor->TakeDamage(
							30, FPointDamageEvent(30, LineTraceHitResult, Direction, UDamageType::StaticClass()), owningPawn->Controller, owningPawn);
					}
				}

				UE_LOG(LogTemp, Warning, TEXT("Fire"));
				// LogVector(Direction);

				LastFireTimestamp = now;
			}

			UpdateSpread();
		}
	}
}

void UWeaponComponent::SetAimingState(bool ShouldBeAiming)
{
	FVector aimingCircleLocation = GetSocketLocation(FName(AimingCircleSocketName));
	FVector aimingHelperLocation = GetSocketLocation(FName(AimingHelperSocketName));

	FVector finalLocation = aimingCircleLocation - CameraOffsetFromAimingReticle * (aimingHelperLocation - aimingCircleLocation).Normalize();
}

void UWeaponComponent::UpdateSpread()
{
	WeaponSpread = std::min(WeaponSpread + 1.0, MaxWeaponSpread);
	WeaponSpreadChanged.Broadcast(WeaponSpread);
}

void UWeaponComponent::OnAttachmentChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("Attachment changed"));
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (auto* world = GetWorld())
	{
		auto now = world->GetTimeSeconds();
		if (WeaponSpread > MinWeaponSpread && WeaponSpreadRegenCooldown < now - LastFireTimestamp)
		{
			WeaponSpread = FMath::Max(MinWeaponSpread, WeaponSpread - WeaponSpreadRegenPerSec * DeltaTime);
			WeaponSpreadChanged.Broadcast(WeaponSpread);
		}
	}
}
