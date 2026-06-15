//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesReplyGraphNode.h"

#include "EdGraphSchema_K2.h"
#include "ToolMenu.h"
#include "ToolMenuSection.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphPin.h"
#include "Modules/ModuleManager.h"
#include "Nodes/QuickDialoguesReplyNode.h"

UQuickDialoguesReplyGraphNode::UQuickDialoguesReplyGraphNode()
{
}

void UQuickDialoguesReplyGraphNode::AllocateDefaultPins()
{
	Pins.Empty();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, TEXT("Previous Node"));
	AddNewReply();
}

void UQuickDialoguesReplyGraphNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->Direction == EGPD_Output)
	{
		if (UQuickDialoguesReplyNode* ReplyNode = Cast<UQuickDialoguesReplyNode>(DialogueNode))
		{
			ReplyNode->AddChildToMap(Pins.IndexOfByKey(Pin) - 1, nullptr);
			for (auto LinkedPin : Pin->LinkedTo)
			{
				UEdGraphNode* Node = LinkedPin->GetOwningNode();
				if (!Node)
				{
					continue;
				}

				if (const UQuickDialoguesBaseGraphNode* GraphNode = Cast<UQuickDialoguesBaseGraphNode>(Node))
				{
					ReplyNode->AddChildToMap(Pins.IndexOfByKey(Pin) - 1, GraphNode->DialogueNode);
				}
			}
		}
	}
	Super::PinConnectionListChanged(Pin);
}

FText UQuickDialoguesReplyGraphNode::GetTooltipText() const
{
	return FText::FromString(TEXT("Node with dynamic output based on class selection"));
}

void UQuickDialoguesReplyGraphNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UQuickDialoguesReplyGraphNode::ReconstructNode()
{
	Super::ReconstructNode();
	ResetOutputPinsNames();
}

void UQuickDialoguesReplyGraphNode::ResetOutputPinsNames()
{
	for (int32 i = Pins.Num(); i >= 0; i--)
	{
		if (!Pins.IsValidIndex(i))
		{
			continue;
		}
		if (UEdGraphPin* FoundPin = Pins[i])
		{
			if (FoundPin->Direction == EGPD_Output)
			{
				FoundPin->Modify();
				FoundPin->PinFriendlyName = FText::FromString(FString::Printf(TEXT("Reply %d"), i - 1));
			}
		}
	}
}

void UQuickDialoguesReplyGraphNode::AddNewReply()
{
	if (UQuickDialoguesReplyNode* ReplyNode = Cast<UQuickDialoguesReplyNode>(
		DialogueNode))
	{
		const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "AddNewReply", "Add new reply"));

		Modify();

		FDialogueReply DefaultReply = FDialogueReply();
		DefaultReply.Text = FText::FromString(TEXT("Button Text"));
		DefaultReply.SelectedClass = nullptr;

		ReplyButtons.Add(DefaultReply);

		UEdGraphPin* OutputPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, "Output");
		
		ReplyNode->AddReply(DefaultReply);
		ReplyNode->AddChildToMap(Pins.IndexOfByKey(OutputPin) - 1, nullptr);
		ReconstructNode();
	}
}

void UQuickDialoguesReplyGraphNode::SetTextAtIndex(FText Text, int Index)
{
	if (!ReplyButtons.IsValidIndex(Index))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "UQuickDialoguesReplyGraphNode::SetTextAtIndex(), Index was not a valid Index for the ReplyButtons Array!"
		       ));
#endif
		return;
	}

	if (UQuickDialoguesReplyNode* ReplyNode = Cast<UQuickDialoguesReplyNode>(
		DialogueNode))
	{
		if (ReplyNode->SetReplyTextAtIndex(Index, Text))
		{
			Modify();
			ReplyButtons[Index].Text = Text;
		}
		return;
	}

#if WITH_EDITOR
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "UQuickDialoguesReplyGraphNode::SetTextAtIndex(), Tree node was not of type UQuickDialoguesReplyNode"
	       ));
