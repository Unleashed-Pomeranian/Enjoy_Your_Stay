//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesMultiOutputNode.h"
#include "QuickDialoguesRandomNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesRandomNode : public UQuickDialoguesMultiOutputNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTypeAsText() const override;
	
	virtual UQuickDialoguesBaseNode* GetNextNode(UObject* InOwner) override;
};
