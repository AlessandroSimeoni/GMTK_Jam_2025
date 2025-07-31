// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionableActors/ActionableClass.h"

// Sets default values
AActionableClass::AActionableClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AActionableClass::IncreaseCurrentActivators()
{
	CurrentActivators++;
	UE_LOG(LogTemp, Warning, TEXT("CurrentActivators: %d / %d"), CurrentActivators, NecessaryActivators);
	CheckActivation();
}

void AActionableClass::DecreaseCurrentActivators()
{
	if (CurrentActivators > 0)
	{
		CurrentActivators--;
		UE_LOG(LogTemp, Warning, TEXT("CurrentActivators: %d / %d"), CurrentActivators, NecessaryActivators);
		CheckDeactivation();
	}
}

void AActionableClass::CheckActivation()
{
	if (CurrentActivators == NecessaryActivators && !IsActivated)
	{
		IsActivated = true;
		UE_LOG(LogTemp, Warning, TEXT("Active Actors"));
		ActivateActor();
	}
}

void AActionableClass::CheckDeactivation()
{
	if (CurrentActivators < NecessaryActivators && IsActivated)
	{
		IsActivated = false;
		UE_LOG(LogTemp, Warning, TEXT("Deactive Actors"));
		DeactivateActor();
	}
}

// Called when the game starts or when spawned
void AActionableClass::BeginPlay()
{
	Super::BeginPlay();
	CurrentActivators = 0;
}


