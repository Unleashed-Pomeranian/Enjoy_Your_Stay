// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_FuelTank.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_FuelTank : public AEYS_HeavyEquipmentBase
{
	GENERATED_BODY()
	
protected:
	
	 void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
public:
	UFUNCTION() void AttachToGenerator(USceneComponent* Parent);
	UPROPERTY(EditAnywhere) float FuelValue = 100;
	
};
