// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EYS_UserSettingsSubsystem.generated.h"

/**
 * 
 */
class UEYS_AudioConfig;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_UserSettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite)
	float MasterVolume =1.0f;
	UPROPERTY(BlueprintReadWrite)
	float MusicVolume = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	float SFXVolume = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	float AmbientVolume = 1.0f;
	
	/*--------Gameplay---------*/
	UPROPERTY(BlueprintReadWrite)
	float MouseSensitivity = 0.5f;
	UPROPERTY(BlueprintReadWrite)
	float CameraShakeIntensity = 0.5f;

	void SetMasterVolume(float NewValue);
	void SetMusicVolume(float NewValue);
	void SetSFXVolume(float NewValue);
	void SetAmbientVolume(float NewValue);

public:
	// Bu fonksiyonu UI veya GameMode bir kez çağırıp Data Asset'i teslim etmeli
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void InitializeAudio(UEYS_AudioConfig* Config);

private:
	UPROPERTY()
	UEYS_AudioConfig* AudioConfig;
	void UpdateSoundVolume(class USoundClass* TargetClass, float Volume);
};
