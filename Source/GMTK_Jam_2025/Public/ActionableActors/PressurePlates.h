// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionableActors/ActuatorClass.h"
#include "PressurePlates.generated.h"

/**
 * 
 */

class UCapsuleComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class GMTK_JAM_2025_API APressurePlates : public AActuatorClass
{
	GENERATED_BODY()
protected:
	APressurePlates();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pressure Plate")
	TObjectPtr<USceneComponent> RootScene;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCapsuleComponent* PressurePlateArea;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PressurePlateMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* CapsuleVisualMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInstanceDynamic* PressurePlateMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsActivated = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 OverlappedActors = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* ActivationSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* DeactivationSound;
	UPROPERTY(Transient)
	TObjectPtr<UAudioComponent> ActivationAudioComponent;
	UPROPERTY(Transient)
	TObjectPtr<UAudioComponent> DeactivationAudioComponent;

public:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnPressurePlateBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPressurePlateEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void ActivateActors() override;
	virtual void DeactivateActors() override;
};
