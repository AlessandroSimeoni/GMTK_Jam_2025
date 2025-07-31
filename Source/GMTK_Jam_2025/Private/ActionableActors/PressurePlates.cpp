// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionableActors/PressurePlates.h"

#include "ActionableActors/ActionableClass.h"
#include "Components/CapsuleComponent.h"

APressurePlates::APressurePlates()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);
	
	PressurePlateArea = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Area"));
	PressurePlateArea -> InitCapsuleSize(100.0f, 20.0f);
	PressurePlateArea -> SetCollisionProfileName(TEXT("Trigger"));
	PressurePlateArea -> SetGenerateOverlapEvents(true);
	PressurePlateArea -> SetHiddenInGame(true);
	PressurePlateArea -> SetMobility(EComponentMobility::Movable);

	PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Mesh"));
	PressurePlateMesh->SetupAttachment(RootComponent);

	CapsuleVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapsuleVisual"));
	CapsuleVisualMesh -> SetupAttachment(PressurePlateArea);
	
	//RootComponent = PressurePlateArea;
}

void APressurePlates::BeginPlay()
{
	Super::BeginPlay();
	if (PressurePlateArea)
	{
		PressurePlateArea -> OnComponentBeginOverlap.AddDynamic(this, &APressurePlates::OnPressurePlateBeginOverlap);
		PressurePlateArea -> OnComponentEndOverlap.AddDynamic(this, &APressurePlates::OnPressurePlateEndOverlap);
	}
}

void APressurePlates::OnPressurePlateBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !OverlappingActors.Contains(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Begin Overlap: Actor %s, Address: %p"), *OtherActor->GetName(), OtherActor);
		OverlappingActors.Add(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Added Actor: %s"), *OtherActor->GetName());
		OverlappedActors++;
		UE_LOG(LogTemp, Warning, TEXT("OnPressurePlateBeginOverlap"));
		if (OverlappedActors == 1)
			ActivateActors();
	}
}

void APressurePlates::OnPressurePlateEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		OverlappingActors.Remove(OtherActor);
		OverlappedActors--;
		UE_LOG(LogTemp, Warning, TEXT("OnPressurePlateEndOverlap"));
		if (OverlappedActors == 0)
			DeactivateActors();
	}
}

void APressurePlates::ActivateActors()
{
	if (IsActivated) return;
	//Super::ActivateActors();
	for (const TObjectPtr<AActionableClass> Actionable : ConnectedActionableActor)
	{
		if (Actionable)
		{
			UE_LOG(LogTemp, Warning, TEXT("Increase Counter"));
			Actionable -> IncreaseCurrentActivators();
		}
	}
	IsActivated = true;
}

void APressurePlates::DeactivateActors()
{
	//Super::DeactivateActors();
	for (const TObjectPtr<AActionableClass> Actionable : ConnectedActionableActor)
	{
		if (Actionable)
		{
			UE_LOG(LogTemp, Warning, TEXT("Decrease Counter"));
			Actionable -> DecreaseCurrentActivators();
		}
	}
	IsActivated = false;
}
