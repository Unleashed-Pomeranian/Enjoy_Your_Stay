// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS_WorldSubsystem.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "EYS/NPC/EYS_GuestCar.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Game Managers/EYS_MySunMoonDaySequenceActor.h"
#include "EYS/NPC/EYS_VehicleSplinePath.h"
#include "EYS/NPC/EYS_Chair.h"
#include "EYS/Game Managers/EYS_MissionSpawner.h"
#include "EngineUtils.h"

AEYS_GuestCharacter* UEYS_WorldSubsystem::RequestSpawnNPC(TSubclassOf<AEYS_GuestCharacter> NPCClass, const FTransform& SpawnTransform, USkeletalMesh* GuestSkel)
{
	if (!GetWorld())
	{
		
		return nullptr;
	}

	if (!*NPCClass)
	{
		return nullptr;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	Params.Owner = nullptr;
	Params.Instigator = nullptr;

	AEYS_GuestCharacter* Spawned = GetWorld()->SpawnActor<AEYS_GuestCharacter>(NPCClass,SpawnTransform,Params);

	if (!Spawned)
	{
		return nullptr;
	}

	ActiveNPCs.Add(Spawned);
	if (Spawned)
	{
		Spawned->SetGuestMesh(GuestSkel);
		Spawned->MoveTo(LobyLocation, 10);
		Spawned->DiningHallLocation = DiningHallLocation;
		Spawned->LobyLocation = LobyLocation;
	}

	if (AEYS_MySunMoonDaySequenceActor* DayActor = Cast<AEYS_MySunMoonDaySequenceActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MySunMoonDaySequenceActor::StaticClass())))
	{
		Spawned->CheckOutDay = DayActor->DayNum+1;
		Spawned->CheckOutTime = DayActor->GetTimeOfDay();
	}

	return Spawned;
}



void UEYS_WorldSubsystem::RequestSpawnGuestCar(TSubclassOf<AEYS_GuestCar> GuestCarClass, const FTransform& SpawnTransform)
{
	if (!GetWorld())
	{

		return;
	}

	if (!*GuestCarClass)
	{
		return;
	}
	AEYS_VehicleSplinePath* FoundPath = nullptr;
	for (AEYS_VehicleSplinePath* Path : AllParkingEntries)
	{
		if (Path && !Path->bIsOccupied) 
		{
			FoundPath = Path;
			break;
		}
	}
	if (!FoundPath)
	{
		return;
	}
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	Params.Owner = nullptr;
	Params.Instigator = nullptr;

	AEYS_GuestCar* Spawned = GetWorld()->SpawnActor<AEYS_GuestCar>(GuestCarClass, SpawnTransform, Params);
	
	if (Spawned)
	{
		
		
		FTimerHandle InitHandle;
		GetWorld()->GetTimerManager().SetTimer(InitHandle, [Spawned, FoundPath]()
			{
				if (IsValid(Spawned))
				{
					Spawned->InitializeCar(FoundPath);
				}
			}, 0.1f, false);
		FoundPath->bIsOccupied = true;
	}
	

}


void UEYS_WorldSubsystem::SetMentalSlate(const float ReduceValue)
{
	for (int32 i = ActiveNPCs.Num() - 1; i >= 0; --i)
	{
		if (!ActiveNPCs[i])
		{
			ActiveNPCs.RemoveAtSwap(i);
			continue;
		}
		else
		{
			ActiveNPCs[i]->MentalSlateValue = FMath::Clamp(ActiveNPCs[i]->MentalSlateValue -= ReduceValue, 0, 100);
		}

	}
}



EFoodType UEYS_WorldSubsystem::GetRandomType(EItemType WantedItemType)
{
	if (!FoodDatabase)
	{
		return EFoodType::None;
	}

	TArray<FFoodDatabase*> Rows;
	FoodDatabase->GetAllRows<FFoodDatabase>(TEXT("Food Database"), Rows);
	TArray<EFoodType> AvailableTypes;

	for (const FFoodDatabase* Row : Rows)
	{
		if (!Row)
		{
			continue;
		}

		if (!Row->IsActivated)
		{
			continue;
		}

		if (Row->FoodType == EFoodType::None)
		{
			continue;
		}

		if (Row->ItemType == WantedItemType)
		{
			AvailableTypes.Add(Row->FoodType);
		}
	}

	if (AvailableTypes.Num() <= 0)
	{
		return EFoodType::None;
	}
	return AvailableTypes[FMath::RandRange(0, AvailableTypes.Num() - 1)];

}
AEYS_Chair* UEYS_WorldSubsystem::GetAvailableChair()
{
	TArray<AEYS_Chair*> AvailableChairs;

	for (TActorIterator<AEYS_Chair> It(GetWorld()); It; ++It)
	{
		AEYS_Chair* CurrentChair = *It;
		if (CurrentChair && !CurrentChair->bIsOccupied)
		{
			AvailableChairs.Add(CurrentChair);
		}
	}

	if (AvailableChairs.Num() == 0)
	{
		return nullptr;
	}

	int32 RandomIdx = FMath::RandRange(0, AvailableChairs.Num() - 1);

	return AvailableChairs[RandomIdx];
}

void UEYS_WorldSubsystem::CheckOutPlayer(int32 DayValue, float TimeValue)
{



	for (int32 i = ActiveNPCs.Num() - 1; i >= 0; --i)
	{
		if ((ActiveNPCs[i]->CheckOutDay == DayValue) && (ActiveNPCs[i]->CheckOutTime <= TimeValue) && !(ActiveNPCs[i]->bIsCheckOut))
		{
			ActiveNPCs[i]->MoveTo(LobyLocation, 50);
			ActiveNPCs[i]->bIsCheckOut = true;
			ActiveNPCs[i]->CurrentStatus = EGuestStatus::GoToCheckOut;
			SpawnCheckOutDirt(ActiveNPCs[i]->GuestRoomID);
			ActiveNPCs.RemoveAtSwap(i);

		}

	}

}
void UEYS_WorldSubsystem::SpawnCheckOutDirt(ERoomID TargetRoom)
{
	if (!TargetMissionSpawner) return;

		
		for (int i = 0; i < 2; i++)
		{
		
			TargetMissionSpawner->SpawnMissionActor(ESurfaceType::Floor, TargetRoom,false);
			TargetMissionSpawner->SpawnMissionActor(ESurfaceType::Wall, TargetRoom,false);
		}
	
}
/*if (!bIsAnyGuestCorrupted)
	{
		for (int32 i = ActiveNPCs.Num() - 1; i >= 0; --i)
		{
			if (!ActiveNPCs[i])
			{
				ActiveNPCs.RemoveAtSwap(i);
				continue;
			}
			else
			{


				if (ActiveNPCs[i]->MentalSlateValue <= 0.0f)
				{

					{
						ActiveNPCs[i]->CorruptTheGuest();


					}

				}


			}

		}
    }
	
}
*/