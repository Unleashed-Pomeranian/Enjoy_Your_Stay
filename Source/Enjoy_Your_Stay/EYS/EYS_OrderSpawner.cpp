// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/EYS_OrderSpawner.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/SceneComponent.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
// Sets default values
AEYS_OrderSpawner::AEYS_OrderSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Deafault Scene Root"));
	RootComponent = DefaultSceneRoot;
	for (int32 i = 0; i < TotalSlotCount; i++)
	{
		FString SlotName = FString::Printf(TEXT("RackSlot_%d"), i + 1);
		USceneComponent* NewSlot = CreateDefaultSubobject<USceneComponent>(*SlotName);

		if (NewSlot)
		{
			NewSlot->SetupAttachment(DefaultSceneRoot);

			
			NewSlot->SetRelativeLocation(FVector(i * 30.0f, 0.0f, 0.0f));

			RackSlots.Add(NewSlot);
		}
	}
}

// Called when the game starts or when spawned
void AEYS_OrderSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}


void AEYS_OrderSpawner::SetOrderClass(UClass* SpawnClass)
{
	if (SpawnClass)
	{
		Orders.Add(SpawnClass);
	}	
}

void AEYS_OrderSpawner::SpawnOrder()
{
	for (int32 i = 0; i < Orders.Num(); i++)
	{
		if (!Orders[i]) continue;


		int32 FoundEmptySlotIndex = -1;
		for (int32 j = 0; j < TotalSlotCount; j++)
		{
			if (RackSlots[j] && RackSlots[j]->GetAttachChildren().Num() == 0)
			{
				FoundEmptySlotIndex = j;
				break;
			}
		}

	
		if (FoundEmptySlotIndex != -1)
		{
		
			FTransform SpawnTransform = RackSlots[FoundEmptySlotIndex]->GetComponentTransform();
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Orders[i], SpawnTransform);

			if (SpawnedActor)
			{
				AEYS_HeavyEquipmentBase* HeavyItem = Cast<AEYS_HeavyEquipmentBase>(SpawnedActor);
				if (HeavyItem)
				{
			
					HeavyItem->PlaceOnOrderSpawener(RackSlots[FoundEmptySlotIndex]);

				
				}
			}
		}
		else
		{

			FTransform SpawnerTransform = GetActorTransform();
			AActor* SpawnedFloorActor = GetWorld()->SpawnActor<AActor>(Orders[i], SpawnerTransform);

			if (SpawnedFloorActor)
			{

			

			
			}
		}
	}


	Orders.Empty();
}



