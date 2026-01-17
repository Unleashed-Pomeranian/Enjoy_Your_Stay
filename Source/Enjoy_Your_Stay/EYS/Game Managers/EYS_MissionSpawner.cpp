// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MissionSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

AEYS_MissionSpawner::AEYS_MissionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEYS_MissionSpawner::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::K2_SetTimer(this, "SpawnFixActor", 3.0f, true);
	UKismetSystemLibrary::K2_SetTimer(this, "SpawnDirtActor", 5.0f, true);
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

