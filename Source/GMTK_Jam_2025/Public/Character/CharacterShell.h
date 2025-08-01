// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterShell.generated.h"

class UBoxComponent;

UCLASS()
class GMTK_JAM_2025_API ACharacterShell : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> ShellRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> ShellMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> CollisionBox = nullptr;
	
public:	
	ACharacterShell();

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyShell();
};
