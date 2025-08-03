// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionableClass.generated.h"

UCLASS()
class GMTK_JAM_2025_API AActionableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActionableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NecessaryActivators;

public:	
	void IncreaseCurrentActivators();
	void DecreaseCurrentActivators();
	UFUNCTION(BlueprintCallable)
	void CheckActivation();
	UFUNCTION(BlueprintCallable)
	void CheckDeactivation();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ActivateActor();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DeactivateActor();

	
private:
	int32 CurrentActivators = 0;
	bool IsActivated = false;

};
