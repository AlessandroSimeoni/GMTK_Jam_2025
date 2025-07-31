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
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementDirection == FVector::ZeroVector)
	{
		return;
	}
	
	ConsumeMovement();
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
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
	
	AddMovementInput(MovementDirection * AttributeSet->GetPlayerSpeed());
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

