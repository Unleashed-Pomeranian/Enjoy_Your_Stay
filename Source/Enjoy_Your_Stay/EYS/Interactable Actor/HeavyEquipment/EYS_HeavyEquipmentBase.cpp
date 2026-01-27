// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"

class AEYS_MyCharacterController;
// Sets default values
AEYS_HeavyEquipmentBase::AEYS_HeavyEquipmentBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Box"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AEYS_HeavyEquipmentBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_HeavyEquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void   AEYS_HeavyEquipmentBase::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void AEYS_HeavyEquipmentBase::PlayHeavyAudio_Implementation()
{
}

void AEYS_HeavyEquipmentBase::AttachActor(AEYS_MyCharacter* myPlayer)
{
	StaticMesh->SetSimulatePhysics(false);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	AttachToComponent(myPlayer->FirstPersonMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HeavyEquipment");
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	myPlayer->PoseNum = 6;
	myPlayer->SetRoot();
	myPlayer->HeldEquipment = this;
	myPlayer->bIsHandsFull = true;
	PlayHeavyAudio();
}

void AEYS_HeavyEquipmentBase::DettachActor()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetSimulatePhysics(true);
	PlayHeavyAudio();
}


void  AEYS_HeavyEquipmentBase::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{

}

void   AEYS_HeavyEquipmentBase::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if(!(myPlayer->bIsHandsFull))
	AttachActor(myPlayer);
}
