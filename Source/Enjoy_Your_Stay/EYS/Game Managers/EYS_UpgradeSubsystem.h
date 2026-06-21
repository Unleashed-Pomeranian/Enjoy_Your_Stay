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
	//Forceinlines
	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Boiler")
	FORCEINLINE float GetBoilerFuelConsumptionMultiplier() const { return BoilerFuelConsumptionMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Boiler")
	FORCEINLINE float GetPipeFailureIntervalMultiplier() const { return PipeFailureIntervalMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Generator")
	FORCEINLINE float GetGeneratorFuelConsumptionMultiplier() const { return GeneratorFuelConsumptionMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Generator")
	FORCEINLINE float GetGeneratorFailureIntervalMultiplier() const { return GeneratorFailureIntervalMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Guest")
	FORCEINLINE float GetCustomerArrivalRateMultiplier() const { return CustomerArrivalRateMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Guest")
	FORCEINLINE float GetNPCMentalResistanceMultiplier() const { return NPCMentalResistanceMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Guest")
	FORCEINLINE float GetCustomerMoneyMultiplier() const { return CustomerMoneyMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Character")
	FORCEINLINE float GetStaminaConsumptionMultiplier() const { return StaminaConsumptionMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Equipment")
	FORCEINLINE float GetEquipmentUseTimeMultiplier() const { return EquipmentUseTimeMultiplier; }

	UFUNCTION(BlueprintPure, Category = "EYS | Upgrade | Cleaning")
	FORCEINLINE float GetDirtAccumulationMultiplier() const { return DirtAccumulationMultiplier; }
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
