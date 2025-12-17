// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/EYS_MyCharacter_An.h"
#include "EYS/EYS_MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEYS_MyCharacter_An::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    APawn* Pawn = TryGetPawnOwner();
    OwnerCharacter = Cast<AEYS_MyCharacter>(Pawn);

    if (OwnerCharacter)
    {
        MoveComp = OwnerCharacter->GetCharacterMovement();
    }
    
}

void UEYS_MyCharacter_An::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!OwnerCharacter)
    {
        APawn* Pawn = TryGetPawnOwner();
        OwnerCharacter = Cast<AEYS_MyCharacter>(Pawn);
        if (OwnerCharacter)
        {
            MoveComp = OwnerCharacter->GetCharacterMovement();
        }
    }

    if (!OwnerCharacter)
        return;

 
    Speed = OwnerCharacter->GetVelocity().Size();

   
    bIsInAir= MoveComp ? MoveComp->IsFalling() : false;

   
    PoseNum = OwnerCharacter->PoseNum;

    bIsInAction = OwnerCharacter->bIsAction;

    bIsPhoneOpen = OwnerCharacter->bIsPhoneMode;
    
}