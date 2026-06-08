// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_Sheet.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Sheet : public AEYS_HeavyEquipmentBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDirty = false;
	virtual void DetachActor() override;
public:
	UFUNCTION() void AttachSheet();
	UFUNCTION() void RemoveSheet();
	

	UFUNCTION() bool GetDirtStatus();
	UFUNCTION() void SetDirtStatus(bool bDirtStatus);
	
};
