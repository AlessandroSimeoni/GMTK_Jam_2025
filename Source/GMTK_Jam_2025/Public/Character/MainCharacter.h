// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UPlayerAttributeSet;
class UGameplayAbility;

UCLASS()
class GMTK_JAM_2025_API AMainCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category="GAS")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbility;
	UPROPERTY(EditDefaultsOnly, Category="GAS")
	FGameplayTag WallRunTag;
	
	UPROPERTY(EditDefaultsOnly, Category="Locomotion|WallRun")
	float WallRayHeightOffset = 0.0f;
	UPROPERTY(EditDefaultsOnly, Category="Locomotion|WallRun", Meta = (UIMin = 0.0f, UIMax = 1.0f, ClampMin = 0.0f, ClampMax = 1.0f))
	float WallRunTriggerDotThreshold = 0.7f;
	UPROPERTY(EditAnywhere, Category="Locomotion|WallRun")
	bool DebugWallRays = false;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	void GiveDefaultAbility();
	void ConsumeMovement();
	
	FVector MovementDirection = FVector::ZeroVector;
	FHitResult RightWallRayHitResult;
	FHitResult LeftWallRayHitResult;
	FCollisionQueryParams CollisionParams;
	
	UFUNCTION()
	bool IsVerticalWall(const FHitResult& TargetHitResult) const;
	
public:
	UPROPERTY(BlueprintReadOnly)
	const UPlayerAttributeSet* AttributeSet;
	UPROPERTY(EditDefaultsOnly, Category="GAS")
	FGameplayTag JumpTag;
	UPROPERTY(EditDefaultsOnly, Category="GAS")
	FGameplayTag WallJumpTag;
	UPROPERTY(BlueprintReadWrite, Category="Locomotion")
	FVector LastMovementDirection = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category="WallRun")
	bool IsRightWall = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locomotion|WallRun", Meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float WallRayLength = 25.0f;
	
	AMainCharacter();

	UFUNCTION(BlueprintCallable, Category="Locomotion")
	void AddMovementDirection(FVector Direction);
	UFUNCTION(BlueprintCallable, Category="Locomotion")
	bool CanWallRun();
	UFUNCTION(BlueprintCallable, Category="Locomotion")
	bool CheckWallInputThreshold(const FVector WallDirection);
	UFUNCTION(BlueprintCallable, Category="Locomotion")
	bool CheckWallForwardThreshold(const FVector WallDirection);
	UFUNCTION(BlueprintCallable, Category="Locomotion")
	FVector GetWallCheckOrigin();
	UFUNCTION(BlueprintCallable, Category="Locomotion")
	FVector CalculateWallDirection(const FHitResult& TargetHitResult) const;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
