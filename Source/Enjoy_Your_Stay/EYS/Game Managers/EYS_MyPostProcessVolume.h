// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "EYS_MyPostProcessVolume.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MyPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()
public:
	AEYS_MyPostProcessVolume();

	UFUNCTION(BlueprintCallable, Category = "EYS | Horror")
	void PlayJumpscareGlitch();

protected:

	FTimerHandle GlitchTimerHandle;

	float CurrentGlitchIntensity = 0.0f;

	// Her tick çalıştığında Post Process ayarlarını delirtecek iç fonksiyon
	void UpdateGlitchSettings();
	
};
