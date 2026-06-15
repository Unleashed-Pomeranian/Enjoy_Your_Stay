//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseNode.h"
#include "QuickDialoguesMultiOutputNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesMultiOutputNode : public UQuickDialoguesBaseNode
{
	GENERATED_BODY()

public:
	UQuickDialoguesMultiOutputNode();
	/**
	 * Sets the index of the reply selected by the player.
	 * @param InIndex Index of the chosen option.
	 */
	virtual void SetChosenIndex(int InIndex) override;

	/**
	 * Removes a child node at the specified index from the map of options.
	 * @param Index Index of the child node to remove.
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void RemoveChildAt(int Index);

	/** 
	 * Retrieves the type of this node as text.
	 * @return The node type as a text description.
	 */
	virtual FText GetNodeTypeAsText() const override;

	/**
	 * Gets the next node in the tree based on the chosen index.
	 * @param InOwner The object owning this dialogue tree.
	 * @return The child node corresponding to the chosen index.
	 */
	virtual UQuickDialoguesBaseNode* GetNextNode(UObject* InOwner) override;

	/** 
	 * Remove a child node from this node.
	 * @param InNode The node to be removed from the child list.
	 */
	virtual void RemoveChild(UQuickDialoguesBaseNode* InNode) override;

	/**
	 * 
	 * @return An Array with all the children of the node
	 */
	virtual TArray<UQuickDialoguesBaseNode*> GetAllChildren() override;

	/**
	 * Adds a new child node corresponding to a specific reply index.
	 * @param InIndex The index of the reply.
	 * @param InNode The node to assign to this reply.
	 */
	virtual void AddChildToMap(int InIndex, UQuickDialoguesBaseNode* InNode);

	/** 
	 * Reset the node's connections, clearing its children and parents.
	 */
	virtual void ResetConnections() override;

	/** 
	 * Handle the removal of this node from the dialogue tree.
	 */
	virtual void OnNodeRemoval() override;

public:
	/**
	 * The map of INDEX - CHILD this ensures that the child is always aligned with the pressed button
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Connection")
	TMap<int32, UQuickDialoguesBaseNode*> ChildrenMap;

	/**
	 * The index of the button pressed, this is set at runtime when any response is pressed
	 */
	UPROPERTY()
	int32 ChosenIndex;
};
