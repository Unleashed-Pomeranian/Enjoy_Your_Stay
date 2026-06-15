//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesRootGraphNodeWidget.h"

void SQuickDialoguesRootGraphNodeWidget::Construct(const FArguments& InArgs,
                                                   UQuickDialoguesBaseGraphNode* InGraphNode)
{
	SQuickDialoguesBaseGraphNodeWidget::Construct({}, InGraphNode);
	SetupDefaultPins();
	SetupErrorSlot();
	CreatePinWidgets();
	this->UpdateGraphNode();
}

void SQuickDialoguesRootGraphNodeWidget::UpdateGraphNode()
{
}
