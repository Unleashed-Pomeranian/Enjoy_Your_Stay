// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_Supermarket_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/EYS_OrderSpawner.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBox.h"

void UEYS_Supermarket_UI::NativeConstruct()
{
	Button_Pirozhki->OnClicked.AddDynamic(this, &UEYS_Supermarket_UI::OnSlot0);
	Button_Vareniki->OnClicked.AddDynamic(this, &UEYS_Supermarket_UI::OnSlot1);
	Button_Kasha->OnClicked.AddDynamic(this, &UEYS_Supermarket_UI::OnSlot2);
	Button_Medovik->OnClicked.AddDynamic(this, &UEYS_Supermarket_UI::OnSlot3);

	SetFoodBoxText();

}

void UEYS_Supermarket_UI::SetFoodBoxText()
{
	FString PirozhkiText = "Pirozhki (" + FString(TEXT("\u20BD")) + FString::FromInt(PirozhkiPrice) + ")";
	Text_Pirozhki->SetText((FText::FromString(PirozhkiText)));
	FString VarenikiText = "Vareniki (" + FString(TEXT("\u20BD")) + FString::FromInt(VarenikiPrice) + ")";
	Text_Vareniki->SetText((FText::FromString(VarenikiText)));
	FString KashaText = "Kasha (" + FString(TEXT("\u20BD")) + FString::FromInt(KashaPrice) + ")";
	Text_Kasha->SetText((FText::FromString(KashaText)));
	FString MedovikText = "Medovik (" + FString(TEXT("\u20BD")) + FString::FromInt(MedovikPrice) + ")";
	Text_Medovik->SetText((FText::FromString(MedovikText)));
}




void UEYS_Supermarket_UI::OnBtnSlotOrder(int32 SlotIndex, int32 Price)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(GetOwningPlayer());
	if (PC)
	{
		if (PC->Money >= Price)
		{
			PC->SetMoneyWidget(-(Price));
			AEYS_OrderSpawner* OrderSpawner = Cast<AEYS_OrderSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_OrderSpawner::StaticClass()));
			if (OrderSpawner && FSpawnActor[SlotIndex])
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "UIOk");
				OrderSpawner->SetOrderClass(FSpawnActor[SlotIndex]);
			}
		}
		else
			return;
	}



}



