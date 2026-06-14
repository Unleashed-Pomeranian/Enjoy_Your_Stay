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

	// 🧠 Algı Motoru ve Duyuları gulum
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EYS | BabaYaga")
	UAIPerceptionComponent* BabaYagaPerceptionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EYS | BabaYaga")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EYS | BabaYaga")
	UAISenseConfig_Hearing* HearingConfig;

	// 🔔 Duyulardan biri tetiklendiğinde patlayacak kutsal fonksiyon ke!
	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
private:
	// ⏳ 5 saniyelik gözden kaybetme sayacı
	FTimerHandle LoseTargetTimerHandle;

	UPROPERTY()
	AActor* TargetPlayer = nullptr;

	// Takibi tamamen bırakıp eski asil düzenine dönme tetiği
	void StopChasing();
	
};
