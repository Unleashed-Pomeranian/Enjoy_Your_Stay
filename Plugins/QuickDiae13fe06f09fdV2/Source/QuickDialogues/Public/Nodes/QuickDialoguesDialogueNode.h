//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseNode.h"
#include "QuickDialoguesDialogueNode.generated.h"

/**
 * UQuickDialoguesDialogueNode is the cornerstone of this plugin it stores one line of dialogue
 * to be displayed at once in the HUD at runtime
 */
UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesDialogueNode : public UQuickDialoguesBaseNode
{
	GENERATED_BODY()

public:
	/**
	 * Constructor to set the default values
	 */
	UQuickDialoguesDialogueNode();


	/**
	 * Set the text for the dialogue node
	 * @param InText The new text for this dialogue node
	 */
	virtual void SetDialogue(FText InText) override;

	/**
	 * Gets the dialogue as text
	 * @return the dialogue text 
	 */
	virtual FText GetNodeDialogueData() override;

	/** 
	 * Retrieves the type of this node as text.
	 * @return The node type as a text description.
	 */
	virtual FText GetNodeTypeAsText() const override;

protected:
	/** 
	 * The actual text of the dialogue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText NodeData;
};
