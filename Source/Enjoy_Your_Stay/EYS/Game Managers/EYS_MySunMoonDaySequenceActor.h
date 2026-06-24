// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SunMoonDaySequenceActor.h"
#include "EYS_MySunMoonDaySequenceActor.generated.h"

class AEYS_MyCharacterController;
class UEYS_TutorialSubsystem;
class UEYS_WorldSubsystem;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MySunMoonDaySequenceActor : public ASunMoonDaySequenceActor
{
	GENERATED_BODY()



	FTimerHandle DayTimerHandle;

 
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
	AEYS_MyCharacterController* PC= nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
	UEYS_TutorialSubsystem* TS = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
	UEYS_WorldSubsystem* Director = nullptr;
	
public:
	UFUNCTION() void FDayTimer();
	UFUNCTION() void SetDayHour(float TimeValue);
	UFUNCTION() void StartNewDay();
	UFUNCTION() void CheckTimeForTutorial();
	UFUNCTION() void CheckTimeForHorror();
	UPROPERTY() int32 DayNum=1;
};
