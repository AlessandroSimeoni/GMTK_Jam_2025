// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GMTK_JAM_2025_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,Category="Base Stats")
	FGameplayAttributeData PlayerSpeed;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet,PlayerSpeed);
	UPROPERTY(BlueprintReadOnly,Category="Base Stats")
	FGameplayAttributeData WallPlayerSpeed;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet,WallPlayerSpeed);
	UPROPERTY(BlueprintReadOnly,Category="Base Stats")
	FGameplayAttributeData DefaultGravityScale;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet,DefaultGravityScale);
	UPROPERTY(BlueprintReadOnly,Category="Base Stats")
	FGameplayAttributeData WallGravityScale;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet,WallGravityScale);
	UPROPERTY(BlueprintReadOnly,Category="Base Stats")
	FGameplayAttributeData WallJumpYaw;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet,WallJumpYaw);
	UPROPERTY(BlueprintReadOnly,Category="Base Stats")
	FGameplayAttributeData WallJumpPitch;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet,WallJumpPitch);
	UPROPERTY(BlueprintReadOnly,Category="Base Stats")
	FGameplayAttributeData WallJumpPower;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet,WallJumpPower);
};
