// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS/WallRunAbility.h"

#include "Character/MainCharacter.h"
#include "Character/GAS/PlayerAttributeSet.h"

void UWallRunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	CachedHandle = Handle;
	CachedActorInfo = ActorInfo;
	CachedActivationInfo = ActivationInfo;
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UWallRunAbility::DoWallRun(AMainCharacter* TargetCharacter)
{
	if (!TargetCharacter)
	{
		return;
	}

	FVector WallRayDirection = TargetCharacter->GetActorRightVector() * TargetCharacter->WallRayLength * (TargetCharacter->IsRightWall ? 1 : -1);
	
	bool WallHit = GetWorld()->LineTraceSingleByChannel(WallHitResult,
													  TargetCharacter->GetWallCheckOrigin(),
													  TargetCharacter->GetWallCheckOrigin() + WallRayDirection,
													  ECC_GameTraceChannel1);

	// se finisce il muro: end ability
	if (!WallHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wall Run Ended | Reason: WALL NOT DETECTED"));
		EndAbility(CachedHandle, CachedActorInfo, CachedActivationInfo, true, false);
		return;
	}
	
	WallNormal = WallHitResult.Normal;
	WallDirection = TargetCharacter->CalculateWallDirection(WallHitResult);
	
	// se l'input non è allineato: end ability
	if (!TargetCharacter->CheckWallInputThreshold(WallDirection))//|| !TargetCharacter->CheckWallForwardThreshold(WallDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Wall Run Ended | Reason: INPUT THRESHOLD NOT VALID"));
		EndAbility(CachedHandle, CachedActorInfo, CachedActivationInfo, true, false);
		return;
	}

	// set character rotation along wall direction
	TargetCharacter->SetActorRotation(WallDirection.Rotation());
	TargetCharacter->AddMovementInput(WallDirection);
}
