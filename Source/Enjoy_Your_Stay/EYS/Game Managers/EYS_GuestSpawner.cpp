// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_GuestSpawner.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

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

	

	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
	if (!Director) return; 
	Director->LobyLocation = LobyLoc;
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->OnFirstPhaseEnd.AddDynamic(this, &AEYS_GuestSpawner::StartGuestSpawning);
	}
}

void AEYS_GuestSpawner::SpawnGuest()
{
	
	if (EmptyRooms > 0)
	{
		UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
		if (!Director) return;
		if (GuestClass)
			Director->RequestSpawnNPC(GuestClass, GetActorTransform());
		EmptyRooms --;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(GuestTimerHandle);
	}

}

void AEYS_GuestSpawner::SpawnGuestTimer()
{
	SpawnGuest();
	float RandomDelay = FMath::RandRange(120, 180);
	GetWorld()->GetTimerManager().SetTimer(GuestTimerHandle, this, &AEYS_GuestSpawner::SpawnGuestTimer, RandomDelay, false);

}

void AEYS_GuestSpawner::StartGuestSpawning()
{
	GetWorld()->GetTimerManager().SetTimer(GuestTimerHandle, this, &AEYS_GuestSpawner::SpawnGuestTimer, 100.0f, false);
}




void AEYS_GuestSpawner::SetEmptyRoom()
{
	EmptyRooms++;
	if (EmptyRooms > 0)
	{
		float RandomDelay = FMath::RandRange(120, 180);
		GetWorld()->GetTimerManager().SetTimer(GuestTimerHandle, this, &AEYS_GuestSpawner::SpawnGuestTimer, RandomDelay, false);
	}
}

