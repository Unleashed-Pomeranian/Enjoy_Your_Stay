// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RadialSlider.h"
#include "Components/TextBlock.h"
#include "EYS_GeneratorActivateWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_GeneratorActivateWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta = (BindWidget))
	URadialSlider* Radial_Slider;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Score_Text;

	virtual void NativeConstruct() override;


public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly) float RadialValue;
	UPROPERTY() int32 Score;
	UPROPERTY() bool bIsBetween;
	UFUNCTION() void StartGenerator();
	UFUNCTION(BlueprintCallable) void FStopTimer();
	UFUNCTION(BlueprintCallable) void FStartTimer();
	UFUNCTION(BlueprintCallable) void TimerFTimer();
	
};
