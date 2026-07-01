// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Generator.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/UI/EYS_GeneratorActivateWidget.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FuelTank.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Game Managers/EYS_MissionSubsystem.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"
#include "Components/AudioComponent.h"
#include "EYS_WorldSubsystem.h"
// Sets default values
AEYS_Generator::AEYS_Generator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	
	WidgetMesh = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Mesh"));
	WidgetMesh->SetupAttachment(DefaultSceneRoot);
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetupAttachment(DefaultSceneRoot);
	Fuelingpoint = CreateDefaultSubobject<USceneComponent>(TEXT("Fueling Point"));
	Fuelingpoint->SetupAttachment(DefaultSceneRoot);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEYS_Generator::BeginPlay()
{
	Super::BeginPlay();

	if (AEYS_MyCharacter* Myplayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		PC = Cast<AEYS_MyCharacterController>(Myplayer->GetController());
		if (PC)
		{
			GeneratorActivateWidgetInstance = CreateWidget<UEYS_GeneratorActivateWidget>(PC, GeneratorActivateWidgetClass);
			if (GeneratorActivateWidgetInstance)
			{
				WidgetMesh->SetWidget(GeneratorActivateWidgetInstance);
				GeneratorActivateWidgetInstance->FSetImageRotation(fuelAmount);
				GeneratorActivateWidgetInstance->GeneratorRef = this;
			}
		}
	}


	if(GetGameInstance()) MissionSubsystem = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>();
	if (GetWorld()) WorldSubsystem = GetWorld()->GetSubsystem<UEYS_WorldSubsystem>();


	if (bIsWorking && fuelAmount > 0.1f)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReduceFuel, this, &AEYS_Generator::ReduceFuel, 5.0f, true);
		SetLightColor(2);
		PlayNaturalSound(bIsWorking,0);
	}
	else
	{
		SetLightColor(0);

		bIsWorking = false;

	}

	if (GetWorld() && WorldSubsystem)
	{
		FTimerHandle LightInitHandle;

		GetWorld()->GetTimerManager().SetTimer(LightInitHandle, [this]()
		{
				if (WorldSubsystem)
				{
					WorldSubsystem->ToggleAllOtelLights(bIsWorking);
				}
			}, 0.5f, false);
	}
}

void AEYS_Generator::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{


	if (!myPlayer || !PC) return;


	int32 FuelPercentage = FMath::Clamp(FMath::RoundToInt(fuelAmount), 0, 100);
	FString WidgetText;
	if (myPlayer->HeldEquipment && myPlayer->HeldEquipment->IsA(AEYS_FuelTank::StaticClass()))
	{
		WidgetText = FString::Printf(TEXT("[E] Fill(%%%d)"), FuelPercentage);
	}

	else if (CurrentFuelTank)
	{

		WidgetText = FString::Printf(TEXT("[E] Take Tank(%%%d)"), FuelPercentage);
	}

	else
	{
		if (!bIsWorking)
		{
			 WidgetText = "[E] Start";
		}
		else
		{
		 WidgetText = FString::Printf(TEXT("Working.(%%%d)"), FuelPercentage);		
		}
	}
	PC->SetInteractionWidget(WidgetText);
}


void AEYS_Generator::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}
//Start Engine
void AEYS_Generator::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	
	if (!myPlayer) return;

	if (myPlayer->HeldEquipment && myPlayer->HeldEquipment->IsA(AEYS_FuelTank::StaticClass()))
	{
		CurrentFuelTank = Cast<AEYS_FuelTank>(myPlayer->HeldEquipment);
		if (CurrentFuelTank)
		{
			CurrentFuelTank->AttachToGenerator(Fuelingpoint);

		
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AddFuel, this, &AEYS_Generator::AddFuel, 0.16f, true);
		}
	}
	else
	{
		if (CurrentFuelTank)
		{
			CurrentFuelTank->AttachActor(myPlayer);

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AddFuel);
			CurrentFuelTank = nullptr;
			if (AudioComponent && (AudioComponent->IsPlaying())&&!bIsWorking)
			{
				PlayNaturalSound(false, 1);
			}
		}
		else
		{
			if (!bIsWorking && fuelAmount > 10.0f)
			{
				if (GeneratorActivateWidgetInstance && !(GeneratorActivateWidgetInstance->bIsWorking))
				{
					if (!PC) return;
					myPlayer->SetRoot(0);
					PC->PlayerCameraManager->StartCameraFade(1.5f, 0.0f, 1.5f, FLinearColor::Black, false, true);
					FVector NewLocation = GetActorLocation();

					float NewZ = myPlayer->GetActorLocation().Z;
					NewLocation.Z = NewZ;
					PC->SetCharacterPositon(NewLocation, 30, 5, FRotator(-45, -90, 0));
					PC->MobilizeCharacter(true, false, false);

					if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
					{
						TS->UpdateTutorialState(ETutorialStep::InteractWithGenerator, ETutorialStep::SpawnFirstHorrorActor);
					}
				}

				if (GeneratorActivateWidgetInstance)
				{
					GeneratorActivateWidgetInstance->TimerFTimer();
				}
				PlayActivateSound();
			}
		}
	}
	
}

