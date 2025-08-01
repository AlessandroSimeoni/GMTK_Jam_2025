// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "Character/GAS/PlayerAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilitySystemComponent))
		AbilitySystemComponent->InitAbilityActorInfo(this,this);

	GiveDefaultAbility();
	AttributeSet = AbilitySystemComponent->GetSet<UPlayerAttributeSet>();

	GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetPlayerSpeed();
	GetCharacterMovement()->GravityScale = AttributeSet->GetDefaultGravityScale();

	CollisionParams.AddIgnoredActor(this);
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->Velocity.Z < 0 && CanWallRun())
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(WallRunTag));
	}

	if (MovementDirection == FVector::ZeroVector)
	{
		LastMovementDirection = MovementDirection;
		return;
	}
	
	ConsumeMovement();	
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}

	SetOwner(NewController);
}

void AMainCharacter::GiveDefaultAbility()
{
	if (!IsValid(AbilitySystemComponent))return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbility)
	{
		//Create a rappresentation of the ability
		const FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void AMainCharacter::ConsumeMovement()
{
	if (!AttributeSet)
	{
		return; 
	}
	
	LastMovementDirection = MovementDirection;

	if (!AbilitySystemComponent->HasMatchingGameplayTag(WallRunTag))
	{
		AddMovementInput(MovementDirection);
	}
	
	MovementDirection = FVector::ZeroVector;
}

void AMainCharacter::AddMovementDirection(FVector Direction)
{
	MovementDirection += Direction;
}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool AMainCharacter::CanWallRun()
{
	bool RightWallHit = GetWorld()->LineTraceSingleByChannel(RightWallRayHitResult,
														   GetWallCheckOrigin(),
														   GetWallCheckOrigin() + GetActorRightVector() * WallRayLength,
														   ECC_GameTraceChannel1, CollisionParams);

	bool LeftWallHit = GetWorld()->LineTraceSingleByChannel(LeftWallRayHitResult,
														  GetWallCheckOrigin(),
														  GetWallCheckOrigin() + GetActorRightVector() * -WallRayLength,
														  ECC_GameTraceChannel1, CollisionParams);

	if (DebugWallRays)
	{
		DrawDebugLine(GetWorld(),GetWallCheckOrigin(),GetWallCheckOrigin() + GetActorRightVector() * WallRayLength, FColor::Red, false,1.0f, 0, 2.0f);
		DrawDebugLine(GetWorld(),GetWallCheckOrigin(),GetWallCheckOrigin() + GetActorRightVector() * -WallRayLength, FColor::Red, false,1.0f, 0, 2.0f);
	}
	
	if ((RightWallHit && IsVerticalWall(RightWallRayHitResult)) || (LeftWallHit && IsVerticalWall(LeftWallRayHitResult)))
	{
		const FVector WallDirection = CalculateWallDirection(RightWallHit ? RightWallRayHitResult : LeftWallRayHitResult);

		if (CheckWallInputThreshold(WallDirection) && CheckWallForwardThreshold(WallDirection))
		{
			IsRightWall = RightWallHit && IsVerticalWall(RightWallRayHitResult);
			return true;
		}
	}
	
	return false;
}

bool AMainCharacter::CheckWallInputThreshold(const FVector WallDirection)
{
	return FVector::DotProduct(LastMovementDirection, WallDirection) >= WallRunTriggerDotThreshold;
}

bool AMainCharacter::CheckWallForwardThreshold(const FVector WallDirection)
{
	return FVector::DotProduct(GetActorForwardVector(), WallDirection) >= WallRunTriggerDotThreshold;
}

FVector AMainCharacter::GetWallCheckOrigin()
{
	return GetActorLocation() + FVector::UpVector * WallRayHeightOffset;
}

FVector AMainCharacter::CalculateWallDirection(const FHitResult& TargetHitResult) const
{
	FVector WallDirection = FVector::CrossProduct(GetActorUpVector(), TargetHitResult.Normal);
	if (FVector::DotProduct(GetActorForwardVector(), WallDirection) < 0)
		WallDirection *= -1;

	return WallDirection;
}

bool AMainCharacter::IsVerticalWall(const FHitResult& TargetHitResult) const
{
	return FVector::DotProduct(GetActorUpVector(), TargetHitResult.Normal) == 0.0f;
}
