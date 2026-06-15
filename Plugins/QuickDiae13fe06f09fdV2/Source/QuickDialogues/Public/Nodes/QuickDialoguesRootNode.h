//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseNode.h"
#include "QuickDialoguesRootNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesRootNode : public UQuickDialoguesBaseNode
{
	GENERATED_BODY()

public:
	/**
	 * Constructor to set default values
	 */
	UQuickDialoguesRootNode();
	
	/** 
	 * Retrieves the type of this node as text.
	 * @return The node type as a text description.
	 */
	virtual FText GetNodeTypeAsText() const override;
};
