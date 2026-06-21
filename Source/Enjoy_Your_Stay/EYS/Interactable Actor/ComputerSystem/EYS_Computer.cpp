// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/ComputerSystem/EYS_Computer.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/UI/Computer Widgets/EYS_ComputerLoading_UI.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"


// Sets default values
AEYS_Computer::AEYS_Computer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_Computer::BeginPlay()
{
	Super::BeginPlay();
	
}



void  AEYS_Computer::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	
		if(PC) PC->SetInteractionWidget("[E] Open");
	
	
}

void AEYS_Computer::OpenComputer()
{
	if (ComputerLoadingWidgetClass) ComputerLoadingWidgetInstance = CreateWidget<UEYS_ComputerLoading_UI>(GetWorld(), ComputerLoadingWidgetClass);
	if (ComputerLoadingWidgetInstance) ComputerLoadingWidgetInstance->AddToViewport();
	
}

void  AEYS_Computer::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (PC)
	{
		PC->PlayerCameraManager->StartCameraFade(2.0f, 0.0f, 1.5f, FLinearColor::Black, false, true);
		PC->MobilizeCharacter(true, true, true);
		OpenComputer();

		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::OpenComputer, ETutorialStep::MakeAnyUpgrade);
		}
	}
	
}
void  AEYS_Computer::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}