// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "EYS_AudioSettings_UI.generated.h"

/**
 * 
 */
class UEYS_SliderSetting_UI;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_AudioSettings_UI : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	UEYS_SliderSetting_UI* Row_MasterVolume;

	UPROPERTY(meta = (BindWidget))
	UEYS_SliderSetting_UI* Row_MusicVolume;

	UPROPERTY(meta = (BindWidget))
	UEYS_SliderSetting_UI* Row_SFXVolume;

	UPROPERTY(meta = (BindWidget))
	UEYS_SliderSetting_UI* Row_AmbientVolume;

	UFUNCTION()
	void OnMasterVolumeChanged(float NewValue);

	UFUNCTION()
	void OnMusicVolumeChanged(float NewValue);

	UFUNCTION()
	void OnSFXVolumeChanged(float NewValue);

	UFUNCTION()
	void OnAmbientVolumeChanged(float NewValue);

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundMix* MainSoundMix;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundClass* MasterClass;
};
