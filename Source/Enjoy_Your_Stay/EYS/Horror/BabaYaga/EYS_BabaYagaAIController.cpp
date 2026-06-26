// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Horror/BabaYaga/EYS_BabaYagaAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "EYS/Horror/BabaYaga/EYS_BabaYaga.h"

#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Game Managers/EYS_MyPostProcessVolume.h"

#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"


AEYS_BabaYagaAIController::AEYS_BabaYagaAIController()
{
	BabaYagaPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("BabaYagaPerceptionComp"));
	SetPerceptionComponent(*BabaYagaPerceptionComp);
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));


	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 2000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f; 
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	BabaYagaPerceptionComp->ConfigureSense(*SightConfig);


	HearingConfig->HearingRange = 1500.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	BabaYagaPerceptionComp->ConfigureSense(*HearingConfig);

	BabaYagaPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEYS_BabaYagaAIController::OnTargetPerceived);
	TargetPlayer = nullptr;
}

void AEYS_BabaYagaAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEYS_BabaYagaAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn)
	{
		
		MyBabaYagaPawn = Cast<AEYS_BabaYaga>(InPawn);
	}
}

void AEYS_BabaYagaAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{

	if (!Actor || !Actor->ActorHasTag("Player") || !MyBabaYagaPawn) return;


	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{

			GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);
			GetWorld()->GetTimerManager().ClearTimer(LoseTargetTimerHandle);

			TargetPlayer = Actor;

	
			if (MyBabaYagaPawn->GetMovementState() != EBabaYagaState::Chasing)
			{
				MyBabaYagaPawn->PlayBabaYagaSound(2); 
			}

		
			MyBabaYagaPawn->SetMovementState(EBabaYagaState::Chasing);
			MoveToActor(TargetPlayer, 70.0f);
			StartStuckCheck();
		}
		else 
		{
			StopStuckCheck();
			GetWorld()->GetTimerManager().SetTimer(LoseTargetTimerHandle, this, &AEYS_BabaYagaAIController::StopChasing, 5.0f, false);
		}
	}


	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
	
		if (Stimulus.WasSuccessfullySensed() && !TargetPlayer)
		{
			GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);

			if (MyBabaYagaPawn->GetMovementState() != EBabaYagaState::Chasing)
			{
				MyBabaYagaPawn->PlayBabaYagaSound(2);
			}


			MyBabaYagaPawn->SetMovementState(EBabaYagaState::Chasing);
			MoveToLocation(Stimulus.StimulusLocation, 70.0f);
			StartStuckCheck();
		}
	}
}

void AEYS_BabaYagaAIController::StopChasing()
{
	TargetPlayer = nullptr;
	StopStuckCheck();

	if (AEYS_BabaYaga* BabaYagaCharacter = Cast<AEYS_BabaYaga>(GetPawn()))
	{
		
		BabaYagaCharacter->SetMovementState(EBabaYagaState::Patrolling);
		BabaYagaCharacter->StartPatrol();
		StartStuckCheck();
	}
}

void AEYS_BabaYagaAIController::CheckIfStuck()
{
	if (!MyBabaYagaPawn)
	{
		StopStuckCheck();
		return;
	}

	FVector CurrentLocation = MyBabaYagaPawn->GetActorLocation();
	float DistanceMoved = FVector::Dist(CurrentLocation, LastCheckedLocation);


	if (DistanceMoved < 15.0f)
	{
		StuckCounter++;


		if (StuckCounter >= 6)
		{
			StopStuckCheck();

			if (TargetPlayer)
			{

				StopMovement();


				MoveToActor(TargetPlayer, 70.0f);
			}
			else
			{

				StopMovement();


				if (MyBabaYagaPawn)
				{
					MyBabaYagaPawn->SetMovementState(EBabaYagaState::Patrolling);
					MyBabaYagaPawn->StartPatrol();
				}
			}
			return;
		}
	}
	else
	{
		
		StuckCounter = 0;
	}

	LastCheckedLocation = CurrentLocation;
}

