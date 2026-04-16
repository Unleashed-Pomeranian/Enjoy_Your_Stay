// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Settings Widgets/EYS_CheckBoxSetting_UI.h"



void UEYS_CheckBoxSetting_UI::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (CheckBox_State) CheckBox_State->OnCheckStateChanged.AddDynamic(this, &UEYS_CheckBoxSetting_UI::OnCheckstateChanged);
}

void UEYS_CheckBoxSetting_UI::SetCheckState(bool bValue)
{
	if (CheckBox_State) CheckBox_State->SetIsChecked(bValue);
}

void UEYS_CheckBoxSetting_UI::OnCheckstateChanged(bool bvalue)
{
	OnCheckBoxStateChanged.Broadcast(bvalue);
}


void  UEYS_CheckBoxSetting_UI::SetSettingName(const FText& InName)
{
	if (Text_SettingName)
	{
		Text_SettingName->SetText(InName);
	}
}