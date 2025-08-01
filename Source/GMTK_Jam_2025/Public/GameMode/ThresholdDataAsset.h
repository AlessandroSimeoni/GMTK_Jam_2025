// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TimeThresoldStruct.h"
#include "ThresholdDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class GMTK_JAM_2025_API UThresholdDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ThresholdDataAsset")
	TArray<FTimeThresoldStruct> Thresholds;
};
