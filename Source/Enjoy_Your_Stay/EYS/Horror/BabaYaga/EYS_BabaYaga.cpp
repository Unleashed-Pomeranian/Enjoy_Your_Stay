// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Horror/BabaYaga/EYS_BabaYaga.h"
#include "EYS/Horror/BabaYaga/EYS_BabaYagaAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"

AEYS_BabaYaga::AEYS_BabaYaga()
{
	PrimaryActorTick.bCanEverTick = false;

	// Baba Yaga'nın varsayılan olarak bu asil controller ile doğmasını sağlıyoruz gulum
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
		// Canavarın durduğu noktanın 15 metre çapında rastgele bir NavMesh koordinatı bul gulum
		if (NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 3000.0f, RandomPt))
		{
			MyCont->MoveToLocation(RandomPt.Location, 50.0f);

			// Gittiği noktada sinsi sinsi 4-8 saniye bekleyip sonra yeni ava çıksın ke gulum
			
		}
	}
}

