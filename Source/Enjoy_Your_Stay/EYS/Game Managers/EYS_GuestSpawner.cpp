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
	Rooms = 4;
	UKismetSystemLibrary::K2_SetTimer(this, "SpawnGuest", 10.0f, false);
}

void AEYS_GuestSpawner::SpawnGuest()
{
	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
	if (!Director) return;

	if(GuestClass)
	Director->RequestSpawnNPC(GuestClass, GetActorTransform());
}

// Called every frame
void AEYS_GuestSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

