//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraphSchema_K2.h"
#include "QuickDialoguesGraphSchema.generated.h"

class UQuickDialoguesBaseGraphNode;

UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	UQuickDialoguesGraphSchema();

public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
	
	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(
		int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect,
		class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;
	virtual bool DoesSupportPinWatching() const override;
	void DeleteNode(const TObjectPtr<const UEdGraphNode>& Node) const;

};

