//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesGraphSchema.h"
#include "QuickDialoguesConnectionDrawingPolicy.h"
#include "QuickDialoguesGraph.h"
#include "QuickDialoguesNodeTree.h"
#include "ToolMenu.h"
#include "ToolMenuSection.h"
#include "EdGraph/EdGraphSchema.h"
#include "Nodes/QuickDialoguesBaseGraphNode.h"
#include "Nodes/QuickDialoguesDialogueGraphNode.h"
#include "Nodes/QuickDialoguesDialogueNode.h"
#include "Nodes/QuickDialoguesEndPointGraphNode.h"
#include "Nodes/QuickDialoguesEndPointNode.h"
#include "Nodes/QuickDialoguesLoopbackGraphNode.h"
#include "Nodes/QuickDialoguesLoopbackNode.h"
#include "Nodes/QuickDialoguesPlayMontageGraphNode.h"
#include "Nodes/QuickDialoguesPlayMontageNode.h"
#include "Nodes/QuickDialoguesRandomGraphNode.h"
#include "Nodes/QuickDialoguesRandomNode.h"
#include "Nodes/QuickDialoguesReplyGraphNode.h"
#include "Nodes/QuickDialoguesReplyNode.h"
#include "Nodes/QuickDialoguesRootGraphNode.h"
#include "Nodes/QuickDialoguesRootNode.h"
#include "Nodes/QuickDialoguesWidgetOpenerGraphNode.h"
#include "Nodes/QuickDialoguesWidgetOpenerNode.h"

struct FNewDialogueNodeAction : public FEdGraphSchemaAction
{
	FNewDialogueNodeAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip,
	                       int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping)
		  , NodeType(EQuickDialoguesNodeType::Root), GraphNodeClass(nullptr), RuntimeNodeClass(nullptr)
	{
	}

	EQuickDialoguesNodeType NodeType;
	TSubclassOf<UQuickDialoguesBaseGraphNode> GraphNodeClass;
	TSubclassOf<UQuickDialoguesBaseNode> RuntimeNodeClass;

	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location,
	                                    bool bSelectNewNode = true) override
	{
		if (GraphNodeClass == nullptr || RuntimeNodeClass == nullptr)
		{
#if WITH_EDITOR
			UE_LOG(LogTemp, Error, TEXT("QuickDialoguesGraphNode_Base::PerformAction(), Class was null"));
#endif
			return nullptr;
		}
		UQuickDialoguesGraph* DialogueGraph = Cast<UQuickDialoguesGraph>(ParentGraph);
		if (!DialogueGraph)
		{
			return nullptr;
		}
		if (NodeType == EQuickDialoguesNodeType::Root && DialogueGraph->GetRootNode() != nullptr)
		{
#if WITH_EDITOR
			UE_LOG(LogTemp, Warning, TEXT("QuickDialoguesGraphNode_Base::PerformAction(), A root already exists!"));
#endif
			return nullptr;
		}

		DialogueGraph->Modify();
		UQuickDialoguesBaseGraphNode* NewGraphNode = NewObject<UQuickDialoguesBaseGraphNode>(
			ParentGraph, GraphNodeClass);
		NewGraphNode->Modify();

		if (NodeType == EQuickDialoguesNodeType::Root)
		{
			DialogueGraph->SetRootNode(NewGraphNode);
		}

		NewGraphNode->DialogueNode = DialogueGraph->NodeTree->AddNode(NodeType, RuntimeNodeClass);

		NewGraphNode->DialogueNode->SetDialogue(FText::FromString("Unimplemented Dialogue"));

		NewGraphNode->AllocateDefaultPins();
		NewGraphNode->NodePosX = Location.X;
		NewGraphNode->NodePosY = Location.Y;

		DialogueGraph->AddNode(NewGraphNode, true, bSelectNewNode);

		if (FromPin)
		{
			UEdGraphPin* NewNodeInputPin = NewGraphNode->FindPin(TEXT("Previous Node"));

			if (FromPin->Direction == EGPD_Output && NewNodeInputPin)
			{
				NewGraphNode->AutowireNewNode(FromPin);
				FromPin->Modify();
				FromPin->BreakAllPinLinks(true);
				FromPin->MakeLinkTo(NewNodeInputPin);
				if (auto TreeNode = Cast<UQuickDialoguesBaseGraphNode>(FromPin->GetOwningNode()))
				{
					NewGraphNode->DialogueNode->AddParent(TreeNode->DialogueNode);
					if (UQuickDialoguesMultiOutputNode* ReplyNode = Cast<UQuickDialoguesMultiOutputNode>(
						TreeNode->DialogueNode))
					{
						ReplyNode->AddChildToMap(TreeNode->Pins.IndexOfByKey(FromPin) - 1,
						                         NewGraphNode->DialogueNode);
					}
					else
					{
						TreeNode->DialogueNode->AddChild(FromPin, NewGraphNode->DialogueNode);
					}
				}
			}
		}

		return NewGraphNode;
	}
};

