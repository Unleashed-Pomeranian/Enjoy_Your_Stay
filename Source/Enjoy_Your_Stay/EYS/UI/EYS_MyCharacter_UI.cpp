// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/EYS_MyCharacter_UI.h"

void UEYS_MyCharacter_UI::NativeConstruct()
{
    Super::NativeConstruct();

    Overlay->SetVisibility(ESlateVisibility::Hidden);
    Interaction_Text->SetVisibility(ESlateVisibility::Hidden);

}


