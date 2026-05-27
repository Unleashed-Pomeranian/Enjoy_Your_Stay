// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MissionSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Interactable Actor/EYS_FixActor.h"
#include "EYS/Interactable Actor/EYS_DirtActor.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Interactable Actor/TargetPoints/EYS_DirtTarget.h"

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

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DirtTargetPoint, FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (AEYS_DirtTarget* Target = Cast<AEYS_DirtTarget>(Actor))
		{
			AllDirtTargets.Add(Target);
		}
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
	TArray<AActor*> AllPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DirtTargetPoint, AllPoints);

	TArray<AEYS_DirtTarget*> AvailablePoints;
	for (AActor* Actor : AllPoints)
	{
		AEYS_DirtTarget* Target = Cast<AEYS_DirtTarget>(Actor);
		if (Target && !Target->bIsOccupied&&(Target->TargetLocation==ETargetLocation::Main))
		{
			AvailablePoints.Add(Target);
		}
	}

	if (AvailablePoints.Num() == 0) return;

	const int32 RandomIndex = FMath::RandRange(0, AvailablePoints.Num() - 1);
	AEYS_DirtTarget* ChosenPoint = AvailablePoints[RandomIndex];

	if (DirtActor)
	{
		AActor* SpawnedDirt = GetWorld()->SpawnActor<AActor>(DirtActor, ChosenPoint->GetActorTransform());

		if (SpawnedDirt)
		{
		
			ChosenPoint->bIsOccupied = true;
			AEYS_DirtActor* Dirt = Cast<AEYS_DirtActor>(SpawnedDirt);
			if (Dirt) Dirt->MySpawnPoint = ChosenPoint;
		}
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
	GetWorld()->GetTimerManager().SetTimer(FixTimerHandle, this, &AEYS_MissionSpawner::SpawnFixActorTimer, 30.0f, false);
	
}

void AEYS_MissionSpawner::SetStepOfTutorial()
{
	if (TutorialSubsystemRef)
	{
		TutorialSubsystemRef->UpdateTutorialState(ETutorialStep::WaitForPipe, ETutorialStep::GoToHammer);
	}
}



