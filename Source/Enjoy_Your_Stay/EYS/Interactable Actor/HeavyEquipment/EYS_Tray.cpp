// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_Tray.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBag.h"

AEYS_Tray::AEYS_Tray()
{


	Slot1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Slot1"));
	Slot1->SetupAttachment(RootComponent);

	Slot2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Slot2"));
	Slot2->SetupAttachment(RootComponent);

	Slot1FoodType = EFoodType::None;
	Slot2FoodType = EFoodType::None;
}

void AEYS_Tray::SetItemToSlot(int32 SlotIndex, TSubclassOf<class AActor> ItemClass, EFoodType NewFoodType)
{
	UChildActorComponent* TargetSlot = (SlotIndex == 0) ? Slot1 : Slot2;
	EFoodType& TargetFoodType = (SlotIndex == 0) ? Slot1FoodType : Slot2FoodType;

	if (TargetSlot)
	{
		TargetSlot->SetChildActorClass(ItemClass);
	
		TargetFoodType = NewFoodType;
	}
	if (AActor* NewChild = TargetSlot->GetChildActor())
	{
		NewChild->SetActorTickEnabled(false);
	    NewChild->SetActorEnableCollision(false);

	}
}
	


bool AEYS_Tray::IsSlotEmpty(int32 SlotIndex) const
{
	UChildActorComponent* TargetSlot = (SlotIndex == 0) ? Slot1 : Slot2;
	return TargetSlot->GetChildActorClass() == nullptr;
}

EFoodType AEYS_Tray::GetFoodTypeInSlot(int32 SlotIndex) const
{
	return (SlotIndex == 0) ? Slot1FoodType : Slot2FoodType;
}

EItemType AEYS_Tray::GetItemTypeInSlot(int32 SlotIndex) const
{
	UChildActorComponent* TargetSlot = (SlotIndex == 0) ? Slot1 : Slot2;
	if (AEYS_FoodBag* Bag = Cast<AEYS_FoodBag>(TargetSlot->GetChildActor()))
	{
		return Bag->ItemType; 
	}
	return EItemType::None;
}

void AEYS_Tray::BeginPlay()
{
	Super::BeginPlay();
}

void AEYS_Tray::DettachActor()
{
	
	Super::DettachActor();
    UChildActorComponent* Slots[] = { Slot1, Slot2 };

    for (int i = 0; i < 2; i++)
    {
		if (Slots[i] && Slots[i]->GetChildActor())
		{
			AActor* ItemToFree = Slots[i]->GetChildActor();


			FActorSpawnParameters Params;
			Params.Owner = this;
			AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemToFree->GetClass(), ItemToFree->GetActorTransform(), Params);
			
			if (!SpawnedItem) return;

			if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(SpawnedItem->GetRootComponent()))
			{
				
				RootPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				RootPrim->SetSimulatePhysics(true);
			
			}

			Slots[i]->SetChildActorClass(nullptr);
		
			if (i == 0) Slot1FoodType = EFoodType::None;
			else Slot2FoodType = EFoodType::None;
		}
	}
	
}