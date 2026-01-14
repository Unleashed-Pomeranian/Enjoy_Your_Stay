// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/EYS_QDialoguesListenerComponent.h"

void UEYS_QDialoguesListenerComponent::FStartDialogue(UQuickDialoguesNodeTree* Dialogue, UQuickDialoguesSpeakerComponent* Speaker)
{
	StartDialogue(Dialogue, Speaker);
}
FOnDialogueEnd& UEYS_QDialoguesListenerComponent::GetOnDialogueEndDelegate()
{
	return OnDialogueEnd; // protected ama türetilmiş class içindeyiz
}