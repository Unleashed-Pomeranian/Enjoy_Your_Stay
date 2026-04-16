// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "EYS_SliderSetting_UI.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderSettingChanged,float,NewValue);

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_SliderSetting_UI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Value;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SliderValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SettingName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* SliderMID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* SliderMaterial;
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSliderValueChanged(float value);

	bool bShowAsPercent = true;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float CurrentValue = 1.0f;
	UFUNCTION() void SetSettingName(const FText& InName);
	UFUNCTION() void SetInitialValue(float InValue, bool bIsPercent);
	UFUNCTION() void SetMinMaxValue(float MinValue, float MaxValue);
	UFUNCTION() void SetValueText(float TextValue);
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnSliderSettingChanged OnSliderSettingChanged;
};
