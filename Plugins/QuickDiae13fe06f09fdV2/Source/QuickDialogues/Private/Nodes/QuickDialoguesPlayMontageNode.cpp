//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesPlayMontageNode.h"
#include "Animation/AnimMontage.h"

FText UQuickDialoguesPlayMontageNode::GetNodeTypeAsText() const
{
	return FText::FromString("Play Montage Node");
}

UQuickDialoguesBaseNode* UQuickDialoguesPlayMontageNode::GetNextNode(UObject* InOwner)
{
	return Super::GetNextNode(InOwner);
}

FQuickDialoguesPlayMontageNodeData UQuickDialoguesPlayMontageNode::GetMontageToPlay()
{
	return MontageData;
}

void UQuickDialoguesPlayMontageNode::SetMontageToPlay(UAnimMontage* InMontage)
{
#if WITH_EDITOR
	Modify();
#endif
	MontageData.MontageToPlay = InMontage;
}

FString UQuickDialoguesPlayMontageNode::GetMontageToPlayPathName() const
{
	if (MontageData.MontageToPlay)
	{
		return MontageData.MontageToPlay->GetPathName();
	}
	return FString();
}
