//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesDialogueGraphNode.h"

#include "Widgets/QuickDialoguesDialogueGraphNodeWidget.h"

TSharedPtr<SGraphNode> UQuickDialoguesDialogueGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesDialogueGraphNodeWidget,this);
}
