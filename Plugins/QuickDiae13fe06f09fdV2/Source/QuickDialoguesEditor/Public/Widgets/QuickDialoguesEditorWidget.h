//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "QuickDialoguesNodeTree.h"
#include "Framework/Commands/UICommandList.h"
#include "GraphEditor.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"

class UQuickDialoguesGraph;
class UQuickDialogueAsset;
class SGraphEditor;
class UEdGraph;
class UQuickDialoguesBaseGraphNode;
class IDetailsView;

DECLARE_DELEGATE_OneParam(FOnNodeSelectionChanged, UObject*);

class SQuickDialoguesEditorWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SQuickDialoguesEditorWidget)
	{
	}

	SLATE_END_ARGS()
	void ValidateGraph() const;
	void OnCompileClicked() const;
	void Construct(const FArguments& InArgs, UQuickDialoguesNodeTree* InNodeTree,UQuickDialoguesGraph* InGraph,
				   FAssetEditorToolkit* InToolKit);
	void AddToolbar(FAssetEditorToolkit* InToolkit);
	UObject* GetSelectedNode() const;
	void RefreshEditor() const;
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	
private:
	TSharedRef<SGraphEditor> CreateGraphEditorWidget();
	void CreateCommandList();
	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);
	void DeleteSelectedNodes() const;
	bool CanDeleteNodes() const;
	void CopySelectedNodes() const;
	bool CanCopyNodes() const;
	void PasteNodes() const;
	bool CanPasteNodes() const;
	void CutSelectedNodes() const;
	bool CanCutNodes() const;
	
public:
	FOnNodeSelectionChanged OnNodeSelectionChanged;
	UQuickDialoguesNodeTree* NodeTree;
	UQuickDialoguesGraph* QuickDialoguesGraph;
	
private:
	TSharedPtr<FUICommandList> CommandList;
	TSharedPtr<SGraphEditor> GraphEditor;
	TWeakObjectPtr<UQuickDialoguesBaseGraphNode> SelectedGraphNode;
};