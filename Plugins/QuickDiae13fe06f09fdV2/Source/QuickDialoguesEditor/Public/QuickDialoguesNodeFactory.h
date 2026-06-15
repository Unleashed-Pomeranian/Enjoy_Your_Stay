//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "Nodes/QuickDialoguesReplyGraphNode.h"
#include "Widgets/QuickDialoguesReplyGraphNodeWidget.h"
#include "EdGraphUtilities.h"

class FQuickDialoguesNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override
	{
		if (UQuickDialoguesReplyGraphNode* DialogueNode = Cast<UQuickDialoguesReplyGraphNode>(InNode))
		{
			return SNew(SQuickDialoguesReplyGraphNodeWidget, DialogueNode);
		}
		return nullptr;
	}
};
