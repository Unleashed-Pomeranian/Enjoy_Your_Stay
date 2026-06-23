// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_Tray.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBag.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GamePlayStatics.h"

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
		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::TakeFoodBag, ETutorialStep::GiveTrayToGuest);
		}
	
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

int32 AEYS_Tray::CheckItemTypes(TArray<EFoodType> GuestOrders)
{
	
	int32 CorrectCount = 0;

  
    TArray<EFoodType> TrayItems;
    TrayItems.Add(Slot1FoodType); 
    TrayItems.Add(Slot2FoodType); 


    for (EFoodType Order : GuestOrders)
    {
       
        if (TrayItems.Contains(Order))
        {
            CorrectCount++;
            TrayItems.RemoveSingle(Order);
        }
    }

    return CorrectCount;
	return int32();
}

void AEYS_Tray::CleanSlots()
{
	
	if (Slot1 && Slot1->GetChildActor())
	{
		Slot1->GetChildActor()->Destroy(); 
		Slot1->SetChildActorClass(nullptr); 
	}

	if (Slot2 && Slot2->GetChildActor())
	{
		Slot2->GetChildActor()->Destroy();
		Slot2->SetChildActorClass(nullptr);
	}


	Slot1FoodType = EFoodType::None;
	Slot2FoodType = EFoodType::None;
	Super::DetachActor();
	
}
void AEYS_Tray::RemoveTray()
{
	DetachFromPlayer();
}
void AEYS_Tray::AttachTray()
{
	AEYS_MyCharacter* myPlayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!myPlayer) return;
	AttachActor(myPlayer);
}
void AEYS_Tray::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Super::eInteract_Implementation(myPlayer);


	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::TakeTray, ETutorialStep::TakeFoodBag);
	}



}


void AEYS_Tray::DetachActor()
{
	
	Super::DetachActor();
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
