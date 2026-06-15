//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesNodeTree.h"

#include "Nodes/QuickDialoguesDialogueNode.h"
#include "Nodes/QuickDialoguesEndPointNode.h"
#include "Nodes/QuickDialoguesLoopbackNode.h"
#include "Nodes/QuickDialoguesPlayMontageNode.h"
#include "Nodes/QuickDialoguesRandomNode.h"
#include "Nodes/QuickDialoguesReplyNode.h"
#include "Nodes/QuickDialoguesRootNode.h"
#include "Nodes/QuickDialoguesWidgetOpenerNode.h"

UQuickDialoguesNodeTree::UQuickDialoguesNodeTree()
	: RootNode(nullptr),
	  CurrentNode(nullptr),
	  Owner(nullptr)
{
#if WITH_EDITORONLY_DATA
	Graph = nullptr;
#endif
}

void UQuickDialoguesNodeTree::SetUp(UObject* InOwner)
{
	// This is like "booting up" the node tree at runtime
	Owner = InOwner;
	CurrentNode = RootNode;
}

void UQuickDialoguesNodeTree::ResetFromRoot()
{
	CurrentNode = RootNode;
}

FName UQuickDialoguesNodeTree::GetNodeNameFromType(EQuickDialoguesNodeType InNodeType)
{
	// creates a unique name per node type, for sanity & readability
	switch (InNodeType)
	{
	case EQuickDialoguesNodeType::Reply:
		return MakeUniqueObjectName(this, UQuickDialoguesReplyNode::StaticClass(), TEXT("Reply Node"));
	case EQuickDialoguesNodeType::Dialogue:
		return MakeUniqueObjectName(this, UQuickDialoguesDialogueNode::StaticClass(), TEXT("Dialogue Node"));
	case EQuickDialoguesNodeType::Root:
		return MakeUniqueObjectName(this, UQuickDialoguesRootNode::StaticClass(), TEXT("Root Node"));
	case EQuickDialoguesNodeType::EndPoint:
		return MakeUniqueObjectName(this, UQuickDialoguesEndPointNode::StaticClass(), TEXT("End Point node"));
	case EQuickDialoguesNodeType::WidgetOpener:
		return MakeUniqueObjectName(this, UQuickDialoguesWidgetOpenerNode::StaticClass(), TEXT("Widget Opener Node"));
	case EQuickDialoguesNodeType::PlayMontage:
		return MakeUniqueObjectName(this, UQuickDialoguesPlayMontageNode::StaticClass(), TEXT("Play Montage Node"));
	case EQuickDialoguesNodeType::Random:
		return MakeUniqueObjectName(this, UQuickDialoguesRandomNode::StaticClass(), TEXT("Random Node"));
	case EQuickDialoguesNodeType::Loopback:
		return MakeUniqueObjectName(this, UQuickDialoguesLoopbackNode::StaticClass(), TEXT("Loopback Node"));
	default:
		return MakeUniqueObjectName(this, UQuickDialoguesBaseNode::StaticClass(), TEXT("Unknown node"));
	}
}

UQuickDialoguesBaseNode* UQuickDialoguesNodeTree::AddNode(
	EQuickDialoguesNodeType InNodeType,
	TSubclassOf<UQuickDialoguesBaseNode> InRunTimeClass)
{
#if WITH_EDITOR
	Modify();
#endif

	UQuickDialoguesBaseNode* NewNode = NewObject<UQuickDialoguesBaseNode>(
		this, InRunTimeClass, GetNodeNameFromType(InNodeType), RF_Transactional);

#if WITH_EDITOR
	NewNode->Modify();
#endif

	NewNode->NodeType = InNodeType;
	NewNode->SetTree(this);

	// only one root allowed, obviously
	if (NewNode->NodeType == EQuickDialoguesNodeType::Root)
	{
		RootNode = NewNode;
	}

	AllNodes.Add(NewNode);
	return NewNode;
}

void UQuickDialoguesNodeTree::RemoveNode(UQuickDialoguesBaseNode* InNode)
{
#if WITH_EDITOR
	Modify();
#endif
	if (!InNode)
	{
		return;
	}

	// if we’re deleting the root, clear that too
	if (RootNode == InNode)
	{
		RootNode = nullptr;
	}

	AllNodes.Remove(InNode);
	InNode->OnNodeRemoval(); // gives the node a chance to clean itself up
}

UQuickDialoguesBaseNode* UQuickDialoguesNodeTree::GetNextNode()
{
	if (!IsValid(Owner))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("UQuickDialoguesNodeTree::GetNextNode(), Owner is null — forgot to call SetUp()?"));
#endif
		return nullptr;
	}

	if (!IsValid(RootNode))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("UQuickDialoguesNodeTree::GetNextNode(), No RootNode defined — tree is broken"));
#endif
		return nullptr;
	}

	if (!IsValid(CurrentNode))
	{
		// starting fresh from root
		CurrentNode = RootNode;
	}
	else
	{
		// progress to next node (whatever the current one defines)
		CurrentNode = CurrentNode->GetNextNode(Owner);
	}

	return CurrentNode;
}

bool UQuickDialoguesNodeTree::GetHasCompileErrors()
{
	return bHasCompilesError;
}

void UQuickDialoguesNodeTree::SetHasCompileErrors(bool bInNewHasCompileErrors)
{
	bHasCompilesError = bInNewHasCompileErrors;
}

bool UQuickDialoguesNodeTree::GetHasBeenSavedAndValidated()
{
	// used to check if this asset was saved & validated (Before PIE)
	UPackage* Package = GetOutermost();
	if (!Package)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error,
		       TEXT("UQuickDialoguesNodeTree::GetHasBeenSavedAndValidated(), Something's wrong with the outer package"
		       ));
#endif
		return false;
	}

	return !Package->IsDirty(); // dirty = modified since last save
}

void UQuickDialoguesNodeTree::SetHasBeenSavedAndValidated(bool bInHasBeenCompiled)
{
	bHasBeenCompiled = bInHasBeenCompiled;
}
