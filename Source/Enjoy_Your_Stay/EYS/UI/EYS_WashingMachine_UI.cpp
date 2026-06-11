// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/EYS_WashingMachine_UI.h"

void UEYS_WashingMachine_UI::NativeConstruct()
{
	Super::NativeConstruct();
	if(Slider)
	Slider->SetValue(SliderValue);
}

void UEYS_WashingMachine_UI::SetSliderBarValue(float Value)
{
	SliderValue = Value / 100;
	if(Slider)
	{
			Slider->SetValue(SliderValue);
	}
}
