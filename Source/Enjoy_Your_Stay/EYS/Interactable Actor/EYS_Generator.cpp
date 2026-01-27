// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Generator.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/UI/EYS_GeneratorActivateWidget.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FuelTank.h"

// Sets default values
AEYS_Generator::AEYS_Generator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
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
}

// Called when the game starts or when spawned
void AEYS_Generator::BeginPlay()
{
	Super::BeginPlay();
	
	AEYS_MyCharacter* Myplayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	 PC = Cast<AEYS_MyCharacterController>(Myplayer->GetController());
	if (PC)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Hellooooo");
		GeneratorActivateWidgetInstance = CreateWidget<UEYS_GeneratorActivateWidget>(PC, GeneratorActivateWidgetClass);
		if (GeneratorActivateWidgetInstance)
		{
			WidgetMesh->SetWidget(GeneratorActivateWidgetInstance);
			GeneratorActivateWidgetInstance->FSetImageRotation(fuelAmount);
		}
	}
	
		PointLight->SetLightColor(LightColor[0]);

}

void AEYS_Generator::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	PC->SetInteractionWidget("[E] Open");
}
void AEYS_Generator::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}
//Start Engine
void AEYS_Generator::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (myPlayer->HeldEquipment && myPlayer->HeldEquipment->IsA(AEYS_FuelTank::StaticClass()))
	{
		CurrentFuelTank = Cast<AEYS_FuelTank>(myPlayer->HeldEquipment);
		CurrentFuelTank->AttachToGenerator(Fuelingpoint);
		UKismetSystemLibrary::K2_SetTimer(this, "AddFuel", 0.16f, true, false, 0, 0);
	}
	else
	{
		if ((CurrentFuelTank))
		{
			CurrentFuelTank->AttachActor(myPlayer);
			UKismetSystemLibrary::K2_ClearTimer(this, "AddFuel");
			CurrentFuelTank = nullptr;
		}
		else
		{
			if (!bIsWorking && fuelAmount > 10)
			{

				if (!(GeneratorActivateWidgetInstance->bIsWorking))
				{
					myPlayer->PoseNum = 0;
					myPlayer->SetRoot();
					PC->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 1.0f, FLinearColor::Black, false, true);
					PC->SetCharacterPositon(GetActorLocation(), 30, 5, FRotator(-45, -90, 0));
					PC->MobilizeCharacter(true, false, false);
				}

				myPlayer->PlayMontage(2);
				GeneratorActivateWidgetInstance->TimerFTimer();
				PlayActivateSound();
			}
		}
	}
	
}

void AEYS_Generator::StartStopTimer()
{
	PC->MobilizeCharacter(false, false, false);
	UKismetSystemLibrary::K2_SetTimer(this, "ReduceFuel", 5.0f, true, false, 0, 0);
}

//ReduceFuel
void AEYS_Generator::ReduceFuel()
{

	

	fuelAmount = FMath::Clamp(fuelAmount-1.0f, 0.0f, 100.0f); 
	GeneratorActivateWidgetInstance->FSetImageRotation(fuelAmount);


	if (fuelAmount <= 5.0f)
	{
		UKismetSystemLibrary::K2_ClearTimer(this, "ReduceFuel");
		bIsWorking = false;
		PointLight->SetLightColor(LightColor[0]);
		PlayNaturalSound(bIsWorking);
	}

}

void AEYS_Generator::AddFuel()
{
	CurrentFuelTank->FuelValue =  FMath::Clamp(CurrentFuelTank->FuelValue - 2.0f, 0.0f, 100.0f);
	fuelAmount = FMath::Clamp(fuelAmount +2.0f, 0.0f, 100.0f);
	GeneratorActivateWidgetInstance->FSetImageRotation(fuelAmount);
	if (CurrentFuelTank->FuelValue <= 0.5f)
	{
		UKismetSystemLibrary::K2_ClearTimer(this, "AddFuel");
		CurrentFuelTank->Destroy();
		CurrentFuelTank = nullptr;
	}

	if (fuelAmount >= 99.5)
	{
		UKismetSystemLibrary::K2_ClearTimer(this, "AddFuel");
	}
	
}

void AEYS_Generator::PlayActivateSound_Implementation()
{
}

void AEYS_Generator::PlayNaturalSound_Implementation(bool bIsWork)
{
}


void AEYS_Generator::testlight_Implementation()
{
}

void AEYS_Generator::SetLightColor(int32 ColorValue)
{
	switch (ColorValue)
	{
	case 0:
	{
		PointLight->SetLightColor(LightColor[0]);
		break;
	}
	case 1:
	{
		PointLight->SetLightColor(LightColor[1]);
		break;
	}
	case 3:
	{
		PointLight->SetLightColor(LightColor[2]);
		break;
	}
	default:
		break;
	}
}


