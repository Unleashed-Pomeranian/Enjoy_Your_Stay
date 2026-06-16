// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestBed.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Sheet.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

// Sets default values
AEYS_GuestBed::AEYS_GuestBed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);
	SheetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sheet Mesh"));
	SheetMesh->SetupAttachment(RootComponent);
	SheetMesh->SetCustomDepthStencilValue(5);
}

// Called when the game starts or when spawned
void AEYS_GuestBed::BeginPlay()
{
	Super::BeginPlay();
	SetSheetStatus(true);
}
void AEYS_GuestBed::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	if (!myPlayer) return;

	if (bIsFocused)
	{
		AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
		if (PC) PC->SetInteractionWidget("[E] Take");
	}
	if (SheetMesh)
	SheetMesh->SetRenderCustomDepth(bIsFocused);
}
void AEYS_GuestBed::Interact(AEYS_MyCharacter* myPlayer)
{

}
void AEYS_GuestBed::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (!myPlayer) return;

	if (!bIsHasSheet && myPlayer->HeldEquipment)
	{
		if (AEYS_Sheet* MySheet = Cast<AEYS_Sheet>(myPlayer->HeldEquipment))
		{
			bool bisDirty = MySheet->GetDirtStatus();
			SetSheetStatus(bisDirty);
			MySheet->RemoveSheet();
			SetSheetMesh(false);
			if (!(MySheet->GetDirtStatus()))
			{
				if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
				{
					TS->UpdateTutorialState(ETutorialStep::PutCleanSheet, ETutorialStep::WaitForUpdate);
				}
			}
		}
	}
		else if (bIsHasSheet && !myPlayer->HeldEquipment)
		{
			SetSheetMesh(true);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Simdi Girdi!");

		}
	
}



void AEYS_GuestBed::SetSheetStatus(bool bIsSheetDirty)

{
	int32 TargetIndex = bIsSheetDirty ? 1 : 0;

	if (SheetMesh && SheetMeshes.IsValidIndex(TargetIndex) && SheetMeshes[TargetIndex])
	{
		SheetMesh->SetStaticMesh(SheetMeshes[TargetIndex]);
		bIsBedDirty = bIsSheetDirty;
	}

}

bool AEYS_GuestBed::GetSheetStatus()
{
	return !bIsHasSheet || bIsBedDirty;
}

void AEYS_GuestBed::SetSheetMesh(bool bIstakingSheet)
{
	if (bIstakingSheet)
	{
		if (!SheetClass)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Second");
			return;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (AEYS_Sheet* SpawnedSheet = GetWorld()->SpawnActor<AEYS_Sheet>(SheetClass, GetActorTransform(), SpawnParams))
		{
			SpawnedSheet->AttachSheet();
			SpawnedSheet->SetDirtStatus(bIsBedDirty);
			SheetMesh->SetVisibility(false);
			bIsHasSheet = false;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Third");
			if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
			{
				TS->UpdateTutorialState(ETutorialStep::TakeDirtySheet, ETutorialStep::GoToLaundryRoom);
			}
		}
		
	}
	else 
	{
		SheetMesh->SetVisibility(true);
		bIsHasSheet = true;
		
	}
	PlayAudioAndVFX();
}

void AEYS_GuestBed::PlayAudioAndVFX_Implementation()
{
}

