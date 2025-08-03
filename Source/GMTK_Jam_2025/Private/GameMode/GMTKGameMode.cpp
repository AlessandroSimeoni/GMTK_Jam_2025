// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GMTKGameMode.h"

#include "GameMode/ThresholdDataAsset.h"
#include "GameMode/TimeThresoldStruct.h"
#include "Kismet/GameplayStatics.h"

void AGMTKGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (Controller)
	{
		FInputModeGameOnly InputMode;
		Controller->SetInputMode(InputMode);
		Controller->SetShowMouseCursor(false);
	}
	CurrentTime = 0.0f;
}

FName AGMTKGameMode::ReturnScore()
{
	if (!ThresholdDataAsset) return FName("None");
	for (const FTimeThresoldStruct& Entry : ThresholdDataAsset -> Thresholds)
	{
		if (CurrentTime <= Entry.MaxTime)
		{
			return Entry.ThresholdName;
		}
	}
	return ThresholdDataAsset -> Thresholds.Last().ThresholdName;
}

void AGMTKGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentTime += DeltaSeconds;
}
