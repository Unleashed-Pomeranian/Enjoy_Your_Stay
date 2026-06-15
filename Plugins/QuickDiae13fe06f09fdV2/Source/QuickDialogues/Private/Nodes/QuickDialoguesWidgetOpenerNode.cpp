//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesWidgetOpenerNode.h"

FText UQuickDialoguesWidgetOpenerNode::GetNodeTypeAsText() const
{
	return FText::FromString("Widget Opener Node");
}

UQuickDialoguesBaseNode* UQuickDialoguesWidgetOpenerNode::GetNextNode(UObject* InOwner)
{
	return Super::GetNextNode(InOwner);
}

TSubclassOf<UUserWidget> UQuickDialoguesWidgetOpenerNode::GetWidgetToOpen()
{
	return WidgetToOpen;
}

void UQuickDialoguesWidgetOpenerNode::SetWidgetToOpen(const TSubclassOf<UCommonUserWidget> InWidgetToOpen)
{
#if WITH_EDITOR
	Modify();
#endif
	WidgetToOpen = InWidgetToOpen;
}

FString UQuickDialoguesWidgetOpenerNode::GetWidgetToOpenPathName() const
{
	if (WidgetToOpen)
	{
		return WidgetToOpen->GetPathName();
	}
	return FString();
}
