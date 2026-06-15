//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesGraph.h"

UQuickDialoguesGraph::UQuickDialoguesGraph(): NodeTree(nullptr), RootNode(nullptr)
{
}

UEdGraphNode* UQuickDialoguesGraph::GetRootNode() const
{
	return RootNode;
}

void UQuickDialoguesGraph::ResetRootNode()
{
#if WITH_EDITOR
	Modify();
#endif
	RootNode = nullptr;
}

void UQuickDialoguesGraph::SetRootNode(UEdGraphNode* InRootNode)
{
#if WITH_EDITOR
	Modify();
#endif
	RootNode = InRootNode;
}
