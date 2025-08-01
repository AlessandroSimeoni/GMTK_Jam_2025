// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActuatorClass.generated.h"

class AActionableClass;

UCLASS()
class GMTK_JAM_2025_API AActuatorClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActuatorClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connected Actionable Actors")
	TArray<TObjectPtr<AActionableClass>> ConnectedActionableActor;
	UPROPERTY()
	TSet<TObjectPtr<AActor>> OverlappingActors;

public:	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateActors();
	UFUNCTION(BlueprintCallable)
	virtual void DeactivateActors();

};
