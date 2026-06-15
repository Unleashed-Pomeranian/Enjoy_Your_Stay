//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesReplyGraphNodeWidget.h"

#include "PropertyCustomizationHelpers.h"
#include "QuickDialoguesUIButton.h"
#include "SGraphPin.h"
#include "Nodes/QuickDialoguesReplyGraphNode.h"
#include "Nodes/QuickDialoguesReplyNode.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SQuickDialoguesReplyGraphNodeWidget::Construct(const FArguments& InArgs,
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
	SetupErrorSlot();
	CreatePinWidgets();
	UpdateGraphNode();
	PopulateReplySlots();
}

void SQuickDialoguesReplyGraphNodeWidget::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();

	if (PinObj->Direction == EGPD_Input)
	{
		LeftNodeBox->AddSlot()
		           .AutoHeight()
		           .HAlign(HAlign_Left)
		           .VAlign(VAlign_Center)
		           .Padding(10.0f, 10.0f)
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
		            .Padding(10.0f, 10.0f)
		[
			PinToAdd
		];
		OutputPins.Add(PinToAdd);
	}
}

void SQuickDialoguesReplyGraphNodeWidget::PopulateReplySlots()
{
	if (ReplyListBox.IsValid())
	{
		ReplyListBox->ClearChildren();

		UQuickDialoguesReplyGraphNode* ReplyNode = Cast<
			UQuickDialoguesReplyGraphNode>(GraphNode);
		if (ReplyNode)
		{
			for (int32 i = 0; i < ReplyNode->ReplyButtons.Num(); ++i)
			{
				TSharedRef<SHorizontalBox> OutputHorizontalBox = SNew(SHorizontalBox);

				// Add Output Label
				OutputHorizontalBox->AddSlot()
				                   .AutoWidth()
				                   .VAlign(VAlign_Center)
				                   .HAlign(HAlign_Left)
				                   .Padding(5, 0)
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("Option %d:"), i)))
				];

				OutputHorizontalBox->AddSlot()
				                   .FillWidth(1.f)
				                   .VAlign(VAlign_Center)
				                   .HAlign(HAlign_Left)
				                   .Padding(5, 0)
				[
					SNew(SObjectPropertyEntryBox)
					.AllowedClass(UBlueprint::StaticClass())
					.OnShouldFilterAsset(FOnShouldFilterAsset::CreateLambda([](const FAssetData& AssetData)
					{
						FAssetTagValueRef ParentClassRef = AssetData.TagsAndValues.FindTag("ParentClass");
						if (ParentClassRef.IsSet())
						{
							UClass* ParentClass = FindObject<UClass>(nullptr, *ParentClassRef.GetValue());
							if (ParentClass && ParentClass->IsChildOf(UQuickDialoguesUIButton::StaticClass()))
							{
								return false;
							}
						}
						return true;
					}))
					.OnObjectChanged_Lambda([this, i, ReplyNode](const FAssetData& AssetData)
					{
						if (ReplyNode && ReplyNode->ReplyButtons.IsValidIndex(i))
						{
							const FScopedTransaction Transaction(
								NSLOCTEXT("UnrealEd", "ReplyClassChanged", "Reply Class Changed"));

							UBlueprint* BlueprintAsset = Cast<UBlueprint>(AssetData.GetAsset());

							UClass* SelectedClass = BlueprintAsset ? BlueprintAsset->GeneratedClass : nullptr;

							ReplyNode->SelectClass(SelectedClass, i);

							ReplyNode->ReconstructNode();
						}
					})
					.ObjectPath(ReplyNode->ReplyButtons.IsValidIndex(i)
						            ? ReplyNode->ReplyButtons[i].SelectedClass->GetPathName()
						            : FString())
					.DisplayUseSelected(true)
					.DisplayBrowse(true)
					.NewAssetFactories({})
				];

				OutputHorizontalBox->AddSlot()
				                   .AutoWidth()
				                   .HAlign(HAlign_Right)
				                   .Padding(5, 0)
				[
					SNew(SMultiLineEditableTextBox)
					.AllowMultiLine(false)
					.SelectAllTextWhenFocused(true)
					.ClearKeyboardFocusOnCommit(true)
					.Text_Lambda([this,i]() -> FText
					{
						if (UQuickDialoguesReplyGraphNode* TypedNode = Cast<
							UQuickDialoguesReplyGraphNode>(
							GraphNode))
						{
							if (TypedNode->ReplyButtons.IsValidIndex(i))
							{
								return TypedNode->ReplyButtons[i].Text;
							}
						}
						return FText::GetEmpty();
					})
					.OnTextCommitted_Lambda([this,i](const FText& NewText, ETextCommit::Type CommitType)
					{
						const FScopedTransaction Transaction(
							NSLOCTEXT("UnrealEd", "ReplyTextChanged", "Reply Text Changed"));

						constexpr int32 MaxCharacters = 50;
						FText Text = NewText;
						if (NewText.ToString().Len() > MaxCharacters)
						{
							Text = FText::FromString(NewText.ToString().Left(MaxCharacters));
						}
						if (UQuickDialoguesReplyGraphNode* TypedNode = Cast<
							UQuickDialoguesReplyGraphNode>(
							GraphNode))
						{
							TypedNode->SetTextAtIndex(Text, i);
							TypedNode->ReconstructNode();
						}
					})
				];
				// Add Remove Button
				OutputHorizontalBox->AddSlot()
				                   .AutoWidth()
				                   .Padding(5, 0)
				[
					SNew(SButton)
					.Text(FText::FromString("X"))
					.ButtonStyle(FAppStyle::Get(), "FlatButton.Danger")
					.OnClicked_Lambda([this, i]() { return OnRemoveReplyButtonClicked(i); })
				];

				ReplyListBox->AddSlot()
				            .AutoHeight()
				            .VAlign(VAlign_Center) // Ensure vertical center alignment
				            .Padding(5, 10.0f) // Match the padding with the pins
				[
					OutputHorizontalBox
				];
			}
		}
	}
}

