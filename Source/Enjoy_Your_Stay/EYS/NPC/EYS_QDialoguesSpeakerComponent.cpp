// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_QDialoguesSpeakerComponent.h"
#include "QuickDialoguesNodeTree.h" 
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UEYS_QDialoguesSpeakerComponent::BeginPlay()
{  
    /*
    if (bRandomDialogueOnBeginPlay && DialoguePool.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, DialoguePool.Num() - 1);

 
        Dialogue = DialoguePool[Index];
    }
    */
    Super::BeginPlay();
}


void UEYS_QDialoguesSpeakerComponent::SetDialogueRuntime()
{
   
  
    if (Dialogue)
    {
        MyPlayer->MyDialogueComponent->FStartDialogue(Dialogue, this);
    }
}

void UEYS_QDialoguesSpeakerComponent::UpdateDialog(int32 dialogueindex)
{
    if (DialoguePool.IsValidIndex(dialogueindex))
    {
        Dialogue = DialoguePool[dialogueindex];


        if (Dialogue && GetOwner())
        {
            Dialogue->SetUp(GetOwner());

        }
    }
}

void UEYS_QDialoguesSpeakerComponent::StartDialogue(AEYS_MyCharacter* myPlayer)
{
    if (Dialogue && GetOwner())
    {
        Dialogue->SetUp(GetOwner());

    }
    myPlayer->MyDialogueComponent->FStartDialogue(Dialogue, this);
}
