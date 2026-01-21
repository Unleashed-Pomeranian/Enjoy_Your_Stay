// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_CoalBox.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_CoalSack.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AEYS_CoalBox::AEYS_CoalBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh_Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Box"));
	StaticMesh_Box->SetupAttachment(DefaultSceneRoot);
	StaticMesh_Coal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Coal"));
	StaticMesh_Coal->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_CoalBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_CoalBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AEYS_CoalBox::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (CoalAmount>0) {
		
		PC->SetInteractionWidget("[M1] Take");
	}
	else
	{
		PC->SetInteractionWidget("No Coal");
	}
}

void  AEYS_CoalBox::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
 
	 if (myPlayer->HeldEquipment && myPlayer->HeldEquipment->IsA(AEYS_CoalSack::StaticClass()))
	 {
		 AEYS_CoalSack* FoodBox = Cast<AEYS_CoalSack>(myPlayer->HeldEquipment);
		 if (CoalAmount < 100 && FoodBox->CoalValue>0)
		 {
			 FoodBox->ReduceFuelValue(20);
			 FillingCoal(+20);
			 
		 }
	 }
}
void  AEYS_CoalBox::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{

	if (Value == 5&& !(myPlayer->bIsCoalMode))
	{
		if (CoalAmount >= 20)
		{
			myPlayer->bIsCoalMode = true;
			if (!bisTakeCoal)
			{
				UKismetSystemLibrary::K2_SetTimer(this, "DrainingCoal", 0.5f, false);
				bisTakeCoal = true;
			}
		}
	}
}
void  AEYS_CoalBox::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void AEYS_CoalBox::FillingCoal(int32 AddValue)
{
	CoalAmount = FMath::Clamp(CoalAmount + AddValue, 0, 100);
	SetCoalMeshCoal();
}
void AEYS_CoalBox::DrainingCoal()
{
	CoalAmount = FMath::Clamp(CoalAmount - 20, 0, 100);
	SetCoalMeshCoal();
	bisTakeCoal = false;
}

void AEYS_CoalBox::SetCoalMeshCoal()
{
	
	int32 MeshValue = CoalAmount / 20;
	StaticMesh_Coal->SetStaticMesh(CoalMeshes[MeshValue]);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(MeshValue));
}
