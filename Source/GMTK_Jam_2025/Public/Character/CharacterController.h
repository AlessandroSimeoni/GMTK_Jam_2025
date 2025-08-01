// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

class AMainCharacter;
/**
 * 
 */
UCLASS()
class GMTK_JAM_2025_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Locomotion")
	TObjectPtr<class UInputMappingContext> LocomotionMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Locomotion")
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Locomotion")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Action")
	TObjectPtr<class UInputMappingContext> ActionMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Action")
	TObjectPtr<UInputAction> CloneDeathAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Action")
	TObjectPtr<UInputAction> DestroyCloneAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping|Action")
	TObjectPtr<UInputAction> PauseAction;
	
	UPROPERTY(BlueprintReadOnly)
	AMainCharacter* PossessedMainCharacter = nullptr;
	
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn * PossessedPawn) override;
	virtual void OnUnPossess() override;
	
	class UEnhancedInputLocalPlayerSubsystem * GetInputSubsystem() const;

	UFUNCTION()
	void HandleMoveAction(const struct FInputActionValue & Value);
	UFUNCTION()
	void HandleJumpAction(const struct FInputActionValue & Value);
	UFUNCTION()
	void HandleCloneDeathAction(const struct FInputActionValue & Value);
	UFUNCTION()
	void HandleDestroyCloneAction(const struct FInputActionValue & Value);
	UFUNCTION(BlueprintCallable)
	void HandlePause(const struct FInputActionValue & Value);

public:
	FVector MovementDirection;
	
	UFUNCTION(BlueprintCallable)
	void ToggleControls(bool Value);
	void SetInputContextEnabled(UInputMappingContext * Context, bool bEnabled, int Priority = 1) const;
	UFUNCTION(BlueprintImplementableEvent)
	void PauseGame();
};


