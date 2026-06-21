// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Horror/BabaYaga/EYS_BabaYaga.h"
#include "EYS/Horror/BabaYaga/EYS_BabaYagaAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "NavigationSystem.h"

AEYS_BabaYaga::AEYS_BabaYaga()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);
	AIControllerClass = AEYS_BabaYagaAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void AEYS_BabaYaga::BeginPlay()
{
	Super::BeginPlay();

	SetMovementState(EBabaYagaState::Patrolling);

	if (!GetController())
	{
		SpawnDefaultController();
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		this,
		&AEYS_BabaYaga::StartPatrol
	);

	PlayBabaYagaSound(0);
}

void AEYS_BabaYaga::SetMovementState(EBabaYagaState NewState)
{
	CurrentState = NewState;

	if (CurrentState == EBabaYagaState::Chasing)
	{
		GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
	}
}

void AEYS_BabaYaga::StartPatrol()
{
	if (CurrentState == EBabaYagaState::Chasing) return;

	AAIController* MyCont = Cast<AAIController>(GetController());
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (MyCont && NavSys)
	{
		FNavLocation RandomPt;
		
		if (NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 3000.0f, RandomPt))
		{
			MyCont->MoveToLocation(RandomPt.Location, 50.0f);

		}
	}
}

void AEYS_BabaYaga::PlayBabaYagaSound(int32 Index)
{
	if (AudioComponent)
	{

		if (AudioComponent->IsPlaying())
		{
			AudioComponent->Stop();
		}


		if (BabaYagaSounds.IsValidIndex(Index) && BabaYagaSounds[Index])
		{
			AudioComponent->SetSound(BabaYagaSounds[Index]);
			AudioComponent->Play();
		}
	}
}

