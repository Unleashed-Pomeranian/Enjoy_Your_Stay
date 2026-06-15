//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesFactory.h"

#include "QuickDialoguesGraph.h"
#include "QuickDialoguesGraphSchema.h"
#include "QuickDialoguesNodeTree.h"

UQuickDialoguesFactory::UQuickDialoguesFactory()
{
	SupportedClass = UQuickDialoguesNodeTree::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UQuickDialoguesFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
                                                  EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn,
                                                  FName CallingContext)
{
	UQuickDialoguesNodeTree* NewAsset = NewObject<UQuickDialoguesNodeTree>(InParent, InClass, InName, Flags);
	NewAsset->Graph = NewObject<UQuickDialoguesGraph>(NewAsset, UQuickDialoguesGraph::StaticClass(),
	                                                  TEXT("EditorGraph"), RF_Transactional);
	NewAsset->Graph->Schema = UQuickDialoguesGraphSchema::StaticClass();
	NewAsset->Graph->NodeTree = NewAsset;	
	return NewAsset;
}
