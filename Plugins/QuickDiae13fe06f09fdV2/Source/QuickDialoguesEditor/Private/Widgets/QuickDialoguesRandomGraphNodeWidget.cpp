//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesRandomGraphNodeWidget.h"

#include "SGraphPin.h"
#include "Nodes/QuickDialoguesRandomGraphNode.h"

SQuickDialoguesRandomGraphNodeWidget::SQuickDialoguesRandomGraphNodeWidget()
{
}

void SQuickDialoguesRandomGraphNodeWidget::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bIsInput = PinObj->Direction == EGPD_Input;

	if (bIsInput)
	{
		LeftNodeBox->AddSlot()
				   .AutoHeight()
				   .HAlign(HAlign_Left)
				   .VAlign(VAlign_Center)
				   .Padding(10.0f, 5.0f)
		[
			PinToAdd
		];
		InputPins.Add(PinToAdd);
	}
	else // Is Output
	{
		RightNodeBox->AddSlot()
					.AutoHeight()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(10.0f, 5.0f)
		[
			PinToAdd
		];
		OutputPins.Add(PinToAdd);
	}
}

SQuickDialoguesRandomGraphNodeWidget::SQuickDialoguesRandomGraphNodeWidget(UQuickDialoguesBaseGraphNode* MyGraphNode,
                                                                             const TSharedPtr<SEditableTextBox>&
                                                                             EditableText)
{
}

void SQuickDialoguesRandomGraphNodeWidget::Construct(const FArguments& InArgs,
                                                      UQuickDialoguesBaseGraphNode* InGraphNode)
{
	SQuickDialoguesBaseGraphNodeWidget::Construct({}, InGraphNode);
	ContentVerticalBox->AddSlot()
	                  .HAlign(HAlign_Fill)
	                  .VAlign(VAlign_Fill)

	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		[
			CreateNodeContentArea()
		]
	];

	if (UQuickDialoguesRandomGraphNode* RandomGraphNode = Cast<UQuickDialoguesRandomGraphNode>(InGraphNode))
	{
		for (int32 i = 0; i < RandomGraphNode->Outputs.Num(); ++i)
		{
			TSharedRef<SHorizontalBox> OutputHorizontalBox = SNew(SHorizontalBox);

			OutputHorizontalBox->AddSlot()
			                   .AutoWidth()
			                   .Padding(5, 0.f)
			[
				SNew(SButton)
				.Text(FText::FromString("X"))
				.ButtonStyle(FAppStyle::Get(), "FlatButton.Danger")
				.OnClicked_Lambda([this, i]() { return OnRemoveChoiceButtonClicked(i); })
			];

			ChoicesBox->AddSlot()
			          .AutoHeight()
			          .VAlign(VAlign_Center) // Ensure vertical center alignment
			          .Padding(5, 5.f) // Match the padding with the pins
			[
				OutputHorizontalBox
			];
		}
	}
	SetupErrorSlot();
	CreatePinWidgets();
	UpdateGraphNode();
}

TSharedRef<SWidget> SQuickDialoguesRandomGraphNodeWidget::CreateNodeContentArea()
{
	TSharedPtr<SVerticalBox> NodeContent = SNew(SVerticalBox);

	NodeContent->AddSlot()
	           .AutoHeight()
	           .HAlign(HAlign_Center)
	           .Padding(10.f)
	[
		SNew(SButton)
		.Text(FText::FromString("Add Choice"))
		.OnClicked(this, &SQuickDialoguesRandomGraphNodeWidget::OnAddChoiceButtonClicked)
		.ButtonStyle(FAppStyle::Get(), "FlatButton.Success")
		.ContentPadding(FMargin(6.0f, 2.0f))
	];

	// Pin boxes
	NodeContent->AddSlot()
	           .AutoHeight()
	           .Padding(10.0f)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		  .AutoWidth() // Left pins get 20% width
		  .VAlign(VAlign_Fill) // Fill vertical space
		  .HAlign(HAlign_Left)
		[
			SAssignNew(LeftNodeBox, SVerticalBox)
		]
		+ SHorizontalBox::Slot()
		  .FillWidth(1.f) // Center ReplyList gets 60% width
		  .HAlign(HAlign_Center)
		  .VAlign(VAlign_Fill) // Fill vertical space
		[
			SAssignNew(ChoicesBox, SVerticalBox)
		]
		+ SHorizontalBox::Slot()
		  .AutoWidth() // Right pins get 20% width
		  .VAlign(VAlign_Fill) // Fill vertical space
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]
	];

	return NodeContent.ToSharedRef();
}

FReply SQuickDialoguesRandomGraphNodeWidget::OnAddChoiceButtonClicked() const
{
	if (GraphNode)
	{
		if (UQuickDialoguesRandomGraphNode* RandomNode = Cast<
			UQuickDialoguesRandomGraphNode>(GraphNode))
		{
			RandomNode->AddNewRandomOutput();
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}

FReply SQuickDialoguesRandomGraphNodeWidget::OnRemoveChoiceButtonClicked(int32 InIndex)
{
	if (GraphNode)
	{
		if (UQuickDialoguesRandomGraphNode* RandomNode = Cast<
			UQuickDialoguesRandomGraphNode>(GraphNode))
		{
			RandomNode->RemoveChoice(InIndex);
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}
