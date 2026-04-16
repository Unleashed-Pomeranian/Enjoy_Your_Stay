// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "EYS_VideoSettings_UI.generated.h"

class UEYS_SliderSetting_UI;
class UEYS_ComboBoxSetting_UI;
class UEYS_CheckBoxSetting_UI;

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_VideoSettings_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_WindowMode;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_Resolution;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_OverallQuality;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_AntiAliasing;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_PostProcessing;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_Shadows;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_Textures;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_Effects;

	UPROPERTY(meta = (BindWidget))
	UEYS_ComboBoxSetting_UI* Row_ViewDistance;

	UPROPERTY(meta = (BindWidget))
	UEYS_SliderSetting_UI* Row_Brightness;

	UPROPERTY(meta = (BindWidget))
	UEYS_CheckBoxSetting_UI* Row_VSync;


	UPROPERTY(meta = (BindWidget))
	UButton* Button_Apply;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Default;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	FString PendingWindowMode;

	UPROPERTY()
	FString PendingResolution;

	UPROPERTY()
	FString PendingOverallQuality;

	UPROPERTY()
	FString PendingAntiAliasing;

	UPROPERTY()
	FString PendingPostProcessing;

	UPROPERTY()
	FString PendingShadows;

	UPROPERTY()
	FString PendingTextures;

	UPROPERTY()
	FString PendingEffects;

	UPROPERTY()
	FString PendingViewDistance;

	UPROPERTY()
	bool bPendingVSync = false;

	UPROPERTY()
	float PendingBrightness = 1.0f;

		





	/* -------------------- Init -------------------- */

		void InitializeVideoSettings();
	void InitializeOptionLists();
	void LoadCurrentSettingsToUI();
	
	void BindingEvents();


	/* -------------------- ComboBox Handlers -------------------- */
	UFUNCTION()
	void OnWindowModeChanged(FString SelectedValue);

	UFUNCTION()
	void OnResolutionChanged(FString SelectedValue);

	UFUNCTION()
	void OnOverallQualityChanged(FString SelectedValue);

	UFUNCTION()
	void OnAntiAliasingChanged(FString SelectedValue);

	UFUNCTION()
	void OnPostProcessingChanged(FString SelectedValue);

	UFUNCTION()
	void OnShadowsChanged(FString SelectedValue);

	UFUNCTION()
	void OnTexturesChanged(FString SelectedValue);

	UFUNCTION()
	void OnEffectsChanged(FString SelectedValue);

	UFUNCTION()
	void OnViewDistanceChanged(FString SelectedValue);

	

	/* -------------------- Other Handlers -------------------- */

	

	UFUNCTION()
	void OnVSyncChanged(bool bIsChecked);

	UFUNCTION()
	void OnApplyClicked();

	UFUNCTION()
	void OnDefaultClicked();

	
	int32 QualityStringToLevel(const FString& InValue) const;
	FString QualityLevelToString(int32 InLevel) const;

	EWindowMode::Type StringToWindowMode(const FString& InValue) const;
	FString WindowModeToString(EWindowMode::Type InMode) const;

	FIntPoint ResolutionStringToPoint(const FString& InValue) const;
	FString ResolutionPointToString(const FIntPoint& InPoint) const;

	
};
