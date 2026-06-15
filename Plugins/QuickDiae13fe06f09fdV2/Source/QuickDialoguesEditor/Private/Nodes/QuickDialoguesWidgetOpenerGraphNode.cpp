//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesWidgetOpenerGraphNode.h"

#include "Widgets/QuickDialoguesWidgetOpenerGraphNodeWidget.h"


void UQuickDialoguesWidgetOpenerGraphNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

TSharedPtr<SGraphNode> UQuickDialoguesWidgetOpenerGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesWidgetOpenerGraphNodeWidget, this);	
}

