// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestAIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"



void AEYS_GuestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GuestCharacter = Cast<AEYS_GuestCharacter>(InPawn);
}
void AEYS_GuestAIController::MoveToPoint(const FVector& Destiniton, float AccceptanceRadius)
{
	FAIMoveRequest MoveReq;
	MoveReq.SetGoalLocation(Destiniton);
	MoveReq.SetAcceptanceRadius(AccceptanceRadius);

	FNavPathSharedPtr NavPath;
	MoveTo(MoveReq, &NavPath);
   
}

void AEYS_GuestAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    if (Result.IsSuccess())	
	{
        OnAIMoveComplete.Broadcast();

    }
}