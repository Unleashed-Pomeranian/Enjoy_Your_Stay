// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EYS_EconomySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_EconomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 Money=10000;


public:

	UFUNCTION()
	void AddMoney(int32 amount);
	UFUNCTION()
	bool SpendMoney(int32 amount);
	UFUNCTION()
	int CurrentMoney();

};
