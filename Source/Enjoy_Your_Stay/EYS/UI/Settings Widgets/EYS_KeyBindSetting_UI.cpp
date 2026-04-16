// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Settings Widgets/EYS_KeyBindSetting_UI.h"
#include "TimerManager.h"

void UEYS_KeyBindSetting_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Key)
	{
		Button_Key->OnClicked.AddDynamic(this, &UEYS_KeyBindSetting_UI::OnKeyButtonClicked);
	}

	SetIsFocusable(true);
}

void UEYS_KeyBindSetting_UI::InitializeSetting(FName InActionName, const FText& InDisplayName, const FKey& InKey)
{
	ActionName = InActionName;
	CurrentKey = InKey;

	if (Text_SettingName)
	{
		Text_SettingName->SetText(InDisplayName);
	}

	if (Text_CurrentKey)
	{
		Text_CurrentKey->SetText(FText::FromName(CurrentKey.GetFName()));
	}
}

void UEYS_KeyBindSetting_UI::OnKeyButtonClicked()
{
	StartListening();
	Button_Key->SetIsEnabled(false);
}

void UEYS_KeyBindSetting_UI::StartListening()
{
	bIsListening = true;
	bIgnoreNextMouseInput = true;

	if (Text_CurrentKey)
	{
		Text_CurrentKey->SetText(FText::FromString(TEXT("Press Any Key...")));
	}

	SetKeyboardFocus();
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				bIgnoreNextMouseInput = false;
			}));
	}
}

void UEYS_KeyBindSetting_UI::StopListening()
{
	bIsListening = false;
	bIgnoreNextMouseInput = false;

	if (Text_CurrentKey)
	{
		Text_CurrentKey->SetText(FText::FromName(CurrentKey.GetFName()));
	}
}

void UEYS_KeyBindSetting_UI::ApplyNewKey(const FKey& NewKey)
{
	if (!NewKey.IsValid())
	{
		return;
	}

	CurrentKey = NewKey;

	if (Text_CurrentKey)
	{
		Text_CurrentKey->SetText(FText::FromName(CurrentKey.GetFName()));
	}

	bIsListening = false;
	bIgnoreNextMouseInput = false;

	OnKeyChanged.Broadcast(ActionName, CurrentKey);
}

FReply UEYS_KeyBindSetting_UI::HandleInputKey(const FKey& PressedKey)
{
	if (!bIsListening)
	{
		return FReply::Unhandled();
	}

	// ESC cancel
	if (PressedKey == EKeys::Escape)
	{
		StopListening();
		return FReply::Handled();
	}

	if (!PressedKey.IsValid())
	{
		return FReply::Handled();
	}

	// APPLY
	CurrentKey = PressedKey;

	if (Text_CurrentKey)
	{
		Text_CurrentKey->SetText(CurrentKey.GetDisplayName());
	}

	bIsListening = false;
	bIgnoreNextMouseInput = false;
	Button_Key->SetIsEnabled(true);
	OnKeyChanged.Broadcast(ActionName, CurrentKey);

	return FReply::Handled();
}
FReply UEYS_KeyBindSetting_UI::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return HandleInputKey(InKeyEvent.GetKey());
}
FReply UEYS_KeyBindSetting_UI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsListening && bIgnoreNextMouseInput)
	{
		return FReply::Handled();
	}

	return HandleInputKey(InMouseEvent.GetEffectingButton());
}
/**
FReply UEYS_KeyBindSetting_UI::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (!bIsListening)
	{
		return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
	}

	const FKey PressedKey = InKeyEvent.GetKey();

	if (PressedKey == EKeys::Escape)
	{
		StopListening();
		return FReply::Handled();
	}

	ApplyNewKey(PressedKey);
	return FReply::Handled();
}

FReply UEYS_KeyBindSetting_UI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bIsListening)
	{
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
		
	}

	if (bIgnoreNextMouseInput)
	{
		bIgnoreNextMouseInput = false;
		return FReply::Handled();
	}

	const FKey PressedMouseButton = InMouseEvent.GetEffectingButton();

	if (PressedMouseButton == EKeys::Invalid)
	{
		return FReply::Handled();
	}

	ApplyNewKey(PressedMouseButton);
	return FReply::Handled();
}
*/
