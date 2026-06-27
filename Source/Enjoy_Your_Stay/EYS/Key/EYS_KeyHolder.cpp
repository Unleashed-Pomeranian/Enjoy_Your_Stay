// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Key/EYS_KeyHolder.h"
#include "EYS/Key/EYS_Key.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

// Sets default values
AEYS_KeyHolder::AEYS_KeyHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}
void AEYS_KeyHolder::UpdateKeyDisplay(ERoomID TargetRoom,bool bNewVisibility)
{
    const UEnum* EnumPtr = StaticEnum<ERoomID>();
    if (!EnumPtr) return;

 
    FString EnumName = EnumPtr->GetNameStringByValue((int64)TargetRoom);
    FName TargetTag = FName(*EnumName);
    
      //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TargetTag.ToString());
   
    TArray<UActorComponent*> ChildComps = GetComponentsByTag(UChildActorComponent::StaticClass(), TargetTag);

    for (UActorComponent* Comp : ChildComps)
    {
        if (UChildActorComponent* ChildActorComp = Cast<UChildActorComponent>(Comp))
        {
          
            if (AEYS_Key* KeyActor = Cast<AEYS_Key>(ChildActorComp->GetChildActor()))
            {
                
                KeyActor->SetActorHiddenInGame(!bNewVisibility);
                KeyActor->SetActorEnableCollision(bNewVisibility);

               
               
            }
        }
    }
}


void AEYS_KeyHolder::BeginPlay()
{
	Super::BeginPlay();
	
}



void AEYS_KeyHolder::Interact(AEYS_MyCharacter* myPlayer)
{


}
void AEYS_KeyHolder::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
    if (bIsFocused&&myPlayer->bIsHaveKey)
    {
        AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
        if (PC) PC->SetInteractionWidget("[E] Place");
        
    }
}
void AEYS_KeyHolder::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
    if (!myPlayer) return;

    if (myPlayer->bIsHaveKey)
    {
        myPlayer->SetRoot(0);
        UpdateKeyDisplay(myPlayer->MyRoomID,true);
        myPlayer->bIsHaveKey = false;
        if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
        {
            TS->UpdateTutorialState(ETutorialStep::PutKey, ETutorialStep::GoToGuestRoom);
        }
    }

}