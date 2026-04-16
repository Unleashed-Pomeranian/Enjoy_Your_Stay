// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EYS_AudioConfig.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_AudioConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, Category = "Audio Settings")
	class USoundMix* MainSoundMix;

	UPROPERTY(EditAnywhere, Category = "Audio Settings")
	class USoundClass* MasterClass;

	UPROPERTY(EditAnywhere, Category = "Audio Settings")
	class USoundClass* MusicClass;

	UPROPERTY(EditAnywhere, Category = "Audio Settings")
	class USoundClass* SFXClass;

	UPROPERTY(EditAnywhere, Category = "Audio Settings")
	class USoundClass* AmbientClass;
};
