// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Computer Widgets/EYS_ComputerLoading_UI.h"
#include "EYS/UI/Computer Widgets/EYS_Computer_UI.h"
#include "Kismet/GameplayStatics.h"

void UEYS_ComputerLoading_UI::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&UEYS_ComputerLoading_UI::loadingto60,0.2f,true);
	if (WidgetAnimation)
		PlayAnimation(WidgetAnimation, 0, 1);
}

void UEYS_ComputerLoading_UI::NativeDestruct()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(MyTimerHandle);
	}

	Super::NativeDestruct();
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
	UWorld* World = GetWorld();
	if (!World) return;

	if (!ProgressBar_Loading)
	{
		World->GetTimerManager().ClearTimer(MyTimerHandle);
		return;
	}

	if (LoadingPercent <= 0.99f)
	{
		LoadingPercent += 0.03f;
		ProgressBar_Loading->SetPercent(LoadingPercent);
		return;
	}

	World->GetTimerManager().ClearTimer(MyTimerHandle);

	if (!ComputerWidgetClass)
	{

		return;
	}
	APlayerController* PC = GetOwningPlayer();

	if (!PC)
	{
		PC = UGameplayStatics::GetPlayerController(this, 0);
	}

	if (!PC)
	{
		return;
	}

	ComputerWidgetInstance = CreateWidget<UEYS_Computer_UI>(PC, ComputerWidgetClass);

	if (!ComputerWidgetInstance)
	{
		return;
	}

	ComputerWidgetInstance->AddToViewport();
	RemoveFromParent();
	
}


