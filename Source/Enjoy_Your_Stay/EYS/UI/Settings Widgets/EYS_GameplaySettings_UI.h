// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EYS_GameplaySettings_UI.generated.h"

/**
 * 
 */
class UEYS_SliderSetting_UI;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_GameplaySettings_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta =(BindWidget))
	UEYS_SliderSetting_UI* Row_MouseSensitivity;
	UPROPERTY(meta = (BindWidget))
	UEYS_SliderSetting_UI* Row_CameraShakeIntensity;
protected:
	virtual void NativeConstruct() override;
	void InitializeGameplayOptions();

	UFUNCTION() void OnMouseSensitivityChanged(float NewValue);
	UFUNCTION() void OnCameraShakeIntensityChanged(float NewValue);
};
