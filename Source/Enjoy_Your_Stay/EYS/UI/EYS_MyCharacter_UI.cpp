// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/EYS_MyCharacter_UI.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"
#include "EYS/EYS_MyCharacterController.h"

void UEYS_MyCharacter_UI::NativeConstruct()
{
    Super::NativeConstruct();

    Overlay->SetVisibility(ESlateVisibility::Hidden);
    Interaction_Text->SetVisibility(ESlateVisibility::Hidden);


    if(PC)
	PC->OnStaminaChanged.AddDynamic(this, &UEYS_MyCharacter_UI::SetStaminaBar);
    

}

void UEYS_MyCharacter_UI::SetStaminaBar(float StaminaValue,bool bIsRecovery)
{
    float Percent = StaminaValue / 100.0f;
    Stamina_ProgressBar->SetPercent(Percent);

    // Overlay görünürlüğü için düzeltme:
    if (StaminaValue < 100.0f)
    {
        Overlay->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        Overlay->SetVisibility(ESlateVisibility::Hidden);
    }

    if (!bIsRecovery)
    {
        if (BarColors.IsValidIndex(1))
        { 
            Stamina_ProgressBar->SetFillColorAndOpacity(BarColors[1]); 
        }
      
    }
    else
    {
        if (BarColors.IsValidIndex(0))
        {
            Stamina_ProgressBar->SetFillColorAndOpacity(BarColors[0]);
        }

    }
}

void UEYS_MyCharacter_UI::SetMoneyText(int32 AddValue)
{
    CurrentMoney += AddValue;
    FString CM = FString(TEXT("₽")) + FString::FromInt(CurrentMoney);

   Money_Text->SetText(FText::FromString(CM));
  
}

void UEYS_MyCharacter_UI::SetChangedMoney_Implementation(const int32 ChangedValue)
{
  
}

void UEYS_MyCharacter_UI::SetMissionText_Implementation(const FText& MissionText)
{
   
}

void UEYS_MyCharacter_UI::SetSubtitle_Implementation(const FText& Subtitle, float Duration)
{
    
}


