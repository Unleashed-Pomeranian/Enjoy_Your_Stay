//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNodeWidget.h"
#include "UObject/Object.h"

/**
 * 
 */
class QUICKDIALOGUESEDITOR_API SQuickDialoguesRootGraphNodeWidget : public SQuickDialoguesBaseGraphNodeWidget
{
	public:
	SQuickDialoguesRootGraphNodeWidget() {}
	SLATE_BEGIN_ARGS(SQuickDialoguesRootGraphNodeWidget) {}
	SLATE_END_ARGS()

	SQuickDialoguesRootGraphNodeWidget(UQuickDialoguesBaseGraphNode* MyGraphNode,
		const TSharedPtr<SEditableTextBox>& EditableText)
		: SQuickDialoguesBaseGraphNodeWidget(MyGraphNode, EditableText)
	{
	}
	

	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InGraphNode);

	virtual void UpdateGraphNode() override;
};
