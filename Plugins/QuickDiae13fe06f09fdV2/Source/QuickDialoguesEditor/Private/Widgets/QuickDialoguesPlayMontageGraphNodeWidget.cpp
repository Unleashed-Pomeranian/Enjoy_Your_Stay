//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesPlayMontageGraphNodeWidget.h"

#include "Nodes/QuickDialoguesPlayMontageGraphNode.h"
#include "Nodes/QuickDialoguesPlayMontageNode.h"
#include "PropertyCustomizationHelpers.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SQuickDialoguesPlayMontageGraphNodeWidget::Construct(const FArguments& InArgs,
                                                                 UQuickDialoguesBaseGraphNode* InNode)
{
	SQuickDialoguesBaseGraphNodeWidget::Construct({}, InNode);


	//this is the one of the few autos I will ever use, i only use it when casting something very long like this
	auto PlayMontageGraphNode = Cast<UQuickDialoguesPlayMontageGraphNode>(InNode);

	auto PlayMontageNode = Cast<UQuickDialoguesPlayMontageNode>(PlayMontageGraphNode->DialogueNode);
	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	                  .Padding(5.0f)
	[
		SNew(SObjectPropertyEntryBox)
		.AllowedClass(UAnimMontage::StaticClass())
		.OnObjectChanged_Lambda([this,PlayMontageGraphNode,PlayMontageNode](const FAssetData& AssetData)
		{
			if (PlayMontageGraphNode)
			{
				if (PlayMontageNode)
				{
					const FScopedTransaction Transaction(
						NSLOCTEXT("UnrealEd", "ReplyClassChanged", "Reply Class Changed"));

					UAnimMontage* Montage = Cast<UAnimMontage>(AssetData.GetAsset());
					PlayMontageNode->SetMontageToPlay(Montage);
					
					PlayMontageGraphNode->ReconstructNode();
					if (PlayMontageGraphNode->GetGraph())
					{
						PlayMontageGraphNode->GetGraph()->NotifyNodeChanged(PlayMontageGraphNode);
					}
				}
			}
		})
		.ObjectPath(PlayMontageNode->GetMontageToPlayPathName())
		.DisplayUseSelected(true)
		.DisplayBrowse(true)
		.NewAssetFactories({})
	];

	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	                  .Padding(5.0f)
	[
		SNew(SMultiLineEditableTextBox)
		.AllowMultiLine(true)
		.SelectAllTextWhenFocused(true)
		.ClearKeyboardFocusOnCommit(true)
		.Text_Lambda([PlayMontageGraphNode]() -> FText
		{
			if (PlayMontageGraphNode && PlayMontageGraphNode->DialogueNode)
			{
				return PlayMontageGraphNode->DialogueNode->GetNodeDialogueData();
			}
			return FText::GetEmpty();
		})
		.OnTextCommitted_Lambda([PlayMontageGraphNode](const FText& NewText, ETextCommit::Type CommitType)
		{
			if (PlayMontageGraphNode && PlayMontageGraphNode->DialogueNode)
			{
				const FScopedTransaction Transaction(
					NSLOCTEXT("UnrealEd", "SelectedMontageChanged", "Selected Montage Changed"));
				PlayMontageGraphNode->DialogueNode->SetDialogue(NewText);
				PlayMontageGraphNode->ReconstructNode();
			}
		})
	];

	SetupDefaultPins();
	SetupErrorSlot();
	CreatePinWidgets();
	this->UpdateGraphNode();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
