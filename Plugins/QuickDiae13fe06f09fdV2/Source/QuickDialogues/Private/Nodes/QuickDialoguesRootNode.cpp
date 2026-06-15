//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesRootNode.h"

UQuickDialoguesRootNode::UQuickDialoguesRootNode()
{
	UsesDefaultParent = false;
}

FText UQuickDialoguesRootNode::GetNodeTypeAsText() const
{
	return FText::FromString("Root Node");
}
