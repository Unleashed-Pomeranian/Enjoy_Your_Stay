// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_Types.h"
#include "EYS_FoodBag.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_FoodBag : public AEYS_HeavyEquipmentBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
	EFoodType FoodType;
	UFUNCTION() void RemoveFoodBag();
};
