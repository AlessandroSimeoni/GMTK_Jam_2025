// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterShell.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

ACharacterShell::ACharacterShell()
{
	ShellRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = ShellRoot;

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellMesh"));
	ShellMesh->SetupAttachment(RootComponent);
	ShellMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetCollisionProfileName(TEXT("BlockAll"));
}
