// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS_Types.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None       UMETA(DisplayName = "None"),
	Food      UMETA(DisplayName = "Food"),
	Drink   UMETA(DisplayName = "Drink"),
};
UENUM(BlueprintType)
enum class EFoodType : uint8
{
	//Food
	None       UMETA(DisplayName = "None", Category = "Food"),
	Kasha      UMETA(DisplayName = "Kasha", Category = "Food"),
	Vareniki   UMETA(DisplayName = "Vareniki" ,Category = "Food"),
	Pirozhki   UMETA(DisplayName = "Pirozhki" ,Category = "Food"),
	Medovik    UMETA(DisplayName = "Medovik" ,Category = "Food"),
	//Drink
	Kefir_Strawberry    UMETA(DisplayName = "Strawberry Kefir",Category = "Drink"),
	Kefir_Blueberry     UMETA(DisplayName = "Blueberry Kefir", Category = "Drink"),
	Kefir_Banana         UMETA(DisplayName = "Banana Kefir", Category = "Drink"),
	Kefir_Peach         UMETA(DisplayName = "Peach Kefir", Category = "Drink"),

	Count             UMETA(Hidden)
};
