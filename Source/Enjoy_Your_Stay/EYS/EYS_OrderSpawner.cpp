// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/EYS_OrderSpawner.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AEYS_OrderSpawner::AEYS_OrderSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Deafault Scene Root"));
	RootComponent = DefaultSceneRoot;
	
}

// Called when the game starts or when spawned
void AEYS_OrderSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_OrderSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_OrderSpawner::SpawnOrder(UClass* SpawnClass)
{
	/*if (ChildActor && SpawnClass)
	{
		ChildActor->SetChildActorClass(SpawnClass);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "spawnokOk");
	}
	*/
	GetWorld()->SpawnActor<AActor>(SpawnClass, GetActorTransform());
	
}

