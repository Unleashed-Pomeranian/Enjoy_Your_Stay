// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_Sheet.h"
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

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
	int32 MeshIndex = bIsDirty ? 1 : 0;
	if (SheetMeshes.IsValidIndex(MeshIndex)&& SheetMeshes[MeshIndex])
	{
		StaticMesh->SetStaticMesh(SheetMeshes[MeshIndex]);
	}
}
void AEYS_Sheet::DetachActor()
{

	Super::DetachActor();
	SetDirtStatus(true);

	
	
}
void AEYS_Sheet::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	Super::InteractUI_Implementation(myPlayer, bIsFocused);
	if (AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController()))
	{
		FString InteractionText = "[E] Take";
		PC->SetInteractionWidget(InteractionText);
	}
	

}

void AEYS_Sheet::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Super::eInteract_Implementation(myPlayer);
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::TakeCleanSheet, ETutorialStep::PutCleanSheet);
	}

}