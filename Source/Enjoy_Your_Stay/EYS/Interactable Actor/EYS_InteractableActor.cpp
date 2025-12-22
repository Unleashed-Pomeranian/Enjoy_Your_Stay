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

void AEYS_InteractableActor::FActionStart_Implementation()
{
}

void  AEYS_InteractableActor::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Interact(myPlayer);
}

void  AEYS_InteractableActor::Interact(AEYS_MyCharacter* myPlayer)
{
	
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	PC->EquipmentWheelInstance->EnableButtons(Index,true,ESlateVisibility::Visible);
	Destroy();

}
