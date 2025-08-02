// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAnimInstance.h"

#include "Character/MainCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerPawn = TryGetPawnOwner();
	if(OwnerPawn)
		OwnerCharacter = Cast<AMainCharacter>(OwnerPawn);
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerPawn)
	{
		PlayerVelocity = OwnerPawn->GetMovementComponent()->Velocity.SquaredLength();
	}
}

