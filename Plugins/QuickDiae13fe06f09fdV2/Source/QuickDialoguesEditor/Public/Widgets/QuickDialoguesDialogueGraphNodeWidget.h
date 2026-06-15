//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNodeWidget.h"
#include "UObject/Object.h"


class QUICKDIALOGUESEDITOR_API SQuickDialoguesDialogueGraphNodeWidget : public SQuickDialoguesBaseGraphNodeWidget
{
public:
	SQuickDialoguesDialogueGraphNodeWidget();
	SLATE_BEGIN_ARGS(SQuickDialoguesDialogueGraphNodeWidget) {}
	SLATE_END_ARGS()

	SQuickDialoguesDialogueGraphNodeWidget(UQuickDialoguesBaseGraphNode* MyGraphNode,
		const TSharedPtr<SEditableTextBox>& EditableText);

	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InGraphNode);

};
