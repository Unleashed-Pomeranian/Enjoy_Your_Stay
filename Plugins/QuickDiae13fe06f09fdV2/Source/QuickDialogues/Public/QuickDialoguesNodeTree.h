//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesTypes.h"
#include "QuickDialoguesNodeTree.generated.h"

class UQuickDialoguesGraph;
class UQuickDialoguesBaseNode;

UCLASS(BlueprintType, Blueprintable)
class QUICKDIALOGUES_API UQuickDialoguesNodeTree : public UObject
{
	GENERATED_BODY()

public:
	/**
	 *  Constructor to initialize default values
	 */
	UQuickDialoguesNodeTree();

	/**
	 *  Set up the dialogue tree for a given owner object. This prepares the tree to run with the specified owner.
	 * @param InOwner Owner of this dialogue typically the Dialogue Listener it is used to retrive the UWorld at runtime
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	void SetUp(UObject* InOwner);

	/**
	 * Resets the dialogue from start
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	void ResetFromRoot();
	
	/** 
	 * Get the name of the node type based on its enum value. This helps in dynamically referencing node names.
	 * @param InNodeType The type of the node.
	 * @return The name of the node type as a FName.
	 */
	FName GetNodeNameFromType(EQuickDialoguesNodeType InNodeType);


	/** 
	 * Add a new node to the dialogue tree. It creates a node of a specified type.
	 * @param InNodeType The type of the node to add.
	 * @param InRunTimeClass The runtime class to instantiate for the node.
	 * @return The newly created node.
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	UQuickDialoguesBaseNode* AddNode(EQuickDialoguesNodeType InNodeType,
	                                       TSubclassOf<UQuickDialoguesBaseNode> InRunTimeClass);

	/** 
	* Remove a node from the dialogue tree.
	* @param InNode The node to remove from the tree.
	*/
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	void RemoveNode(UQuickDialoguesBaseNode* InNode);

	/** 
	* Get all nodes that are part of the dialogue tree.
	* @return An array of all nodes in the dialogue tree.
	*/
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="QuickDialogues")
	TArray<UQuickDialoguesBaseNode*> GetAllNodes() { return AllNodes; }

	/** 
	 * Get the root node of the dialogue tree. This is the starting point of the dialogue flow.
	 * @return The root node of the tree.
	 */
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="QuickDialogues")
	UQuickDialoguesBaseNode* GetRootNode() { return RootNode; }

	/** 
	 * Get the next node in the dialogue sequence. This advances the dialogue based on logic.
	 * @return The next node to transition to.
	 */
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="QuickDialogues")
	UQuickDialoguesBaseNode* GetNextNode();

	/** 
	 * Get the current active node in the dialogue. This allows checking which node is being evaluated.
	 * @return The current active node.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category="QuickDialogues")
	UQuickDialoguesBaseNode* GetCurrentNode() { return CurrentNode; };

	/** 
	 * Check if there are any compilation errors in the dialogue tree.
	 * @return True if there are compile errors, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure,Category="QuickDialogues")
	bool GetHasCompileErrors();

	/** 
	 * Set the compile error status. Used internally to mark the dialogue tree as having compile issues.
	 * @param bInNewHasCompileErrors The new compile error status.
	 */
	UFUNCTION()
	void SetHasCompileErrors(bool bInNewHasCompileErrors);

	/** 
	 * Check if the dialogue tree has been saved and or validated NOTE Saving the asset also validates it
	 * @return True if the tree has been saved and validated, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	bool GetHasBeenSavedAndValidated();

	/** 
	 * Set the saved and validated status. Marks the dialogue tree as successfully compiled and saved.
	 * @param bInHasBeenCompiled The new saved and validated status.
	 */
	void SetHasBeenSavedAndValidated(bool bInHasBeenCompiled);

public:
#if WITH_EDITORONLY_DATA
	/**
	* The UEDGraph for this tree
	*/
	UPROPERTY(Instanced)
	UQuickDialoguesGraph* Graph;
#endif
	
protected:
	/** 
	 * Root node of the tree. All dialogue paths branch from this starting node.
	 */
	UPROPERTY()
	UQuickDialoguesBaseNode* RootNode;

	/** 
	 * Current node in the dialogue. This tracks the dialogue state as it progresses.
	 */
	UPROPERTY()
	UQuickDialoguesBaseNode* CurrentNode;

	/** 
	 * All nodes in the dialogue tree. This stores every node added to the tree.
	 */
	UPROPERTY()
	TArray<UQuickDialoguesBaseNode*> AllNodes;
	/** 
	 * The owner of the dialogue tree, typically the actor or object interacting with the dialogue.
	 */
	UPROPERTY()
	UObject* Owner;
	/** 
	 * Flag indicating if the dialogue tree has any compile errors. Used to track validation state.
	 */
	UPROPERTY()
	bool bHasCompilesError = true;
	/** 
	 * Flag indicating whether the dialogue tree has been successfully compiled. Helps track the tree's state.
	 */
	UPROPERTY()
	bool bHasBeenCompiled = false;


};
