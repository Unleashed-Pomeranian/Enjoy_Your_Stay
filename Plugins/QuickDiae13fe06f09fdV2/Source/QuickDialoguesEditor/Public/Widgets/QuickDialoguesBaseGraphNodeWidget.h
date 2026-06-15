//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "Nodes/QuickDialoguesBaseGraphNode.h"
#include "UObject/Object.h"

class QUICKDIALOGUESEDITOR_API SQuickDialoguesBaseGraphNodeWidget : public SGraphNode
{
public:
	SQuickDialoguesBaseGraphNodeWidget();
	SLATE_BEGIN_ARGS(SQuickDialoguesBaseGraphNodeWidget) {}
	SLATE_END_ARGS()

	SQuickDialoguesBaseGraphNodeWidget(UQuickDialoguesBaseGraphNode* MyGraphNode,
		const TSharedPtr<SEditableTextBox>& EditableText);

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InGraphNode);
	virtual void UpdateGraphNode() override;
	bool HasCompileError() const { return !ErrorMsg.IsEmpty(); }
	FText GetErrorMsg() const;
	FColor GetNodeColor() const;
	void SetupErrorSlot();
	void SetupDefaultPins();
	
protected:
	TSharedPtr<SVerticalBox> ContentVerticalBox;
	UQuickDialoguesBaseGraphNode* MyGraphNode;
};
