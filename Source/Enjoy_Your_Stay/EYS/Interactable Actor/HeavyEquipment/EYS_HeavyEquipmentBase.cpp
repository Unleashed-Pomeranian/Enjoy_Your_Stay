// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GamePlayStatics.h"

class AEYS_MyCharacterController;
// Sets default values
AEYS_HeavyEquipmentBase::AEYS_HeavyEquipmentBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Box"));
	RootComponent = StaticMesh;
	StaticMesh->SetCustomDepthStencilValue(5);
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

void AEYS_HeavyEquipmentBase::PlayHeavyAudio()
{
	if (!HeavySound) return;
	FVector SoundLocation = GetActorLocation();
	UGameplayStatics::PlaySoundAtLocation(this, HeavySound, SoundLocation);
}

void AEYS_HeavyEquipmentBase::AttachActor(AEYS_MyCharacter* myPlayer)
{
	StaticMesh->SetSimulatePhysics(false);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	AttachToComponent(myPlayer->FirstPersonMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HeavyEquipment");
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	myPlayer->SetRoot(8);
	myPlayer->HeldEquipment = this;
	myPlayer->bIsHandsFull = true;
	PlayHeavyAudio();
}

void AEYS_HeavyEquipmentBase::DetachFromPlayer()
{
	AEYS_MyCharacter* Player = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player && Player->HeldEquipment)
		Player->DetachHeavyEquipment();
	Destroy();
}

void AEYS_HeavyEquipmentBase::PlaceOnRack(AEYS_MyCharacter* myPlayer, USceneComponent* TargetSlot)
{
	if (!myPlayer || !TargetSlot) return;
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	AttachToComponent(TargetSlot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	myPlayer->DetachHeavyEquipment();
	PlayHeavyAudio();
}



void AEYS_HeavyEquipmentBase::DetachActor()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetSimulatePhysics(true);
	PlayHeavyAudio();
}


void  AEYS_HeavyEquipmentBase::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	StaticMesh->SetRenderCustomDepth(bIsFocused);
}

void   AEYS_HeavyEquipmentBase::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if(!(myPlayer->bIsHandsFull))
	AttachActor(myPlayer);
}
