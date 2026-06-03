// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MySunMoonDaySequenceActor.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

void AEYS_MySunMoonDaySequenceActor::BeginPlay()
{

     PC =Cast<AEYS_MyCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	 TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	 Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();

	 SetTimeOfDay(10.0f);
	 SetTimePerCycle(1.0f);
	GetWorld()->GetTimerManager().SetTimer(DayTimerHandle, this, &AEYS_MySunMoonDaySequenceActor::FDayTimer, 10.0f, true);
	Play();
	if (TS)
	{
		TS->DayManager = this;
		if (TS->bIsTutorialFinished)
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

	if (!Director) return;
	Director->Hour = GetTimeOfDay();
	Director->CheckOutPlayer(DayNum,GetTimeOfDay());
	

}

void AEYS_MySunMoonDaySequenceActor::SetDayHour(float TimeValue)
{
	SetTimeOfDay(TimeValue);
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

void AEYS_MySunMoonDaySequenceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(GetTimeOfDay()));
	
}



