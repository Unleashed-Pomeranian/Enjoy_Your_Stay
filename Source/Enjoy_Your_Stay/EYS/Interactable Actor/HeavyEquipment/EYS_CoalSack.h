// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_CoalSack.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_CoalSack : public AEYS_HeavyEquipmentBase
{
	GENERATED_BODY()

protected:
	

public:
	UFUNCTION() void ReduceFuelValue(int32 ReduceValue);
	UPROPERTY() int32 CoalValue = 100;
};
