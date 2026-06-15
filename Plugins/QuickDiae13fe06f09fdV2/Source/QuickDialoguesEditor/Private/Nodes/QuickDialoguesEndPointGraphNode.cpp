//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesEndPointGraphNode.h"

#include "Widgets/QuickDialoguesDialogueGraphNodeWidget.h"

TSharedPtr<SGraphNode> UQuickDialoguesEndPointGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesDialogueGraphNodeWidget,this);
}

void UQuickDialoguesEndPointGraphNode::AllocateDefaultPins()
{
	Modify();
	Pins.Empty();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, TEXT("Previous Node"));
}
