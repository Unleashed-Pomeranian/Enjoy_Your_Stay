// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Computer Widgets/EYS_ComputerLoading_UI.h"
#include "EYS/UI/Computer Widgets/EYS_Computer_UI.h"

void UEYS_ComputerLoading_UI::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&UEYS_ComputerLoading_UI::loadingto60,0.2f,true);
	if (WidgetAnimation)
		PlayAnimation(WidgetAnimation, 0, 1);
}

void UEYS_ComputerLoading_UI::loadingto60()
{
	if (ProgressBar_Loading)
	{
		if (LoadingPercent <= 0.6)
		{
			LoadingPercent += 0.03f;
			ProgressBar_Loading->SetPercent(LoadingPercent);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UEYS_ComputerLoading_UI::SetSecondTimer, 2.0f, false);
		}
	}
}

void UEYS_ComputerLoading_UI::SetSecondTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UEYS_ComputerLoading_UI::loadingto100, 0.2f, true);
}

void UEYS_ComputerLoading_UI::loadingto100()
{
	if (ProgressBar_Loading)
	{
		if (LoadingPercent <= 0.99)
		{
			LoadingPercent += 0.03f;
			ProgressBar_Loading->SetPercent(LoadingPercent);
		}

		else
		{
			GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
			if (ComputerWidgetClass)
			{
				ComputerWidgetInstance = CreateWidget<UEYS_Computer_UI>(GetOwningPlayer(), ComputerWidgetClass);
				if (ComputerWidgetInstance)
				{
					ComputerWidgetInstance->AddToViewport();
					RemoveFromParent();
				}
			}
		}
	}
	
}


