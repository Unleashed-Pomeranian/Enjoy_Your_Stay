//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesMultiOutputNode.h"


UQuickDialoguesMultiOutputNode::UQuickDialoguesMultiOutputNode()
{
	UsesDefaultChildren = false;
	ChosenIndex = 0;

}

void UQuickDialoguesMultiOutputNode::SetChosenIndex(const int InIndex)
{
	ChosenIndex = InIndex;
}

void UQuickDialoguesMultiOutputNode::RemoveChildAt(int32 Index)
{
#if WITH_EDITOR
	Modify();
#endif
	
	if (!ChildrenMap.Contains(Index))
	{
		return; // Nothing to remove
	}

	// Remove the selected index
	ChildrenMap.Remove(Index);

	// Shift subsequent nodes one index down
	TMap<int32, UQuickDialoguesBaseNode*> NewMap;
	for (const TPair<int32, UQuickDialoguesBaseNode*>& Pair : ChildrenMap)
	{
		int32 OldIndex = Pair.Key;
		UQuickDialoguesBaseNode* Node = Pair.Value;

		if (OldIndex > Index)
		{
			NewMap.Add(OldIndex - 1, Node);
		}
		else
		{
			NewMap.Add(OldIndex, Node);
		}
	}

	ChildrenMap = MoveTemp(NewMap);
}

FText UQuickDialoguesMultiOutputNode::GetNodeTypeAsText() const
{
	return FText::FromString("Unknown Node");
}

UQuickDialoguesBaseNode* UQuickDialoguesMultiOutputNode::GetNextNode(UObject* InOwner)
{
	if (ChildrenMap.Find(ChosenIndex))
	{
		return ChildrenMap[ChosenIndex];
	}
	return nullptr;
}

void UQuickDialoguesMultiOutputNode::RemoveChild(UQuickDialoguesBaseNode* InNode)
{
#if WITH_EDITOR
	Modify();
#endif	
	TArray<int32> KeysToRemove;
	for (const TPair<int32, UQuickDialoguesBaseNode*>& Pair : ChildrenMap)
	{
		if (Pair.Value == InNode)
		{
			KeysToRemove.Add(Pair.Key);
		}
	}
	for (int32 Key : KeysToRemove)
	{
		AddChildToMap(Key, nullptr);
	}
}

TArray<UQuickDialoguesBaseNode*> UQuickDialoguesMultiOutputNode::GetAllChildren()
{
	TArray<UQuickDialoguesBaseNode*> RetVal;
	for (const TPair<int32, UQuickDialoguesBaseNode*>& Pair : ChildrenMap)
	{
		if (Pair.Value)
		{
			RetVal.Add(Pair.Value);
		}
	}
	return RetVal;
}

void UQuickDialoguesMultiOutputNode::AddChildToMap(int InIndex, UQuickDialoguesBaseNode* InNode)
{
#if WITH_EDITOR
	Modify();
#endif	
	ChildrenMap.FindOrAdd(InIndex, InNode);
	ChildrenMap[InIndex] = InNode;
}

void UQuickDialoguesMultiOutputNode::ResetConnections()
{
	Super::ResetConnections();
	
	for (TPair<int32, UQuickDialoguesBaseNode*>& Pair : ChildrenMap)
	{
		Pair.Value = nullptr;
	}
}

void UQuickDialoguesMultiOutputNode::OnNodeRemoval()
{
	Super::OnNodeRemoval();
	
	for (auto Element : ChildrenMap)
	{
		if (Element.Value)
		{
			Element.Value->RemoveParent(this);
		}
	}
}
