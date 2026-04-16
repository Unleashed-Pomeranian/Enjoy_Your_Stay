// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Settings Widgets/EYS_SliderSetting_UI.h"



void UEYS_SliderSetting_UI::NativeConstruct()
{
	Super::NativeConstruct();
	Slider_Value->OnValueChanged.AddDynamic(this, &UEYS_SliderSetting_UI::OnSliderValueChanged);


	if (SliderMaterial && Slider_Value)
	{

		SliderMID = UMaterialInstanceDynamic::Create(SliderMaterial, this);
		if (SliderMID)
		{
			FSliderStyle SliderStyle = Slider_Value->GetWidgetStyle();

			SliderStyle.NormalBarImage.SetResourceObject(SliderMID);
			SliderStyle.HoveredBarImage.SetResourceObject(SliderMID);

			Slider_Value->SetWidgetStyle(SliderStyle);
			
		}
	}
}

void UEYS_SliderSetting_UI::SetInitialValue(float InValue,bool bIsPercent)
{
	CurrentValue = InValue;
	bShowAsPercent = bIsPercent;
	if (Slider_Value && Slider_Value)
	{
		float MaxVal = Slider_Value->GetMaxValue();
		float NormalizedValue = (MaxVal > 0.0f) ? (InValue / MaxVal) : 0.0f;;
		SliderMID->SetScalarParameterValue("Value", NormalizedValue);
	}
	SetValueText(InValue);
	
}

void UEYS_SliderSetting_UI::OnSliderValueChanged(float Value)
{
	CurrentValue = Value;

	if (Slider_Value && Slider_Value)
	{
		float MaxVal = Slider_Value->GetMaxValue();
		float NormalizedValue = (MaxVal > 0.0f) ? (Value / MaxVal) : 0.0f;;
		SliderMID->SetScalarParameterValue("Value",  NormalizedValue);
	}


	SetValueText(Value);

	OnSliderSettingChanged.Broadcast(Value);
}



void UEYS_SliderSetting_UI::SetSettingName(const FText& InName)
{
	if (Text_SettingName)
	{
		Text_SettingName->SetText(InName);
	}
}

void UEYS_SliderSetting_UI::SetMinMaxValue(float MinValue, float MaxValue)
{
	Slider_Value->SetMinValue(MinValue);
	Slider_Value->SetMaxValue(MaxValue);
}

void UEYS_SliderSetting_UI::SetValueText(float TextValue)
{
	if (bShowAsPercent)
	{
		const int32 Percent = FMath::RoundToInt(TextValue * 100.0f);
		Text_SliderValue->SetText(FText::Format(FText::FromString("%{0}"), FText::AsNumber(Percent)));
	}
	else
	{
		FString FormattedString = FString::Printf(TEXT("%.2f"), TextValue);

		Text_SliderValue->SetText(FText::FromString(FormattedString));
	}
}
