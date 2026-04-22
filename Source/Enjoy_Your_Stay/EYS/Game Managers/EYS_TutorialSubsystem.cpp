// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/UI/EYS_MyCharacter_UI.h"
#include "EYS/Interactable Actor/TutorialSystem/EYS_BossSpeaker.h"
#include "EYS/Interactable Actor/TutorialSystem/EYS_TutorialHitBox.h"


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
			MyCharacterUIIns->SetSubtitle(FoundRow->SubtitleText, FoundRow->SubtitleDuration);

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
		
	}
	else
	{
	
	}
}
