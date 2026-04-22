// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_InteractableActor_WP.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Game Managers/EYS_MissionSpawner.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AEYS_InteractableActor_WP::AEYS_InteractableActor_WP()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

void AEYS_InteractableActor_WP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_InteractableActor_WP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void  AEYS_InteractableActor_WP::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	PC->SetInteractionWidget("[E] Take");
}
void AEYS_InteractableActor_WP::PlayEquipAudio_Implementation()
{

}
void  AEYS_InteractableActor_WP::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Interact(myPlayer);
	
}

void  AEYS_InteractableActor_WP::Interact(AEYS_MyCharacter* myPlayer)
{

	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	PC->EquipmentWheelInstance->EnableButtons(Index, true, ESlateVisibility::Visible);
	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (TS)

	{
		switch (Index)
		{
		case 4:
		{
			TS->UpdateTutorialState(ETutorialStep::TakeMop, ETutorialStep::CleanDirt);
			AEYS_MissionSpawner* MissionSpawner = Cast<AEYS_MissionSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MissionSpawner::StaticClass()));
			if (MissionSpawner)
			{
				for (int i = 0; i <= 5; i++)
				{
					MissionSpawner->SpawnDirtActor();
				}
			}
			break;
		}
		case 5:
		{

			TS->UpdateTutorialState(ETutorialStep::TakeFlashlight, ETutorialStep::GoToBoosRoom);

			break;
		}
		case 6:
		{
			TS->UpdateTutorialState(ETutorialStep::TakeShovel, ETutorialStep::GoToBoilerRoom);
		}
		default:
			break;
		}
	}
	PlayEquipAudio();

	
}
