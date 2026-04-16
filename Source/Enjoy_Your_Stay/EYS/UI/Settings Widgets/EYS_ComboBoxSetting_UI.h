// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/ComboBoxString.h"
#include "EYS_ComboBoxSetting_UI.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboSelectionChanged,FString, SelectedKey);
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_ComboBoxSetting_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox_Value;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SettingName;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void HandleSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

public:
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnComboSelectionChanged OnComboSelectionChanged;

	void SetSettingName(const FText& InName);
	void SetOptions(const TArray<FString>& InOptions);
	void SetSelectedOption(const FString& InOption);
};

