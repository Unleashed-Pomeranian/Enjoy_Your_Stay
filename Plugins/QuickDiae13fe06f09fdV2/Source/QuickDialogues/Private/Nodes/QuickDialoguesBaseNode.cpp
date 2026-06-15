//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesBaseNode.h"

UQuickDialoguesBaseNode::UQuickDialoguesBaseNode()
	: Tree(nullptr), Child(nullptr), UsesDefaultChildren(true), UsesDefaultParent(true)
{
	// Start off as a root node by default, this can be changed later
	NodeType = EQuickDialoguesNodeType::Root;

	// Generate a fresh GUID for this node so it's uniquely identifiable
	NodeGuid = FGuid::NewGuid();
}

//  Value passthroughs (these call interface defaults unless overridden in child classes) 
FQuickDialoguesPlayMontageNodeData UQuickDialoguesBaseNode::GetMontageToPlay()
{
	// Montage to play used on Play montage node
	return IQuickDialoguesValueInterface::GetMontageToPlay();
}

void UQuickDialoguesBaseNode::SetChosenIndex(int InIndex)
{
	// Set which reply was picked (used by Reply nodes)
	IQuickDialoguesValueInterface::SetChosenIndex(InIndex);
}

TSubclassOf<UUserWidget> UQuickDialoguesBaseNode::GetWidgetToOpen()
{
	// Widget that should open when this node activates
	return IQuickDialoguesValueInterface::GetWidgetToOpen();
}

void UQuickDialoguesBaseNode::SetDialogue(FText InText)
{
	// Set the actual dialogue text used by dialogue nodes
	IQuickDialoguesValueInterface::SetDialogue(InText);
}

FText UQuickDialoguesBaseNode::GetNodeDialogueData()
{
	return IQuickDialoguesValueInterface::GetNodeDialogueData();
}

TArray<FDialogueReply> UQuickDialoguesBaseNode::GetReplies()
{
	// Used by reply nodes to spawn buttons
	return IQuickDialoguesValueInterface::GetReplies();
}

FText UQuickDialoguesBaseNode::GetNodeTypeAsText() const
{
	// Can be overridden to return more meaningful node type labels
	return FText::FromString("Unknown Node Type");
}

UQuickDialoguesBaseNode* UQuickDialoguesBaseNode::GetNextNode(UObject* InOwner)
{
	// Just go to child by default. More complex nodes override this.
	return Child;
}

TArray<UQuickDialoguesBaseNode*> UQuickDialoguesBaseNode::GetAllChildren()
{
	return TArray{Child};
}

UQuickDialoguesBaseNode* UQuickDialoguesBaseNode::GetChild()
{
	return Child;
}

void UQuickDialoguesBaseNode::AddChild(UEdGraphPin* FromPin, UQuickDialoguesBaseNode* InDialogueNode)
{
#if WITH_EDITOR
	Modify();
#endif
	// This is just a simple "one child only" model.
	// For multi-output branching nodes, override this behavior.
	Child = InDialogueNode;
}

void UQuickDialoguesBaseNode::RemoveChild(UQuickDialoguesBaseNode* InNode)
{
#if WITH_EDITOR
	Modify();
#endif
	if (IsValid(Child))
	{
		Child = nullptr;
	}
}

void UQuickDialoguesBaseNode::RemoveParent(UQuickDialoguesBaseNode* InParent)
{
#if WITH_EDITOR
	Modify();
#endif
	Parents.Remove(InParent);
}

void UQuickDialoguesBaseNode::OnNodeRemoval()
{
#if WITH_EDITOR
	Modify();
#endif
	// Inform parents that you're gone
	for (auto Element : Parents)
	{
		if (Element)
		{
			Element->RemoveChild(this);
		}
	}

	// And tell your child you're gone too
	if (IsValid(Child))
	{
		Child->RemoveParent(this);
	}
}

void UQuickDialoguesBaseNode::ResetConnections()
{
#if WITH_EDITOR
	Modify();
#endif
	// Nuke all connections (use when duplicating or resetting tree)
	Child = nullptr;
	Parents.Empty();
}

void UQuickDialoguesBaseNode::EmptyParents()
{
#if WITH_EDITOR
	Modify();
#endif
	Parents.Empty();
}

void UQuickDialoguesBaseNode::AddParent(UQuickDialoguesBaseNode* InParent)
{
#if WITH_EDITOR
	Modify();
#endif
	Parents.Add(InParent);
}

void UQuickDialoguesBaseNode::SetChildValue(UQuickDialoguesBaseNode* InChild)
{
#if WITH_EDITOR
	Modify();
#endif
	Child = InChild;
}

EQuickDialoguesNodeType UQuickDialoguesBaseNode::GetNodeType() const
{
	return NodeType;
}

void UQuickDialoguesBaseNode::SetTree(UQuickDialoguesNodeTree* InTree)
{
#if WITH_EDITOR
	Modify();
#endif
	Tree = InTree;
}

UQuickDialoguesNodeTree* UQuickDialoguesBaseNode::GetTree() const
{
	return Tree;
}

TArray<UQuickDialoguesBaseNode*> UQuickDialoguesBaseNode::GetParents() const
{
	return Parents;
}
