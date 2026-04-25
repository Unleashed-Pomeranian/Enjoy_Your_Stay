// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_MissionSpawner.generated.h"
class AEYS_FixActor;
class AEYS_DirtActor;
class ATargetPoint;
class UEYS_TutorialSubsystem;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MissionSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEYS_MissionSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AEYS_FixActor> FixActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AEYS_DirtActor> DirtActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UClass* PipeRef;
	AActor* SinglePipeRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ATargetPoint> DirtTargetPoint;

	UPROPERTY()
	 UEYS_TutorialSubsystem* TutorialSubsystemRef;
	/*------------TimerHandle----------*/
	FTimerHandle DirtTimerHandle;
	FTimerHandle FixTimerHandle;
public:
	UFUNCTION() void SpawnFixActor();
	UFUNCTION() void SpawnDirtActor();
	UFUNCTION() void SpawnFixActorTimer();
	UFUNCTION() void SpawnDirtActorTimer();
	UFUNCTION() void StartFixActorSpawening();
	UFUNCTION() void SetStepOfTutorial();

public:	
	

};