void AEYS_BabaYagaAIController::StartStuckCheck()
{
	UWorld* World = GetWorld();
	if (!World || !MyBabaYagaPawn || !IsValid(MyBabaYagaPawn)) return;

	World->GetTimerManager().ClearTimer(StuckCheckTimerHandle);
	StuckCounter = 0;
	LastCheckedLocation = MyBabaYagaPawn->GetActorLocation();

	World->GetTimerManager().SetTimer(
		StuckCheckTimerHandle,
		this,
		&AEYS_BabaYagaAIController::CheckIfStuck,
		1.0f,
		true
	);
}


void AEYS_BabaYagaAIController::StopStuckCheck()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(StuckCheckTimerHandle);
	}
	StuckCounter = 0;
}

void AEYS_BabaYagaAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	StopStuckCheck();
	Super::OnMoveCompleted(RequestID, Result);
	UWorld* World = GetWorld();
	if (!World || !MyBabaYagaPawn || !IsValid(MyBabaYagaPawn)) return;

	if (!MyBabaYagaPawn) return; 

	if (Result.IsSuccess() && TargetPlayer)
	{
		AEYS_MyCharacter* PlayerCharacter = Cast<AEYS_MyCharacter>(TargetPlayer);

		if (PlayerCharacter)
		{
			AEYS_MyCharacterController* MyPC = Cast<AEYS_MyCharacterController>(PlayerCharacter->GetController());

			if (MyPC)
			{
				MyBabaYagaPawn->SetMovementState(EBabaYagaState::Catch);
				MyPC->MobilizeCharacter(true, true, false);
				MyPC->StopPlayer();

				FVector BabaYagaForward = MyBabaYagaPawn->GetActorForwardVector();
				FVector TargetPlayerLocation = MyBabaYagaPawn->GetActorLocation() + (BabaYagaForward * 80.0f);
				TargetPlayerLocation.Z = PlayerCharacter->GetActorLocation().Z;

				FVector BabaYagaFaceLoc = MyBabaYagaPawn->GetActorLocation();
				BabaYagaFaceLoc.Z += 200.0f;

				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TargetPlayerLocation, BabaYagaFaceLoc);

				MyPC->SetCharacterPositon(TargetPlayerLocation, 0.0f, 0.0f, TargetRotation);


				float FinalZ = MyBabaYagaPawn->GetActorLocation().Z - 50.0f;
				FVector LockedLocation = FVector(PlayerCharacter->GetActorLocation().X, PlayerCharacter->GetActorLocation().Y, FinalZ);

				PlayerCharacter->SetActorLocation(LockedLocation);
				PlayerCharacter->AttachToActor(MyBabaYagaPawn, FAttachmentTransformRules::KeepWorldTransform);
			}

			AActor* FoundPPVolume = UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MyPostProcessVolume::StaticClass());
			if (FoundPPVolume)
			{
				if (AEYS_MyPostProcessVolume* MyPP = Cast<AEYS_MyPostProcessVolume>(FoundPPVolume))
				{
					MyPP->PlayJumpscareGlitch();
					MyBabaYagaPawn->PlayBabaYagaSound(3);
				}
			}

			TargetPlayer = nullptr;
		}
	}

	else
	{
		if (Result.IsSuccess() && MyBabaYagaPawn->GetMovementState() == EBabaYagaState::Patrolling)
		{

			GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);


			StopMovement();


			MyBabaYagaPawn->PlayBabaYagaSound(1);


			GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, MyBabaYagaPawn, &AEYS_BabaYaga::StartPatrol, FMath::RandRange(3.0f, 5.0f), false);
		}
	}
}

void AEYS_BabaYagaAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopMovement();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PatrolTimerHandle);
		World->GetTimerManager().ClearTimer(LoseTargetTimerHandle);
		World->GetTimerManager().ClearTimer(StuckCheckTimerHandle);
	}

	Super::EndPlay(EndPlayReason);
}