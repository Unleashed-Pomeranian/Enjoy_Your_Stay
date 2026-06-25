// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Types.h"
#include "EYS_WorldSubsystem.generated.h"

class AEYS_LightBase;
class AEYS_GuestCharacter;
class AEYS_GuestCar;
class AEYS_VehicleSplinePath;
class AEYS_Chair;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_WorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	

public:
	// NPC spawn API
	UFUNCTION(BlueprintCallable, Category = "EYS|NPC")
	AEYS_GuestCharacter* RequestSpawnNPC(TSubclassOf<AEYS_GuestCharacter> NPCClass, const FTransform& SpawnTransform, USkeletalMesh* GuestSkel);

	AEYS_Chair* GetAvailableChair();
	void  RequestSpawnGuestCar(TSubclassOf<AEYS_GuestCar> GuestCarClass, const FTransform& SpawnTransform);
	void SetMentalSlate( const float ReduceValue);
	void CheckOutPlayer(int32 DayValue,float TimeValue);
	void SpawnCheckOutDirt(ERoomID TargetRoom);

	UPROPERTY(EditInstanceOnly, Category = "Parking Setup")
	TArray<class AEYS_VehicleSplinePath*> AllParkingEntries;

	UPROPERTY() class AEYS_MissionSpawner* TargetMissionSpawner;
private:
	
	UPROPERTY()
	TArray<TObjectPtr<AEYS_GuestCharacter>> ActiveNPCs;

public:
	UPROPERTY() bool bIsAnyGuestCorrupted = false;
	UPROPERTY() FVector LobyLocation;
	UPROPERTY() FVector DiningHallLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float Hour;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* FoodDatabase = nullptr;

	UFUNCTION() EFoodType GetRandomType(EItemType WantedItemType);

	UFUNCTION() int32 GetFoodPrice(EFoodType WantedItemType);

	UFUNCTION(BlueprintCallable, Category = "EYS|Food System")
	void CompleteTutorial() { FoodStage = 1; }
protected:
	UPROPERTY()
	int32 FoodStage = 0;


	/*--------Light Codes-------------*/
public:
	UFUNCTION(BlueprintCallable, Category = "EYS | Light")
	void RegisterSingleLight(AEYS_LightBase* NewLight);

	UFUNCTION(BlueprintCallable, Category = "EYS | Light")
	void ToggleAllOtelLights(bool bActivate);

private:
	UPROPERTY()
	TArray<TObjectPtr<AEYS_LightBase>> AllOtelLights;
};
