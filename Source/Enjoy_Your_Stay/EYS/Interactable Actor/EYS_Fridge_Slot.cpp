// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Fridge_Slot.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
AEYS_Fridge_Slot::AEYS_Fridge_Slot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMesh"));
	InstancedStaticMesh->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void AEYS_Fridge_Slot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEYS_Fridge_Slot::FAddSlot()
{
	if (InstanceIndex >= 0)
	{
		InstancedStaticMesh->RemoveInstance(InstanceIndex);
		InstanceIndex--;
	}
}

void AEYS_Fridge_Slot::FDeleteSlot()
{
	if(InstanceIndex<5)
	{
		InstancedStaticMesh->AddInstance(InstanceTransform[InstanceIndex + 1], false);
		InstanceIndex++;
	}
}

// Called every frame
void AEYS_Fridge_Slot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

