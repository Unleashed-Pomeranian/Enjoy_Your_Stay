// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_GuestSpawner.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/NPC/EYS_GuestCharacter.h"


// Sets default values
AEYS_GuestSpawner::AEYS_GuestSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEYS_GuestSpawner::BeginPlay()
{
	Super::BeginPlay();
	EmptyRooms = 4;

	UKismetSystemLibrary::K2_SetTimer(this, "SpawnGuest", 5.0f, false);

	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
	if (!Director) return; 
	Director->LobyLocation = LobyLoc;
}

void AEYS_GuestSpawner::SpawnGuest()
{
	
	if (EmptyRooms > 0)
	{
		UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
		if (!Director) return;
		if (GuestClass)
			Director->RequestSpawnNPC(GuestClass, GetActorTransform());
		EmptyRooms -= 1;
		 int32 RandomIndex = FMath::RandRange(55,120);
		UKismetSystemLibrary::K2_SetTimer(this, "SpawnGuest", RandomIndex, false);
	}

}


// Called every frame
void AEYS_GuestSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_GuestSpawner::SetEmptyRoom()
{
	EmptyRooms++;
	if (EmptyRooms > 0)
	{
		int32 RandomIndex = FMath::RandRange(55, 120);
		UKismetSystemLibrary::K2_SetTimer(this, "SpawnGuest", RandomIndex, false);
	}
}

