// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_HorrorSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "EYS/Horror/BabaYaga/EYS_BabaYaga.h"
#include "EYS/Horror/BabaYaga/EYS_BabaYagaAIController.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/Interactable Actor/EYS_Boiler.h"
#include "EYS/Game Managers/EYS_MissionSubsystem.h"
#include "EYS/Interactable Actor/TargetPoints/EYS_DirtTarget.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

UEYS_HorrorSubsystem::UEYS_HorrorSubsystem()
{
	SpawnedMissionBabaYaga = nullptr;
	CurrentSpawnChance = 0.0f;
	bIsMissionActive = false;
	SpawnedMainBabaYaga = nullptr;
	BoundBoiler = nullptr;
	BabaYagaClass = nullptr;
}

void UEYS_HorrorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	

}
void UEYS_HorrorSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	UGameInstance* GI = InWorld.GetGameInstance();
	if (!GI) return;

	UEYS_TutorialSubsystem* TS = GI->GetSubsystem<UEYS_TutorialSubsystem>();
	if (!TS) return;

	ActivateHorrorSystem(TS->bIsTutorialFinished);
}

void UEYS_HorrorSubsystem::Deinitialize()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HorrorTickTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(DataFetchTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(MainLifespanTimerHandle);
	}
	Super::Deinitialize();
}
void UEYS_HorrorSubsystem::ActivateHorrorSystem(bool bIsActivate)
{
	UWorld* World = GetWorld();
	if (!World) return;
	
	bIsSysemActive = bIsActivate;

	if (bIsActivate)
	{
		if (!World->GetTimerManager().IsTimerActive(DataFetchTimerHandle))
		{
			World->GetTimerManager().SetTimer(DataFetchTimerHandle, this, &UEYS_HorrorSubsystem::FetchAndProcessMainHotelData, 3.0f, true);
		}
	}
	else
	{
		World->GetTimerManager().ClearTimer(DataFetchTimerHandle);
	}

}

void UEYS_HorrorSubsystem::OnMissionEnabled()
{
	
	UWorld* World = GetWorld();
	UGameplayStatics::SetGlobalTimeDilation(World, 0.25f);
	if (!bIsSysemActive) return;
	if (SpawnedMissionBabaYaga) return;
	bIsMissionActive = true;
	CurrentSpawnChance = FMath::Clamp(CurrentSpawnChance + 15.0f, 0.0f, 100.0f);
	if (!GetWorld()->GetTimerManager().IsTimerActive(HorrorTickTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(HorrorTickTimerHandle, this, &UEYS_HorrorSubsystem::CheckHorrorRoll, 1.0f, true);
	}
}

void UEYS_HorrorSubsystem::CheckHorrorRoll()
{
if (SpawnedMissionBabaYaga || !BabaYagaClass || !bIsMissionActive)
	{
		if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(HorrorTickTimerHandle);
		return;
	}

	float DiceRoll = FMath::RandRange(0.0f, 100.0f);


	if (DiceRoll <= CurrentSpawnChance)
	{
		if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(HorrorTickTimerHandle);
		SpawnBabaYaga();
	}
}

void UEYS_HorrorSubsystem::SpawnBabaYaga()
{
	UWorld* World = GetWorld();
	if (!World) return;


	if (!BabaYagaClass)
	{

		return;
	}

	AEYS_MyCharacter* PlayerChar = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));

	if (!PlayerChar) return;

	UGameplayStatics::SetGlobalTimeDilation(World, 0.25f);

	FVector PlayerLoc = PlayerChar->GetActorLocation();
	FVector PlayerForward = PlayerChar->GetActorForwardVector();
	FVector PlayerRight = PlayerChar->GetActorRightVector();

	FVector SpawnBaseLocation = PlayerLoc + (PlayerForward * 1000.0f);
	float RandomSideOffset = FMath::RandRange(-250.0f, 250.0f);
	FVector CalculatedLocation = SpawnBaseLocation + (PlayerRight * RandomSideOffset);
	CalculatedLocation.Z = PlayerLoc.Z;

	FVector FinalSpawnLocation = CalculatedLocation;

	if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World))
	{
		FNavLocation ProjectedLocation;
		if (NavSys->ProjectPointToNavigation(CalculatedLocation, ProjectedLocation, FVector(500.0f, 500.0f, 500.0f)))
		{
			FinalSpawnLocation = ProjectedLocation.Location;
		}
	}

	FRotator SpawnRotation = (PlayerLoc - FinalSpawnLocation).Rotation();
	SpawnRotation.Pitch = 0.0f;
	SpawnRotation.Roll = 0.0f;

	FActorSpawnParameters SpawnParams;

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEYS_BabaYaga* SpawnedBabaYaga = World->SpawnActor<AEYS_BabaYaga>(BabaYagaClass, FinalSpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedBabaYaga)
	{
		SpawnedBabaYaga->CustomTimeDilation = 4.0f;
		SpawnedMissionBabaYaga = SpawnedBabaYaga;
		SpawnedBabaYaga->SpawnDefaultController();

		if (AEYS_BabaYagaAIController* AICon = Cast<AEYS_BabaYagaAIController>(SpawnedBabaYaga->GetController()))
		{
			AICon->SetTargetPlayer(PlayerChar);
			SpawnedBabaYaga->SetMovementState(EBabaYagaState::Chasing);
			AICon->MoveToActor(PlayerChar, 20.0f);
			SpawnedBabaYaga->PlayBabaYagaSound(2);
		}
	}
}

