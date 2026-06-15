//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNode.h"
#include "QuickDialoguesEndPointGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesEndPointGraphNode : public UQuickDialoguesBaseGraphNode
{
	GENERATED_BODY()
public:
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual void AllocateDefaultPins() override;
};
