// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_WashingMachine.generated.h"

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_WashingMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEYS_WashingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
