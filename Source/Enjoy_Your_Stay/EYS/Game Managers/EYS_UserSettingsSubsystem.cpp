// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_UserSettingsSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Data/EYS_AudioConfig.h"


void UEYS_UserSettingsSubsystem::SetMasterVolume(float NewValue)
{
    MasterVolume = NewValue;
    if (AudioConfig) UpdateSoundVolume(AudioConfig->MasterClass, NewValue);

}

void UEYS_UserSettingsSubsystem::SetMusicVolume(float NewValue)
{
    MusicVolume = NewValue;
    if (AudioConfig) UpdateSoundVolume(AudioConfig->MusicClass, NewValue);
}

void UEYS_UserSettingsSubsystem::SetSFXVolume(float NewValue)
{
    SFXVolume = NewValue;
    if (AudioConfig) UpdateSoundVolume(AudioConfig->SFXClass, NewValue);

}

void UEYS_UserSettingsSubsystem::SetAmbientVolume(float NewValue)
{
    AmbientVolume = NewValue;
    if (AudioConfig) UpdateSoundVolume(AudioConfig->AmbientClass, NewValue);
}

void UEYS_UserSettingsSubsystem::SetUIVolume(float NewValue)
{
    UIVolume = NewValue;
    if (AudioConfig) UpdateSoundVolume(AudioConfig->UIClass, NewValue);
}


void UEYS_UserSettingsSubsystem::InitializeAudio(UEYS_AudioConfig* Config)
{
    AudioConfig = Config;
  
}

void UEYS_UserSettingsSubsystem::UpdateSoundVolume(USoundClass* TargetClass, float Volume)
{
    if (AudioConfig && AudioConfig->MainSoundMix && TargetClass)
    {
        // Değeri Mix içinde değiştir
        UGameplayStatics::SetSoundMixClassOverride(GetWorld(), AudioConfig->MainSoundMix, TargetClass, Volume, 1.0f, 0.0f, true);

        // Değişikliği anında hoparlöre gönderir
        UGameplayStatics::PushSoundMixModifier(GetWorld(), AudioConfig->MainSoundMix);
    }
}
