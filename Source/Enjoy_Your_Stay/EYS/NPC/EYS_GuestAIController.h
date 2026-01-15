// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EYS_GuestAIController.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_GuestAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	DECLARE_MULTICAST_DELEGATE(FOnAIMoveComplete);
	FOnAIMoveComplete OnAIMoveComplete;

	UFUNCTION(BlueprintCallable, Category = "Ai")
	void MoveToPoint(const FVector& Destiniton, float AccceptanceRadius);
	UFUNCTION(BlueprintCallable, Category = "Ai")
	void CorruptedNPC();
	UFUNCTION() void  BrokePipe();
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UClass* PipeRef;
	AActor* SinglePipeRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UClass* BrokenPipeRef;
	bool Iscorrapted = false;
};
