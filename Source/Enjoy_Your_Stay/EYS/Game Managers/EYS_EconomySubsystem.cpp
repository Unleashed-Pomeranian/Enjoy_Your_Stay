// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_EconomySubsystem.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GameplayStatics.h"
void UEYS_EconomySubsystem::UpdateMoney(int32 amount)
{
	Money += amount;


	if (!MyPC)
	{
		if (UWorld* World = GetWorld())
		{
			MyPC = Cast<AEYS_MyCharacterController>(UGameplayStatics::GetPlayerController(World, 0));
		}
	}

	if (MyPC)
	{
		MyPC->SetMoneyWidget(amount);
	}

}

bool UEYS_EconomySubsystem::CheckMoney(int32 amount)
{
	if (Money >= amount)
	{
		return true;
	}
	return false;
}

int UEYS_EconomySubsystem::GetCurrentMoney()
{
	return Money;
}
