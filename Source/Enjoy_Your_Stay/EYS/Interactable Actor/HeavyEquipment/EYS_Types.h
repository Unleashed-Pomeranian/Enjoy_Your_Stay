// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS_Types.generated.h"

UENUM(BlueprintType)
enum class EFoodType : uint8
{
	Kasha      UMETA(DisplayName = "Kasha"),
	Vareniki   UMETA(DisplayName = "Vareniki"),
	Pirozhki   UMETA(DisplayName = "Pirozhki"),
	Medovik    UMETA(DisplayName = "Medovik"),

	Count      UMETA(Hidden)
};
