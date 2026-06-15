//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesRandomNode.h"

FText UQuickDialoguesRandomNode::GetNodeTypeAsText() const
{
	return FText::FromString("Random Node");
}

UQuickDialoguesBaseNode* UQuickDialoguesRandomNode::GetNextNode(UObject* InOwner)
{
	const int RandomIndex = FMath::RandRange(0, ChildrenMap.Num() - 1);
	if (RandomIndex <= ChildrenMap.Num())
	{
		return ChildrenMap[RandomIndex];
	}
	return nullptr;	
}
