// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_Detergent.h"

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
