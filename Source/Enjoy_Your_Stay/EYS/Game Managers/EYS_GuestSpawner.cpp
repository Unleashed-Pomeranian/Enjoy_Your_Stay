// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_GuestSpawner.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "EYS/NPC/EYS_GuestCar.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/NPC/EYS_VehicleSplinePath.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"
// Sets default values
AEYS_GuestSpawner::AEYS_GuestSpawner()
{

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
		Director->DiningHallLocation = DiningHallLoc;
		Director->AllParkingEntries = ParkingEntries;

		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			if (TS->bIsTutorialFinished || TS->CurrentPhase == ETutorialPhase::ThirdPhase)
			{
				SpawnGuestTimer();
			}

			else if (TS->CurrentPhase == ETutorialPhase::FirstPhase|| TS->CurrentPhase == ETutorialPhase::SecondPhase)
			{
				TS->OnThirdPhaseEnd.AddDynamic(this, &AEYS_GuestSpawner::SpawnGuestTimer);
			}
	
			else
			{
				TS->OnFirstPhaseEnd.AddDynamic(this, &AEYS_GuestSpawner::SpawnGuest);
				TS->OnThirdPhaseEnd.AddDynamic(this, &AEYS_GuestSpawner::SpawnGuestTimer);
			}
		}


}

void AEYS_GuestSpawner::SpawnGuest()
{
	
	if (!bCanSpawnGuest) return;

	if (EmptyRooms > 0)
	{
		UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
		if (!Director) return;
		if (GuestCarClass)
		{
			Director->RequestSpawnGuestCar(GuestCarClass, GetActorTransform());

			EmptyRooms--;
		}

	
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(GuestTimerHandle);
	}

}

void AEYS_GuestSpawner::SpawnGuestTimer()
{
	SpawnGuest();
	float CurrentMultiplier = 1.0f;
	if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		CurrentMultiplier = UpgradeSys->GetCustomerArrivalRateMultiplier();
	}
	float RandomDelay = FMath::RandRange(120.0f, 180.0f);
	RandomDelay *= CurrentMultiplier;
	GetWorld()->GetTimerManager().SetTimer(GuestTimerHandle, this, &AEYS_GuestSpawner::SpawnGuestTimer, RandomDelay, false);

}

void AEYS_GuestSpawner::StartGuestSpawning()
{
	GetWorld()->GetTimerManager().SetTimer(GuestTimerHandle, this, &AEYS_GuestSpawner::SpawnGuestTimer, 30.0f, false);
}

void AEYS_GuestSpawner::SetEmptyRoom()
{
	EmptyRooms++;
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		if (!(TS->bIsTutorialFinished) || TS->CurrentPhase != ETutorialPhase::ThirdPhase)
		{
			return;
		}
	}
	if (!GetWorld()->GetTimerManager().IsTimerActive(GuestTimerHandle))
	{
		float CurrentMultiplier = 1.0f;
		if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
		{
			CurrentMultiplier = UpgradeSys->GetCustomerArrivalRateMultiplier();
		}
		float RandomDelay = FMath::RandRange(120.0f, 180.0f);
		RandomDelay *= CurrentMultiplier;
		GetWorld()->GetTimerManager().SetTimer(GuestTimerHandle, this, &AEYS_GuestSpawner::SpawnGuestTimer, RandomDelay, false);
	}
}


