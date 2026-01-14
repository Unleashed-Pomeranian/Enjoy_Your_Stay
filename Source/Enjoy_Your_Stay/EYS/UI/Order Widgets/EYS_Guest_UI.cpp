// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_Guest_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Interactable Actor/EYS_Phone.h"

void  UEYS_Guest_UI::NativeConstruct()
{
	Button_TakeOrder->OnClicked.AddDynamic(this, &UEYS_Guest_UI::TakeOrder);
	Button_RejectOrder->OnClicked.AddDynamic(this, &UEYS_Guest_UI::RejectOrder);
	


	

}

void UEYS_Guest_UI::TakeOrder()
{
	AEYS_Phone* Phone = Cast<AEYS_Phone>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Phone::StaticClass()));
	if (Phone)
	{
		Phone->CloseUI();
	}
}

void UEYS_Guest_UI::RejectOrder()
{
	AEYS_Phone* Phone = Cast<AEYS_Phone>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Phone::StaticClass()));
	if (Phone)
	{
		Phone->CloseUI();
	}
}

void UEYS_Guest_UI::SetGuestText(FString foodType, int32 roomNum)
{
	FString Settedtext = "Could I have one " + foodType + " sent to room " + FString::FromInt(roomNum) + ", please?";
	Text_Customer->SetText(FText::FromString(Settedtext));

}

