//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"


class QUICKDIALOGUESEDITOR_API FQuickDialoguesEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};