// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GMTKGameMode.h"

#include "Kismet/GameplayStatics.h"

void AGMTKGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(true);
	if (Controller)
	{
		Controller->SetInputMode(InputMode);
		Controller->SetShowMouseCursor(false);
	}
}
