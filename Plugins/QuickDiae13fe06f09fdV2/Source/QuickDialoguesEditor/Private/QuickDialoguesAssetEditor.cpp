//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesAssetEditor.h"

#include "GraphEditor.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "QuickDialoguesGraph.h"
#include "QuickDialoguesNodeTree.h"
#include "EdGraph/EdGraphNode.h"
#include "Framework/Commands/UICommandList.h"
#include "Framework/Docking/TabManager.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Widgets/QuickDialoguesEditorWidget.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "QuickDialoguesEditor"

FQuickDialoguesAssetEditor::FQuickDialoguesAssetEditor()
	: EditorGraph(nullptr), RuntimeAsset(nullptr)
{
}

FQuickDialoguesAssetEditor::~FQuickDialoguesAssetEditor()
{
	if (GEditor)
	{
		GEditor->UnregisterForUndo(this);
	}
}

void FQuickDialoguesAssetEditor::InitQuickDialoguesEditor(const EToolkitMode::Type Mode,
                                                          const TSharedPtr<IToolkitHost>& InitToolkitHost,
                                                          UQuickDialoguesNodeTree* InNodeTree)
{
	if (!InNodeTree)
	{
		UE_LOG(LogTemp, Error, TEXT("FQuickDialoguesAssetEditor::InitQuickDialoguesEditor(), InNodeTree was nullptr"))
		return;
	}
	RuntimeAsset = InNodeTree;
	if (!RuntimeAsset->Graph)
	{
		UE_LOG(LogTemp, Error, TEXT("FQuickDialoguesAssetEditor::InitQuickDialoguesEditor(), RuntimeAsset->Graph was nullptr"))
		return;
	}
	EditorGraph = RuntimeAsset->Graph;

	EditorGraph->NotifyGraphChanged();
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("FQuickDialoguesEditor_Layout")->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
		                             ->Split
		                             (
			                             FTabManager::NewStack()
			                             ->AddTab(GraphTabId, ETabState::OpenedTab)
			                             ->SetHideTabWell(true)
		                             )
		                             ->Split
		                             (
			                             FTabManager::NewStack()
			                             ->AddTab(DetailViewTabId, ETabState::OpenedTab)
			                             ->SetHideTabWell(true)
		                             )
	);

	InitAssetEditor(
		Mode,
		InitToolkitHost,
		FName(TEXT("QuickDialoguesEditor")),
		Layout,
		true,
		true,
		InNodeTree
	);
	if (GEditor)
	{
		GEditor->RegisterForUndo(this);
	}
	RegenerateMenusAndToolbars();
}

void FQuickDialoguesAssetEditor::SaveAsset_Execute()
{
	FAssetEditorToolkit::SaveAsset_Execute();
	FText ErrorMessage;
	if (QuickDialoguesEditorWidget.IsValid())
	{
		QuickDialoguesEditorWidget->ValidateGraph();
	}
	else
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("FQuickDialoguesAssetEditor::SaveAsset_Execute(), QuickDialoguesEditorWidget Is Null"));
#endif
	}
}

FName FQuickDialoguesAssetEditor::GetToolkitFName() const
{
	return FName(TEXT("QuickDialoguesNodeTreeEditor"));
}

FText FQuickDialoguesAssetEditor::GetBaseToolkitName() const
{
	return FText::FromString(TEXT("Quick Dialogue Editor"));
}

FText FQuickDialoguesAssetEditor::GetToolkitName() const
{
	return FText::FromString(TEXT("Quick Dialogue Node Tree Editor"));
}

FText FQuickDialoguesAssetEditor::GetToolkitToolTipText() const
{
	return FText::FromString(TEXT("Node Tree Editor"));
}

FLinearColor FQuickDialoguesAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FQuickDialoguesAssetEditor::GetWorldCentricTabPrefix() const
{
	return FString(TEXT("Dialogue Node Tree"));
}

void FQuickDialoguesAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(
		            GraphTabId, FOnSpawnTab::CreateSP(this, &FQuickDialoguesAssetEditor::SpawnTab_GraphCanvas))
	            .SetDisplayName(LOCTEXT("GraphTabName", "Graph"))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(DetailViewTabId,
	                                 FOnSpawnTab::CreateSP(this, &FQuickDialoguesAssetEditor::SpawnTab_Properties))
	            .SetDisplayName(LOCTEXT("PropertiesTabName", "Properties"))
	            .SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FQuickDialoguesAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(GraphTabId);
	InTabManager->UnregisterTabSpawner(DetailViewTabId);
}

void FQuickDialoguesAssetEditor::OnFinishedEditingDetailsView(const FPropertyChangedEvent& Event)
{
	QuickDialoguesEditorWidget->RefreshEditor();
}

TSharedRef<SDockTab> FQuickDialoguesAssetEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args)
{
	if (!QuickDialoguesEditorWidget.IsValid())
	{
		QuickDialoguesEditorWidget = SNew(SQuickDialoguesEditorWidget, RuntimeAsset, EditorGraph, this);
	}

	return SNew(SDockTab)
		.Label(FText::FromString(TEXT("Graph")))
		[
			QuickDialoguesEditorWidget.ToSharedRef()
		];
}

TSharedRef<SDockTab> FQuickDialoguesAssetEditor::SpawnTab_Properties(const FSpawnTabArgs& Args)
{
	// Create the details view
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;

	TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailViewWidget = DetailsView;
	DetailViewWidget->OnFinishedChangingProperties().
	                AddSP(this, &FQuickDialoguesAssetEditor::OnFinishedEditingDetailsView);
	if (QuickDialoguesEditorWidget.IsValid())
	{
		QuickDialoguesEditorWidget->OnNodeSelectionChanged.BindRaw(
			this, &FQuickDialoguesAssetEditor::OnSelectionChanged);
	}

	return SNew(SDockTab)
		.Label(FText::FromString("Properties"))
		[
			DetailsView.ToSharedRef()
		];
}
void FQuickDialoguesAssetEditor::SelectClassSettings()
{
	if (DetailViewWidget.IsValid() && RuntimeAsset)
	{
		DetailViewWidget->SetObject(RuntimeAsset);
	}
}

void FQuickDialoguesAssetEditor::OnSelectionChanged(UObject* Object)
{
	if (DetailViewWidget.IsValid())
	{
		DetailViewWidget->SetObject(Object);
	}
}

void FQuickDialoguesAssetEditor::PostRedo(bool bSuccess)
{
	if (bSuccess && QuickDialoguesEditorWidget.IsValid())
	{
		QuickDialoguesEditorWidget->RefreshEditor();
	}
}

void FQuickDialoguesAssetEditor::PostUndo(bool bSuccess)
{
	if (bSuccess && QuickDialoguesEditorWidget.IsValid())
	{
		QuickDialoguesEditorWidget->RefreshEditor();
	}
	FEditorUndoClient::PostUndo(bSuccess);
}
#undef LOCTEXT_NAMESPACE