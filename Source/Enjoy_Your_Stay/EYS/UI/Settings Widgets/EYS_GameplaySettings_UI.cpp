// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Settings Widgets/EYS_GameplaySettings_UI.h"
#include "EYS_SliderSetting_UI.h"
#include "EYS/Game Managers/EYS_UserSettingsSubsystem.h"

void UEYS_GameplaySettings_UI::NativeConstruct()
{
	InitializeGameplayOptions();
}

void UEYS_GameplaySettings_UI::InitializeGameplayOptions()
{
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();

	if (Row_MouseSensitivity)
	{
		Row_MouseSensitivity->SetSettingName(FText::FromString("Mouse Sensitivity"));
		Row_MouseSensitivity->SetMinMaxValue(0.05f, 1.5f);
		Row_MouseSensitivity->SetInitialValue(US->MouseSensitivity,false);
		Row_MouseSensitivity->OnSliderSettingChanged.AddDynamic(this, &UEYS_GameplaySettings_UI::OnMouseSensitivityChanged);
		
	}
	if (Row_CameraShakeIntensity)
	{
		Row_CameraShakeIntensity->SetSettingName(FText::FromString("Camera Shake Intensity"));
		Row_CameraShakeIntensity->SetMinMaxValue(0.0f, 2.0f);
		Row_CameraShakeIntensity->SetInitialValue(US->CameraShakeIntensity,false);
		Row_CameraShakeIntensity->OnSliderSettingChanged.AddDynamic(this, &UEYS_GameplaySettings_UI::OnCameraShakeIntensityChanged);
	

	}

}

void UEYS_GameplaySettings_UI::OnMouseSensitivityChanged(float NewValue)
{
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	US->MouseSensitivity = NewValue;
}

void UEYS_GameplaySettings_UI::OnCameraShakeIntensityChanged(float NewValue)
{
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	US->CameraShakeIntensity = NewValue;
	
}

