// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "EYS_WashingMachine_UI.generated.h"



UCLASS()
class ENJOY_YOUR_STAY_API UEYS_WashingMachine_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	USlider* Slider;

	protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float SliderValue=0.0f;

public:
	UFUNCTION() void SetSliderBarValue(float Value);
};
