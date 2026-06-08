// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_Sheet.h"
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GamePlayStatics.h"

void AEYS_Sheet::AttachSheet()
{
	AEYS_MyCharacter* myPlayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!myPlayer) return;
	AttachActor(myPlayer);
}

void AEYS_Sheet::RemoveSheet()
{
	DetachFromPlayer();
}

bool AEYS_Sheet::GetDirtStatus()
{
	return bIsDirty;
}

void AEYS_Sheet::SetDirtStatus(bool bDirtStatus)
{
	bIsDirty = bDirtStatus;
}
void AEYS_Sheet::DetachActor()
{

	Super::DetachActor();
	bIsDirty = true;
	
	
}