#endif
}

void UQuickDialoguesReplyGraphNode::SelectClass(UClass* Class, int Index)
{
	if (!ReplyButtons.IsValidIndex(Index))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "UQuickDialoguesReplyGraphNode::SetTextAtIndex(), Index was not a valid Index for the ReplyButtons Array!"
		       ));
#endif
		return;
	}

	if (UQuickDialoguesReplyNode* ReplyNode = Cast<UQuickDialoguesReplyNode>(
		DialogueNode))
	{
		if (ReplyNode->SetClassAtIndex(Index, Class))
		{
			Modify();
			ReplyButtons[Index].SelectedClass = Class;
		}
		return;
	}

#if WITH_EDITOR
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "UQuickDialoguesReplyGraphNode::SelectClass(), Tree node was not of type UQuickDialoguesReplyNode"
	       ));
#endif
}

void UQuickDialoguesReplyGraphNode::RemoveReply(int32 ReplyIndex)
{
	if (ReplyButtons.Num() <= 1)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "UQuickDialoguesGraphNode_ReplyGraphNode::RemoveReply(), Node must have at least 1 Reply"
		       ));
#endif
		return;
	}
	if (!ReplyButtons.IsValidIndex(ReplyIndex))
	{
		return;
	}
	if (UQuickDialoguesReplyNode* ReplyNode = Cast<UQuickDialoguesReplyNode>(
		DialogueNode))
	{
		const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "RemoveReply", "Remove reply"));

		Modify();

		ReplyNode->RemoveChildAt(ReplyIndex);
		ReplyButtons.RemoveAt(ReplyIndex);

		if (Pins.IsValidIndex(1 + ReplyIndex))
		{
			Pins[1 + ReplyIndex]->BreakAllPinLinks(true);
			Pins.RemoveAt(1 + ReplyIndex);
		}

		ReconstructNode();
		return;
	}

#if WITH_EDITOR
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "UQuickDialoguesGraphNode_ReplyGraphNode::RemoveReply(), Tree node was not of type UQuickDialoguesReplyNode"
	       ));
#endif
}

TSharedPtr<SGraphNode> UQuickDialoguesReplyGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesReplyGraphNodeWidget, this);
}

#if WITH_EDITOR
void UQuickDialoguesReplyGraphNode::GetNodeContextMenuActions(
	UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (Context && Context->Pin == nullptr)
	{
		FToolMenuSection& Section = Menu->FindOrAddSection("CustomDecisionGraphNodeActions");

		Section.AddMenuEntry(
			"AddChildToMap",
			FText::FromString("Add New Reply"),
			FText::FromString("Adds a new output pin with class selection"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateLambda([this]()
				{
					UQuickDialoguesReplyGraphNode* MutableThis = const_cast<
						UQuickDialoguesReplyGraphNode*>(this);
					MutableThis->AddNewReply();
				})
			)
		);

		if (ReplyButtons.Num() > 0)
		{
			Section.AddSubMenu(
				"RemoveReply",
				FText::FromString("Remove Reply"),
				FText::FromString("Remove an existing Reply"),
				FNewMenuDelegate::CreateLambda([this](FMenuBuilder& SubMenuBuilder)
				{
					for (int32 i = 0; i < ReplyButtons.Num(); i++)
					{
						FText Label = FText::FromString(FString::Printf(TEXT("Remove Output %d"), i));
						FMenuEntryParams Params;
						Params.LabelOverride = Label;
						Params.IconOverride = FSlateIcon();
						Params.DirectActions = FUIAction(
							FExecuteAction::CreateLambda([this, i]()
							{
								UQuickDialoguesReplyGraphNode* MutableThis = const_cast<
									UQuickDialoguesReplyGraphNode*>(this);
								MutableThis->RemoveReply(i);
							})
						);
						SubMenuBuilder.AddMenuEntry(Params
						);
					}
				})
			);
		}
	}
}
#endif
