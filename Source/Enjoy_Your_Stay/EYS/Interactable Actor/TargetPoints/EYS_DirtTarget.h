// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EYS_DirtTarget.generated.h"


UENUM(BlueprintType)
enum class ETargetLocation: uint8
{
	Main UMETA(DisplayName = "Reception"),
	R101 UMETA(DisplayName = "101"),
	R102 UMETA(DisplayName = "102"),
	R103 UMETA(DisplayName = "103"),
	R104 UMETA(DisplayName = "104"),
};

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_DirtTarget : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bIsOccupied = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) 
	ETargetLocation TargetLocation;
};
