// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EYS/Interactable Actor\HeavyEquipment\EYS_Types.h"
#include "EYS_DirtTarget.generated.h"


UCLASS()
class ENJOY_YOUR_STAY_API AEYS_DirtTarget : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bIsOccupied = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESurfaceType SurfaceType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
	ERoomID RoomID;
};
