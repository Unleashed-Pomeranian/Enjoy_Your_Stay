//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "QuickDialoguesGraph.generated.h"

class UQuickDialoguesNodeTree;

UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UQuickDialoguesGraph();
	UEdGraphNode* GetRootNode() const;
	// UEdGraphNode* GetEndNode() const;
	void ResetRootNode();
	// void ResetEndNode();
	void SetRootNode(UEdGraphNode* InRootNode);
	// void SetEndNode(UEdGraphNode* InEndNode);

public:
	UPROPERTY()
	UQuickDialoguesNodeTree* NodeTree;

protected:
	UPROPERTY(Instanced)
	UEdGraphNode* RootNode;
	// UPROPERTY(Instanced)
	// UEdGraphNode* EndPointNode;
};
