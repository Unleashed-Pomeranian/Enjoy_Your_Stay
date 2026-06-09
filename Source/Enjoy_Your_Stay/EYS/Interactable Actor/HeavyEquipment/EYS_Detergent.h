// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_Detergent.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Detergent : public AEYS_HeavyEquipmentBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detergent Settings")
	float DetergentValue = 100.0f;
protected:

	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
public:

	float ConsumeDetergent(float AmountNeeded);
};
