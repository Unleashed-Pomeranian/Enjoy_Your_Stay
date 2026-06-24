// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_TrayHolder.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "HeavyEquipment/EYS_Tray.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

// Sets default values
AEYS_TrayHolder::AEYS_TrayHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	StaticMesh->SetCustomDepthStencilValue(5);
	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced Static Mesh"));
	InstancedStaticMesh->SetupAttachment(DefaultSceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_TrayHolder::BeginPlay()
{
	Super::BeginPlay();

	int32 LoadedTrayCount = 4;
	InstanceIndex = -1;

	for (int32 i = 0; i < LoadedTrayCount; i++)
	{

		AddTray();
	}
}

void AEYS_TrayHolder::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (!myPlayer) return;


	if (myPlayer->HeldEquipment != nullptr)
	{
		AEYS_Tray* Tray = Cast<AEYS_Tray>(myPlayer->HeldEquipment);
		if (Tray && InstanceIndex < MaxTrayCount - 1)
		{

			if (!Tray->IsSlotEmpty(0) || !Tray->IsSlotEmpty(1))
			{

				return;
			}


			Tray->RemoveTray();

			AddTray();
		}
	}
	else
	{
		if (InstanceIndex >= 0)
		{
		
			DeleteTray();
		}
	}
}

void AEYS_TrayHolder::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (!PC) return;

	if (myPlayer->HeldEquipment)
	{
		if (myPlayer->HeldEquipment->IsA(AEYS_Tray::StaticClass()))
		{
			AEYS_Tray* Tray = Cast<AEYS_Tray>(myPlayer->HeldEquipment);

			
			if (Tray && (!Tray->IsSlotEmpty(0) || !Tray->IsSlotEmpty(1)))
			{
				PC->SetInteractionWidget("Empty the tray first!");
			}
			else if (InstanceIndex < MaxTrayCount - 1)
			{
				PC->SetInteractionWidget("[E] Place Tray");
			}
			else
			{
				PC->SetInteractionWidget("Tray Holder is Full.");
			}
		}
		else
		{
			PC->SetInteractionWidget("Only Trays allowed here.");
		}
	}
	else
	{
		if (InstanceIndex >= 0)
		{
			PC->SetInteractionWidget("[E] Take Tray");
		}
		else
		{
			PC->SetInteractionWidget("No Trays Left.");
		}
	}
	StaticMesh->SetRenderCustomDepth(bIsFocused);
}

void AEYS_TrayHolder::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void AEYS_TrayHolder::AddTray()
{
	int32 NextIndex = InstanceIndex + 1;


	if (NextIndex < MaxTrayCount && InstanceTransform.IsValidIndex(NextIndex))
	{
		InstancedStaticMesh->AddInstance(InstanceTransform[NextIndex], false);

	
		InstanceIndex = NextIndex;
	}
}

void AEYS_TrayHolder::DeleteTray()
{
	if (InstanceIndex >= 0 && CurrentTray)
	{
	
		FTransform SpawnTransform = GetActorTransform();

		AEYS_Tray* SpawnedTray = GetWorld()->SpawnActor<AEYS_Tray>(CurrentTray, SpawnTransform);
		if (SpawnedTray)
		{
			
			SpawnedTray->AttachTray();
			InstancedStaticMesh->RemoveInstance(InstanceIndex);
			InstanceIndex--;
		}

		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::TakeTray, ETutorialStep::TakeFoodBag);
		}
	}
}
