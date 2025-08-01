// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WallRunAbility.generated.h"

class AMainCharacter;

UCLASS()
class GMTK_JAM_2025_API UWallRunAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	
	/**
	 * This should be executed in a Tick
	 * @param TargetCharacter the target main character
	 */
	UFUNCTION(BlueprintCallable)
	void DoWallRun(AMainCharacter* TargetCharacter);

	UPROPERTY(BlueprintReadOnly)
	FHitResult WallHitResult;
	UPROPERTY(BlueprintReadOnly)
	FVector WallNormal = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly)
	FVector WallDirection = FVector::ZeroVector;

	FGameplayAbilitySpecHandle CachedHandle;
	const FGameplayAbilityActorInfo* CachedActorInfo;
	FGameplayAbilityActivationInfo CachedActivationInfo;
};
