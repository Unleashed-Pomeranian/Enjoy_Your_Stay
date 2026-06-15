//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesDialogueGraphNodeWidget.h"

#include "Nodes/QuickDialoguesDialogueNode.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

SQuickDialoguesDialogueGraphNodeWidget::SQuickDialoguesDialogueGraphNodeWidget()
{
}

SQuickDialoguesDialogueGraphNodeWidget::SQuickDialoguesDialogueGraphNodeWidget(
	UQuickDialoguesBaseGraphNode* MyGraphNode, const TSharedPtr<SEditableTextBox>& EditableText)
{
}
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SQuickDialoguesDialogueGraphNodeWidget::Construct(const FArguments& InArgs,
                                                              UQuickDialoguesBaseGraphNode* InGraphNode)
{
	SQuickDialoguesBaseGraphNodeWidget::Construct({}, InGraphNode);
	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	                  .Padding(5.0f)
	[
		SNew(SMultiLineEditableTextBox)
		.AllowMultiLine(true)
		.SelectAllTextWhenFocused(true)
		.ClearKeyboardFocusOnCommit(true)
		.Text_Lambda([InGraphNode]() -> FText
		{
			if (InGraphNode && InGraphNode->DialogueNode)
			{
				return InGraphNode->DialogueNode->GetNodeDialogueData();
			}
			return FText::GetEmpty();
		})
		.OnTextCommitted_Lambda([InGraphNode](const FText& NewText, ETextCommit::Type CommitType)
		{
			if (InGraphNode && InGraphNode->DialogueNode)
			{
				const FScopedTransaction Transaction(
					NSLOCTEXT("UnrealEd", "DialogueTextChanged", "Dialogue Text Changed"));
				InGraphNode->DialogueNode->SetDialogue(NewText);
				InGraphNode->ReconstructNode();
			}
		})
	];
	SetupDefaultPins();
	SetupErrorSlot();
	CreatePinWidgets();
	this->UpdateGraphNode();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
