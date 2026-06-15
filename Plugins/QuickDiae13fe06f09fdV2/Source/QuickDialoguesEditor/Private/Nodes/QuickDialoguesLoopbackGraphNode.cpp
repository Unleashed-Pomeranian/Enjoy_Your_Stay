//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesLoopbackGraphNode.h"

#include "Widgets/QuickDialoguesLoopbackGraphNodeWidget.h"

TSharedPtr<SGraphNode> UQuickDialoguesLoopbackGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesLoopbackGraphNodeWidget,this);
}

void UQuickDialoguesLoopbackGraphNode::AllocateDefaultPins()
{
	Modify();
	Pins.Empty();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, TEXT("Previous Node"));
}

void UQuickDialoguesLoopbackGraphNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::PinConnectionListChanged(Pin);
	GetGraph()->NotifyNodeChanged(this);
}
