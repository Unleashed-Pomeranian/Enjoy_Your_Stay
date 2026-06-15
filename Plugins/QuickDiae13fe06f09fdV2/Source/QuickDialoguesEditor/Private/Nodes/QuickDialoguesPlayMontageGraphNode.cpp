//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesPlayMontageGraphNode.h"

#include "Widgets/QuickDialoguesPlayMontageGraphNodeWidget.h"

void UQuickDialoguesPlayMontageGraphNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

TSharedPtr<SGraphNode> UQuickDialoguesPlayMontageGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesPlayMontageGraphNodeWidget, this);
}
