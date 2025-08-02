// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GMTKSave.generated.h"

/**
 * 
 */
UCLASS()
class GMTK_JAM_2025_API UGMTKSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Save)
	TMap<FString, float> TimeInLevels;

	UFUNCTION(BlueprintCallable, Category = Save)
	void SaveTimeToLevel(FString LevelName, float Time);

	UFUNCTION(BlueprintPure, Category = Save)
	void GetLevelNames(TArray<FString>& Keys);
};
