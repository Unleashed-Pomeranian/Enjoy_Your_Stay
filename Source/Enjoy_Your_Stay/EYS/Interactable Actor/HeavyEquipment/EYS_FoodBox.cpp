// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBox.h"
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GamePlayStatics.h"

void AEYS_FoodBox::RemoveFood()
{
	FoodAmount--;
	if (FoodAmount == 0)
	{
		AEYS_MyCharacter* Player = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if(Player&&Player->HeldEquipment)
		Player->HeldEquipment = nullptr;
		Destroy();
		
	}
}