UQuickDialoguesGraphSchema::UQuickDialoguesGraphSchema()
{
	this->SetFlags(RF_Transactional);
}

void UQuickDialoguesGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const FText CategoryName = FText::FromString(TEXT("Quick Dialogue"));

	auto AddNodeAction = [&ContextMenuBuilder, &CategoryName](FText NodeLabel, FText Tooltip,
	                                                          EQuickDialoguesNodeType NodeType,
	                                                          UClass* RuntimeNodeClass, UClass* GraphNodeClass)
	{
		TSharedPtr<FNewDialogueNodeAction> NewNodeAction = MakeShareable(new FNewDialogueNodeAction(
			CategoryName,
			NodeLabel,
			Tooltip,
			0));

		NewNodeAction->NodeType = NodeType;
		NewNodeAction->RuntimeNodeClass = RuntimeNodeClass;
		NewNodeAction->GraphNodeClass = GraphNodeClass;

		ContextMenuBuilder.AddAction(NewNodeAction);
	};

	AddNodeAction(
		FText::FromString(TEXT("Add the Root Node")),
		FText::FromString(TEXT("Add a Root node (only one allowed per tree)")),
		EQuickDialoguesNodeType::Root,
		UQuickDialoguesRootNode::StaticClass(),
		UQuickDialoguesRootGraphNode::StaticClass()
	);

	AddNodeAction(
		FText::FromString(TEXT("Add a Dialogue Node")),
		FText::FromString(TEXT("Add a new Dialogue node")),
		EQuickDialoguesNodeType::Dialogue,
		UQuickDialoguesDialogueNode::StaticClass(),
		UQuickDialoguesDialogueGraphNode::StaticClass()
	);

	AddNodeAction(
		FText::FromString(TEXT("Add the EndPoint Node")),
		FText::FromString(TEXT("Add an EndPoint node (only one allowed per tree)")),
		EQuickDialoguesNodeType::EndPoint,
		UQuickDialoguesEndPointNode::StaticClass(),
		UQuickDialoguesEndPointGraphNode::StaticClass()
	);

	AddNodeAction(
		FText::FromString(TEXT("Add a Reply Node")),
		FText::FromString(TEXT("Add a Reply node")),
		EQuickDialoguesNodeType::Reply,
		UQuickDialoguesReplyNode::StaticClass(),
		UQuickDialoguesReplyGraphNode::StaticClass()
	);

	AddNodeAction(
		FText::FromString(TEXT("Add a Widget Opener Node")),
		FText::FromString(TEXT("Add a Widget Opener node")),
		EQuickDialoguesNodeType::WidgetOpener,
		UQuickDialoguesWidgetOpenerNode::StaticClass(),
		UQuickDialoguesWidgetOpenerGraphNode::StaticClass()
	);

	AddNodeAction(
		FText::FromString(TEXT("Add a Play Montage Node")),
		FText::FromString(TEXT("Add a Play Montage node")),
		EQuickDialoguesNodeType::PlayMontage,
		UQuickDialoguesPlayMontageNode::StaticClass(),
		UQuickDialoguesPlayMontageGraphNode::StaticClass()
	);

	AddNodeAction(
		FText::FromString(TEXT("Add a Random Node")),
		FText::FromString(TEXT("Add a Random node")),
		EQuickDialoguesNodeType::Random,
		UQuickDialoguesRandomNode::StaticClass(),
		UQuickDialoguesRandomGraphNode::StaticClass()
	);

	AddNodeAction(
		FText::FromString(TEXT("Add a Loopback Node")),
		FText::FromString(TEXT("Add a Loopback node")),
		EQuickDialoguesNodeType::Loopback,
		UQuickDialoguesLoopbackNode::StaticClass(),
		UQuickDialoguesLoopbackGraphNode::StaticClass()
	);
}

