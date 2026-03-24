// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"

void UEYS_UpgradeSubsystem::ApplyGeneratorUpgrade(int32 UpgradeIndex)
{
	switch (UpgradeIndex)
	{
	case 0:
		GeneratorFuelConsumptionMultiplier *= 0.85f;
		GeneratorUpgradeLevel = 1;
		break;

	case 1:
		GeneratorFailureIntervalMultiplier *= 0.90f;
		GeneratorUpgradeLevel = 2;
		break;

	case 2:
	{
		GeneratorFuelConsumptionMultiplier *= 0.85f;
		GeneratorFailureIntervalMultiplier *= 0.90f;
		GeneratorUpgradeLevel = 3;
		break;
	}

	default:
		break;
	}
}

void UEYS_UpgradeSubsystem::ApplyBoilerUpgrade(int32 UpgradeIndex)
{
	switch (UpgradeIndex)
	{
	case 0:
		BoilerFuelConsumptionMultiplier *= 0.95f;
		BoilerUpgradeLevel = 1;
		break;

	case 1:
		PipeFailureIntervalMultiplier *= 1.1f;
		BoilerUpgradeLevel = 2;
		break;

	case 2:
	{
		BoilerFuelConsumptionMultiplier *= 0.9f;
		PipeFailureIntervalMultiplier *= 1.1f;
		BoilerUpgradeLevel = 3;
		break;
	}
	default:
		break;
	}
}

void UEYS_UpgradeSubsystem::ApplyGuestUpgrade(int32 UpgradeIndex)
{
	switch (UpgradeIndex)
	{
	case 0:
	{
		CustomerArrivalRateMultiplier *= 0.85f;
		GuestUpgradeLevel = 1;
		break;

	}

	case 1:
	{
		NPCMentalResistanceMultiplier *= 0.9f;
		GuestUpgradeLevel = 2;
		break;

	}

	case 2:
	{
		CustomerMoneyMultiplier *= 1.1f;
		GuestUpgradeLevel = 3;
		break;

	}


		
	default:
		break;
	}

}

void UEYS_UpgradeSubsystem::ApplySingleUpgrade(int32 UpgradeIndex)
{
	switch (UpgradeIndex)
	{
	case 0:
	{
		StaminaConsumptionMultiplier *= 0.85f;
		bMyCharacterUpgradePurchased = true;
		break;
	}
	case 1:
	{
		EquipmentUseTimeMultiplier *= 0.80f;
		bEquipmentUpgradePurchased = true;
		break;
	}
	case 2:
	{
		DirtAccumulationMultiplier *= 0.80f;
		bDoormatUpgradePurchased = true;
		break;
	}
	default:
		break;
	}
}
