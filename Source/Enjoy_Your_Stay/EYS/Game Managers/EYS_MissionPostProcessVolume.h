// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "EYS_MissionPostProcessVolume.generated.h"


class AEYS_DirtActor;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MissionPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()
	protected:
	UPROPERTY() TArray<AEYS_DirtActor*>  DirtActorss;
public:
	UFUNCTION(BlueprintCallable) void ShowMissions();
	UFUNCTION(BlueprintCallable) void HideMissions();
	UFUNCTION(BlueprintCallable) void SetMissionPPEnabled(bool bEnablePPV);
};