TSharedRef<SWidget> SQuickDialoguesReplyGraphNodeWidget::CreateNodeContentArea()
{
	TSharedPtr<SVerticalBox> NodeContent = SNew(SVerticalBox);

	NodeContent->AddSlot()
	           .AutoHeight()
	           .VAlign(VAlign_Center)
	           .HAlign(HAlign_Center)
	           .Padding(5, 0)
	[
		SNew(SMultiLineEditableTextBox)
		.AllowMultiLine(true)
		.Text_Lambda([this]() -> FText
		{
			if (UQuickDialoguesBaseGraphNode* TypedNode = Cast<UQuickDialoguesBaseGraphNode>(GraphNode))
			{
				if (TypedNode && TypedNode->DialogueNode)
				{
					return TypedNode->DialogueNode->GetNodeDialogueData();
				}
			}

			return FText::GetEmpty();
		})
		.OnTextCommitted_Lambda([this](const FText& NewText, ETextCommit::Type CommitType)
		{
			if (UQuickDialoguesBaseGraphNode* TypedNode = Cast<UQuickDialoguesBaseGraphNode>(GraphNode))
			{
				if (TypedNode && TypedNode->DialogueNode)
				{
					const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "DialogueTextChanged",
					                                               "Dialogue Text Changed"));
					TypedNode->DialogueNode->SetDialogue(NewText);
					TypedNode->ReconstructNode();
				}
			}
		})
	];
	NodeContent->AddSlot()
	           .AutoHeight()
	           .HAlign(HAlign_Center)
	           .Padding(10.0f)
	[
		SAssignNew(AddReplyButton, SButton)
		.Text(FText::FromString("Add Reply"))
		.OnClicked(this, &SQuickDialoguesReplyGraphNodeWidget::OnAddReplyButtonClicked)
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
			SAssignNew(ReplyListBox, SVerticalBox)
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

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SQuickDialoguesReplyGraphNodeWidget::OnAddReplyButtonClicked()
{
	if (GraphNode)
	{
		if (UQuickDialoguesReplyGraphNode* ReplyNode = Cast<
			UQuickDialoguesReplyGraphNode>(GraphNode))
		{
			ReplyNode->AddNewReply();
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}

FReply SQuickDialoguesReplyGraphNodeWidget::OnRemoveReplyButtonClicked(int32 Index)
{
	if (GraphNode)
	{
		if (UQuickDialoguesReplyGraphNode* ReplyNode = Cast<
			UQuickDialoguesReplyGraphNode>(GraphNode))
		{
			ReplyNode->RemoveReply(Index);
			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}
