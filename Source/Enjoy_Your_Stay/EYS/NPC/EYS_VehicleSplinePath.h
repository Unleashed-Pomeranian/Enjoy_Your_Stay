// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_VehicleSplinePath.generated.h"
enum class EPathState : uint8
{
	Main,
	Exiting,
	Leaving
};
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_VehicleSplinePath : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USplineComponent* PathSpline;

	
public:	
	// Sets default values for this actor's properties
	AEYS_VehicleSplinePath();

protected:
	
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//FVector GetTangentClosestToWorld(const FVector& worldlock);
	//FVector GetLocationClosestToWorld(const FVector& worldlock);
	float GetBreakDistance(const FVector& worldlock);
	float FindInputKeyClosest(const FVector& worldlock);
	float GetDistanceAlongSpline(float Key);
	FVector GetLocationAtDistance(float Distance);
	float ReturnLength();
	UPROPERTY(EditInstanceOnly, Category = "Navigation")
	AEYS_VehicleSplinePath* NextPath;
	UPROPERTY() bool bIsOccupied = false;
};
