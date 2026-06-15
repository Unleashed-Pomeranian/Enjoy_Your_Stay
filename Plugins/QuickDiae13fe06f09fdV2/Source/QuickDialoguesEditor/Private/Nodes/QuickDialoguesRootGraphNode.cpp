//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesRootGraphNode.h"

#include "Widgets/QuickDialoguesRootGraphNodeWidget.h"

void UQuickDialoguesRootGraphNode::AllocateDefaultPins()
{
	Pins.Empty();
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Entry Point"));
}

TSharedPtr<SGraphNode> UQuickDialoguesRootGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesRootGraphNodeWidget, this);
}
