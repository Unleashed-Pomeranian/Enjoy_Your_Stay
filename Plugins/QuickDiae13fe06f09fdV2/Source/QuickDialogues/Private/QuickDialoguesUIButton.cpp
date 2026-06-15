//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesUIButton.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"

void UQuickDialoguesUIButton::SetupButton(const FText& InText, int32 InIndex)
{
	Text = InText;
	Index = InIndex;

	if (ButtonText)
	{
		ButtonText->SetText(Text);
	}
}

void UQuickDialoguesUIButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	// This check might be redundant cause of meta = BindWidget of these UProperties but better safe than sorry
	if (!IsValid(ButtonText) || !IsValid(ButtonOverlay))
	{
		return;
	}
	ButtonOverlay->AddChild(ButtonText);
	ButtonText->SetText(Text);
}
