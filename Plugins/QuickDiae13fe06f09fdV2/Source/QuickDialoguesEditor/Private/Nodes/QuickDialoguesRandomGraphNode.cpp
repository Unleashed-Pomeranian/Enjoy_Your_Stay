//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesRandomGraphNode.h"

#include "Nodes/QuickDialoguesRandomNode.h"
#include "Widgets/QuickDialoguesRandomGraphNodeWidget.h"

UQuickDialoguesRandomGraphNode::UQuickDialoguesRandomGraphNode()
{
}

void UQuickDialoguesRandomGraphNode::AllocateDefaultPins()
{
	Pins.Empty();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, TEXT("Previous Node"));
	AddNewRandomOutput();
}

void UQuickDialoguesRandomGraphNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->Direction == EGPD_Output)
	{
		if (UQuickDialoguesRandomNode* RandomNode = Cast<UQuickDialoguesRandomNode>(DialogueNode))
		{
			RandomNode->AddChildToMap(Pins.IndexOfByKey(Pin) - 1, nullptr);
			for (auto LinkedPin : Pin->LinkedTo)
			{
				UEdGraphNode* Node = LinkedPin->GetOwningNode();
				if (!Node)
				{
					continue;
				}

				if (const UQuickDialoguesBaseGraphNode* GraphNode = Cast<UQuickDialoguesBaseGraphNode>(Node))
				{
					RandomNode->AddChildToMap(Pins.IndexOfByKey(Pin) - 1, GraphNode->DialogueNode);
				}
			}
		}
	}
	Super::PinConnectionListChanged(Pin);

}

FText UQuickDialoguesRandomGraphNode::GetTooltipText() const
{
	return FText::FromString(TEXT("Node with dynamic output based on Randomness"));
}

void UQuickDialoguesRandomGraphNode::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UQuickDialoguesRandomGraphNode::ReconstructNode()
{
	Super::ReconstructNode();
	ResetOutputPinsNames();
}

void UQuickDialoguesRandomGraphNode::RemoveChoice(int32 InChoiceIndex)
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "Remove Choice", "Remove Choice"));

	Modify();

	if (Outputs.Num() <= 1)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "UQuickDialoguesGraphNode_RandomGraphNode::RemoveChoice Node must have at least 1 Choice"
		       ));
#endif
		return;
	}
	if (UQuickDialoguesRandomNode* RandomNode = Cast<UQuickDialoguesRandomNode>(
		DialogueNode))
	{
		RandomNode->Modify();
		RandomNode->RemoveChildAt(InChoiceIndex);
		Outputs.RemoveAt(InChoiceIndex);
	}
	else
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "UQuickDialoguesGraphNode_RandomGraphNode::RemoveChoice Tree node was not of type UQuickDialoguesRandomNode"
		       ));
#endif
	}
	if (Pins.IsValidIndex(1 + InChoiceIndex))
	{
		Pins[1 + InChoiceIndex]->BreakAllPinLinks(true);
		Pins.RemoveAt(1 + InChoiceIndex);
	}
	
	ReconstructNode();
}

void UQuickDialoguesRandomGraphNode::ResetOutputPinsNames()
{
	for (int32 i = Outputs.Num(); i > 0; i--)
	{
		if (Pins.IsValidIndex(i))
		{
			UEdGraphPin* FoundPin = Pins[i];
			if (FoundPin->Direction == EGPD_Output)
			{
				FoundPin->Modify();
				FoundPin->PinFriendlyName = FText::FromString(FString::Printf(TEXT("Output %d"), i - 1));
			}
		}
	}
}

void UQuickDialoguesRandomGraphNode::AddNewRandomOutput()
{

	if (UQuickDialoguesRandomNode* RandomNode = Cast<UQuickDialoguesRandomNode>(
		DialogueNode))
	{
		const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "AddNewRandomOutput", "Add new random output"));
		Modify();
		UEdGraphPin* OutputPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, "Output");
		Outputs.Add(nullptr);
		RandomNode->AddChildToMap(Pins.IndexOfByKey(OutputPin) - 1, nullptr);
		ReconstructNode();
	}

}

TSharedPtr<SGraphNode> UQuickDialoguesRandomGraphNode::CreateVisualWidget()
{
	return SNew(SQuickDialoguesRandomGraphNodeWidget, this);
}

void UQuickDialoguesRandomGraphNode::PostPasteNode()
{
	ReconstructNode();
}

#if WITH_EDITOR
void UQuickDialoguesRandomGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
                                                                class UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (Context && Context->Pin == nullptr)
	{
		FToolMenuSection& Section = Menu->FindOrAddSection("CustomDecisionGraphNodeActions");

		Section.AddMenuEntry(
			"AddChoice",
			FText::FromString("Add New Choice"),
			FText::FromString("Adds a new output pin"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateLambda([this]()
				{
					UQuickDialoguesRandomGraphNode* MutableThis = const_cast<
						UQuickDialoguesRandomGraphNode*>(this);
					MutableThis->AddNewRandomOutput();
				})
			)
		);

		if (Outputs.Num() > 0)
		{
			Section.AddSubMenu(
				"RemoveChoice",
				FText::FromString("Remove Choice"),
				FText::FromString("Remove an existing Choice"),
				FNewMenuDelegate::CreateLambda([this](FMenuBuilder& SubMenuBuilder)
				{
					for (int32 i = 0; i < Outputs.Num(); i++)
					{
						// FName Name = *FString::Printf(TEXT("Remove Output %d"), i);
						FText Label = FText::FromString(FString::Printf(TEXT("Remove Output %d"), i));
						FMenuEntryParams Params;
						Params.LabelOverride = Label;
						Params.IconOverride = FSlateIcon();
						Params.DirectActions = FUIAction(
							FExecuteAction::CreateLambda([this, i]()
							{
								UQuickDialoguesRandomGraphNode* MutableThis = const_cast<
									UQuickDialoguesRandomGraphNode*>(this);
								MutableThis->RemoveChoice(i);
							})
						);
						SubMenuBuilder.AddMenuEntry(Params);
					}
				})
			);
		}
	}
}
#endif
