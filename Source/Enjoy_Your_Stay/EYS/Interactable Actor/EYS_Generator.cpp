// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Generator.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AEYS_Generator::AEYS_Generator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	FuelText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Fuel Amount Text"));
	FuelText->SetupAttachment(StaticMesh);


}

// Called when the game starts or when spawned
void AEYS_Generator::BeginPlay()
{
	Super::BeginPlay();
	
	UKismetSystemLibrary::K2_SetTimer(this, "TimerTest", 20.0f, true, false, 0, 0);
	if (FuelText)
	{

		
		FuelText->SetText(FText::FromString(FString::SanitizeFloat(fuelAmount)));
		
	}

}

// Called every frame
void AEYS_Generator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AEYS_Generator::testlight_Implementation()
{
}

void AEYS_Generator:: Interact(AEYS_MyCharacter* myPlayer)
{
	Interact(myPlayer);
	
}
void AEYS_Generator::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	if (Value == 4)
	{
		fuelAmount = FMath::Clamp(fuelAmount + 0.5f, 0.0f, 100.0f);
		FuelText->SetText(FText::FromString(FString::SanitizeFloat(fuelAmount)));
		
		myPlayer->FuelValue = FMath::Clamp(myPlayer->FuelValue - 0.5f, 0.0f, 100.0f);

		if (myPlayer->FuelValue <= 0)
		{
			DestroyFuelTank(myPlayer);
			
		
		}
		if (fuelAmount > 80)
		{
			testlight();
		}
	
	}
}

void AEYS_Generator::TimerTest()
{

	

	fuelAmount = FMath::Clamp(fuelAmount-5.0f, 0.0f, 100.0f);
	FuelText->SetText(FText::FromString(FString::SanitizeFloat(fuelAmount)));

	/******if (fuelAmount < 30)
	{
		
		AEYS_Notebook* Notebook = Cast<AEYS_Notebook>(
			UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Notebook::StaticClass()));
		if (Notebook)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "HandleMoveCompleted");
			Notebook->FuelingTotal += 1;
			Notebook->FuelingMission();
			
		}
	}
	***/
}

void AEYS_Generator::DestroyFuelTank(AEYS_MyCharacter* myPlayer)
{
	myPlayer->PoseNum = 0;
	myPlayer->LastPoseNum = 0;
	myPlayer->SetRoot();
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	PC->EquipmentWheelInstance->EnableButtons(5, false, ESlateVisibility::Hidden);
	
}
