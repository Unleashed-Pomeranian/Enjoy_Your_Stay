// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EYS_HorrorSubsystem.generated.h"


class AEYS_BabaYaga;
class AEYS_Boiler; 
class AEYS_DirtTarget;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_HorrorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	UEYS_HorrorSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;

	
	void OnMissionEnabled();


	void OnMissionDisabled();
	UFUNCTION(BlueprintCallable, Category = "EYS | Horror ")
	void ActivateHorrorSystem(bool bIsActivate);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EYS | Horror")
	TSubclassOf<AEYS_BabaYaga> BabaYagaClass;

private:
	FTimerHandle HorrorTickTimerHandle;
	FTimerHandle DataFetchTimerHandle;
	FTimerHandle MainLifespanTimerHandle;

	UPROPERTY()
	AEYS_BabaYaga* SpawnedMissionBabaYaga;
	UPROPERTY()
	AEYS_BabaYaga* SpawnedMainBabaYaga;

	float CurrentSpawnChance;
	bool bIsMissionActive;
	bool bIsSysemActive=false;

	void CheckHorrorRoll();
	void SpawnBabaYaga();


	/*----Main Baba Yaga-------*/
protected:
	UPROPERTY()
	AEYS_Boiler* BoundBoiler;
	UPROPERTY()
	TArray<AEYS_DirtTarget*> HorrorTargets;
	
	UFUNCTION(BlueprintCallable, Category = "EYS | Horror Config")
	void FetchAndProcessMainHotelData();
	void PlayMainSpawnHeraldSound();
	void SpawnMainBabaYaga();
	void DestroyMainBabaYaga();

public:
	void SetBoilerReference(AEYS_Boiler* InBoiler);
	UFUNCTION(BlueprintCallable, Category = "EYS | Horror | Main")
	void SetHorrorTargets(const TArray<AEYS_DirtTarget*>& InTargets);
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "EYS | Horror | Sound")
	class USoundBase* SpawnSound;
};
