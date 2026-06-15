//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesEditor.h"

#include "AssetToolsModule.h"
#include "AssetTypeActions_QuickDialogues.h"
#include "IAssetTools.h"
#include "QuickDialoguesDetailsCustomizationBaseNode.h"
#include "Nodes/QuickDialoguesBaseNode.h"

#define LOCTEXT_NAMESPACE "FQuickDialoguesEditorModule"

TSharedPtr<IAssetTypeActions> QuickDialoguesAssetActions;

void FQuickDialoguesEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	QuickDialoguesAssetActions = MakeShareable(new FAssetTypeActions_QuickDialogues);
	AssetTools.RegisterAssetTypeActions(QuickDialoguesAssetActions.ToSharedRef());

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UQuickDialoguesBaseNode::StaticClass()->GetFName(),
	                                         FOnGetDetailCustomizationInstance::CreateStatic(
		                                         &FQuickDialoguesDetailsCustomizationBaseNode::MakeInstance));

}

void FQuickDialoguesEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		if (QuickDialoguesAssetActions.IsValid())
		{
			AssetTools.UnregisterAssetTypeActions(QuickDialoguesAssetActions.ToSharedRef());
			QuickDialoguesAssetActions.Reset();
		}
	}
	
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FQuickDialoguesEditorModule, QuickDialoguesEditor)
