// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Fridge_Slot.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "HeavyEquipment/EYS_FoodBox.h"
#include "HeavyEquipment/EYS_FoodBag.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "HeavyEquipment/EYS_Tray.h"
// Sets default values
AEYS_Fridge_Slot::AEYS_Fridge_Slot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
		if (InstanceIndex >= 5)
		{
			if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
			{
				TS->RegisterFilledSlot(SlotFoodType);
			}
		}
	}
}

void AEYS_Fridge_Slot::FDeleteSlot(bool bSpawnActor)
{
	if (InstanceIndex >= 0)
	{

		InstancedStaticMesh->RemoveInstance(InstanceIndex);
		InstanceIndex--;

		if (CurrentFoodBag&&bSpawnActor)
		{
			
			if(AEYS_FoodBag* SpawnedFoodBag= GetWorld()->SpawnActor<AEYS_FoodBag>(CurrentFoodBag, GetActorTransform()))
			{
				SpawnedFoodBag->AttachFoodBag();
			}
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Cantake");
		}
		
		
	}
	 if (InstanceIndex <= -1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "bCanIsqdsdnteract");
		SlotFoodType = EFoodType::None;
		InstancedStaticMesh->SetStaticMesh(nullptr);
		CurrentFoodBag = nullptr;
	}
}



void   AEYS_Fridge_Slot::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
	

}




void  AEYS_Fridge_Slot::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (!PC) return;

	if (myPlayer->HeldEquipment)
	{
		
		EFoodType EquipmentType = EFoodType::None;
		EItemType EquipmentItemType = EItemType::None;

		if (AEYS_FoodBox* FoodBox = Cast<AEYS_FoodBox>(myPlayer->HeldEquipment))
		{
			EquipmentType = FoodBox->FoodType;
			EquipmentItemType = FoodBox->ItemType;
		}
		else if (AEYS_FoodBag* FoodBag = Cast<AEYS_FoodBag>(myPlayer->HeldEquipment))
		{
			EquipmentType = FoodBag->FoodType;
			EquipmentItemType = FoodBag->ItemType;
		}

		if (EquipmentItemType != EItemType::None && EquipmentItemType != SlotItemType)
		{
		
			FString CategoryName = (SlotItemType == EItemType::Drink) ? "Drinks" : "Food";
			PC->SetInteractionWidget("Only " + CategoryName + " allowed here.");
			return;
		}

		if (EquipmentType != EFoodType::None)
		{
			if (SlotFoodType == EFoodType::None || EquipmentType == SlotFoodType)
			{
				if (InstanceIndex < 5)
				{
					PC->SetInteractionWidget("[E] Place");
				}
				else
				{
					PC->SetInteractionWidget("Slot is Full.");
				}
			}
			else
			{
				PC->SetInteractionWidget("Wrong Item Type.");
			}
		}
	
	}
	else
	{
		
		if (InstanceIndex >= 0)
		{
			PC->SetInteractionWidget("[E] Take");
		}
		else
		{
			PC->SetInteractionWidget("");
		}
	}

}

void   AEYS_Fridge_Slot::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (myPlayer->HeldEquipment != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "HeldEquipment");
		AEYS_Tray* Tray = Cast<AEYS_Tray>(myPlayer->HeldEquipment);

		if (Tray)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Tray");
			if (InstanceIndex >= 0 && SlotFoodType != EFoodType::None)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "SetItemSlot");
				if (Tray->IsSlotEmpty(0))
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "IsSlotEmpty(0)");
					Tray->SetItemToSlot(0, CurrentFoodBag, SlotFoodType);
					FDeleteSlot(false);
					return; 
				}
				else if (Tray->IsSlotEmpty(1))
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "IsSlotEmpty(1)");
					Tray->SetItemToSlot(1, CurrentFoodBag, SlotFoodType);
					FDeleteSlot(false);
					return; 
				}
			}

			
			for (int32 i = 0; i < 2; i++)
			{
				if (!Tray->IsSlotEmpty(i))
				{
					
					EFoodType TrayFoodType = Tray->GetFoodTypeInSlot(i);
					EItemType TrayItemType = Tray->GetItemTypeInSlot(i);

					
					if (TrayItemType == SlotItemType)
					{
						
						if ((SlotFoodType == EFoodType::None || SlotFoodType == TrayFoodType) && InstanceIndex < 5)
						{
							// İlk kez koyuluyorsa slotu yapılandır
							if (SlotFoodType == EFoodType::None)
							{
								SlotFoodType = TrayFoodType;
								if (FFoodData* FoundData = FoodDataMap.Find(SlotFoodType))
								{
									CurrentFoodBag = FoundData->FoodBagClass;
									if (FoundData->FoodMesh)
										InstancedStaticMesh->SetStaticMesh(FoundData->FoodMesh);
								}
							}
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "AddItemToSlot");
							FAddSlot();
							Tray->SetItemToSlot(i, nullptr, EFoodType::None); 
							 
						}
					}
				}
			}
			return;
		}
		
		else
		{
			EFoodType EquipmentType = EFoodType::None;
			EItemType EquipmentItemType = EItemType::None;


			AEYS_FoodBox* FoodBox = Cast<AEYS_FoodBox>(myPlayer->HeldEquipment);
			AEYS_FoodBag* FoodBag = Cast<AEYS_FoodBag>(myPlayer->HeldEquipment);

			if (FoodBox)
			{
				EquipmentType = FoodBox->FoodType;
				EquipmentItemType = FoodBox->ItemType;
			}
			else if (FoodBag)
			{
				EquipmentType = FoodBag->FoodType;
				EquipmentItemType = FoodBag->ItemType;
			}
			


			if (SlotItemType != EquipmentItemType) return;


			if (EquipmentType != EFoodType::None)
			{

				if (SlotFoodType == EFoodType::None)
				{
					SlotFoodType = EquipmentType;
					if (FFoodData* FoundData = FoodDataMap.Find(SlotFoodType))
					{
						CurrentFoodBag = FoundData->FoodBagClass;
						if (FoundData->FoodMesh)
							InstancedStaticMesh->SetStaticMesh(FoundData->FoodMesh);
					}
				}


				if (SlotFoodType == EquipmentType)
				{
					if (FoodBox) FoodBox->RemoveFood();
					else if (FoodBag) FoodBag->RemoveFoodBag();

					FAddSlot();
				}
			}
			return;
		}
		
	}
	else
	{
		FDeleteSlot(true);
	}
}
