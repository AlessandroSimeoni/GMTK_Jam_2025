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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	void GiveDefaultAbility();
	void ConsumeMovement();
	
	FVector MovementDirection = FVector::ZeroVector;
	UPROPERTY()
	const UPlayerAttributeSet* AttributeSet;
	
public:
	AMainCharacter();

	UFUNCTION(BlueprintCallable, Category="Locomotion")
	void AddMovementDirection(FVector Direction);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
