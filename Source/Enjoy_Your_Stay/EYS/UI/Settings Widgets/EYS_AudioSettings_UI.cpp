// Fill out your copyright notice in the Description page of Project Settings.

#include "EYS_AudioSettings_UI.h"
#include "EYS_SliderSetting_UI.h"
#include "EYS/Game Managers/EYS_UserSettingsSubsystem.h"



void UEYS_AudioSettings_UI::NativeConstruct()
{
	Super::NativeConstruct();
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	

	if (Row_MasterVolume)
	{
		Row_MasterVolume->SetSettingName(FText::FromString("Master Volume"));
		Row_MasterVolume->SetInitialValue(US->MasterVolume,true);
		Row_MasterVolume->OnSliderSettingChanged.AddDynamic(this, &UEYS_AudioSettings_UI::OnMasterVolumeChanged);
	}
	if (Row_MusicVolume)
	{
		Row_MusicVolume->SetSettingName(FText::FromString("Music Volume"));
		Row_MusicVolume->SetInitialValue(US->MusicVolume,true);
		Row_MusicVolume->OnSliderSettingChanged.AddDynamic(this, &UEYS_AudioSettings_UI::OnMusicVolumeChanged);
	}
	if (Row_SFXVolume)
	{
        Row_SFXVolume->SetSettingName(FText::FromString("SFX Volume"));
	    Row_SFXVolume->SetInitialValue(US->SFXVolume,true);
        Row_SFXVolume->OnSliderSettingChanged.AddDynamic(this, &UEYS_AudioSettings_UI::OnSFXVolumeChanged);
	}
	
	if(Row_AmbientVolume)
	{
		Row_AmbientVolume->SetSettingName(FText::FromString("Ambient Volume"));
		Row_AmbientVolume->SetInitialValue(US->AmbientVolume,true);
		Row_AmbientVolume->OnSliderSettingChanged.AddDynamic(this, &UEYS_AudioSettings_UI::OnAmbientVolumeChanged);
	}
	

}

void UEYS_AudioSettings_UI::OnMasterVolumeChanged(float NewValue)
{
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	US->SetMasterVolume(NewValue);
	
}

void UEYS_AudioSettings_UI::OnMusicVolumeChanged(float NewValue)
{
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	US->SetMusicVolume(NewValue);
}

void UEYS_AudioSettings_UI::OnSFXVolumeChanged(float NewValue)
{
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	US->SetSFXVolume(NewValue);
}

void UEYS_AudioSettings_UI::OnAmbientVolumeChanged(float NewValue)
{
	UEYS_UserSettingsSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	US->SetAmbientVolume(NewValue);
}

