// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Generator.h"
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
	
	UKismetSystemLibrary::K2_SetTimer(this, "TimerTest", 4.0f, true, false, 0, 0);
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

void AEYS_Generator:: Interact(AEYS_MyCharacter* myPlayer)
{
	Interact(myPlayer);

}
void AEYS_Generator::aInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	
	fuelAmount = FMath::Clamp(fuelAmount+0.5f, 0.0f, 100.0f);
	FuelText->SetText(FText::FromString(FString::SanitizeFloat(fuelAmount)));

}

void AEYS_Generator::TimerTest()
{

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "timertest msg");

	fuelAmount = FMath::Clamp(fuelAmount-20, 0.0f, 100.0f);
	FuelText->SetText(FText::FromString(FString::SanitizeFloat(fuelAmount)));
}
