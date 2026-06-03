// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_Guest_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Interactable Actor/EYS_Phone.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
void  UEYS_Guest_UI::NativeConstruct()
{
	Super::NativeConstruct();
	Button_TakeOrder->OnClicked.AddDynamic(this, &UEYS_Guest_UI::TakeOrder);
	Button_RejectOrder->OnClicked.AddDynamic(this, &UEYS_Guest_UI::RejectOrder);
	

	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		if (TS->CurrentStep == ETutorialStep::TakeGuestOrder)
		{
			Button_RejectOrder->SetIsEnabled(false);
		}
	}
	

}

void UEYS_Guest_UI::TakeOrder()
{
	
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::WaitGuestOrder, ETutorialStep::TakeTray);
	}
	OrderDialogEnd.Broadcast();
	RemoveFromParent();
	
}

void UEYS_Guest_UI::RejectOrder()
{

}

void UEYS_Guest_UI::SetGuestText(FString foodType, FString drinktype)
{
	FString SettedText = "Could I have one <key>" + foodType + "</> and one <key>" + drinktype + "</>, please?";
	Text_Customer->SetText(FText::FromString(SettedText));

}

