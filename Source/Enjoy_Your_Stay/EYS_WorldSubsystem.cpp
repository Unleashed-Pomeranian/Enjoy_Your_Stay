// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS_WorldSubsystem.h"
#include "EYS/NPC/EYS_GuestCharacter.h"

AEYS_GuestCharacter* UEYS_WorldSubsystem::RequestSpawnNPC(TSubclassOf<AEYS_GuestCharacter> NPCClass, const FTransform& SpawnTransform)
{
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("HotelDirectorSubsystem: GetWorld() is null"));
		return nullptr;
	}

	if (!*NPCClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("HotelDirectorSubsystem: NPCClass is null"));
		return nullptr;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	Params.Owner = nullptr; // istersen owner set edersin
	Params.Instigator = nullptr;

	AEYS_GuestCharacter* Spawned = GetWorld()->SpawnActor<AEYS_GuestCharacter>(NPCClass,SpawnTransform,Params);

	if (!Spawned)
	{
		UE_LOG(LogTemp, Error, TEXT("HotelDirectorSubsystem: SpawnActor failed"));
		return nullptr;
	}

	ActiveNPCs.Add(Spawned);



	return Spawned;
}

void UEYS_WorldSubsystem::SetMentalSlate( const float ReduceValue)
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
			ActiveNPCs[i]->MentalSlateValue -= ReduceValue;
		}

	}

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
				ActiveNPCs[i]->CorruptTheGuest();
				ActiveNPCs.RemoveAtSwap(i);
			}
		}

	}
}
