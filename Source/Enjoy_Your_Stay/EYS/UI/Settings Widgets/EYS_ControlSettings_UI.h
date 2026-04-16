// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "InputCoreTypes.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "EYS_ControlSettings_UI.generated.h"

class UEYS_KeyBindSetting_UI;

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_ControlSettings_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_MoveForward;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_MoveLeft;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_MoveBackward;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_MoveRight;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_Sprint;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_Jump;


	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_PrimaryAction;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_SecondaryAction;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_Interact;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_Drop;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_EquipmentWheel;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_MissionSense;

	UPROPERTY(meta = (BindWidget))
	UEYS_KeyBindSetting_UI* Row_Notebook;

	

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Default;

	void InitializeRows();
	FKey GetCurrentKeyForAction(FName ActionName);
	void BindRowEvents();
	UFUNCTION() void ApplyChangedKey(FName ActionName, FKey NewKey);
	UFUNCTION() void ApplyDefaultKey();

	
	FKey MoveRightKey = EKeys::V;
	
	TMap<FName, FKey> DefaultKeyBinding =
	{
	{ "MoveForward", EKeys::W },
	{ "MoveLeft", EKeys::A },
	{ "MoveBackward", EKeys::S },
	{ "MoveRight", EKeys::D },
	{ "Sprint", EKeys::LeftShift },
	{ "Jump", EKeys::SpaceBar },
	{ "PrimaryAction", EKeys::LeftMouseButton },
	{ "SecondaryAction", EKeys::RightMouseButton },
	{ "Interact", EKeys::E },
	{ "Drop", EKeys::G },
	{ "EquipmentWheel", EKeys::Tab },
	{ "MissionSense", EKeys::MiddleMouseButton},
	{ "Notebook", EKeys::Q }
	};
	class UEnhancedInputUserSettings* EnhancedInputUserSettings = nullptr;
	class UEnhancedInputLocalPlayerSubsystem* EnhancedInputSystem = nullptr;

};