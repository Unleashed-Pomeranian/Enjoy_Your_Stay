//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNode.h"
#include "QuickDialoguesRandomGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesRandomGraphNode : public UQuickDialoguesBaseGraphNode
{
	GENERATED_BODY()

public:
	UQuickDialoguesRandomGraphNode();

	virtual void AllocateDefaultPins() override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual FText GetTooltipText() const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void ReconstructNode() override;
	virtual void RemoveChoice(int32 InChoiceIndex);
	virtual void PostPasteNode() override;
	void ResetOutputPinsNames();
	void AddNewRandomOutput();
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	
#if WITH_EDITOR
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
#endif

public:
	UPROPERTY(EditAnywhere, Category = "Replies")
	TArray<UQuickDialoguesBaseNode*> Outputs;
};
