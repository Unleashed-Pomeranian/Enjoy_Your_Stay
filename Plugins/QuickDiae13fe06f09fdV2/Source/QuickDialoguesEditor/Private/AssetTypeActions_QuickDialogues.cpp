//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "AssetTypeActions_QuickDialogues.h"

#include "QuickDialoguesAssetEditor.h"
#include "QuickDialoguesNodeTree.h"

FText FAssetTypeActions_QuickDialogues::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_QuickDialogues", "Quick Dialogue");
}

FColor FAssetTypeActions_QuickDialogues::GetTypeColor() const
{
	return FColor(100, 150, 255); // Light blue
}

UClass* FAssetTypeActions_QuickDialogues::GetSupportedClass() const
{
	return UQuickDialoguesNodeTree::StaticClass();
}

uint32 FAssetTypeActions_QuickDialogues::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FAssetTypeActions_QuickDialogues::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	for (UObject* Obj : InObjects)
	{
		if (UQuickDialoguesNodeTree* Asset = Cast<UQuickDialoguesNodeTree>(Obj))
		{
			const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() 
				? EToolkitMode::WorldCentric 
				: EToolkitMode::Standalone;

			TSharedRef<FQuickDialoguesAssetEditor> EditorToolkit = MakeShared<FQuickDialoguesAssetEditor>();
			EditorToolkit->InitQuickDialoguesEditor(Mode, EditWithinLevelEditor, Asset);
		}
	}
}

bool FAssetTypeActions_QuickDialogues::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}
