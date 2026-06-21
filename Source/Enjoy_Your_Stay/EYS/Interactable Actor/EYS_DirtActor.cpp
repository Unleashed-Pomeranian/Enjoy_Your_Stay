// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_DirtActor.h"
#include "TargetPoints/EYS_DirtTarget.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

#include "EYS/Game Managers/EYS_MissionSubsystem.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"

AEYS_DirtActor::AEYS_DirtActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	DirtDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Dirt Decal"));
	DirtDecal->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject <UBoxComponent> (TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_DirtActor::BeginPlay()
{
	Super::BeginPlay();
	if (DirtDecal)
	{
		const int32 Index = FMath::RandRange(0, DirtMaterial.Num() - 1);
		if(DirtMaterial[Index])
		DirtDecal->SetDecalMaterial(DirtMaterial[Index]);

		DynMath = DirtDecal->CreateDynamicMaterialInstance();
		if (DynMath)
		{
			DirtDecal->SetMaterial(0,DynMath);
			opacityValue = FMath::Clamp(opacityValue, 0.0f, 3.0f);
			StaticMesh->SetVisibility(false);
		}

	}
	GetWorld()->GetTimerManager().SetTimer(DirtTimerHandle, this, &AEYS_DirtActor::SetGuestMentalHealth, 2.0f, true);

	if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
	{
		MS->RegisterMissionTarget(EMissionType::Cleaning);
	}
	if (UEYS_UpgradeSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		// Kendi yazdığın o asil hız çarpanı fonksiyonu ke (Örn: Seviye 1'de 1.0f, Seviye 2'de 1.5f, Seviye 3'de 2.0f döner)
		CleaningSpeedMultiplier = US->GetEquipmentUseTimeMultiplier();
	}
}
void AEYS_DirtActor::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());

	PC->SetInteractionWidget("[M1] Clean");
}
void AEYS_DirtActor::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	if (Value == EquipmentValue)
	{
		
		Interact(myPlayer);
	}
}



void AEYS_DirtActor::SetGuestMentalHealth()
{
	if (bIsEffectMental)
	{
		UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
		if (!Director) return;

		Director->SetMentalSlate(MentalReduceValue);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(DirtTimerHandle);
	}
}

void AEYS_DirtActor::PlayCleaningAudio_Implementation()
{
}


void AEYS_DirtActor::Interact(AEYS_MyCharacter* myPlayer) 
{
	float FinalCleaningValue = cleaningValue * CleaningSpeedMultiplier;
	opacityValue -= FinalCleaningValue;
	DynMath->SetScalarParameterValue("Opacity", opacityValue);
	PlayCleaningAudio();
	if (opacityValue <= 2.1f)
	{
		cleaningValue = 0.021f;

		if (opacityValue <= 0.2f)
		{
			if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
			{
				MS->UpdateMissionProgress(EMissionType::Cleaning);
			}
			

			
			if (MyDirtTarget) MyDirtTarget->bIsOccupied=false;
			if (!bIsEffectMental)
			{
				if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
				{
					if (TS->CurrentStep == ETutorialStep::CleanCheckOutDirts)
					{
						TS->RegisterCheckoutDirt();
					}
				}
			}
			Destroy();

		}

	}
}
