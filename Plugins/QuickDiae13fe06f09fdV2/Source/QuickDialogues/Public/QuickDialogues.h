//Copyright (c) 2025 Elia Cantini. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

// Module setup for editor integration
#include "Modules/ModuleManager.h"

class FQuickDialoguesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
