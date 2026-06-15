//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseNode.h"
#include "QuickDialoguesMultiOutputNode.h"
#include "QuickDialoguesReplyNode.generated.h"

class UQuickDialoguesUIButton;
/**
 * UQuickDialoguesReplyNode represents a dialogue node that offers
 * multiple responses in a dialogue in the form of CommonButtons.
 * Each reply is mapped to a different child node, allowing dynamic dialogue branching based on player input.
 */
UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesReplyNode : public UQuickDialoguesMultiOutputNode
{
	GENERATED_BODY()

public:
	/**
	 * Constructor to set default values
	 */
	UQuickDialoguesReplyNode();

	/**
	 * Gets the list of dialogue button widget classes associated with each reply.
	 * @return Array of dialogue button widget types.
	 */
	virtual TArray<FDialogueReply> GetReplies() override;

	/**
	 * Removes a child node at the specified index from the map of options.
	 * @param Index Index of the child node to remove.
	 */
	virtual void RemoveChildAt(int Index) override;

	/** 
	 * Retrieves the type of this node as text.
	 * @return The node type as a text description.
	 */
	virtual FText GetNodeTypeAsText() const override;

	/**
	 * Adds the reply to the array of replies
	 * @param InReply The reply to add
	 */
	virtual void AddReply(FDialogueReply InReply);

	/**
	 * Sets the text of the reply at a specific index, also checks if the index is valid before so it should never crash
	 * @param InIndex The index of the reply text to be changed
	 * @param InText The new reply text
	 * @return True if successful false otherwise
	 */
	virtual bool SetReplyTextAtIndex(int32 InIndex, const FText& InText);

	/**
	 * Sets a Class to a specific FDialogueReply given by the Index 
	 * @param InIndex Access point to the Replies Array 
	 * @param InClass The class to set to the access point
	 * @return true if successful false otherwise
	 */
	virtual bool SetClassAtIndex(int32 InIndex, TSubclassOf<UQuickDialoguesUIButton> InClass);

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
	
protected:
	/** 
	 * The actual text of the dialogue
	 */		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText NodeData;
	
	/**
	 * The array of replies (Buttons) 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialogue",
		meta = (TitleProperty = "Text", ShowOnlyInnerProperties))
	TArray<FDialogueReply> Replies;
};
