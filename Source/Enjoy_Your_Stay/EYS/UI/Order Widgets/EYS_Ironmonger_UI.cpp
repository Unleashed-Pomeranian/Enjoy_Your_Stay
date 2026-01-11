// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_Ironmonger_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_OrderSpawner.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS_Supermarket_UI.h"
#include "EYS/Interactable Actor/EYS_InteractableActor_WP.h"


void UEYS_Ironmonger_UI::NativeConstruct()
{
	Button_Hammer-> OnClicked.AddDynamic(this, &UEYS_Ironmonger_UI::OnSlot0);
	Button_Shovel->OnClicked.AddDynamic(this, &UEYS_Ironmonger_UI::OnSlot1);
	Button_FuelTank->OnClicked.AddDynamic(this, &UEYS_Ironmonger_UI::OnSlot2);


	SetEquipmentText();

}



void UEYS_Ironmonger_UI::OnBtnSlotOrder(int32 SlotIndex, int32 Price)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(GetOwningPlayer());
	if (PC)
	{
		if (PC->Money >= Price)
		{
			PC->SetMoneyWidget(-(Price));
			AEYS_OrderSpawner* OrderSpawner = Cast<AEYS_OrderSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_OrderSpawner::StaticClass()));
			if (OrderSpawner && SpawnActor[SlotIndex])
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "UIOk");
				OrderSpawner->SetOrderClass(SpawnActor[SlotIndex]);
			}
		}
		else 
			return;
	}

	
	
}



void UEYS_Ironmonger_UI::SetEquipmentText()
{
	FString HammerText = "Hammer (" + FString(TEXT("\u20BD")) + FString::FromInt(HammerPrice) + ")";
	Text_Hammer->SetText((FText::FromString(HammerText)));
	FString ShovelText = "Shovel (" + FString(TEXT("\u20BD")) +  FString::FromInt(ShovelPrice) + ")";
	Text_Shovel->SetText((FText::FromString(ShovelText)));
	FString FuelTankText = "FuelTank (" + FString(TEXT("\u20BD")) + FString::FromInt(FuelTankPrice) + ")";
	Text_FuelTank->SetText((FText::FromString(FuelTankText)));
}