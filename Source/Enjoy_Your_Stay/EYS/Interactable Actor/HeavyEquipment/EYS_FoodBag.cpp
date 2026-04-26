// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBag.h"
#include "EYS/EYS_MyCharacter.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
void  AEYS_FoodBag::BeginPlay()
{
	Super::BeginPlay();
	AEYS_MyCharacter* myPlayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AttachActor(myPlayer);

	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::TakeFoodBag, ETutorialStep::GoToGuestRoom);
	}
}

void AEYS_FoodBag::RemoveFoodBag()
{
	AEYS_MyCharacter* myPlayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	myPlayer->HeldEquipment = nullptr;
	myPlayer->bIsHandsFull = false;
	Destroy();
	

}
