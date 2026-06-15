//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "QuickDialoguesFactory.generated.h"

UCLASS()
class QUICKDIALOGUESEDITOR_API UQuickDialoguesFactory : public UFactory
{
	GENERATED_BODY()

public:
	UQuickDialoguesFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	                                  UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
};
