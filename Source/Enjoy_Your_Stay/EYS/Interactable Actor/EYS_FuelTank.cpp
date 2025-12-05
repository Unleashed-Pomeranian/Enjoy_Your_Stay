// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_FuelTank.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/EYS_MyCharacter.h"

// Sets default values
AEYS_FuelTank::AEYS_FuelTank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DirtMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_FuelTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_FuelTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AEYS_FuelTank::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Interact(myPlayer);
}

void  AEYS_FuelTank::Interact(AEYS_MyCharacter* myPlayer)
{
	
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	PC->EquipmentWheelInstance->EnableButtons(5,true,ESlateVisibility::Visible);
	Destroy();
	
}
