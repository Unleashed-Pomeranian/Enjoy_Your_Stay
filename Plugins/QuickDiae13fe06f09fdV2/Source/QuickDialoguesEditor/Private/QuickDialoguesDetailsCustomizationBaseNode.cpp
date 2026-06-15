//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesDetailsCustomizationBaseNode.h"

#include "DetailLayoutBuilder.h"
#include "Nodes/QuickDialoguesBaseNode.h"

TSharedRef<IDetailCustomization> FQuickDialoguesDetailsCustomizationBaseNode::MakeInstance()
{
	return MakeShareable(new FQuickDialoguesDetailsCustomizationBaseNode);
}

void FQuickDialoguesDetailsCustomizationBaseNode::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> CustomizedObjects;
	DetailBuilder.GetObjectsBeingCustomized(CustomizedObjects);

	for (TWeakObjectPtr<UObject> Object : CustomizedObjects)
	{
		if (UQuickDialoguesBaseNode* Node = Cast<UQuickDialoguesBaseNode>(Object.Get()))
		{
			if (!Node->GetUsesDefaultParent())
			{
				DetailBuilder.HideProperty(GET_MEMBER_NAME_CHECKED(UQuickDialoguesBaseNode, Parents));
			}
			if (!Node->GetUsesDefaultChildren())
			{
				DetailBuilder.HideProperty(GET_MEMBER_NAME_CHECKED(UQuickDialoguesBaseNode, Child));
			}
		}
	}
}
