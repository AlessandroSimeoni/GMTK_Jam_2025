// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS/CharacterAbilityTask_OnTick.h"

UCharacterAbilityTask_OnTick::UCharacterAbilityTask_OnTick(const FObjectInitializer& ObjectInitializer)
{
	bTickingTask = true;
}

UCharacterAbilityTask_OnTick* UCharacterAbilityTask_OnTick::AbilityTaskOnTick(UGameplayAbility* OwningAbility)
{
	UCharacterAbilityTask_OnTick* MyObj = NewAbilityTask<UCharacterAbilityTask_OnTick>(OwningAbility);
	return MyObj;
}

void UCharacterAbilityTask_OnTick::Activate()
{
	Super::Activate();
}

void UCharacterAbilityTask_OnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTick.Broadcast(DeltaTime);
	}
}