void UEYS_HorrorSubsystem::OnMissionDisabled()
{
	bIsMissionActive = false;

	GetWorld()->GetTimerManager().ClearTimer(HorrorTickTimerHandle);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);

	if (SpawnedMissionBabaYaga)
	{

		if (SpawnedMissionBabaYaga->GetMovementState() == EBabaYagaState::Catch) return;

		AController* AICon = SpawnedMissionBabaYaga->GetController();
		if (AICon) AICon->Destroy();

		SpawnedMissionBabaYaga->Destroy();
		SpawnedMissionBabaYaga = nullptr;

		CurrentSpawnChance = 0.0f;
	
	}
}




void UEYS_HorrorSubsystem::FetchAndProcessMainHotelData()
{

	UWorld* World = GetWorld();
	if (!World || !BabaYagaClass || SpawnedMainBabaYaga) return;
	if (!World->GetTimerManager().IsTimerActive(DataFetchTimerHandle))
	{
		World->GetTimerManager().SetTimer(DataFetchTimerHandle, this, &UEYS_HorrorSubsystem::FetchAndProcessMainHotelData, 3.0f, true);
	}
	float BoilerFuel = 100.0f;
	float HotelRating = 100.0f;
	if (BoundBoiler)
	{
		BoilerFuel = BoundBoiler->GetBoilerFuel();
	}
	if (UGameInstance* GameInstance = World->GetGameInstance())
	{
		if (UEYS_MissionSubsystem* MissionSys = GameInstance->GetSubsystem<UEYS_MissionSubsystem>())
		{
			HotelRating = MissionSys->GetHotelRating();
		}
	}
	
	if (BoilerFuel >= 40.0f)
	{
		return;
	}

	float FuelUrgencyWeight = (40.0f - BoilerFuel) / 40.0f;

	float HotelRatingWeight = FMath::Clamp(HotelRating / 100.0f, 0.0f, 1.0f);

	float MainSpawnChance = (FuelUrgencyWeight + HotelRatingWeight) * 0.5f * 20.0f;

	float DangerDiceRoll = FMath::FRandRange(0.0f, 100.0f);

	
	//GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Purple, FString::Printf(TEXT("Yakıt Baskısı: %.2f | Reyting Baskısı: %.2f | Toplam Şans: %%%.2f | Atılan Zar: %.2f"), FuelUrgencyWeight, HotelRatingWeight, MainSpawnChance, DangerDiceRoll));

	if (DangerDiceRoll <= MainSpawnChance)
	{
		PlayMainSpawnHeraldSound();
		World->GetTimerManager().ClearTimer(DataFetchTimerHandle);
		
	}
	
}

