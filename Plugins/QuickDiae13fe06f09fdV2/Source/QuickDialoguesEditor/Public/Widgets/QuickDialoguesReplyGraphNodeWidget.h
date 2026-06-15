//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNodeWidget.h"

class UQuickDialoguesBaseGraphNode;
class SButton;

class SQuickDialoguesReplyGraphNodeWidget : public SQuickDialoguesBaseGraphNodeWidget
{
public:
	SLATE_BEGIN_ARGS(SQuickDialoguesReplyGraphNodeWidget)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UQuickDialoguesBaseGraphNode* InGraphNode);

	// virtual void UpdateGraphNode() override;
	// virtual void CreatePinWidgets() override;

protected:
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	void PopulateReplySlots();
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	FReply OnAddReplyButtonClicked();
	FReply OnRemoveReplyButtonClicked(int32 Index);

private:
	TSharedPtr<SButton> AddReplyButton;
	TSharedPtr<SVerticalBox> ReplyListBox;
	TSharedPtr<SVerticalBox> ReplyBox;
};
