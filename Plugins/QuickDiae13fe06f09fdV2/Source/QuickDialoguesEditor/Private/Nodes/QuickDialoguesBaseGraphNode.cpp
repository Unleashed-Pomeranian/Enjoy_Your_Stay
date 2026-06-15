//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesBaseGraphNode.h"

#include "EdGraph/EdGraphPin.h"
#include "Nodes/QuickDialoguesBaseNode.h"
#include "Widgets/QuickDialoguesBaseGraphNodeWidget.h"
#include "Widgets/Text/STextBlock.h"

UQuickDialoguesBaseGraphNode::UQuickDialoguesBaseGraphNode()
{
	DialogueNode = nullptr;
	SetFlags(RF_Transactional);
}

UQuickDialoguesBaseGraphNode::~UQuickDialoguesBaseGraphNode()
{
}

TSharedPtr<SGraphNode> UQuickDialoguesBaseGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesBaseGraphNodeWidget, this);
}

void UQuickDialoguesBaseGraphNode::AllocateDefaultPins()
{
	Pins.Empty();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, TEXT("Previous Node"));
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Next Node"));
}

FText UQuickDialoguesBaseGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (DialogueNode)
	{
		FString NameWithoutUnderScore = FText::FromName(DialogueNode->GetFName()).ToString().Replace(TEXT("_"),TEXT(" "));
		FString NameWithoutPrefix = NameWithoutUnderScore.Replace(TEXT("QuickDialogues"), TEXT(" "));
		return FText::FromString(NameWithoutPrefix);
	}
	return FText::FromString("Untitled Node");
}

FLinearColor UQuickDialoguesBaseGraphNode::GetNodeTitleColor() const
{
	if (!DialogueNode)
	{
		return FLinearColor::White;
	}

	switch (DialogueNode->GetNodeType())
	{
	case EQuickDialoguesNodeType::Root:
		return FLinearColor::Green;
	case EQuickDialoguesNodeType::Dialogue:
		return FLinearColor::Red;
	default:
		return FLinearColor::White;
	}
}

FText UQuickDialoguesBaseGraphNode::GetTooltipText() const
{
	return DialogueNode ? FText::FromString("Yep, that's a node!") : FText::FromString("No data available");
}

void UQuickDialoguesBaseGraphNode::PostLoad()
{
	Super::PostLoad();

	// Last resort if it failed to create a DialogueNode
	if (!DialogueNode)
	{
		DialogueNode = NewObject<UQuickDialoguesBaseNode>(this);
	}
}

void UQuickDialoguesBaseGraphNode::PostEditImport()
{
	Super::PostEditImport();

	if (!NodeGuid.IsValid())
	{
		NodeGuid = FGuid::NewGuid();
	}

	if (!DialogueNode)
	{
		DialogueNode = NewObject<UQuickDialoguesBaseNode>(this);
	}
	ReconstructNode();
}

void UQuickDialoguesBaseGraphNode::PostDuplicate(bool bDuplicateForPIE)
{
	Super::PostDuplicate(bDuplicateForPIE);
}

void UQuickDialoguesBaseGraphNode::PostInitProperties()
{
	Super::PostInitProperties();
	if (!NodeGuid.IsValid())
	{
		NodeGuid = FGuid::NewGuid();
	}
}

void UQuickDialoguesBaseGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin)
	{
		UEdGraphPin* TargetInputPin = FindPin(TEXT("Input"));
		if (TargetInputPin && FromPin->Direction == EGPD_Output)
		{
			UE_LOG(LogTemp, Log, TEXT("Auto-wiring from pin %s to %s"), *FromPin->PinName.ToString(),
			       *TargetInputPin->PinName.ToString());
			FromPin->MakeLinkTo(TargetInputPin);
		}
	}
}

bool UQuickDialoguesBaseGraphNode::CheckIfNodeIsPresentInParentChain(UQuickDialoguesBaseNode* NodeToFind)
{
	if (NodeToFind->GetNodeType() == EQuickDialoguesNodeType::Loopback ||
		NodeToFind->GetNodeType() == EQuickDialoguesNodeType::Root ||
		NodeToFind->GetNodeType() == EQuickDialoguesNodeType::EndPoint)
	{
		return false;
	}
	
	constexpr int MAX_ITERATIONS = 300;

	TSet<UQuickDialoguesBaseNode*> Visited;
	TArray<UQuickDialoguesBaseNode*> ToBeVisited = DialogueNode->GetParents();
	int Iterations = 0;
	while (ToBeVisited.Num() > 0 && Iterations < MAX_ITERATIONS)
	{
		UQuickDialoguesBaseNode* CurrentNode = ToBeVisited.Pop();
		Iterations++;

		if (!CurrentNode || Visited.Contains(CurrentNode) || CurrentNode->GetNodeType() == EQuickDialoguesNodeType::Loopback)
		{
			continue;
		}

		if (CurrentNode == NodeToFind)
		{
			return true;
		}
		Visited.Add(CurrentNode);
		TArray<UQuickDialoguesBaseNode*> Children = CurrentNode->GetParents();
		ToBeVisited.Append(Children);
	}
	return false;
}

void UQuickDialoguesBaseGraphNode::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UQuickDialoguesBaseGraphNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::PinConnectionListChanged(Pin);
	if (Pin->Direction == EGPD_Input)
	{
		DialogueNode->EmptyParents();
		for (auto LinkedPin : Pin->LinkedTo)
		{
			UEdGraphNode* Node = LinkedPin->GetOwningNode();
			if (!Node)
			{
				continue;
			}
			if (UQuickDialoguesBaseGraphNode* GraphNode = Cast<UQuickDialoguesBaseGraphNode>(Node))
			{
				DialogueNode->AddParent(GraphNode->DialogueNode);
			}
		}
	}
	else if (Pin->Direction == EGPD_Output && DialogueNode->GetUsesDefaultChildren())
	{
		DialogueNode->SetChildValue(nullptr);
		for (auto LinkedPin : Pin->LinkedTo)
		{
			UEdGraphNode* Node = LinkedPin->GetOwningNode();
			if (!Node)
			{
				continue;
			}

			if (UQuickDialoguesBaseGraphNode* GraphNode = Cast<UQuickDialoguesBaseGraphNode>(Node))
			{
				DialogueNode->SetChildValue(GraphNode->DialogueNode);
			}
		}
	}
}

void UQuickDialoguesBaseGraphNode::ReconstructNode()
{
	Super::ReconstructNode();
	GetGraph()->NotifyNodeChanged(this);
}

#if WITH_EDITOR
void UQuickDialoguesBaseGraphNode::PostEditUndo()
{
	Super::PostEditUndo();

	// Re‑run your pin‑sync logic on every pin so your runtime model is updated
	for (UEdGraphPin* Pin : Pins)
	{
		PinConnectionListChanged(Pin);
	}

	// Make sure the graph UI stays up to date
	if (UEdGraph* Graph = GetGraph())
	{
		Graph->NotifyNodeChanged(this);
	}
}
#endif
void UQuickDialoguesBaseGraphNode::SetNode(UQuickDialoguesBaseNode* InNode)
{
	DialogueNode = InNode;
}
