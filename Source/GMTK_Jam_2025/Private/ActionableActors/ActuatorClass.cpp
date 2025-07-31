// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionableActors/ActuatorClass.h"

#include "ActionableActors/ActionableClass.h"

// Sets default values
AActuatorClass::AActuatorClass()
{
	
}

// Called when the game starts or when spawned
void AActuatorClass::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActuatorClass::ActivateActors()
{
	for (const TObjectPtr<AActionableClass> Actionable : ConnectedActionableActor)
	{
		if (Actionable)
		{
			Actionable -> IncreaseCurrentActivators();
		}
	}
}

void AActuatorClass::DeactivateActors()
{
	for (const TObjectPtr<AActionableClass> Actionable : ConnectedActionableActor)
	{
		if (Actionable)
		{
			Actionable -> DecreaseCurrentActivators();
		}
	}
}


