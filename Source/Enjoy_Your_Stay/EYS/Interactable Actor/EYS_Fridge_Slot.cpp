// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Fridge_Slot.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBox.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBag.h"
// Sets default values
AEYS_Fridge_Slot::AEYS_Fridge_Slot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMesh"));
	InstancedStaticMesh->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void AEYS_Fridge_Slot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEYS_Fridge_Slot::FAddSlot()
{
	
	if (InstanceIndex < 5)
	{
		InstancedStaticMesh->AddInstance(InstanceTransform[InstanceIndex + 1], false);
		InstanceIndex++;
	}
}

void AEYS_Fridge_Slot::FDeleteSlot()
{
	if (InstanceIndex >= 0)
	{

		InstancedStaticMesh->RemoveInstance(InstanceIndex);
		InstanceIndex--;

		GetWorld()->SpawnActor<AActor>(FoodBagActor, GetActorTransform());
		
	}
}

// Called every frame
void AEYS_Fridge_Slot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void   AEYS_Fridge_Slot::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
	

}




void  AEYS_Fridge_Slot::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (myPlayer->HeldEquipment)
	{
		
			if (myPlayer->HeldEquipment->IsA(AEYS_FoodBox::StaticClass()))
			{
				AEYS_FoodBox* FoodBox = Cast<AEYS_FoodBox>(myPlayer->HeldEquipment);

				if (FoodBox->FoodType == SlotFoodType)
				{
					PC->SetInteractionWidget("[E] Place");
				}
				else
					PC->SetInteractionWidget("Wrong Food Type.");
			}
		    else if(myPlayer->HeldEquipment->IsA(AEYS_FoodBag::StaticClass()))
			{ 
				AEYS_FoodBag* FoodBag = Cast<AEYS_FoodBag>(myPlayer->HeldEquipment);
				
				if (FoodBag->FoodType == SlotFoodType)
				{
					PC->SetInteractionWidget("[E] Place");
				}
				else
				    PC->SetInteractionWidget("Wrong Food Type.");
			}
			else
				PC->SetInteractionWidget("Your hands are full.");
			
		
	}
	else
		PC->SetInteractionWidget("[E] Take");

}

void   AEYS_Fridge_Slot::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (myPlayer->HeldEquipment)
	{
		if (myPlayer->HeldEquipment->IsA(AEYS_FoodBox::StaticClass()))
		{
			AEYS_FoodBox* FoodBox = Cast<AEYS_FoodBox>(myPlayer->HeldEquipment);
			if (SlotFoodType == FoodBox->FoodType)
			{
				if (InstanceIndex < 5)
				{
					FoodBox->RemoveFood();
				}
				FAddSlot();
			}
		}
		
		if (myPlayer->HeldEquipment&&myPlayer->HeldEquipment->IsA(AEYS_FoodBag::StaticClass()))
		{
			AEYS_FoodBag* FoodBag = Cast<AEYS_FoodBag>(myPlayer->HeldEquipment);
			if (SlotFoodType == FoodBag->FoodType)
			{
				if (InstanceIndex < 5)
				{
					FoodBag->RemoveFoodBag();
				}
				FAddSlot();
			}
		}
		
	}
	else
	{
		FDeleteSlot();
	}
}
