// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeThresoldStruct.generated.h"

USTRUCT(BlueprintType)
struct FTimeThresoldStruct
{
	GENERATED_BODY()
public:
	// The name of the rank or medal (can be shown in UI)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ThresholdName;

	// The maximum time to achieve this medal
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxTime = 0.f;
};