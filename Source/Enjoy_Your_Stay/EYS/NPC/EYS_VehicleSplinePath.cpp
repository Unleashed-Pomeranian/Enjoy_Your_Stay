// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_VehicleSplinePath.h"
#include "Components/SplineComponent.h"
// Sets default values
AEYS_VehicleSplinePath::AEYS_VehicleSplinePath()
{
	PathSpline = CreateDefaultSubobject<USplineComponent>(TEXT("PathSpline"));
	SetRootComponent(PathSpline);
}

// Called when the game starts or when spawned
void AEYS_VehicleSplinePath::BeginPlay()
{
	Super::BeginPlay();
	
}
/**
FVector AEYS_VehicleSplinePath::GetTangentClosestToWorld(const FVector& worldlock)
{

	FVector Target = PathSpline->FindTangentClosestToWorldLocation(worldlock, ESplineCoordinateSpace::World);
	return Target;
	
}

FVector AEYS_VehicleSplinePath::GetLocationClosestToWorld(const FVector& worldlock)
{

	FVector Target = PathSpline->FindLocationClosestToWorldLocation(worldlock, ESplineCoordinateSpace::World);
	return Target;

	
}
*/

float AEYS_VehicleSplinePath::FindInputKeyClosest(const FVector& worldlock)
{

	return PathSpline->FindInputKeyClosestToWorldLocation(worldlock);
		
}
float AEYS_VehicleSplinePath::GetDistanceAlongSpline(float Key)
{

	
	return PathSpline->GetDistanceAlongSplineAtSplineInputKey(Key);
	

}
FVector AEYS_VehicleSplinePath::GetLocationAtDistance(float Distance)
{
	FVector Target = PathSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	return Target;
}
float AEYS_VehicleSplinePath::ReturnLength()
{
	return PathSpline->GetSplineLength();
}
float AEYS_VehicleSplinePath::GetBreakDistance(const FVector& worldlock)
{
	float SplineLength = PathSpline->GetSplineLength();
	float Distance = PathSpline->GetDistanceAlongSplineAtLocation(worldlock, ESplineCoordinateSpace::World);
	return (SplineLength - Distance);
}



// Called every frame
void AEYS_VehicleSplinePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

