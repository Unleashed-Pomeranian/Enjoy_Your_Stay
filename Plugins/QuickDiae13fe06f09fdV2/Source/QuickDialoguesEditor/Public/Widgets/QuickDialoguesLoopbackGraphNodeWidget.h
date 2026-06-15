//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/QuickDialoguesBaseGraphNodeWidget.h"

/**
 * 
 */
class QUICKDIALOGUESEDITOR_API SQuickDialoguesLoopbackGraphNodeWidget : public SQuickDialoguesBaseGraphNodeWidget
{
public:
	SLATE_BEGIN_ARGS(SQuickDialoguesLoopbackGraphNodeWidget)
	{
	}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InNode);
	TSharedPtr<SComboBox<UQuickDialoguesBaseNode*>> LoopbackComboBox;
	TArray<UQuickDialoguesBaseNode*> AllNodes;

};