void AEYS_Generator::StartStopTimer()
{
	if (PC)
	{
		PC->MobilizeCharacter(false, false, false);
	}
	bIsWorking = true;
	if (WorldSubsystem) WorldSubsystem->ToggleAllOtelLights(bIsWorking);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReduceFuel);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReduceFuel, this, &AEYS_Generator::ReduceFuel, 5.0f, true);
	if (AudioComponent && !(AudioComponent->IsPlaying()))
	{
		PlayNaturalSound(bIsWorking, 0);
	}
}

bool AEYS_Generator::BrokeGenerator()
{
	
	if (!bIsWorking || fuelAmount <= 5.0f) return false;

	float GeneratorFailureMultiplier = 1.0f;
	float DiceRoll = FMath::FRandRange(0.0f, 100.0f);

	if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		GeneratorFailureMultiplier = UpgradeSys->GetGeneratorFailureIntervalMultiplier();
	}

	float RawDiceRoll = DiceRoll;
	DiceRoll *= GeneratorFailureMultiplier;
	BreakdownChance = FMath::Clamp(BreakdownChance + 0.005f, 0.0f, 10.0f);
	/*
	if (GEngine)
	{
		/**FString DiceMessage = FString::Printf(
			TEXT("🎲 Jeneratör Zarı -> Ham Zar: %.2f | Upgrade Çarpanı: %.2f | İşlenmiş Nihai Zar: %.2f [Sınır: %.2f]"),
			RawDiceRoll,
			GeneratorFailureMultiplier,
			DiceRoll,
			BreakdownChance
		);
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, DiceMessage);
		
	}
	*/
	if (DiceRoll <= BreakdownChance)
	{
		bIsWorking = false; 
		BreakdownChance = 0.02f;
		if (WorldSubsystem) WorldSubsystem->ToggleAllOtelLights(bIsWorking);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReduceFuel);

		
	
		SetLightColor(0);
		if (AudioComponent && AudioComponent->IsPlaying())
		{
			PlayNaturalSound(bIsWorking, 0);
		}

		return true; 
	}

	return false; 
}


void AEYS_Generator::ReduceFuel()
{

	if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		GeneratorConsumptionMultiplier = UpgradeSys->GetBoilerFuelConsumptionMultiplier();
	}

	float FinalCalculatedConsumption = GeneratorConsumptionValue * GeneratorConsumptionMultiplier;
	fuelAmount = FMath::Clamp(fuelAmount - FinalCalculatedConsumption, 0.0f, 100.0f);

	if (GeneratorActivateWidgetInstance)
	{
		GeneratorActivateWidgetInstance->FSetImageRotation(fuelAmount);
	}

	
	if (BrokeGenerator())
	{
		return; 
	}

	if (fuelAmount <= 20.0f)
	{
		if (MissionSubsystem)
		{
			if (!bIsFuelMissionActive)
			{
				MissionSubsystem->RegisterMissionTarget(EMissionType::Fueling);
				bIsFuelMissionActive = true;
			}
			MissionSubsystem->UpdateMissionProgress(EMissionType::Fueling, FMath::RoundToInt(fuelAmount));
		}
	}

	if (fuelAmount <= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReduceFuel);
		bIsWorking = false;
		SetLightColor(0);
		if (AudioComponent && (AudioComponent->IsPlaying()))
		{
			PlayNaturalSound(bIsWorking, 0);
		}
		if (WorldSubsystem) WorldSubsystem->ToggleAllOtelLights(bIsWorking);
	}

}

void AEYS_Generator::AddFuel()
{
	if (!CurrentFuelTank) return;

	CurrentFuelTank->FuelValue = FMath::Clamp(CurrentFuelTank->FuelValue - 2.0f, 0.0f, 100.0f);
	fuelAmount = FMath::Clamp(fuelAmount + 2.0f, 0.0f, 100.0f);

	if (GeneratorActivateWidgetInstance)
	{
		GeneratorActivateWidgetInstance->FSetImageRotation(fuelAmount);
	}
	if (AudioComponent && !(AudioComponent->IsPlaying()))
	{
		PlayNaturalSound(true,1);
	}
	if (CurrentFuelTank->FuelValue <= 0.5f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AddFuel);
		CurrentFuelTank->Destroy();
		CurrentFuelTank = nullptr;
		if (AudioComponent && (AudioComponent->IsPlaying())&&!bIsWorking)
		{
			PlayNaturalSound(false, 1);
		}
	}

	if (bIsFuelMissionActive && MissionSubsystem)
	{
		if (fuelAmount >= 50.0f)
		{
			MissionSubsystem->UpdateMissionProgress(EMissionType::Fueling, 50);
			bIsFuelMissionActive = false;
		}
	}

	if (fuelAmount >= 99.5f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AddFuel);
	}
	
}



void AEYS_Generator::PlayActivateSound_Implementation()
{
}

void AEYS_Generator::PlayNaturalSound_Implementation(bool bIsWork, int32 audioindex)
{
}


void AEYS_Generator::SetLightColor(int32 ColorValue)
{
	if (!PointLight || !LightColor.IsValidIndex(ColorValue)) return;


	PointLight->SetLightColor(LightColor[ColorValue]);
	
}


