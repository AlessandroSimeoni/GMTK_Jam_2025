// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GMTK_JAM_2025_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	APawn * OwnerPawn;
	UPROPERTY(BlueprintReadOnly)
	class AMainCharacter * OwnerCharacter;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	float PlayerVelocity = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	bool IsJumping = false;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
