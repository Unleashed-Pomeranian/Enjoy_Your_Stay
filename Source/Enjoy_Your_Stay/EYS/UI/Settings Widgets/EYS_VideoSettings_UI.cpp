// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Settings Widgets/EYS_VideoSettings_UI.h"
#include "EYS_SliderSetting_UI.h"
#include "EYS_ComboBoxSetting_UI.h"
#include "EYS_CheckBoxSetting_UI.h"
#include "GameFramework/GameUserSettings.h"

void UEYS_VideoSettings_UI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeVideoSettings();

}

void UEYS_VideoSettings_UI::InitializeVideoSettings()
{
	InitializeOptionLists();
	LoadCurrentSettingsToUI();
	BindingEvents();
	
}

void UEYS_VideoSettings_UI::InitializeOptionLists()
{
	if (Row_WindowMode)
	{
		Row_WindowMode->SetSettingName(FText::FromString(TEXT("Window Mode")));
		Row_WindowMode->SetOptions({TEXT("Fullscreen"),TEXT("Windowed"),TEXT("Borderless")});
	}
	if (Row_Resolution)
	{
		Row_Resolution->SetSettingName(FText::FromString(TEXT("Resolution")));
		Row_Resolution->SetOptions({TEXT("1280x720"),TEXT("1600x900"),TEXT("1920x1080"),TEXT("2560x1440")});
	}

	if (Row_OverallQuality)
	{
		Row_OverallQuality->SetSettingName(FText::FromString(TEXT("Overall Quality")));
		Row_OverallQuality->SetOptions({ TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic"),  });
	}

	if (Row_AntiAliasing)
	{
		Row_AntiAliasing->SetSettingName(FText::FromString(TEXT("Anti-Aliasing")));
		Row_AntiAliasing->SetOptions({ TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic") });
	}

	if (Row_PostProcessing)
	{
		Row_PostProcessing->SetSettingName(FText::FromString(TEXT("Post Processing")));
		Row_PostProcessing->SetOptions({ TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic") });
	}

	if (Row_Shadows)
	{
		Row_Shadows->SetSettingName(FText::FromString(TEXT("Shadows")));
		Row_Shadows->SetOptions({ TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic") });
	}

	if (Row_Textures)
	{
		Row_Textures->SetSettingName(FText::FromString(TEXT("Textures")));
		Row_Textures->SetOptions({ TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic") });
	}

	if (Row_Effects)
	{
		Row_Effects->SetSettingName(FText::FromString(TEXT("Effects")));
		Row_Effects->SetOptions({ TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic") });
	}

	if (Row_ViewDistance)
	{
		Row_ViewDistance->SetSettingName(FText::FromString(TEXT("View Distance")));
		Row_ViewDistance->SetOptions({ TEXT("Low"), TEXT("Medium"), TEXT("High"), TEXT("Epic") });
	}
	if(Row_VSync)
	{
		Row_VSync->SetSettingName(FText::FromString(TEXT("VSync")));
	}

	if (Row_Brightness)
	{
		Row_Brightness->SetSettingName(FText::FromString(TEXT("Brightness")));
	}

}

void UEYS_VideoSettings_UI::LoadCurrentSettingsToUI()
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	if (!Settings)
	{
		RemoveFromParent();
		return;
		
	}

	PendingWindowMode = WindowModeToString(Settings->GetFullscreenMode());
	PendingResolution = ResolutionPointToString(Settings->GetScreenResolution());
	PendingOverallQuality = QualityLevelToString(Settings->GetOverallScalabilityLevel());
	PendingAntiAliasing = QualityLevelToString(Settings->GetAntiAliasingQuality());
	PendingPostProcessing = QualityLevelToString(Settings->GetPostProcessingQuality());
	PendingShadows = QualityLevelToString(Settings->GetShadowQuality());
	PendingTextures = QualityLevelToString(Settings->GetTextureQuality());
	PendingEffects = QualityLevelToString(Settings->GetVisualEffectQuality());
	PendingViewDistance = QualityLevelToString(Settings->GetViewDistanceQuality());
	bPendingVSync = Settings->IsVSyncEnabled();

	PendingBrightness = 1.0f;

	if (Row_WindowMode)      Row_WindowMode->SetSelectedOption(PendingWindowMode);
	if (Row_Resolution)      Row_Resolution->SetSelectedOption(PendingResolution);
	if (Row_OverallQuality)  Row_OverallQuality->SetSelectedOption(PendingOverallQuality);
	if (Row_AntiAliasing)    Row_AntiAliasing->SetSelectedOption(PendingAntiAliasing);
	if (Row_PostProcessing)  Row_PostProcessing->SetSelectedOption(PendingPostProcessing);
	if (Row_Shadows)         Row_Shadows->SetSelectedOption(PendingShadows);
	if (Row_Textures)        Row_Textures->SetSelectedOption(PendingTextures);
	if (Row_Effects)         Row_Effects->SetSelectedOption(PendingEffects);
	if (Row_ViewDistance)    Row_ViewDistance->SetSelectedOption(PendingViewDistance);
	if (Row_VSync)           Row_VSync->SetCheckState(bPendingVSync);
	if (Row_Brightness)      Row_Brightness->SetInitialValue(PendingBrightness,true);
}

void UEYS_VideoSettings_UI::BindingEvents()
{
	if (Row_WindowMode)
	{
		Row_WindowMode->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnWindowModeChanged);
	}

	if (Row_Resolution)
	{
		Row_Resolution->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnResolutionChanged);
	}

	if (Row_OverallQuality)
	{
		Row_OverallQuality->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnOverallQualityChanged);
	}

	if (Row_AntiAliasing)
	{
		Row_AntiAliasing->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnAntiAliasingChanged);
	}

	if (Row_PostProcessing)
	{
		Row_PostProcessing->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnPostProcessingChanged);
	}

	if (Row_Shadows)
	{
		Row_Shadows->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnShadowsChanged);
	}

	if (Row_Textures)
	{
		Row_Textures->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnTexturesChanged);
	}

	if (Row_Effects)
	{
		Row_Effects->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnEffectsChanged);
	}

	if (Row_ViewDistance)
	{
		Row_ViewDistance->OnComboSelectionChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnViewDistanceChanged);
	}



	if (Row_VSync)
	{
		Row_VSync->OnCheckBoxStateChanged.AddDynamic(this, &UEYS_VideoSettings_UI::OnVSyncChanged);
	}

	if (Button_Apply)
	{
		Button_Apply->OnClicked.AddDynamic(this, &UEYS_VideoSettings_UI::OnApplyClicked);
	}

	
	if (Button_Default)
	{
		Button_Default->OnClicked.AddDynamic(this, &UEYS_VideoSettings_UI::OnDefaultClicked);
	}
}




int32 UEYS_VideoSettings_UI::QualityStringToLevel(const FString& InValue) const
{
	if (InValue == TEXT("Low")) return 0;
	if (InValue == TEXT("Medium")) return 1;
	if (InValue == TEXT("High")) return 2;
	if (InValue == TEXT("Epic")) return 3;
	return 2;
}

FString UEYS_VideoSettings_UI::QualityLevelToString(int32 InLevel) const
{
	switch (InLevel)
	{
	case 0: return TEXT("Low");
	case 1: return TEXT("Medium");
	case 2: return TEXT("High");
	case 3: return TEXT("Epic");
	default: return TEXT("High");
	}
}

EWindowMode::Type UEYS_VideoSettings_UI::StringToWindowMode(const FString& InValue) const
{
	if (InValue == TEXT("Fullscreen")) return EWindowMode::Fullscreen;
	if (InValue == TEXT("Windowed")) return EWindowMode::Windowed;
	if (InValue == TEXT("Borderless")) return EWindowMode::WindowedFullscreen;
	return EWindowMode::Fullscreen;
}

FString UEYS_VideoSettings_UI::WindowModeToString(EWindowMode::Type InMode) const
{
	switch (InMode)
	{
	case EWindowMode::Fullscreen: return TEXT("Fullscreen");
	case EWindowMode::Windowed: return TEXT("Windowed");
	case EWindowMode::WindowedFullscreen: return TEXT("Borderless");
	default: return TEXT("Fullscreen");
	}
}

FIntPoint UEYS_VideoSettings_UI::ResolutionStringToPoint(const FString& InValue) const
{
	FString Left, Right;
	if (InValue.Split(TEXT("x"), &Left, &Right))
	{
		return FIntPoint(FCString::Atoi(*Left), FCString::Atoi(*Right));
	}

	return FIntPoint(1920, 1080);
}

FString UEYS_VideoSettings_UI::ResolutionPointToString(const FIntPoint& InPoint) const
{
	return FString::Printf(TEXT("%dx%d"), InPoint.X, InPoint.Y);
}

void UEYS_VideoSettings_UI::OnWindowModeChanged(FString SelectedValue)
{
	PendingWindowMode = SelectedValue;

}

void UEYS_VideoSettings_UI::OnResolutionChanged(FString SelectedValue)
{
	PendingResolution = SelectedValue;
}

void UEYS_VideoSettings_UI::OnOverallQualityChanged(FString SelectedValue)
{
	PendingOverallQuality = SelectedValue;
	PendingAntiAliasing = SelectedValue;
	PendingPostProcessing = SelectedValue;
	PendingShadows = SelectedValue;
	PendingTextures = SelectedValue;
	PendingEffects = SelectedValue;
	PendingViewDistance = SelectedValue;

	if (Row_AntiAliasing)
		Row_AntiAliasing->SetSelectedOption(SelectedValue);

	if (Row_PostProcessing)
		Row_PostProcessing->SetSelectedOption(SelectedValue);

	if (Row_Shadows)
		Row_Shadows->SetSelectedOption(SelectedValue);

	if (Row_Textures)
		Row_Textures->SetSelectedOption(SelectedValue);

	if (Row_Effects)
		Row_Effects->SetSelectedOption(SelectedValue);

	if (Row_ViewDistance)
		Row_ViewDistance->SetSelectedOption(SelectedValue);
}

void UEYS_VideoSettings_UI::OnAntiAliasingChanged(FString SelectedValue)
{
	PendingAntiAliasing = SelectedValue;
	
}

void UEYS_VideoSettings_UI::OnPostProcessingChanged(FString SelectedValue)
{
	PendingPostProcessing = SelectedValue;
	
}

void UEYS_VideoSettings_UI::OnShadowsChanged(FString SelectedValue)
{
	PendingShadows = SelectedValue;
	
}

void UEYS_VideoSettings_UI::OnTexturesChanged(FString SelectedValue)
{
	PendingTextures = SelectedValue;
	
}

void UEYS_VideoSettings_UI::OnEffectsChanged(FString SelectedValue)
{
	PendingEffects = SelectedValue;
	
}

void UEYS_VideoSettings_UI::OnViewDistanceChanged(FString SelectedValue)
{
	PendingViewDistance = SelectedValue;
	
}


void UEYS_VideoSettings_UI::OnVSyncChanged(bool bIsChecked)
{
	bPendingVSync = bIsChecked;
	
}


void UEYS_VideoSettings_UI::OnApplyClicked()
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	if (!Settings)
	{
		return;
	}

	Settings->SetFullscreenMode(StringToWindowMode(PendingWindowMode));
	Settings->SetScreenResolution(ResolutionStringToPoint(PendingResolution));
	Settings->SetVSyncEnabled(bPendingVSync);

	Settings->SetOverallScalabilityLevel(QualityStringToLevel(PendingOverallQuality));
	Settings->SetAntiAliasingQuality(QualityStringToLevel(PendingAntiAliasing));
	Settings->SetPostProcessingQuality(QualityStringToLevel(PendingPostProcessing));
	Settings->SetShadowQuality(QualityStringToLevel(PendingShadows));
	Settings->SetTextureQuality(QualityStringToLevel(PendingTextures));
	Settings->SetVisualEffectQuality(QualityStringToLevel(PendingEffects));
	Settings->SetViewDistanceQuality(QualityStringToLevel(PendingViewDistance));

	Settings->ApplySettings(false);
	Settings->SaveSettings();


}
void UEYS_VideoSettings_UI::OnDefaultClicked()
{
	PendingWindowMode = TEXT("Fullscreen");
	PendingResolution = TEXT("1920x1080");
	PendingOverallQuality = TEXT("High");
	PendingAntiAliasing = TEXT("High");
	PendingPostProcessing = TEXT("High");
	PendingShadows = TEXT("High");
	PendingTextures = TEXT("High");
	PendingEffects = TEXT("High");
	PendingViewDistance = TEXT("High");
	bPendingVSync = false;
	PendingBrightness = 1.0f;

	if (Row_WindowMode)      Row_WindowMode->SetSelectedOption(PendingWindowMode);
	if (Row_Resolution)      Row_Resolution->SetSelectedOption(PendingResolution);
	if (Row_OverallQuality)  Row_OverallQuality->SetSelectedOption(PendingOverallQuality);
	if (Row_AntiAliasing)    Row_AntiAliasing->SetSelectedOption(PendingAntiAliasing);
	if (Row_PostProcessing)  Row_PostProcessing->SetSelectedOption(PendingPostProcessing);
	if (Row_Shadows)         Row_Shadows->SetSelectedOption(PendingShadows);
	if (Row_Textures)        Row_Textures->SetSelectedOption(PendingTextures);
	if (Row_Effects)         Row_Effects->SetSelectedOption(PendingEffects);
	if (Row_ViewDistance)    Row_ViewDistance->SetSelectedOption(PendingViewDistance);
	if (Row_VSync)           Row_VSync->SetCheckState(bPendingVSync);
	if (Row_Brightness)      Row_Brightness->SetInitialValue(PendingBrightness,true);
}
