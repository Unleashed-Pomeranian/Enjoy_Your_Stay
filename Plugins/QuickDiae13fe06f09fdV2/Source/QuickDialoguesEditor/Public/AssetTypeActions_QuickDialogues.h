//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "AssetTypeActions_Base.h"

class FAssetTypeActions_QuickDialogues : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override;

	virtual FColor GetTypeColor() const override;

	virtual UClass* GetSupportedClass() const override;

	virtual uint32 GetCategories() override;

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;

	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
};
