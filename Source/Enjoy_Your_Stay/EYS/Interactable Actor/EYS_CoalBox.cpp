// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_CoalBox.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"

// Sets default values
AEYS_CoalBox::AEYS_CoalBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh_Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Box"));
	StaticMesh_Box->SetupAttachment(DefaultSceneRoot);
	StaticMesh_Coal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Coal"));
	StaticMesh_Coal->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_CoalBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_CoalBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AEYS_CoalBox::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	PC->SetInteractionWidget("[E] Take");
}

void  AEYS_CoalBox::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	
	CoalAmount = FMath::Clamp(CoalAmount + 20, 0, 100);
	int32 MeshValue = CoalAmount / 20;
	if (CoalMeshes[MeshValue])
	{
		StaticMesh_Coal->SetStaticMesh(CoalMeshes[MeshValue]);
	}

}
void  AEYS_CoalBox::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	if (Value == 6)
	{
		CoalAmount = FMath::Clamp(CoalAmount - 20, 0, 100);
		int32 MeshValue = CoalAmount / 20;

		if (CoalMeshes[MeshValue])
		{
			StaticMesh_Coal->SetStaticMesh(CoalMeshes[MeshValue]);
		}
	}
}
void  AEYS_CoalBox::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void AEYS_CoalBox::FillingCoal()
{
	CoalAmount = FMath::Clamp(CoalAmount + 20, 0, 100);
}
void AEYS_CoalBox::DrainingCoal()
{
	CoalAmount = FMath::Clamp(CoalAmount - 20, 0, 100);
}