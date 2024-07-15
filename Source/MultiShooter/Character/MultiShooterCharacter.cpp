// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiShooterCharacter.h"

#include "../Helpers/DebugLog.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InputComponent.h"
#include "Components/WeaponComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MultiShooter/UI/MainUserWidget.h"

namespace
{
constexpr const char* WeaponSocketName = "RightHandWeaponSocket";
}	 // namespace

AMultiShooterCharacter::AMultiShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->BodyInstance.SetObjectType(ECC_GameTraceChannel1);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	bUseControllerRotationYaw = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;				// Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);	// ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SocketOffset = FVector(0, 60, 80);
	CameraBoom->TargetArmLength = 400.0f;		   // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true;	   // Rotate the arm based on the controller

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);	 // Attach the camera to the end of the boom and let the boom adjust to
																			 // match the controller orientation
	Camera->bUsePawnControlRotation = false;								 // Camera does not rotate relative to arm

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->HealthChanged.AddDynamic(this, &AMultiShooterCharacter::OnHealthChanged_Server);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	if (WeaponComponent != nullptr)
	{
		WeaponComponent->SetupAttachment(GetCapsuleComponent());
		WeaponComponent->RegisterComponent();
	}
}

void AMultiShooterCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMultiShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMultiShooterCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMultiShooterCharacter::Look);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &AMultiShooterCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(SecondaryAttackAction, ETriggerEvent::Triggered, this, &AMultiShooterCharacter::SecondaryAttack);
	}
}

void AMultiShooterCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMultiShooterCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMultiShooterCharacter::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void AMultiShooterCharacter::PrimaryAttack(const FInputActionValue& Value)
{
	if (auto* controller = GetController())
	{
		PrimaryAttack_Server();
	}
}

void AMultiShooterCharacter::OnHealthChanged_Server_Implementation(float OldValue, float NewValue)
{
}

void AMultiShooterCharacter::PrimaryAttack_Server_Implementation()
{
	if (WeaponComponent != nullptr)
	{
		WeaponComponent->Fire();
	}
	else
	{
		DebugLog::DebugAssert();
	}
	// if (GetLocalRole() == ROLE_Authority)
	//{
	//	if (auto* world = GetWorld())
	//	{
	//		FHitResult LineTraceHitResult;
	//		FVector ActorLocation = Camera->GetComponentLocation();
	//		FVector Direction = Camera->GetComponentRotation().Vector();
	//		FVector TraceEndLocation = ActorLocation + 100000.f * Direction;
	//		FCollisionObjectQueryParams ObjectQueryParams(ECC_GameTraceChannel1);
	//		FCollisionQueryParams QueryParams(CharacterTraceTag, false, this);

	//		bool wasHit = world->LineTraceSingleByObjectType(LineTraceHitResult, ActorLocation, TraceEndLocation, ObjectQueryParams, QueryParams);

	//		if (wasHit)
	//		{
	//			DrawDebugLine(GetWorld(), ActorLocation, LineTraceHitResult.ImpactPoint, FColor::Blue, false, 5.f, 0, 1.f);
	//			if (AActor* hitActor = LineTraceHitResult.GetActor())
	//			{
	//				hitActor->TakeDamage(30, FPointDamageEvent(30, LineTraceHitResult, Direction, UDamageType::StaticClass()), Controller, this);
	//			}
	//		}

	//		UE_LOG(LogTemp, Warning, TEXT("Fire"));
	//		LogVector(Direction);
	//	}
	//}
}

void AMultiShooterCharacter::SecondaryAttack(const FInputActionValue& Value)
{
	if (IsValid(WeaponComponent))
	{
		bool isPressed = Value.Get<FInputActionValue::Axis1D>() == 1;
		WeaponComponent->SetAimingState(isPressed);
	}
}
