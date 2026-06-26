// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EYS_BabaYagaAIController.generated.h"

/**
 * 
 */
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_BabaYagaAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEYS_BabaYagaAIController();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EYS | BabaYaga")
	UAIPerceptionComponent* BabaYagaPerceptionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EYS | BabaYaga")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EYS | BabaYaga")
	UAISenseConfig_Hearing* HearingConfig;

	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY()
	class AEYS_BabaYaga* MyBabaYagaPawn;
	
private:

	FTimerHandle LoseTargetTimerHandle;
	FTimerHandle PatrolTimerHandle;

	UPROPERTY()
	AActor* TargetPlayer = nullptr;

	void StopChasing();

public:
	FORCEINLINE void SetTargetPlayer(AActor* NewTarget) { TargetPlayer = NewTarget; }
	

	/*------Stuck Control---------*/
protected:
	FTimerHandle StuckCheckTimerHandle;
	FVector LastCheckedLocation;
	int32 StuckCounter; 


	void CheckIfStuck();
	void StartStuckCheck();
	void StopStuckCheck();
};
