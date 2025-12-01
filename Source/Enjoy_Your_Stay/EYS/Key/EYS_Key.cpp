// Fill out your copyright notice in the Description page of Project Settings.
#include "EYS/Key/EYS_Key.h"
#include "EYS/EYS_MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Key/EYS_KeyHolder.h"



// Sets default values
AEYS_Key::AEYS_Key()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	
}

// Called when the game starts or when spawned
void AEYS_Key::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_Key::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_Key::Interact(AEYS_MyCharacter* myPlayer)
{
	if (myPlayer->bIsKeyMode)
	{
		AEYS_KeyHolder* KeyHolder = Cast<AEYS_KeyHolder>(
			UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_KeyHolder::StaticClass())
		);

		if (KeyHolder)
		{
			myPlayer->bIsKeyMode = false;
			KeyHolder->SetPose();   
			KeyHolder->LastRoomNum = RoomNum;
			
		}
		myPlayer->bIsHaveKey = true;
		myPlayer->RoomLock = RoomLocation;
		myPlayer->PoseNum = 2;
	
		Destroy();
		
	}
	
}

void AEYS_Key::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	Interact(myPlayer);
	
}