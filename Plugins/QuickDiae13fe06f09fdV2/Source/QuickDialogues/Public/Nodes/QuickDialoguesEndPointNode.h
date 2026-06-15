//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesDialogueNode.h"
#include "QuickDialoguesEndPointNode.generated.h"

/**
 * UQuickDialoguesEndPointNode is the Endpoint of the dialogue, once this node is reached the system is informed
 * that the dialogue is ended
 */
UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesEndPointNode : public UQuickDialoguesDialogueNode
{
	GENERATED_BODY()
	/**
	 * Constructor to set default values
	 */
	UQuickDialoguesEndPointNode();
	
	/** 
	 * Retrieves the type of this node as text.
	 * @return The node type as a text description.
	 */
	virtual FText GetNodeTypeAsText() const override;

	/**
	 * 
	 * @return An Array with all the children of the node
	 */
	virtual TArray<UQuickDialoguesBaseNode*> GetAllChildren() override;
	
	/**
	 * Gets the dialogue as text
	 * @return the dialogue text 
	 */
	virtual FText GetNodeDialogueData() override;

};
