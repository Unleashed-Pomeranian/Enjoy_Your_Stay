//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesDialogueNode.h"

void UQuickDialoguesDialogueNode::SetDialogue(const FText InText)
{
#if WITH_EDITOR
	Modify();
#endif	
	NodeData = InText;	
}

UQuickDialoguesDialogueNode::UQuickDialoguesDialogueNode()
{
	NodeData = FText::FromString("Default Node Data");
}

FText UQuickDialoguesDialogueNode::GetNodeDialogueData()
{
	return NodeData;
}

FText UQuickDialoguesDialogueNode::GetNodeTypeAsText() const
{
	return FText::FromString("Dialogue Node");
}
