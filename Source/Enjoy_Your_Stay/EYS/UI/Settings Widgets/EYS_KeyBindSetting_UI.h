// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputCoreTypes.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "EYS_KeyBindSetting_UI.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKeyChanged, FName, ActionName, FKey, NewKey);
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_KeyBindSetting_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Key;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SettingName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentKey;


protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FReply HandleInputKey(const FKey& PressedKey);
	UFUNCTION()
	void OnKeyButtonClicked();
	void StartListening();
	void StopListening();


public:
	void InitializeSetting(FName InActionName, const FText& InDisplayName, const FKey& InKey);
	UPROPERTY(BlueprintAssignable, Category = "KeyBind")
	FOnKeyChanged OnKeyChanged;
	void ApplyNewKey(const FKey& NewKey);


protected:

	UPROPERTY()
	FName ActionName;

	UPROPERTY()
	FKey CurrentKey;

	UPROPERTY()
	bool bIsListening = false;
	UPROPERTY()
	bool bIgnoreNextMouseInput = false;


};

