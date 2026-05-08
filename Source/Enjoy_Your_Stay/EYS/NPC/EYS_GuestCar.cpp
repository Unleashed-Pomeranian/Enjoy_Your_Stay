// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestCar.h"
#include "EYS_VehicleSplinePath.h"
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
	SetGuestMesh();
}
void AEYS_GuestCar::InitializeCar(AEYS_VehicleSplinePath* Path)
{
	AssignedPath = Path;
	if (WheeledMovement)
	{
		WheeledMovement->SetUseAutomaticGears(false);
		WheeledMovement->SetThrottleInput(0.0f);
		WheeledMovement->SetTargetGear(1, true);
		WheeledMovement->SetThrottleInput(0.54f);
		GetWorld()->GetTimerManager().SetTimer(CarTimerHandle, this, &AEYS_GuestCar::MoveCar, 0.02f, true, -1.0f);
	}
}

float AEYS_GuestCar::GetSteeringAmount()
{
	AEYS_VehicleSplinePath* ActivePathActor = nullptr;


	switch (CurrentState)
	{
	case EGuestCarState::Arriving: ActivePathActor = AssignedPath; break;
	case EGuestCarState::Exiting:  ActivePathActor = ExitPath;     break;
	case EGuestCarState::Leaving:  ActivePathActor = GlobalLeavingPath; break;
	default: break;
	}

	if (ActivePathActor)
	{
		FVector CarLoc = GetActorLocation();
		float ClosestKey = ActivePathActor->FindInputKeyClosest(CarLoc);
		float ClosestDist = ActivePathActor->GetDistanceAlongSpline(ClosestKey);

		float LookAheadDist = 400.0f;
		float TargetDist = ClosestDist + LookAheadDist;

		TargetDist = FMath::Clamp(TargetDist, 0.0f, ActivePathActor->ReturnLength());
		FVector LookAheadPoint = ActivePathActor->GetLocationAtDistance(TargetDist);

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CarLoc, LookAheadPoint);
		FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(TargetRotation, GetActorRotation());

		float Steering = UKismetMathLibrary::MapRangeClamped(DeltaRot.Yaw, -45.0f, 45.0f, -1.0f, 1.0f);


		return Steering;
	}

	return 0.0f;
}

void AEYS_GuestCar::MoveCar()
{


	AEYS_VehicleSplinePath* PathToUse = nullptr;
	switch (CurrentState)
	{
	case EGuestCarState::Arriving: PathToUse = AssignedPath; break;
	case EGuestCarState::Exiting:  PathToUse = ExitPath;     break;
	case EGuestCarState::Leaving:  PathToUse = GlobalLeavingPath; break;
	default: break;
	}
	

	if (WheeledMovement && PathToUse)
	{
	
		FVector CarLoc = GetActorLocation();
		float DistanceToTarget = PathToUse->GetBreakDistance(CarLoc);
		UE_LOG(LogTemp, Warning, TEXT("DistanceToTarget: %f"), DistanceToTarget);
		if (DistanceToTarget < 250.0f)
		{
			
			if (CurrentState == EGuestCarState::Arriving)
			{
				WheeledMovement->SetThrottleInput(0.0f);
				WheeledMovement->SetBrakeInput(1.0f);
				WheeledMovement->SetHandbrakeInput(true);
				WheeledMovement->SetTargetGear(0, true);
				bIsParking = true;
				GetWorld()->GetTimerManager().ClearTimer(CarTimerHandle);
				GetWorld()->GetTimerManager().SetTimer(CarTimerHandle, this, &AEYS_GuestCar::SetGuestSpawn, 3.0f, false);
				if(AssignedPath) ExitPath = AssignedPath->NextPath;
			}
			else if (CurrentState == EGuestCarState::Exiting&& DistanceToTarget<150.0f)
			{

				WheeledMovement->SetThrottleInput(0.0f);
				WheeledMovement->SetBrakeInput(1.0f);
				GetWorld()->GetTimerManager().ClearTimer(CarTimerHandle);

				FTimerDelegate LeaveDelegate;
				LeaveDelegate.BindLambda([this]() {
					this->CurrentState = EGuestCarState::Leaving;
					this->WheeledMovement->SetHandbrakeInput(false);
					this->WheeledMovement->SetBrakeInput(0.0f);
					this->WheeledMovement->SetTargetGear(1, true);
					GetWorld()->GetTimerManager().SetTimer(CarTimerHandle, this, &AEYS_GuestCar::MoveCar, 0.02f, true);
					});

				GetWorld()->GetTimerManager().SetTimer(CarTimerHandle, LeaveDelegate, 1.0f, false);
			}
			
			else if (CurrentState == EGuestCarState::Leaving)
			{
				GetWorld()->GetTimerManager().ClearTimer(CarTimerHandle);
				Destroy();
			}
		}
		else
		{
			
			float SteeringInput = GetSteeringAmount();

			if (CurrentState == EGuestCarState::Exiting)
			{
				WheeledMovement->SetSteeringInput(SteeringInput);
				WheeledMovement->SetThrottleInput(0.4f);
			}
			else
			{
				
			
				WheeledMovement->SetSteeringInput(SteeringInput);
				float ThrottleAmount = FMath::GetMappedRangeValueClamped(FVector2D(250.f, 1000.f), FVector2D(0.2f, 0.6f), DistanceToTarget);
				WheeledMovement->SetThrottleInput(ThrottleAmount);
				
			}
			
		}
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
	{
		AEYS_GuestCharacter* AssignedNPC = Director->RequestSpawnNPC(GuestClass, SpawnPoint->GetComponentTransform(), CharacterSkeletalMesh->GetSkeletalMeshAsset());
		AssignedNPC->AssignedCar = this;
	}
	    CurrentState = EGuestCarState::Waiting;
		

}

void AEYS_GuestCar::DriveBack()
{
	CharacterSkeletalMesh->SetVisibility(true);
	if (WheeledMovement)
	{
		CurrentState = EGuestCarState::Exiting;
		bIsParking = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "driveback");
		WheeledMovement->SetUseAutomaticGears(false);
		WheeledMovement->SetBrakeInput(0.0f);
		WheeledMovement->SetHandbrakeInput(false);
		WheeledMovement->SetTargetGear(-1, true);
		WheeledMovement->SetThrottleInput(0.45f);
	}

	if (AssignedPath) AssignedPath->bIsOccupied = false;
	if (ExitPath) GlobalLeavingPath = ExitPath->NextPath;
	GetWorld()->GetTimerManager().SetTimer(CarTimerHandle, this, &AEYS_GuestCar::MoveCar, 0.02f, true);
	
}

