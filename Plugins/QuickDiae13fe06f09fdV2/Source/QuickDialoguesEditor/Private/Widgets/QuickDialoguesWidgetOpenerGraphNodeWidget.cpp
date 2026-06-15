//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesWidgetOpenerGraphNodeWidget.h"

#include "PropertyCustomizationHelpers.h"
#include "SlateOptMacros.h"
#include "Nodes/QuickDialoguesWidgetOpenerGraphNode.h"
#include "Nodes/QuickDialoguesWidgetOpenerNode.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SQuickDialoguesWidgetOpenerGraphNodeWidget::SQuickDialoguesWidgetOpenerGraphNodeWidget()
{
}

SQuickDialoguesWidgetOpenerGraphNodeWidget::SQuickDialoguesWidgetOpenerGraphNodeWidget(
	UQuickDialoguesBaseGraphNode* MyGraphNode,
	const TSharedPtr<SEditableTextBox>& EditableText): SQuickDialoguesBaseGraphNodeWidget(
	MyGraphNode, EditableText)
{
}

void SQuickDialoguesWidgetOpenerGraphNodeWidget::Construct(const FArguments& InArgs,
                                                            UQuickDialoguesBaseGraphNode* InGraphNode)
{
	SQuickDialoguesBaseGraphNodeWidget::Construct({}, InGraphNode);

	UQuickDialoguesWidgetOpenerNode* WidgetOpenerNode = Cast<UQuickDialoguesWidgetOpenerNode>(
		InGraphNode->DialogueNode);

	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	                  .Padding(5.0f)
	[
		SNew(SObjectPropertyEntryBox)
		.AllowedClass(UBlueprint::StaticClass())
		.OnShouldFilterAsset(FOnShouldFilterAsset::CreateLambda([](const FAssetData& AssetData)
		{
			FAssetTagValueRef ParentClassRef = AssetData.TagsAndValues.FindTag("ParentClass");
			if (ParentClassRef.IsSet())
			{
				UClass* ParentClass = FindObject<UClass>(nullptr, *ParentClassRef.GetValue());
				if (ParentClass && ParentClass->IsChildOf(UCommonUserWidget::StaticClass()))
				{
					return false;
				}
			}
			return true;
		}))
		.OnObjectChanged_Lambda([this,WidgetOpenerNode,InGraphNode](const FAssetData& AssetData)
		{
			UBlueprint* BlueprintAsset = Cast<UBlueprint>(AssetData.GetAsset());
			if (!BlueprintAsset)
			{
				return;
			}

			const FScopedTransaction Transaction(
				NSLOCTEXT("UnrealEd", "SelectedWidgetChanged", "Selected Widget Changed"));

			WidgetOpenerNode->SetWidgetToOpen(*BlueprintAsset->GeneratedClass);

			InGraphNode->ReconstructNode();
		})
		.ObjectPath(WidgetOpenerNode->GetWidgetToOpenPathName())
		.DisplayUseSelected(true)
		.DisplayBrowse(true)
	];
	SetupDefaultPins();
	SetupErrorSlot();
	CreatePinWidgets();
	this->UpdateGraphNode();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
