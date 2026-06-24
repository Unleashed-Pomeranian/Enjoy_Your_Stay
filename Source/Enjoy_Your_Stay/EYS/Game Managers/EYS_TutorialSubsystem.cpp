// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/UI/EYS_MyCharacter_UI.h"
#include "EYS/Interactable Actor/TutorialSystem/EYS_BossSpeaker.h"
#include "EYS/Interactable Actor/TutorialSystem/EYS_TutorialHitBox.h"
#include "EYS/Game Managers/EYS_MySunMoonDaySequenceActor.h"
#include "EYS/Game Managers/EYS_HorrorSubsystem.h"


void UEYS_TutorialSubsystem::UpdateTutorialState(ETutorialStep RequiredStep, ETutorialStep NextStep)
{
	if (bIsTutorialFinished) return;

	if (CurrentStep != RequiredStep) return;
	SetTutorialStep(NextStep);
}

void UEYS_TutorialSubsystem::SetTutorialStep(ETutorialStep NewStep)
{
	if (!MissionDataTable)
	{
		return;
	}
	CurrentStep = NewStep;

	FString EnumFullName = UEnum::GetValueAsString(CurrentStep);
	FString RowNameString;
	EnumFullName.Split(TEXT("::"), nullptr, &RowNameString);
	FName RowName = FName(*RowNameString);

	
	static const FString ContextString(TEXT("Tutorial Mission Context"));
	FTutorialMissionData* FoundRow = MissionDataTable->FindRow<FTutorialMissionData>(RowName, ContextString);


	if (FoundRow)
	{
		if (MyCharacterUIIns)
		{
			if (!FoundRow->SubtitleText.IsEmpty())
			{
				MyCharacterUIIns->SetSubtitle(FoundRow->SubtitleText, FoundRow->SubtitleDuration);
			}
			
			MyCharacterUIIns->SetMissionText(FoundRow->MissionObjective);
		}
		if (TargetSpeaker)
		{
			TargetSpeaker->PlayBossMessage(FoundRow->BossAudio);
		}
		if (TargetHitBox)
		{
			
			if (!FoundRow->HitBoxLocation.IsNearlyZero())
			{
				TargetHitBox->SetHitBoxLocation(FoundRow->HitBoxLocation);
			}
			if (FoundRow->EquipmentRef)
			{
				TargetHitBox->SpawnEquipment(FoundRow->EquipmentRef);

			}
		}
		if (DayManager&&!(FoundRow->DayTime==0.0f))
		{
			DayManager->SetDayHour(FoundRow->DayTime);
		}


		if (CurrentStep == ETutorialStep::WaitTheGuest)
		{
			CurrentPhase = ETutorialPhase::FirstPhase;
			CheckTutorialPhase();
		}
	
		if(CurrentStep == ETutorialStep::GiveRightFood|| CurrentStep == ETutorialStep::GiveWrongFood)
		{
			CurrentStep = ETutorialStep::WaitForPipe;
			CurrentPhase = ETutorialPhase::SecondPhase;
			CheckTutorialPhase();
		}
		if (CurrentStep == ETutorialStep::WaitForUpdate)
		{
			CurrentPhase = ETutorialPhase::ThirdPhase;
			CheckTutorialPhase();

		}
		if (CurrentStep == ETutorialStep::EndTutorial)
		{
			FinishTutorial();

		}
	}
	
	else
	{
		return;
	}
}

void UEYS_TutorialSubsystem::CheckTutorialPhase()
{
	switch (CurrentPhase)
	{
	case ETutorialPhase::NoPhase:

		break;
	case ETutorialPhase::FirstPhase:
		OnFirstPhaseEnd.Broadcast();
		break;
	case ETutorialPhase::SecondPhase:
		OnSecondPhaseEnd.Broadcast();
		break;
		
	case ETutorialPhase::ThirdPhase:
		OnThirdPhaseEnd.Broadcast();
		break;
	default:
		break;
	}
} 

void UEYS_TutorialSubsystem::RegisterNewOrder(const TArray<TSubclassOf<AActor>>& OrderedItemClasses)
{

	if (CurrentStep != ETutorialStep::OrderSupplies) return;


	for (TSubclassOf<AActor> ProductClass : OrderedItemClasses)
	{
		if (!ProductClass) continue;


		RequiredOrderItems.Remove(ProductClass);
	}

	if (RequiredOrderItems.Num() <= 0)
	{
	
		UpdateTutorialState(ETutorialStep::OrderSupplies, ETutorialStep::GoToBed);

	}
}

void UEYS_TutorialSubsystem::RegisterFilledSlot(EFoodType FilledType)
{
	if(CurrentStep != ETutorialStep::PlaceFoodBox) return;

	FilledFridgeSlots.AddUnique(FilledType);
	if (FilledFridgeSlots.Num() >= 8)
	{
		UpdateTutorialState(ETutorialStep::PlaceFoodBox, ETutorialStep::FindSponge);
	}
}

void UEYS_TutorialSubsystem::RegisterCheckoutDirt()
{
	DirtValue++;
	if (DirtValue >= 4)
	{
		UpdateTutorialState(ETutorialStep::CleanCheckOutDirts, ETutorialStep::TakeDirtySheet);
	}
}
void UEYS_TutorialSubsystem::FinishTutorial()
{
	bIsTutorialFinished = true;
	/*
	UWorld* World = GetWorld();
	if (!World) return;

	UEYS_HorrorSubsystem* HorrorSubsystem = World->GetSubsystem<UEYS_HorrorSubsystem>();
	if (!HorrorSubsystem) return;

	HorrorSubsystem->ActivateHorrorSystem(true);
	*/
}