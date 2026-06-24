// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MyPostProcessVolume.h"
#include "Blueprint/UserWidget.h"
AEYS_MyPostProcessVolume::AEYS_MyPostProcessVolume()
{

	bUnbound = false;
	Priority = 10.0f; 
	bEnabled = true;  

	Settings.bOverride_SceneFringeIntensity = true;
	Settings.SceneFringeIntensity = 0.0f;

	Settings.bOverride_FilmGrainIntensity = true;
	Settings.FilmGrainIntensity = 0.0f;

	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = 0.0f;
}
void AEYS_MyPostProcessVolume::PlayJumpscareGlitch()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(GlitchTimerHandle);
	}

	
	bUnbound = true;
	CurrentGlitchIntensity = 0.0f;

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(GlitchTimerHandle, this, &AEYS_MyPostProcessVolume::UpdateGlitchSettings, 0.02f, true);
	}
}

void AEYS_MyPostProcessVolume::UpdateGlitchSettings()
{
	CurrentGlitchIntensity += 0.02f;

	FPostProcessSettings& PP = Settings;


	if (CurrentGlitchIntensity <= 3.5f)
	{
	
		float Wave = FMath::Abs(FMath::Sin(CurrentGlitchIntensity * 12.0f));

	
		PP.bOverride_SceneFringeIntensity = true;
		PP.SceneFringeIntensity = Wave * 35.0f;

	
		PP.bOverride_FilmGrainIntensity = true;
		PP.FilmGrainIntensity = Wave * 2.0f;
		PP.bOverride_FilmGrainTexelSize = true;
		PP.FilmGrainTexelSize = Wave * 7.0f;

		PP.bOverride_VignetteIntensity = true;
		PP.VignetteIntensity = Wave * 0.4f;
		float BlindingBrightness = FMath::Lerp(1.0f, -4.0f, Wave);
		PP.AutoExposureMinBrightness = BlindingBrightness;
		PP.AutoExposureMaxBrightness = BlindingBrightness;

		// Parlamanın etrafa ışık sızdırması (Glow hissi) için Bloom'u da dalgaya oranlıyoruz
		PP.bOverride_BloomIntensity = true;
		PP.BloomIntensity = Wave * 15.0f;
	}

	else if (CurrentGlitchIntensity > 3.5f && CurrentGlitchIntensity <= 5.0f)
	{
	
		float Alpha = (CurrentGlitchIntensity - 3.5f) / 1.5f;

	
		PP.SceneFringeIntensity = FMath::Lerp(PP.SceneFringeIntensity, 0.0f, Alpha);
		PP.FilmGrainIntensity = FMath::Lerp(PP.FilmGrainIntensity, 0.0f, Alpha);
		PP.FilmGrainTexelSize = FMath::Lerp(PP.FilmGrainTexelSize, 0.0f, Alpha);
	
		PP.bOverride_VignetteIntensity = true;
		PP.VignetteIntensity = FMath::Lerp(PP.VignetteIntensity, 10.0f, Alpha);
		PP.bOverride_AutoExposureMinBrightness = true;
		PP.bOverride_AutoExposureMaxBrightness = true;
		PP.AutoExposureMinBrightness = FMath::Lerp(PP.AutoExposureMinBrightness, 0.0f, Alpha);
		PP.AutoExposureMaxBrightness = FMath::Lerp(PP.AutoExposureMaxBrightness, 0.0f, Alpha);
	}
	else
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(GlitchTimerHandle);
		}
		PP.AutoExposureMinBrightness = 0.0f;
		PP.AutoExposureMaxBrightness = 0.0f;
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(	EndGameWidgetTimerHandle,this,&AEYS_MyPostProcessVolume::ShowEndGameWidget,2.0f,false);
		}


	}
}

void AEYS_MyPostProcessVolume::ShowEndGameWidget()
{
	if (EndGameWidgetClass && GetWorld())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			EndGameWidgetInstance = CreateWidget<UUserWidget>(PC, EndGameWidgetClass);

			if (EndGameWidgetInstance)
			{

				EndGameWidgetInstance->AddToViewport();


			}
		}
	}
}
