// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EYS_WorldSubsystem.generated.h"

class AEYS_GuestCharacter;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_WorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	

public:
	// NPC spawn API
	UFUNCTION(BlueprintCallable, Category = "EYS|NPC")
	AEYS_GuestCharacter* RequestSpawnNPC(TSubclassOf<AEYS_GuestCharacter> NPCClass, const FTransform& SpawnTransform);
	void SetMentalSlate( const float ReduceValue);

private:
	// ?stersen aktif NPC listesi
	UPROPERTY()
	TArray<TObjectPtr<AEYS_GuestCharacter>> ActiveNPCs;
};
