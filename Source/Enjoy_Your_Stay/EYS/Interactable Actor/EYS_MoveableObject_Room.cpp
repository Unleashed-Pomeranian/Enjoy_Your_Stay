// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_MoveableObject_Room.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "Components/BoxComponent.h"
#include "EYS/Interactable Actor/TargetPoints/EYS_DirtTarget.h"

void AEYS_MoveableObject_Room::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	
    if (!bIsDoorLocked)
    {
        Super::eInteract_Implementation(myPlayer);
    }
	else
	{
		myPlayer->PlayMontage(0);
		if (AssignedNPCs)
		{
			AssignedNPCs->MoveTo(TriggerBox->GetComponentLocation(), 50.0f);
			AssignedNPCs->bisDialogueEnd = false;
		}
	}

}

void AEYS_MoveableObject_Room::OnDoorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnDoorOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (!OtherActor) return;
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "InInteract");

    bool bIsRoomDirty = false;
    for (AEYS_DirtTarget* SingleTarget : MyRoomTargets)
    {
        if (SingleTarget && SingleTarget->bIsOccupied)
        {
            bIsRoomDirty = true;
            break;
        }
    }

    if (AEYS_GuestCharacter* OverlappingNPC = Cast<AEYS_GuestCharacter>(OtherActor))
    {
        if (bIsRoomDirty)
        {
          

          
            OverlappingNPC->CurrentStatus = EGuestStatus::DirtyRoom;
            OverlappingNPC->MoveTo(OverlappingNPC->LobyLocation, 50.0f); 
        }
        else
        {
            
            AssignedNPCs = OverlappingNPC;
            bIsDoorLocked = true;
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "HaveRoom");
        }
    }
}
	


void AEYS_MoveableObject_Room::OnDoorOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnDoorOverlapEnd(OverlappedComponent, OtherActor,
		OtherComp, OtherBodyIndex);
}