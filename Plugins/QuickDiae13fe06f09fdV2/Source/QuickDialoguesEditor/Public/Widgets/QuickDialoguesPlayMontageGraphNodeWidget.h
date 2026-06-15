//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNodeWidget.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class QUICKDIALOGUESEDITOR_API SQuickDialoguesPlayMontageGraphNodeWidget : public SQuickDialoguesBaseGraphNodeWidget
{
public:
	SLATE_BEGIN_ARGS(SQuickDialoguesPlayMontageGraphNodeWidget)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InNode);
};
