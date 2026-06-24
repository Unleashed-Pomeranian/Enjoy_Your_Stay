// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_StorageRack.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"

// Sets default values
AEYS_StorageRack::AEYS_StorageRack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	RackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RackMesh"));
	RackMesh->SetupAttachment(RootComponent);

	

	for (int32 i = 0; i < 12; i++)
	{
		FString ComponentName = FString::Printf(TEXT("Slot_%d"), i + 1);
		USceneComponent* NewSlot = CreateDefaultSubobject<USceneComponent>(*ComponentName);
		if (NewSlot)
		{
			NewSlot->SetupAttachment(RootComponent);
		
			NewSlot->SetRelativeLocation(FVector(0.f, 0.f, i * 25.f));
			StorageSlots.Add(NewSlot);
		}
	}
}


void AEYS_StorageRack::BeginPlay()
{
	Super::BeginPlay();
	
}
void AEYS_StorageRack::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	if (!myPlayer) return;
	{
		if (myPlayer->HeldEquipment)
		{
			AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
			if (PC) PC->SetInteractionWidget("[E] Place");
		}
		
	}
}
void AEYS_StorageRack::Interact(AEYS_MyCharacter* myPlayer)
{

}
void AEYS_StorageRack::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (!myPlayer || !myPlayer->HeldEquipment) return;

	
	if (AEYS_HeavyEquipmentBase* PlayerEquipment = Cast<AEYS_HeavyEquipmentBase>(myPlayer->HeldEquipment))
	{
		USceneComponent* FoundEmptySlot = nullptr;

		
		for (USceneComponent* Slot : StorageSlots)
		{
			
			if (Slot && Slot->GetAttachChildren().Num() == 0)
			{
				FoundEmptySlot = Slot;
				break;
			}
		}

	
		if (!FoundEmptySlot)
		{
			
			return;
		}


		PlayerEquipment->PlaceOnRack(myPlayer, FoundEmptySlot);

		
	}
}




