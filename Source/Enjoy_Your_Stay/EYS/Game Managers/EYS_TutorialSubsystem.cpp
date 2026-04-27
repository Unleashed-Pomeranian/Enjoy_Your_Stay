// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/UI/EYS_MyCharacter_UI.h"
#include "EYS/Interactable Actor/TutorialSystem/EYS_BossSpeaker.h"
#include "EYS/Interactable Actor/TutorialSystem/EYS_TutorialHitBox.h"
#include "EYS/Game Managers/EYS_MySunMoonDaySequenceActor.h"


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

	// 2. Tabloda o satırı (Row) bul
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
			OnFirstPhaseEnd.Broadcast();
		}
	
		if(CurrentStep == ETutorialStep::GiveRightFood|| CurrentStep == ETutorialStep::GiveWrongFood)
		{
			CurrentStep = ETutorialStep::WaitForPipe;
			OnSecondPhaseEnd.Broadcast();
		}

	}
	else
	{
		return;
	}
}

void UEYS_TutorialSubsystem::RegisterNewOrder(TSubclassOf<AActor> OrderedItemClass)
{
	
	if (CurrentStep != ETutorialStep::OrderSupplies) return;

	
	if (RequiredOrderItems.Contains(OrderedItemClass))
	{
		
		CurrentlyOrderedItems.AddUnique(OrderedItemClass);

		if (CurrentlyOrderedItems.Num() >= RequiredOrderItems.Num())
		{

			
			UpdateTutorialState(ETutorialStep::OrderSupplies, ETutorialStep::GoToBed);
			CurrentlyOrderedItems.Empty();
		}
	}
}

void UEYS_TutorialSubsystem::RegisterFilledSlot(EFoodType FilledType)
{
	if(CurrentStep != ETutorialStep::PlaceFoodBox) return;

	FilledFridgeSlots.AddUnique(FilledType);
	if (FilledFridgeSlots.Num() >= 4)
	{
		UpdateTutorialState(ETutorialStep::PlaceFoodBox, ETutorialStep::WaitTheGuest);
	}
}
