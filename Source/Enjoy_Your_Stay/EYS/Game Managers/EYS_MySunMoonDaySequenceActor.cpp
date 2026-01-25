// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MySunMoonDaySequenceActor.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS_WorldSubsystem.h"

void AEYS_MySunMoonDaySequenceActor::BeginPlay()
{

     PC =Cast<AEYS_MyCharacterController>(UGameplayStatics::GetPlayerController(this, 0));

	SetTimeOfDay(10.0f);
	SetTimePerCycle(1.0f);
	Play();
	
	UKismetSystemLibrary::K2_SetTimer(this, "FSetTimer", 2.0f, true);
	SetTimePerCycle(0.016f);
}

void AEYS_MySunMoonDaySequenceActor::FSetTimer()
{
	if (GetTimeOfDay() >= 22.0f)
	{
		Pause();
	}
if (PC) PC->SetHourWidget(GetTimeOfDay());

	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
	if (!Director) return;

	Director->CheckOutPlayer(DayNum,GetTimeOfDay());
}

void AEYS_MySunMoonDaySequenceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(GetTimeOfDay()));
	
}



