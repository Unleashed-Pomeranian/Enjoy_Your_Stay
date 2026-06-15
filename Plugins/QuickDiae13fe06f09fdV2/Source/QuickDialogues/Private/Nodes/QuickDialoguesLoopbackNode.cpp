//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesLoopbackNode.h"

UQuickDialoguesLoopbackNode::UQuickDialoguesLoopbackNode(): LoopBackTo(nullptr)
{
	UsesDefaultChildren = false;
}

FText UQuickDialoguesLoopbackNode::GetNodeTypeAsText() const
{
	return FText::FromString("Loopback Node");
}

TArray<UQuickDialoguesBaseNode*> UQuickDialoguesLoopbackNode::GetParentChain() const
{

	constexpr int MAX_ITERATIONS = 300;

	TSet<UQuickDialoguesBaseNode*> Visited;
	TArray<UQuickDialoguesBaseNode*> ToBeVisited = Parents;
	
	int Iterations = 0;
	while (ToBeVisited.Num() > 0 && Iterations < MAX_ITERATIONS)
	{
		UQuickDialoguesBaseNode* CurrentNode = ToBeVisited.Pop();
		Iterations++;

		if (!CurrentNode || CurrentNode->GetNodeType() == EQuickDialoguesNodeType::Loopback)
		{
			continue;
		}

		Visited.Add(CurrentNode);
		TArray<UQuickDialoguesBaseNode*> Children = CurrentNode->GetParents();
		ToBeVisited.Append(Children);
	}
	return Visited.Array();
}

void UQuickDialoguesLoopbackNode::SetChildValue(UQuickDialoguesBaseNode* InChild)
{
#if WITH_EDITOR
	Modify();
#endif
	LoopBackTo = InChild;
	if (LoopBackTo)
	{
		LoopBackTo->AddParent(this);
	}
}

UQuickDialoguesBaseNode* UQuickDialoguesLoopbackNode::GetChild()
{
	return LoopBackTo;	
}

void UQuickDialoguesLoopbackNode::RemoveChild(UQuickDialoguesBaseNode* InNode)
{
#if WITH_EDITOR
	Modify();
#endif
	LoopBackTo = nullptr;
}

UQuickDialoguesBaseNode* UQuickDialoguesLoopbackNode::GetNextNode(UObject* InOwner)
{
	return LoopBackTo;	
}
