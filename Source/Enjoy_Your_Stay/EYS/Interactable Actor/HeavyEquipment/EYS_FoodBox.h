// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_Types.h"
#include "EYS_FoodBox.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_FoodBox : public AEYS_HeavyEquipmentBase
{
	GENERATED_BODY()


protected:
	UPROPERTY() int32 FoodAmount=6;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
public:
	UFUNCTION() void RemoveFood();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
	EFoodType FoodType;
	
};
