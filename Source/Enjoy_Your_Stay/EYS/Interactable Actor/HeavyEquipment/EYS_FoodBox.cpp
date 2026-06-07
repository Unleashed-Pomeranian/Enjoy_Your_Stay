// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBox.h"
#include "EYS/EYS_MyCharacter.h"

#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

void AEYS_FoodBox::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	Super::InteractUI_Implementation(myPlayer, bIsFocused);
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	FString InteractionText = "[E] Take(" + FString::FromInt(FoodAmount) + "/6)";
    PC->SetInteractionWidget(InteractionText);



}
void AEYS_FoodBox::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Super::eInteract_Implementation(myPlayer);

	
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::TakeFoodBox, ETutorialStep::GoToFridge);
	}
	


}

void AEYS_FoodBox::RemoveFood()
{
	FoodAmount--;
	if (FoodAmount == 0)
	{
		DetachFromPlayer();
		
	}
}
