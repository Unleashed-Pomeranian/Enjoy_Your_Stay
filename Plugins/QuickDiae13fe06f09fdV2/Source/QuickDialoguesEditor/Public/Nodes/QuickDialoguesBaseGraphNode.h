//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Nodes/QuickDialoguesBaseNode.h"
#include "QuickDialoguesBaseGraphNode.generated.h"

UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesBaseGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UQuickDialoguesBaseGraphNode();
	virtual ~UQuickDialoguesBaseGraphNode() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual void PostLoad() override;
	virtual void PostInitProperties() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	void SetNode(UQuickDialoguesBaseNode* InNode);
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void ReconstructNode() override;
	virtual void PostEditImport() override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool CheckIfNodeIsPresentInParentChain(UQuickDialoguesBaseNode* NodeToFind);
#if WITH_EDITOR
	virtual void PostEditUndo() override;
#endif
	
public:	
	UPROPERTY(Instanced)
	UQuickDialoguesBaseNode* DialogueNode;

};


