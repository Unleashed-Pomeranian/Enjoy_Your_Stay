//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNodeWidget.h"
#include "UObject/Object.h"

class QUICKDIALOGUESEDITOR_API SQuickDialoguesRandomGraphNodeWidget : public SQuickDialoguesBaseGraphNodeWidget
{
public:
	SQuickDialoguesRandomGraphNodeWidget();
	SLATE_BEGIN_ARGS(SQuickDialoguesRandomGraphNodeWidget) {}
	SLATE_END_ARGS()

	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	SQuickDialoguesRandomGraphNodeWidget(UQuickDialoguesBaseGraphNode* MyGraphNode,
		const TSharedPtr<SEditableTextBox>& EditableText);
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InGraphNode);
	FReply OnAddChoiceButtonClicked() const;
	FReply OnRemoveChoiceButtonClicked(int32 InIndex);

protected:
	TSharedPtr<SVerticalBox> ChoicesBox;

};
