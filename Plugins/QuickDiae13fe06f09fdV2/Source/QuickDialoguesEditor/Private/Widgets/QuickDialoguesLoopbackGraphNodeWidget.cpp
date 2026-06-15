//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesLoopbackGraphNodeWidget.h"

#include "Nodes/QuickDialoguesLoopbackNode.h"

void SQuickDialoguesLoopbackGraphNodeWidget::Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InNode)
{
	SQuickDialoguesBaseGraphNodeWidget::Construct({}, InNode);

	UQuickDialoguesLoopbackNode* LoopbackNode = Cast<UQuickDialoguesLoopbackNode>(InNode->DialogueNode);
	if (!IsValid(LoopbackNode))
	{
		return;
	}

	AllNodes = LoopbackNode->GetParentChain();

	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	                  .HAlign(HAlign_Center)
	                  .Padding(0, 0, 0, 0)
	[
		SAssignNew(LoopbackComboBox, SComboBox<UQuickDialoguesBaseNode*>)
		.OptionsSource(&AllNodes)
		.OnGenerateWidget_Lambda([](UQuickDialoguesBaseNode* Item)
		{
			if (Item)
			{
				FString NoUnderscoreName = Item->GetFName().ToString().Replace(TEXT("_"),TEXT(" "));
				return SNew(STextBlock).Text(FText::FromString(NoUnderscoreName));
			}
			return SNew(STextBlock).Text(FText::FromString("No node selected."));
		})
		.OnSelectionChanged_Lambda([this, LoopbackNode](UQuickDialoguesBaseNode* NewValue, ESelectInfo::Type)
		{
			if (IsValid(NewValue))
			{
				const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "BooleanChanged", "Boolean Changed"));
				LoopbackNode->SetChildValue(NewValue);
			}
		})
		.Content()
		[
			SNew(STextBlock).Text_Lambda([this,LoopbackNode]() -> FText
			{
				if (LoopbackNode->GetChild())
				{
					return FText::FromName(LoopbackNode->GetChild()->GetFName());
				}
				return FText::FromString(TEXT("NoneSelected"));
			})
		]
	];

	SetupDefaultPins();
	SetupErrorSlot();
	CreatePinWidgets();
	this->UpdateGraphNode();
}
