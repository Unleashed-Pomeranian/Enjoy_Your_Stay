// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EYS_UpgradeSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_UpgradeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	



protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float BoilerFuelConsumptionMultiplier = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PipeFailureIntervalMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GeneratorFuelConsumptionMultiplier = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GeneratorFailureIntervalMultiplier = 1.0f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CustomerArrivalRateMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NPCMentalResistanceMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CustomerMoneyMultiplier = 1.0f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float StaminaConsumptionMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float EquipmentUseTimeMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DirtAccumulationMultiplier = 1.0f;
	//Levels

	
	

public:
	//Functions
	UFUNCTION() void ApplyGeneratorUpgrade(int32 UpgradeIndex);
	UFUNCTION() void ApplyBoilerUpgrade(int32 UpgradeIndex);
	UFUNCTION() void ApplyGuestUpgrade(int32 UpgradeIndex);
	UFUNCTION() void ApplySingleUpgrade(int32 UpgradeIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 GeneratorUpgradeLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 BoilerUpgradeLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 GuestUpgradeLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bMyCharacterUpgradePurchased = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bEquipmentUpgradePurchased = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDoormatUpgradePurchased = false;
};
