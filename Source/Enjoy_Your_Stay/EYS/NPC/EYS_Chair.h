// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "EYS_Chair.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Chair : public AStaticMeshActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Root Component", meta = (AllowPrivateAccess=true))
	USceneComponent* ChairRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Root Component", meta = (AllowPrivateAccess = true))
	USceneComponent* TableRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Root Component", meta = (AllowPrivateAccess = true))
	USceneComponent* LeaveRoot;

public:
	AEYS_Chair();
	
	FTransform GetChairTransform();
	FTransform GetTableTransform();
	FVector GetLeaveLocation();
	UPROPERTY() bool bIsOccupied = false;
};
