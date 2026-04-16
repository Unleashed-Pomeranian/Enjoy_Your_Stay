// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "EYS_CheckBoxSetting_UI.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckBoxStateChanged,bool,bNewValue);

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_CheckBoxSetting_UI : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* CheckBox_State;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SettingName;

	
protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION() void OnCheckstateChanged(bool bvalue);

public:
	UFUNCTION() void SetSettingName(const FText& InName);
	UFUNCTION() void SetCheckState(bool bValue);
	FOnCheckBoxStateChanged OnCheckBoxStateChanged;
};
