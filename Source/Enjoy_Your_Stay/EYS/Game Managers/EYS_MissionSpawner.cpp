// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MissionSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "EYS/Interactable Actor/EYS_FixActor.h"
#include "EYS/Interactable Actor/EYS_DirtActor.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

AEYS_MissionSpawner::AEYS_MissionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AEYS_MissionSpawner::BeginPlay()
{
	Super::BeginPlay();
	TutorialSubsystemRef = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (TutorialSubsystemRef)
	{
		TutorialSubsystemRef->OnFirstPhaseEnd.AddDynamic(this, &AEYS_MissionSpawner::SpawnDirtActorTimer);
		TutorialSubsystemRef->OnSecondPhaseEnd.AddDynamic(this, &AEYS_MissionSpawner::StartFixActorSpawening);
	}

}

void AEYS_MissionSpawner::SpawnFixActor()
{
	TArray<AActor*> FoundPipes;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PipeRef, FoundPipes);

	if (FoundPipes.Num() == 0)
	{
		return;
	}
	const int32 RandomIndex = FMath::RandRange(0, FoundPipes.Num() - 1);
	SinglePipeRef = FoundPipes[RandomIndex];
	
	if (FixActor)
		GetWorld()->SpawnActor<AActor>(FixActor, SinglePipeRef->GetActorTransform());
	SinglePipeRef->Destroy();
}

void AEYS_MissionSpawner::SpawnDirtActor()
{
	TArray<AActor*> TargetPoints;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DirtTargetPoint, TargetPoints);
	if (TargetPoints.Num() == 0)
	{
		return;
	}
	const int32 RandomIndex = FMath::RandRange(0, TargetPoints.Num() - 1);
	if (DirtActor)
	{
		GetWorld()->SpawnActor<AActor>(DirtActor, TargetPoints[RandomIndex]->GetActorTransform());
		TargetPoints[RandomIndex]->Destroy();
		
	}
	
}

void AEYS_MissionSpawner::SpawnFixActorTimer()
{
	SpawnFixActor();
	SetStepOfTutorial();
	float RandomDelay = FMath::RandRange(15.0f, 120.0f);
	GetWorld()->GetTimerManager().SetTimer(FixTimerHandle, this, &AEYS_MissionSpawner::SpawnFixActorTimer,RandomDelay, false);
	
}

void AEYS_MissionSpawner::SpawnDirtActorTimer()
{
	
	SpawnDirtActor();
	float RandomDelay = FMath::RandRange(15.0f, 120.0f);
	GetWorld()->GetTimerManager().SetTimer(DirtTimerHandle, this, &AEYS_MissionSpawner::SpawnDirtActorTimer, RandomDelay, false);
	
}

void AEYS_MissionSpawner::StartFixActorSpawening()
{
	GetWorld()->GetTimerManager().SetTimer(FixTimerHandle, this, &AEYS_MissionSpawner::SpawnFixActorTimer, 60.0f, false);
	
}

void AEYS_MissionSpawner::SetStepOfTutorial()
{
	if (TutorialSubsystemRef)
	{
		TutorialSubsystemRef->UpdateTutorialState(ETutorialStep::WaitForPipe, ETutorialStep::GoToHammer);
	}
}



