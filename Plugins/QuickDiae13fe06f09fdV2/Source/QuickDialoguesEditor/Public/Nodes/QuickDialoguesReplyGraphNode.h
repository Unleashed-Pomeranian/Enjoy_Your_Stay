//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesBaseGraphNode.h"
#include "Widgets/QuickDialoguesReplyGraphNodeWidget.h"
#include "QuickDialoguesReplyGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesReplyGraphNode : public UQuickDialoguesBaseGraphNode
{
	GENERATED_BODY()
public:
	UQuickDialoguesReplyGraphNode();
	// Override UEdGraphNode
	virtual void AllocateDefaultPins() override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual FText GetTooltipText() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual void ReconstructNode() override;
	void ResetOutputPinsNames();
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	void AddNewReply();
	virtual void SetTextAtIndex(FText Text, int Index);
	void SelectClass(UClass* Class, int Index);
	void RemoveReply(int32 ReplyIndex);

#if WITH_EDITOR
	// Override for custom node visualization in the graph editor
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
#endif
public:
	// Array to store selected classes for each output pin
	UPROPERTY(EditAnywhere, Category = "Replies")
	TArray<FDialogueReply> ReplyButtons;
};
