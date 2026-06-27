// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MySunMoonDaySequenceActor.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Game Managers/EYS_HorrorSubsystem.h"

void AEYS_MySunMoonDaySequenceActor::BeginPlay()
{

     PC =Cast<AEYS_MyCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	 TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	 Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
	 
	 SetTimeOfDay(10.0f);
	 SetTimePerCycle(10.0f);
	GetWorld()->GetTimerManager().SetTimer(DayTimerHandle, this, &AEYS_MySunMoonDaySequenceActor::FDayTimer, 10.0f, true);
	if (TS)
	{
		TS->DayManager = this;
		if (TS->bIsTutorialFinished|| TS->CurrentPhase==ETutorialPhase::ThirdPhase)
		{
			Play();
		}

	}
}

void AEYS_MySunMoonDaySequenceActor::FDayTimer()
{
	if (GetTimeOfDay() >= 22.0f)
	{
		Pause();
	}
if (PC) PC->SetHourWidget(GetTimeOfDay());

CheckTimeForTutorial();
if (TS)
	{
		if (TS->bIsTutorialFinished || TS->CurrentPhase == ETutorialPhase::ThirdPhase)
		{
			CheckTimeForHorror();
		}

	}


	if (!Director) return;
	Director->Hour = GetTimeOfDay();
	Director->CheckOutPlayer(DayNum,GetTimeOfDay());
	

}

void AEYS_MySunMoonDaySequenceActor::SetDayHour(float TimeValue)
{
	SetTimeOfDay(TimeValue);
	if (!Director) return;
	Director->Hour = GetTimeOfDay();
	Director->CheckOutPlayer(DayNum, GetTimeOfDay());
}

void AEYS_MySunMoonDaySequenceActor::StartNewDay()
{
	DayNum++;
	SetTimeOfDay(10.0f);
	FDayTimer();
	if (TS)
	{
		if (TS->bIsTutorialFinished || TS->CurrentPhase == ETutorialPhase::ThirdPhase)
		{
			Play();
		}

	}
}

void AEYS_MySunMoonDaySequenceActor::CheckTimeForTutorial()
{
	if (DayNum<=5&&DayNum >= 3 && GetTimeOfDay() > 15.00)
	{
		if (TS)
		{
			TS->UpdateTutorialState(ETutorialStep::WaitForUpdate, ETutorialStep::GoToComputer);
		}
	}
}

void AEYS_MySunMoonDaySequenceActor::CheckTimeForHorror()
{
	if (DayNum >= 6)
	{
		UWorld* World = GetWorld();
		if (!World) return;

		UEYS_HorrorSubsystem* HorrorSubsystem = World->GetSubsystem<UEYS_HorrorSubsystem>();
		if (!HorrorSubsystem) return;

		HorrorSubsystem->ActivateHorrorSystem(true);
	}
}