void UEYS_HorrorSubsystem::PlayMainSpawnHeraldSound()
{
	UWorld* World = GetWorld();

	if (!World) return;

	if (SpawnSound)
	{
		if (AEYS_MyCharacter* PlayerChar = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0)))
		{
			FVector SoundLoc = PlayerChar->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(World, SpawnSound, SoundLoc);
		}
	}
	
	
	float HeraldSoundDuration = 10.0f;
	World->GetTimerManager().SetTimer(MainLifespanTimerHandle, this, &UEYS_HorrorSubsystem::SpawnMainBabaYaga, HeraldSoundDuration, false);
}


void UEYS_HorrorSubsystem::SetBoilerReference(AEYS_Boiler* InBoiler)
{
	BoundBoiler = InBoiler;
}

void UEYS_HorrorSubsystem::SetHorrorTargets(const TArray<AEYS_DirtTarget*>& InTargets)
{
	
	HorrorTargets = InTargets;
}

void UEYS_HorrorSubsystem::SpawnMainBabaYaga()
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (!BabaYagaClass)
	{
		World->GetTimerManager().SetTimer(DataFetchTimerHandle, this, &UEYS_HorrorSubsystem::FetchAndProcessMainHotelData, 3.0f, true);
		return;
	}
	if (HorrorTargets.Num() <= 0)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(World, AEYS_DirtTarget::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0)
		{
			for (AActor* Actor : FoundActors)
			{
				if (AEYS_DirtTarget* Target = Cast<AEYS_DirtTarget>(Actor))
				{
					if (Target->SurfaceType == ESurfaceType::Horror)
					{
						HorrorTargets.Add(Target);
					}
				}
			}

		}
	}
	if (HorrorTargets.Num() <= 0)
	{
		World->GetTimerManager().SetTimer(DataFetchTimerHandle, this, &UEYS_HorrorSubsystem::FetchAndProcessMainHotelData, 3.0f, true);
		return;
	}
	AEYS_DirtTarget* ChosenPoint = HorrorTargets[FMath::RandRange(0, HorrorTargets.Num() - 1)];
	if (!ChosenPoint)
	{
		World->GetTimerManager().SetTimer(DataFetchTimerHandle, this, &UEYS_HorrorSubsystem::FetchAndProcessMainHotelData, 3.0f, true);
		return;
	}

	FVector SpawnLocation = ChosenPoint->GetActorLocation();
	FRotator SpawnRotation = ChosenPoint->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnedMainBabaYaga = World->SpawnActor<AEYS_BabaYaga>(BabaYagaClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedMainBabaYaga)
	{
		SpawnedMainBabaYaga->SpawnDefaultController();

		if (AEYS_BabaYagaAIController* AICon = Cast<AEYS_BabaYagaAIController>(SpawnedMainBabaYaga->GetController()))
		{
			
			SpawnedMainBabaYaga->SetMovementState(EBabaYagaState::Patrolling);
		
		}

		float LifeSpanValue = FMath::FRandRange(60.0f, 120.0f);
		World->GetTimerManager().SetTimer(MainLifespanTimerHandle, this, &UEYS_HorrorSubsystem::DestroyMainBabaYaga, LifeSpanValue, false);
	}
}

void UEYS_HorrorSubsystem::DestroyMainBabaYaga()
{
	if (SpawnedMainBabaYaga)
	{
	
		if (SpawnedMainBabaYaga->GetMovementState() == EBabaYagaState::Catch) return;

		AController* AICon = SpawnedMainBabaYaga->GetController();
		if (AICon) AICon->Destroy();

		SpawnedMainBabaYaga->Destroy();
		SpawnedMainBabaYaga = nullptr;
		GetWorld()->GetTimerManager().SetTimer(DataFetchTimerHandle, this, &UEYS_HorrorSubsystem::FetchAndProcessMainHotelData, 180.0f, false);
		
	}
}

