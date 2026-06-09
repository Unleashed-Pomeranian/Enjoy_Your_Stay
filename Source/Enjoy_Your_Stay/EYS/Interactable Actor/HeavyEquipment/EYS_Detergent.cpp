// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_Detergent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"


float AEYS_Detergent::ConsumeDetergent(float AmountNeeded)
{
	float RequiredDetergent = AmountNeeded / 2.0f;
	float ActualAmountToReturn = 0.0f;

	if (DetergentValue >= RequiredDetergent)
	{
		DetergentValue -= RequiredDetergent;
		ActualAmountToReturn = AmountNeeded;
	}
	
	else
	{
		ActualAmountToReturn = DetergentValue * 2.0f;
		DetergentValue = 0.0f;
	}


	if (DetergentValue <= 0.0f)
	{
		DetachFromPlayer();
	}


	return ActualAmountToReturn;
}
void AEYS_Detergent::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	Super::InteractUI_Implementation(myPlayer, bIsFocused);
	if (AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController()))
	{
		FString InteractionText = "[E] Take(%" + FString::FromInt(DetergentValue) + ")";
		PC->SetInteractionWidget(InteractionText);
	}

}

void AEYS_Detergent::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Super::eInteract_Implementation(myPlayer);
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::TakeDetergent, ETutorialStep::FillDetergent);
	}

}
