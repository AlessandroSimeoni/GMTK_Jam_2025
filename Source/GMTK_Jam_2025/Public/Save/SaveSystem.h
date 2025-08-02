// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveSystem.generated.h"

class UGMTKSave;
/**
 * 
 */
UCLASS()
class GMTK_JAM_2025_API USaveSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	TObjectPtr<UGMTKSave> GMTKSave = nullptr;

	FString GameSlotName = TEXT("SaveSlot");
public:
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	UGMTKSave* LoadGame();
	UFUNCTION(BlueprintCallable)
	bool DoesSaveExist(FString SlotName = TEXT("SaveSlot")) const;
};
