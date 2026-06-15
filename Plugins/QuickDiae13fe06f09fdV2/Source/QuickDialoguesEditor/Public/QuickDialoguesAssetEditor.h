//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesGraph.h"
#include "Toolkits/AssetEditorToolkit.h"

class SQuickDialoguesEditorWidget;
class IDetailsView;


class FQuickDialoguesAssetEditor : public FAssetEditorToolkit, public FNotifyHook, public FEditorUndoClient   
{
public:
	FQuickDialoguesAssetEditor();
	virtual ~FQuickDialoguesAssetEditor() override;

	void InitQuickDialoguesEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost,
	                                  UQuickDialoguesNodeTree* InNodeTree);
	virtual void SaveAsset_Execute() override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void OnFinishedEditingDetailsView(const FPropertyChangedEvent& Event);
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
	
private:
	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);
	void OnSelectionChanged(UObject* Object);
	void SelectClassSettings();
private:
	UQuickDialoguesGraph* EditorGraph;
	UQuickDialoguesNodeTree* RuntimeAsset;
	static const FName GraphTabId;
	static const FName DetailViewTabId;
	TSharedPtr<SQuickDialoguesEditorWidget> QuickDialoguesEditorWidget;
	TSharedPtr<IDetailsView> DetailViewWidget;
};


