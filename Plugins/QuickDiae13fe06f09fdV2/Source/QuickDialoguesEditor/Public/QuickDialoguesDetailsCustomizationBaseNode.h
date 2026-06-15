//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "IDetailCustomization.h"

class QUICKDIALOGUESEDITOR_API FQuickDialoguesDetailsCustomizationBaseNode : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};
