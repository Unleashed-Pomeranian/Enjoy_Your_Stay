//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "QuickDialoguesBaseNode.h"
#include "QuickDialoguesWidgetOpenerNode.generated.h"

UCLASS()
class QUICKDIALOGUES_API UQuickDialoguesWidgetOpenerNode : public UQuickDialoguesBaseNode
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
	 * @return The widget class that should be Opened/Created once this node is reached at runtime
	 */
	virtual TSubclassOf<UUserWidget> GetWidgetToOpen() override;

	/**
	 * Sets the value of WidgeToOpen
	 * @param InWidgetToOpen New value for WidgetToOpen
	 */
	virtual void SetWidgetToOpen(TSubclassOf<UCommonUserWidget> InWidgetToOpen);

	/**
	 * 
	 * @return The PathName for WidgetToOpen
	 */
	FString GetWidgetToOpenPathName() const;

protected:
	/**
	 * The widget class that should be Opened/Created once this node is reached at runtime
	 */
	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	TSubclassOf<UCommonUserWidget> WidgetToOpen;
};
