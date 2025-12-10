// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestAIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

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
      //  UE_LOG(LogTemp, Warning, TEXT("AI Move Completed Successfully!"));
        OnAIMoveComplete.Broadcast();   
    }
}