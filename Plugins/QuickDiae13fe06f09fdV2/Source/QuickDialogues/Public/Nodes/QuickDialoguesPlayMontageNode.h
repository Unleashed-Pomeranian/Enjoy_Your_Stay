//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesDialogueNode.h"
#include "QuickDialoguesPlayMontageNode.generated.h"

class UAnimMontage;

UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesPlayMontageNode : public UQuickDialoguesDialogueNode
{
	GENERATED_BODY()

public:
	/** 
	 * Retrieves the type of this node as text.
	 * @return The node type as a text description.
	 */	
	virtual FText GetNodeTypeAsText() const override;

	/** 
	 * Retrieves the next node in the dialogue tree sequence.
	 * @param InOwner The owner of the dialogue tree (e.g., the Dialogue Listener).
	 * @return The next node in the tree or nullptr if there are no more nodes.
	 */
	virtual UQuickDialoguesBaseNode* GetNextNode(UObject* InOwner) override;

	/**
	 * Gets the FPlayMontageNodeData associated with this node
	 * FPlayMontageNodeData is a struct containing all the infos to play a Montage
	 * @return the FPlayMontageNodeData associated with this node
	 */
	virtual FQuickDialoguesPlayMontageNodeData GetMontageToPlay() override;
	
	/**
	 * Sets MontageToPlay in MontageData struct
	 * @param InMontage new montage to play
	 */
	virtual void SetMontageToPlay(UAnimMontage* InMontage);

	/**
	 * 
	 * @return the PathName for MontageToPlay in MontageData
	 */
	FString GetMontageToPlayPathName() const;
	
protected:
	/**
	 * The FPlayMontageNodeData contained in this node  
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MontageData")
	FQuickDialoguesPlayMontageNodeData MontageData;
};
