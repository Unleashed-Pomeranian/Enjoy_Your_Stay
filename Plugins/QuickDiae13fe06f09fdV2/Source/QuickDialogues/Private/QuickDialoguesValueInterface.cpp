//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesValueInterface.h"


void IQuickDialoguesValueInterface::SetDialogue(FText InText)
{
	
}

FText IQuickDialoguesValueInterface::GetNodeDialogueData()
{
	return FText::FromString("Called GetNodeDialogueData() on a non dialogue node");
}

TArray<FDialogueReply> IQuickDialoguesValueInterface::GetReplies()
{
	return TArray<FDialogueReply>{};
}

void IQuickDialoguesValueInterface::SetChosenIndex(int InIndex)
{
}

TSubclassOf<UUserWidget> IQuickDialoguesValueInterface::GetWidgetToOpen()
{
	return nullptr;
}

FQuickDialoguesPlayMontageNodeData IQuickDialoguesValueInterface::GetMontageToPlay()
{
	return FQuickDialoguesPlayMontageNodeData();
}
