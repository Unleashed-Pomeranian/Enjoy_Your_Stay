// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Settings Widgets/EYS_ComboBoxSetting_UI.h"

void UEYS_ComboBoxSetting_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (ComboBox_Value)
	{
		ComboBox_Value->OnSelectionChanged.AddDynamic(this, &UEYS_ComboBoxSetting_UI::HandleSelectionChanged);
	}
}


void UEYS_ComboBoxSetting_UI::HandleSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnComboSelectionChanged.Broadcast(SelectedItem);
}
void UEYS_ComboBoxSetting_UI::SetSettingName(const FText& InName)
{
	if (Text_SettingName)
	{
		Text_SettingName->SetText(InName);
	}
}


void UEYS_ComboBoxSetting_UI::SetOptions(const TArray<FString>& InOptions)
{
	if (!ComboBox_Value) return;

	ComboBox_Value->ClearOptions();

	for (const FString& Option : InOptions)
	{
		ComboBox_Value->AddOption(Option);
	}
}
void UEYS_ComboBoxSetting_UI::SetSelectedOption(const FString& InOption)
{
	if (ComboBox_Value)
	{
		ComboBox_Value->SetSelectedOption(InOption);
	}
}