// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/EYS_Day_UI.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GamePlayStatics.h"

void UEYS_Day_UI::NativeConstruct()
{
    Super::NativeConstruct();

    Start_Button->OnPressed.AddDynamic(this, &UEYS_Day_UI::StarNewDay);
}

void UEYS_Day_UI::SetDayText(int32 DayValue)
{

    FString DayString = "Day" + FString::FromInt(DayValue);
    Day_Text->SetText(FText::FromString(DayString));
}

void UEYS_Day_UI::StarNewDay()
{
    if (myPC)
    {
        UGameplayStatics::SetGamePaused(GetWorld(), false);
        myPC->bShowMouseCursor = false;
        myPC->SetInputMode(FInputModeGameOnly());
        RemoveFromParent();
    }
}
