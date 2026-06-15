//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNode.h"
#include "QuickDialoguesPlayMontageGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesPlayMontageGraphNode : public UQuickDialoguesBaseGraphNode
{
	GENERATED_BODY()
public:
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
