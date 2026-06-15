//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseNode.h"
#include "QuickDialoguesLoopbackNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesLoopbackNode : public UQuickDialoguesBaseNode
{
	GENERATED_BODY()

public:
	UQuickDialoguesLoopbackNode();

	/** 
     * Retrieves the type of this node as text.
     * @return The node type as a text description.
     */
	virtual FText GetNodeTypeAsText() const override;

	TArray<UQuickDialoguesBaseNode*> GetParentChain() const;

	virtual void SetChildValue(UQuickDialoguesBaseNode* InChild) override;

	virtual UQuickDialoguesBaseNode* GetChild() override;

	virtual void RemoveChild(UQuickDialoguesBaseNode* InNode) override;

	virtual UQuickDialoguesBaseNode* GetNextNode(UObject* InOwner) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Connection")
	UQuickDialoguesBaseNode* LoopBackTo;
};
