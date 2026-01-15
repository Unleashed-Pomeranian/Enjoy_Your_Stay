// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestAIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"

void AEYS_GuestAIController::MoveToPoint(const FVector& Destiniton, float AccceptanceRadius)
{
	FAIMoveRequest MoveReq;
	MoveReq.SetGoalLocation(Destiniton);
	MoveReq.SetAcceptanceRadius(AccceptanceRadius);

	FNavPathSharedPtr NavPath;
	MoveTo(MoveReq, &NavPath);
   
}

void AEYS_GuestAIController::CorruptedNPC()
{
	TArray<AActor*> FoundPipes;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),PipeRef,FoundPipes);

	if (FoundPipes.Num() == 0)
	{
		return;
	}
	const int32 RandomIndex = FMath::RandRange(0, FoundPipes.Num() - 1);
	SinglePipeRef = FoundPipes[RandomIndex];
	MoveToPoint(SinglePipeRef->GetActorLocation(), 50);
	Iscorrapted= true;
	
}

void AEYS_GuestAIController::BrokePipe()
{
	if (BrokenPipeRef)
		GetWorld()->SpawnActor<AActor>(BrokenPipeRef, SinglePipeRef->GetActorTransform());
	SinglePipeRef->Destroy();
	CorruptedNPC();

}

void AEYS_GuestAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    if (Result.IsSuccess())
    {
      //  UE_LOG(LogTemp, Warning, TEXT("AI Move Completed Successfully!"));
        OnAIMoveComplete.Broadcast();
		if (Iscorrapted)
			UKismetSystemLibrary::K2_SetTimer(this, "BrokePipe", 3.0f, false);
    }
}