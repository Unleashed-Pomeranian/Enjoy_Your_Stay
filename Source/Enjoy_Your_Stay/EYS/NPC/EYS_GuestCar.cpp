// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestCar.h"
#include "EYS/NPC/EYS_VehicleSplinePath.h"
#include "Kismet/KismetMathLibrary.h"
#include "EYS_WorldSubsystem.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EYS_GuestCharacter.h"
AEYS_GuestCar::AEYS_GuestCar()
{
	if (GetMesh())
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->BodyInstance.bSimulatePhysics = true;
	}
	CarBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car Body"));
	CarBody->SetupAttachment(GetMesh());
	CharacterSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Guest Skeletal Mesh"));
	CharacterSkeletalMesh->SetupAttachment(GetMesh());
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(GetMesh());
}
void AEYS_GuestCar::BeginPlay()
{
	Super::BeginPlay();
	WheeledMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	if (WheeledMovement)
	{
		WheeledMovement->SetThrottleInput(0.54f);
		GetWorld()->GetTimerManager().SetTimer(CarTimerHandle,this, &AEYS_GuestCar::MoveCar, 0.02f, true, -1.0f);
	}
	SetGuestMesh();
}

float AEYS_GuestCar::GetSteeringAmount()
{
	if (AssignedPath)
	{
		 
		FVector CarLoc = GetActorLocation();
		FVector	Target = AssignedPath->GetTangentClosestToWorld(CarLoc);
		Target.Normalize(0.0001);
		Target *= 200;
		Target += GetActorLocation();
		
		FVector	LookAheadPoint = AssignedPath->GetLocationClosestToWorld(Target);

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LookAheadPoint);

		FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(TargetRotation, GetActorRotation());
		return UKismetMathLibrary::MapRangeClamped(DeltaRot.Yaw, -30.0f, 30.0f, -1.0f, 1.0f);
	}
	else
	return 0.0f;
}

void AEYS_GuestCar::MoveCar()
{
	if (!bIsParking)
	{
		if (WheeledMovement&& AssignedPath)
		{
			FVector CarLoc = GetActorLocation();
			float DistanceToTarget = AssignedPath->GetBreakDistance(CarLoc);
			if (DistanceToTarget < 250)
			{
				WheeledMovement->SetThrottleInput(0.0f);
				WheeledMovement->SetBrakeInput(1.0f);
				WheeledMovement->SetHandbrakeInput(true);
				WheeledMovement->SetTargetGear(0, true);
				bIsParking=true;
				
			}
			else
			{
				float SteeringInput = GetSteeringAmount();
				WheeledMovement->SetSteeringInput(SteeringInput);
				float ThrottleAmount = FMath::GetMappedRangeValueClamped(FVector2D(250.f, 1000.f), FVector2D(0.3f, 0.7f), DistanceToTarget);
				WheeledMovement->SetThrottleInput(ThrottleAmount);
			}
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(CarTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(CarTimerHandle, this, &AEYS_GuestCar::SetGuestSpawn, 3.0f, false, -1.0f);
	}
}

void AEYS_GuestCar::SetGuestMesh()
{
	if (GuestMeshes.Num() > 0 && CharacterSkeletalMesh)
	{
		int32 RandomIndex = FMath::RandRange(0, GuestMeshes.Num() - 1);
		CharacterSkeletalMesh->SetSkeletalMesh(GuestMeshes[RandomIndex]);
	}
}

void AEYS_GuestCar::SetGuestSpawn()
{
	CharacterSkeletalMesh->SetVisibility(false);
	CharacterSkeletalMesh->Deactivate();
	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
	if (!Director) return;
	if (GuestClass)
		Director->RequestSpawnNPC(GuestClass, SpawnPoint->GetComponentTransform(), CharacterSkeletalMesh->GetSkeletalMeshAsset());
}

