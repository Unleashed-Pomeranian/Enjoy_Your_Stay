// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_InteractableActor.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/EYS_MyCharacter.h"

// Sets default values
AEYS_InteractableActor::AEYS_InteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);


}

// Called when the game starts or when spawned
void AEYS_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_InteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_InteractableActor::FActionStart_Implementation(AEYS_MyCharacter* myPlayer)
{
}

void AEYS_InteractableActor::FSecondAction_Implementation(AEYS_MyCharacter* myPlayer)
{
}