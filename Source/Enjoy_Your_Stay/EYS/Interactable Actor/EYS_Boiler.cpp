// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Boiler.h"
#include "EYS/UI/EYS_Boiler_UI.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Game Managers/EYS_MissionSubsystem.h"
#include "EYS/Game Managers/EYS_HorrorSubsystem.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"
#include "Components/AudioComponent.h"

// Sets default values
AEYS_Boiler::AEYS_Boiler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(SkeletalMesh,FName("Kapak"));
	WidgetMesh = CreateDefaultSubobject<UWidgetComponent>(TEXT("NoteBook Widget"));
	WidgetMesh->SetupAttachment(DefaultSceneRoot);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("WashingAudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEYS_Boiler::BeginPlay()
{
	Super::BeginPlay();
	//WidgetMesh->SetWidgetClass(BoilerWidgetClass);
	//if (Widget)
	
	WidgetMesh->SetWidgetClass(BoilerWidgetClass);
	WidgetMesh->InitWidget();
	BoilerWidgetInstance = Cast<UEYS_Boiler_UI>(WidgetMesh->GetUserWidgetObject());

	if (BoilerWidgetInstance && BoilerWidgetInstance->ProgressBar)
	{
		BoilerWidgetInstance->ProgressBar->SetPercent(BoilerCoalValue / 100.0f);
	}
		
		MissionSubsystem = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>();

		
			if (UEYS_HorrorSubsystem* HorrorSys = GetWorld()->GetSubsystem<UEYS_HorrorSubsystem>())
			{
		
				HorrorSys->SetBoilerReference(this);
			}
			bool bPlayAudio = BoilerCoalValue > 0.0f;;
			
			PlayBoilerAudio(bPlayAudio);

			if(bPlayAudio) GetWorld()->GetTimerManager().SetTimer(BoilerTimerHandle, this, &AEYS_Boiler::ReduceCoalValue, 5.0f, true);
}


void AEYS_Boiler::ReduceCoalValue()
{
	if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		
		float CurrentConsumptionMultiplier = UpgradeSys->GetBoilerFuelConsumptionMultiplier();

		BoilerConsumptionMultiplier = CurrentConsumptionMultiplier;
	}

	float FinalCalculatedConsumption = BoilerConsumptionValue * BoilerConsumptionMultiplier;
	BoilerCoalValue = FMath::Clamp(BoilerCoalValue- FinalCalculatedConsumption, 0.0f, 100.0f);
	if (BoilerWidgetInstance && BoilerWidgetInstance->ProgressBar)
	{
		BoilerWidgetInstance->ProgressBar->SetPercent(BoilerCoalValue / 100.0f);
	}

	if (BoilerCoalValue <= 20.0f)
	{
		if (MissionSubsystem)
		{
			if (!bIsBoilerMissionActive)
			{
				MissionSubsystem->RegisterMissionTarget(EMissionType::Boiler);
				bIsBoilerMissionActive = true;
			}
			MissionSubsystem->UpdateMissionProgress(EMissionType::Boiler, FMath::RoundToInt(BoilerCoalValue));

		}
		if (BoilerCoalValue <= 0.0f)
		{
			GetWorld()->GetTimerManager().ClearTimer(BoilerTimerHandle);

			if (AudioComponent)
			{
				PlayBoilerAudio(false);
			}
		}
	}
}
void AEYS_Boiler::PlayBoilerAudio_Implementation(bool bIsPlaying)
{

}
void   AEYS_Boiler::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void   AEYS_Boiler::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	
}

void   AEYS_Boiler::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{


	if (bAnimFlip)
	{
		// B
		SkeletalMesh->PlayAnimation(AnimAssets[0], false);
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
	
		SkeletalMesh->PlayAnimation(AnimAssets[1], false);
		
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	bAnimFlip = !bAnimFlip; 
}


void AEYS_Boiler::SetCoalAmount(float FuelAddValue)
{
	BoilerCoalValue =  FMath::Clamp(BoilerCoalValue + FuelAddValue, 0.0f, 100.0f);

	if (BoilerWidgetInstance && BoilerWidgetInstance->ProgressBar)
	{
		BoilerWidgetInstance->ProgressBar->SetPercent(BoilerCoalValue / 100.0f);
	}

	if (BoilerCoalValue >= 5.0f && AudioComponent && !AudioComponent->IsPlaying())
	{
		PlayBoilerAudio(true);

		UWorld* World = GetWorld();
		if (!World) return;
		if (!GetWorld()->GetTimerManager().IsTimerActive(BoilerTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(
				BoilerTimerHandle,
				this,
				&AEYS_Boiler::ReduceCoalValue,
				5.0f,
				true
			);
		}
	}

	if (BoilerCoalValue >= 40.0f)
	{
		UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
		if (TS)
		{
			TS->UpdateTutorialState(ETutorialStep::FillBoiler, ETutorialStep::SpawnThirdHorrorActor);
		}

	}
	if (bIsBoilerMissionActive)
	{
		if (MissionSubsystem)
		{
			if (BoilerCoalValue >= 40.0f)
			{

				MissionSubsystem->UpdateMissionProgress(EMissionType::Boiler, 40);
				bIsBoilerMissionActive = false;
			}
		}
	}

}