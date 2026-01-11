// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_FuelTank.h"
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_MyCharacterController.h"
void AEYS_FuelTank::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	Super::InteractUI_Implementation(myPlayer);
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());

	FString InteractionText = "[E] Take(%" + FString::Printf(TEXT("%.0f"), FuelValue) + ")";
			PC->SetInteractionWidget(InteractionText);
	
	

}

void AEYS_FuelTank::AttachToGenerator(USceneComponent* Parent)
{
	AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	AEYS_MyCharacter* myPlayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (myPlayer && myPlayer->HeldEquipment)
	{
		myPlayer->HeldEquipment = nullptr;
		myPlayer->bIsHandsFull = false;
	}
}
