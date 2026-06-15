//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNode.h"
#include "QuickDialoguesRootGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesRootGraphNode : public UQuickDialoguesBaseGraphNode
{
	GENERATED_BODY()
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
