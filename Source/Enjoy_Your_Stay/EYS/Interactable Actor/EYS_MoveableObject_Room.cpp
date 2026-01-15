// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_MoveableObject_Room.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "Components/BoxComponent.h"

void AEYS_MoveableObject_Room::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	
	if(!bIsDoorLocked)
	Super::eInteract_Implementation(myPlayer);
	else
	{
		myPlayer->PlayMontage(0);
		AssignedNPCs->MoveTo(TriggerBox->GetComponentLocation(), 50.0f);
		AssignedNPCs->bisDialogueEnd = false;
	}
}