//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesEndPointNode.h"

UQuickDialoguesEndPointNode::UQuickDialoguesEndPointNode()
{
	UsesDefaultChildren = false;
}

FText UQuickDialoguesEndPointNode::GetNodeTypeAsText() const
{
	return FText::FromString("EndPoint Node");
}

TArray<UQuickDialoguesBaseNode*> UQuickDialoguesEndPointNode::GetAllChildren()
{
	return TArray<UQuickDialoguesBaseNode*>();	
}

FText UQuickDialoguesEndPointNode::GetNodeDialogueData()
{
	return Super::GetNodeDialogueData();
}

