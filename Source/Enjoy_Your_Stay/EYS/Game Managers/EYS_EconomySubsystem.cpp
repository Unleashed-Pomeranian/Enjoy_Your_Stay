// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_EconomySubsystem.h"

void UEYS_EconomySubsystem::AddMoney(int32 amount)
{
	Money += amount;
}

bool UEYS_EconomySubsystem::SpendMoney(int32 amount)
{
	if (Money >= amount)
	{
		Money -= amount;
			return true;
	}

	return false;
}

int UEYS_EconomySubsystem::CurrentMoney()
{
	return Money;
}
