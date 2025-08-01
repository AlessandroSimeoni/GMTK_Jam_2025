// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/MainCharacter.h"

void ACharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//	Find enhanced input component
	UEnhancedInputComponent * enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if(!enhancedInputComponent)
		return;
	
	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::HandleMoveAction);
	enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::HandleJumpAction);
	enhancedInputComponent->BindAction(CloneDeathAction, ETriggerEvent::Started, this, &ThisClass::HandleCloneDeathAction);
	enhancedInputComponent->BindAction(DestroyCloneAction, ETriggerEvent::Started, this, &ThisClass::HandleDestroyCloneAction);
}

void ACharacterController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);
	
	PossessedMainCharacter = Cast<AMainCharacter>(PossessedPawn);
	ToggleControls(true);
}

void ACharacterController::OnUnPossess()
{
	Super::OnUnPossess();

	ToggleControls(false);
}

void ACharacterController::HandleMoveAction(const struct FInputActionValue& Value)
{
	FVector CamLoc;
	FRotator CamRot;
	PlayerCameraManager->GetCameraViewPoint(CamLoc, CamRot);

	FVector2D CurrentMovementVector = Value.Get<FVector2D>();

	FVector Forward = CamRot.Vector();
	FVector Right = FRotationMatrix(CamRot).GetUnitAxis(EAxis::Y);

	Forward.Z = 0.f;
	Right.Z = 0.f;
	Right.Normalize();
	
	if (FMath::IsNearlyEqual(Forward.SquaredLength(), 0.0f))
		Forward = FVector::CrossProduct(Right, FVector::UpVector);
	
	Forward.Normalize();

	MovementDirection = Right * CurrentMovementVector.X + Forward * CurrentMovementVector.Y;
	MovementDirection.Normalize();
	PossessedMainCharacter->AddMovementDirection(MovementDirection);
}

void ACharacterController::HandleJumpAction(const struct FInputActionValue& Value)
{
	PossessedMainCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FGameplayTagContainer(PossessedMainCharacter->JumpTag));
	PossessedMainCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FGameplayTagContainer(PossessedMainCharacter->WallJumpTag));
}

void ACharacterController::HandleCloneDeathAction(const struct FInputActionValue& Value)
{
	PossessedMainCharacter->CloneDeath();
}

void ACharacterController::HandleDestroyCloneAction(const struct FInputActionValue& Value)
{
	PossessedMainCharacter->DestroyClone();
}

void ACharacterController::ToggleControls(bool Value)
{
	SetInputContextEnabled(LocomotionMappingContext, Value);
	SetInputContextEnabled(ActionMappingContext, Value);
}

void ACharacterController::SetInputContextEnabled(UInputMappingContext* Context, bool bEnabled, int Priority) const
{
	//	Check valid context
	if(!Context)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid context to de/activate."));
		return;
	}

	//	Check valid input subsystem
	const auto EnhancedInput = GetInputSubsystem();
	if(!EnhancedInput)
		return;

	//	Add or remove the given context, based on the request
	if(bEnabled)
		EnhancedInput->AddMappingContext(Context, Priority);
	else
		EnhancedInput->RemoveMappingContext(Context);
}

class UEnhancedInputLocalPlayerSubsystem* ACharacterController::GetInputSubsystem() const
{
	//	Get local player
	const auto LocalPlayer = GetLocalPlayer();
	if(!LocalPlayer)
		return nullptr;

	//	Get enhanced input subsystem
	return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
}
