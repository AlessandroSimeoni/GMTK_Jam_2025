// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/SaveSystem.h"

#include "Kismet/GameplayStatics.h"
#include "Save/GMTKSave.h"

void USaveSystem::SaveGame()
{
	if (!GMTKSave)
	{
		GMTKSave = Cast<UGMTKSave>(UGameplayStatics::CreateSaveGameObject(UGMTKSave::StaticClass()));
	}
	UGameplayStatics::SaveGameToSlot(GMTKSave, GameSlotName, 0);
}

UGMTKSave* USaveSystem::LoadGame()
{
	if (GMTKSave)
		return GMTKSave;
	if (DoesSaveExist(GameSlotName))
		GMTKSave =Cast<UGMTKSave>(UGameplayStatics::LoadGameFromSlot(GameSlotName, 0));
	else
	{
		GMTKSave = Cast<UGMTKSave>(UGameplayStatics::CreateSaveGameObject(UGMTKSave::StaticClass()));
	}
	return GMTKSave;
}

bool USaveSystem::DoesSaveExist(FString SlotName) const
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}
