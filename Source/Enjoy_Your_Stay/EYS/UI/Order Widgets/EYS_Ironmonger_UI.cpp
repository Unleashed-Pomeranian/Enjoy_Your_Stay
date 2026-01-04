// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_Ironmonger_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_OrderSpawner.h"



void UEYS_Ironmonger_UI::NativeConstruct()
{
	Button_Hammer-> OnClicked.AddDynamic(this, &UEYS_Ironmonger_UI::OnSlot0);
	Button_Shovel->OnClicked.AddDynamic(this, &UEYS_Ironmonger_UI::OnSlot1);
	Button_FuelTank->OnClicked.AddDynamic(this, &UEYS_Ironmonger_UI::OnSlot2);
}

void UEYS_Ironmonger_UI::OnBtnSlotOrder(int32 SlotIndex)
{
	AEYS_OrderSpawner* OrderSpawner = Cast<AEYS_OrderSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_OrderSpawner::StaticClass()));
	if (OrderSpawner&& SpawnActor[SlotIndex])
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "UIOk");
		OrderSpawner->SpawnOrder(SpawnActor[SlotIndex]);
	}
}

