// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MissionSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Interactable Actor/EYS_FixActor.h"
#include "EYS/Interactable Actor/EYS_DirtActor.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/Interactable Actor/TargetPoints/EYS_DirtTarget.h"
#include "EYS/Interactable Actor/EYS_SnowPileActor.h"

AEYS_MissionSpawner::AEYS_MissionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

// Called when the game starts or when spawned
void AEYS_MissionSpawner::BeginPlay()
{
	Super::BeginPlay();
	TutorialSubsystemRef = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (TutorialSubsystemRef||TutorialSubsystemRef->bIsTutorialFinished)
	{
		TutorialSubsystemRef->OnFirstPhaseEnd.AddDynamic(this, &AEYS_MissionSpawner::SpawnDirtActorTimer);
		TutorialSubsystemRef->OnFirstPhaseEnd.AddDynamic(this, &AEYS_MissionSpawner::SpawnWallDirtActorTimer);
		TutorialSubsystemRef->OnFirstPhaseEnd.AddDynamic(this, &AEYS_MissionSpawner::SpawnSnowPileActorTimer);
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


	if (UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>())
	{
		Director->TargetMissionSpawner = this;
	}
	
}
void AEYS_MissionSpawner::SpawnFixActorTimer()
{
	SpawnFixActor();
	SetStepOfTutorial();
	float RandomDelay = FMath::RandRange(60.0f, 120.0f);
	float CurrentMultiplier = 1.0f;

		if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
		{
			CurrentMultiplier = UpgradeSys->GetPipeFailureIntervalMultiplier();
		}
		RandomDelay *= CurrentMultiplier;
	GetWorld()->GetTimerManager().SetTimer(FixTimerHandle, this, &AEYS_MissionSpawner::SpawnFixActorTimer, RandomDelay, false);

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




void AEYS_MissionSpawner::SpawnDirtActorTimer()
{

	SpawnMissionActor(ESurfaceType::Floor, ERoomID::None,true);
	float CurrentMultiplier = 1.0f;
	float RandomDelay = FMath::RandRange(60.0f, 120.0f);
	if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		CurrentMultiplier = UpgradeSys->GetDirtAccumulationMultiplier();
	}
	RandomDelay *= CurrentMultiplier;
	GetWorld()->GetTimerManager().SetTimer(DirtTimerHandle, this, &AEYS_MissionSpawner::SpawnDirtActorTimer, RandomDelay, false);

}



void AEYS_MissionSpawner::SpawnWallDirtActorTimer()
{
	SpawnMissionActor(ESurfaceType::Wall, ERoomID::None,true);
	float CurrentMultiplier = 1.0f;
	float RandomDelay = FMath::RandRange(60.0f, 120.0f);
	if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		CurrentMultiplier = UpgradeSys->GetDirtAccumulationMultiplier();
	}
	RandomDelay *= CurrentMultiplier;
	GetWorld()->GetTimerManager().SetTimer(WallDirtTimerHandle, this, &AEYS_MissionSpawner::SpawnWallDirtActorTimer, RandomDelay, false);
}

void AEYS_MissionSpawner::SpawnSnowPileActorTimer()
{
	SpawnMissionActor(ESurfaceType::Exterior, ERoomID::None,true);
	float RandomDelay = FMath::RandRange(60.0f, 120.0f);
	GetWorld()->GetTimerManager().SetTimer(SnowPileTimerHandle, this, &AEYS_MissionSpawner::SpawnSnowPileActorTimer, RandomDelay, false);
}

void AEYS_MissionSpawner::SpawnMissionActor(ESurfaceType TargetSurfaceType, ERoomID TargetRoomID,bool bisReduceMental)
{
	UClass* ClassToSpawn = nullptr;

	switch (TargetSurfaceType)
	{
	case ESurfaceType::Floor:
		ClassToSpawn = DirtActor.Get();
		break;
	case ESurfaceType::Wall:
		ClassToSpawn = WallDirtActor.Get();
		break;
	case ESurfaceType::Exterior:
		ClassToSpawn = SnowPileActor;
		break;
	default:
		return;
	}

	if (!ClassToSpawn) return;

	TArray<AEYS_DirtTarget*> AvailablePoints;
	for (AEYS_DirtTarget* Target : AllDirtTargets)
	{
		if (Target && !Target->bIsOccupied && Target->SurfaceType == TargetSurfaceType)
		{
			if (Target->RoomID == TargetRoomID)
			{
				AvailablePoints.Add(Target);
			}
		}
	}

	if (AvailablePoints.Num() == 0) return;

	AEYS_DirtTarget* ChosenPoint = AvailablePoints[FMath::RandRange(0, AvailablePoints.Num() - 1)];

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ClassToSpawn, ChosenPoint->GetActorTransform());

	if (SpawnedActor)
	{
		ChosenPoint->bIsOccupied = true;

		if (AEYS_DirtActor* Dirt = Cast<AEYS_DirtActor>(SpawnedActor))
		{
			Dirt->MyDirtTarget = ChosenPoint;
			Dirt->bIsEffectMental = bisReduceMental;
		}
		else if (AEYS_SnowPileActor* Snow = Cast<AEYS_SnowPileActor>(SpawnedActor))
		{
			Snow->MySnowTarget = ChosenPoint;
		}
	}
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

