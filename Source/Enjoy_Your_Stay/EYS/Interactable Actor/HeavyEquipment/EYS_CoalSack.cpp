// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_CoalSack.h"
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GamePlayStatics.h"


void AEYS_CoalSack::ReduceFuelValue(int32 ReduceValue)
{
	CoalValue -= ReduceValue;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(CoalValue));
	if (CoalValue <= 0)
	{
		AEYS_MyCharacter* myPlayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (myPlayer && myPlayer->HeldEquipment)
			myPlayer->HeldEquipment = nullptr;
		myPlayer->bIsHandsFull = false;
		Destroy();
	}
}
void AEYS_CoalSack::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	Super::InteractUI_Implementation(myPlayer);
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());

	FString InteractionText = "[E] Take(%" +  FString::FromInt(CoalValue) + ")";
	PC->SetInteractionWidget(InteractionText);


}
