//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNode.h"
#include "QuickDialoguesLoopbackGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesLoopbackGraphNode : public UQuickDialoguesBaseGraphNode
{
	GENERATED_BODY()
public:
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual void AllocateDefaultPins() override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

};
