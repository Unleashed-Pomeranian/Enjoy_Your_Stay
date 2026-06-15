//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesTypes.h"
#include "QuickDialoguesValueInterface.h"
#include "UObject/Object.h"
#include "EdGraph/EdGraphPin.h"
#include "QuickDialoguesBaseNode.generated.h"

/**
 * UQuickDialoguesBaseNode serves as the base class for all nodes in the dialogue node tree.
 * It implements the IQuickDialoguesValueInterface for nodes that can hold values and interact with the node tree.
 */
UCLASS(BlueprintType)
class QUICKDIALOGUES_API UQuickDialoguesBaseNode : public UObject, public IQuickDialoguesValueInterface
{
	friend class UQuickDialoguesNodeTree;
	friend class FQuickDialoguesDetailsCustomizationBaseNode;
	GENERATED_BODY()

public:
	/** 
	 * Default constructor for the node. Initializes the node with default values.
	 */
	UQuickDialoguesBaseNode();

public:
	/**
	 * Gets the FPlayMontageNodeData associated with this node
	 * FPlayMontageNodeData is a struct containing all the infos to play a Montage
	 * @return the FPlayMontageNodeData associated with this node
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual FQuickDialoguesPlayMontageNodeData GetMontageToPlay() override;

	/**
	 * Sets the index of the reply selected by the player.
	 * @param InIndex Index of the chosen option.
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void SetChosenIndex(int InIndex) override;

	/**
	 * @return The widget class that should be Opened/Created once this node is reached at runtime
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual TSubclassOf<UUserWidget> GetWidgetToOpen() override;

	/**
	 * Set the text for the dialogue node
	 * @param InText The new text for this dialogue node
	 */
	UFUNCTION()
	virtual void SetDialogue(FText InText) override;

	/**
	 * Gets the dialogue as text
	 * @return the dialogue text 
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual FText GetNodeDialogueData() override;

	/**
	 * Gets the list of dialogue button widget classes associated with each reply.
	 * @return Array of dialogue button widget types.
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual TArray<FDialogueReply> GetReplies() override;

	/** 
	 * Retrieves the type of this node as text.
	 * @return The node type as a text description.
	 */
	virtual FText GetNodeTypeAsText() const;

	/** 
	 * Retrieves the next node in the dialogue tree sequence.
	 * @param InOwner The owner of the dialogue tree (e.g., the Dialogue Listener).
	 * @return The next node in the tree or nullptr if there are no more nodes.
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual UQuickDialoguesBaseNode* GetNextNode(UObject* InOwner);

	
	/**
	 * 
	 * @return An Array with all the children of the node
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual TArray<UQuickDialoguesBaseNode*> GetAllChildren();

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual UQuickDialoguesBaseNode* GetChild();
	
	/** 
	 * Add a child node to this node.
	 * @param FromPin The pin that connects this node to another.
	 * @param InDialogueNode The node to be added as a child.
	 */
	virtual void AddChild(UEdGraphPin* FromPin, UQuickDialoguesBaseNode* InDialogueNode);

	/** 
	 * Remove a child node from this node.
	 * @param InNode The node to be removed.
	 */
	virtual void RemoveChild(UQuickDialoguesBaseNode* InNode);

	/** 
	 * Remove a parent node from this node.
	 * @param InParent The parent node to be removed.
	 */
	virtual void RemoveParent(UQuickDialoguesBaseNode* InParent);

	/** 
	 * Handle the removal of this node from the dialogue tree.
	 */
	virtual void OnNodeRemoval();

	/** 
	 * Check if this node uses default child nodes.
	 * @return True if default children are used, false otherwise.
	 */
	virtual bool GetUsesDefaultChildren() { return UsesDefaultChildren; }

	/** 
	 * Check if this node uses the default parent node.
	 * @return True if default parent is used, false otherwise.
	 */
	virtual bool GetUsesDefaultParent() { return UsesDefaultParent; }

	/** 
	 * Reset the node's connections, clearing its children and parents.
	 */
	virtual void ResetConnections();

	/**
	 * Clears the Parents Array;
	 */
	virtual void EmptyParents();

	/**
	 * Adds a parent to the Parents array
	 * @param InParent The parent to add
	 */
	virtual void AddParent(UQuickDialoguesBaseNode* InParent);

	/**
	 * Sets the value of Child node
	 * @param InChild New value for Child node
	 */
	virtual void SetChildValue(UQuickDialoguesBaseNode* InChild);

	/**
	 * 
	 * @return the Node type
	 */
	EQuickDialoguesNodeType GetNodeType() const;

	/**
	 * Sets the value of Tree that owns this node
	 * @param InTree New value for the tree that owns this node
	 */
	void SetTree(UQuickDialoguesNodeTree* InTree);

	/**
	 * 
	 * @return The tree that owns this node
	 */
	UQuickDialoguesNodeTree* GetTree() const;

	TArray<UQuickDialoguesBaseNode*> GetParents() const;
	
public:
	/** 
	 * A unique identifier for this node. It helps track the node even if the order or other data changes.
	 */
	UPROPERTY()
	FGuid NodeGuid;

protected:
	/**
	 * The tree that owns this node
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="QuickDialogues")
	UQuickDialoguesNodeTree* Tree;
	
	/** 
	 * The type of this node (e.g., Dialogue, Reply, Action).
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,  Category="QuickDialogues")
	EQuickDialoguesNodeType NodeType;

	/** 
	 * A reference to the child node of this node. This represents the node that follows this one.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Connection")
	UQuickDialoguesBaseNode* Child;

	/** 
	 * The list of parent nodes that this node is connected to.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Connection")
	TArray<UQuickDialoguesBaseNode*> Parents;

	/** 
	 * Flag indicating if this node uses default children for behavior. Controls whether the node automatically handles children.
	 */
	UPROPERTY()
	bool UsesDefaultChildren;

	/** 
	 * Flag indicating if this node uses a default parent for behavior. Controls whether the node automatically handles parents.
	 */
	UPROPERTY()
	bool UsesDefaultParent;
};
