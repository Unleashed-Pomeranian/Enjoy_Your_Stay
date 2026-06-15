//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNodeWidget.h"
#include "Widgets/SCompoundWidget.h"


class QUICKDIALOGUESEDITOR_API SQuickDialoguesWidgetOpenerGraphNodeWidget : public SQuickDialoguesBaseGraphNodeWidget
{
public:
	SQuickDialoguesWidgetOpenerGraphNodeWidget();
	SLATE_BEGIN_ARGS(SQuickDialoguesWidgetOpenerGraphNodeWidget) {}
	SLATE_END_ARGS()

	SQuickDialoguesWidgetOpenerGraphNodeWidget(UQuickDialoguesBaseGraphNode* MyGraphNode,
		const TSharedPtr<SEditableTextBox>& EditableText);

	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InGraphNode);
};
