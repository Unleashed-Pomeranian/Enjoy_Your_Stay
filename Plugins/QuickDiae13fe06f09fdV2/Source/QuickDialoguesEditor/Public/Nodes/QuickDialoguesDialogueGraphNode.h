//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNode.h"
#include "QuickDialoguesDialogueGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesDialogueGraphNode : public UQuickDialoguesBaseGraphNode
{
	GENERATED_BODY()
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
