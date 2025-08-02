// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GMTKGameMode.generated.h"

class UThresholdDataAsset;
/**
 * 
 */
UCLASS()
class GMTK_JAM_2025_API AGMTKGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	FName ReturnScore();
protected:
	UPROPERTY(BlueprintReadOnly)
	float CurrentTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UThresholdDataAsset> ThresholdDataAsset;
	virtual void Tick(float DeltaSeconds) override;
};
