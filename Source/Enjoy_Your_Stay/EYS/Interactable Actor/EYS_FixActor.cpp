// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_FixActor.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Interactable Actor/EYS_Boiler.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Game Managers/EYS_MissionSubsystem.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"
AEYS_FixActor::AEYS_FixActor()
{

	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
		RootComponent = DefaultSceneRoot;
		StaticMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
		StaticMesh->SetupAttachment(DefaultSceneRoot);

		
		
}

// Called when the game starts or when spawned
void AEYS_FixActor::BeginPlay()
{
	Super::BeginPlay();
	
		BoilerActor = Cast<AEYS_Boiler>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Boiler::StaticClass()));
		if (BoilerActor)
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AEYS_FixActor::SetBoilerFuel, 10.0f, true);

		if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
		{
			MS->RegisterMissionTarget(EMissionType::Fixing);
		}
		if (UEYS_UpgradeSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
		{
			
			FixingSpeedMultiplier = US->GetEquipmentUseTimeMultiplier();
		}
}


void AEYS_FixActor::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	
		PC->SetInteractionWidget("[M1] Fix");

	

}
void AEYS_FixActor::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	if (Value == 2)
		SetPipeMesh();

}
void AEYS_FixActor::Interact(AEYS_MyCharacter* myPlayer)
{
	

}

void AEYS_FixActor::SetPipeMesh()
{
	float FinalFixingValue = FixingValue * FixingSpeedMultiplier;
	FixRate = FMath::Clamp(FixRate + FinalFixingValue,0.0f,100.0f);
	PlayFixAudio();

	if (FixRate >= 100.f)
	{
		GetWorld()->SpawnActor<AActor>(SinglePipeRef, GetActorTransform());
		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::FixBrokenPipe, ETutorialStep::GoToBedSecond);
		}
		if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
		{
			MS->UpdateMissionProgress(EMissionType::Fixing);
		}
		Destroy();

	}
	else if (FixRate > 75.f)
	{
		StaticMesh->SetStaticMesh(PipeMeshes[2]);
	}
	else if (FixRate > 50.f)
	{
		StaticMesh->SetStaticMesh(PipeMeshes[1]);
	}
	else if (FixRate > 25.f)
	{
		StaticMesh->SetStaticMesh(PipeMeshes[0]);
	}
}

void AEYS_FixActor::SetBoilerFuel()
{
	if (!(BoilerActor==nullptr))
	BoilerActor->SetCoalAmount(-0.5f);
}

void AEYS_FixActor::PlayFixAudio_Implementation()
{

}