void UQuickDialoguesGraphSchema::GetContextMenuActions(UToolMenu* Menu,
                                                       UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection("QuickDialoguesNodeActions",
		                                             FText::FromString(TEXT("Node Actions")));
		Section.AddMenuEntry(
			"DeleteNode",
			FText::FromString(TEXT("Delete Node")),
			FText::FromString(TEXT("Delete this node")),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateLambda([this,Context]()
					{
						const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "Delete Node", "Delete Node"));
						DeleteNode(Context->Node);
					}
				)

			)
		);
	}
}

void UQuickDialoguesGraphSchema::DeleteNode(const TObjectPtr<const UEdGraphNode>& Node) const
{
	if (Node)
	{
		UEdGraphNode* NonConstNode = const_cast<UEdGraphNode*>(Node.Get());
		if (UQuickDialoguesGraph* DialogueGraph = Cast<UQuickDialoguesGraph>(
			Node->GetGraph()))
		{
			if (UQuickDialoguesBaseGraphNode* BaseNode = Cast<
				UQuickDialoguesBaseGraphNode>(NonConstNode))
			{
				if (DialogueGraph->GetRootNode() == Node)
				{
					DialogueGraph->ResetRootNode();
				}
				DialogueGraph->NodeTree->RemoveNode(BaseNode->DialogueNode);
				Node->GetGraph()->RemoveNode(NonConstNode);
				BaseNode->DestroyNode();
			}
		}
	}
}

const FPinConnectionResponse UQuickDialoguesGraphSchema::CanCreateConnection(
	const UEdGraphPin* A, const UEdGraphPin* B) const
{
	UE_LOG(LogTemp, Log, TEXT("CanCreateConnection called: A = %s, B = %s"),
	       *A->PinName.ToString(), *B->PinName.ToString());

	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Cannot connect a node to itself"));
	}

	bool bProperDirection = (A->Direction == EGPD_Output && B->Direction == EGPD_Input) ||
		(A->Direction == EGPD_Input && B->Direction == EGPD_Output);

	if (!bProperDirection)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Pins must have opposite directions"));
	}

	const UEdGraphPin* OutputPin = (A->Direction == EGPD_Output) ? A : B;
	const UEdGraphPin* InputPin = (A->Direction == EGPD_Input) ? A : B;

	auto CastedOutput = Cast<UQuickDialoguesBaseGraphNode>(OutputPin->GetOwningNode());
	auto CastedInput = Cast<UQuickDialoguesBaseGraphNode>(InputPin->GetOwningNode());
	if (CastedOutput && CastedInput)
	{
		if (CastedOutput->CheckIfNodeIsPresentInParentChain(CastedInput->DialogueNode))
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
			                              TEXT("Nodes can't loop back, use a loopback node"));
		}
	}

	if (OutputPin->LinkedTo.Num() > 0)
	{
		if (A->Direction == EGPD_Input)
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_B, TEXT("Replacing existing connection"));
		}
		else
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT("Replacing existing connection"));
		}
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT("Add connection"));
}

FLinearColor UQuickDialoguesGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor(0.7f, 0.7f, 0.7f);
}

FConnectionDrawingPolicy* UQuickDialoguesGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID,
	int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect,
	class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	return new FQuickDialoguesConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect,
	                                                  InDrawElements, InGraphObj);
}

bool UQuickDialoguesGraphSchema::DoesSupportPinWatching() const
{
	return true;
}
