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
	StaticMesh->SetCustomDepthStencilValue(5);
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
void  AEYS_InteractableActor_WP::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	if (bIsFocused)
	{
		AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
		if (PC) PC->SetInteractionWidget("[E] Take");
	}

	StaticMesh->SetRenderCustomDepth(bIsFocused);
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
	if(PC)PC->EquipmentWheelInstance->EnableButtons(Index, true, ESlateVisibility::Visible);
	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (TS)

	{
		switch (Index)
		{
		case 3:
			{
				TS->UpdateTutorialState(ETutorialStep::TakeHammer, ETutorialStep::FixBrokenPipe);
				break;
			}
		case 4:
		{
			
			if (TS->CurrentStep == ETutorialStep::TakeMop)
			{
				TS->UpdateTutorialState(ETutorialStep::TakeMop, ETutorialStep::CleanDirt);
				
				if (AEYS_MissionSpawner* MissionSpawner = Cast<AEYS_MissionSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MissionSpawner::StaticClass())))
				{
					if (MissionSpawner)
					{
						for (int i = 0; i <= 5; i++)
						{
							MissionSpawner->SpawnMissionActor(ESurfaceType::Floor, ERoomID::None,true);
						}
					}
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
			TS->UpdateTutorialState(ETutorialStep::TakeShovel, ETutorialStep::SpawnSecondHorrorActor);
			break;
		}
		case 7:
		{
			if (TS->CurrentStep == ETutorialStep::TakeSponge)
			{
				TS->UpdateTutorialState(ETutorialStep::TakeSponge, ETutorialStep::CleanWallDirt);
				{
					if (AEYS_MissionSpawner* MissionSpawner = Cast<AEYS_MissionSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MissionSpawner::StaticClass())))
					{
						if (MissionSpawner)
						{
							for (int i = 0; i <= 3; i++)
							{
								MissionSpawner->SpawnMissionActor(ESurfaceType::Wall, ERoomID::None, true);
							}
						}
					}
				}
			}
			break;
		}
		default:
			break;
		}
	}
	PlayEquipAudio();

	
}
