// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SunMoonDaySequenceActor.h"

#include "EYS_MySunMoonDaySequenceActor.generated.h"

class AEYS_MyCharacterController;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MySunMoonDaySequenceActor : public ASunMoonDaySequenceActor
{
	GENERATED_BODY()



	

 
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
	AEYS_MyCharacterController* PC;
	
public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void FSetTimer();
};
