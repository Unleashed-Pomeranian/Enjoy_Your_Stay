// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "EYS/Interactable Actor/EYS_NotebookWidget.h"
#include "Blueprint/UserWidget.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

#include "EYS/Game Managers/EYS_MissionSubsystem.h"

// Sets default values
AEYS_Notebook::AEYS_Notebook()
{
	
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	WidgetMesh = CreateDefaultSubobject<UWidgetComponent>(TEXT("NoteBook Widget"));
	WidgetMesh->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AEYS_Notebook::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = WidgetMesh->GetUserWidgetObject();
	if (Widget)
	{
		NotebookWidgetInstance = Cast<UEYS_NotebookWidget>(Widget);
		if (NotebookWidgetInstance)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "NotebookWidgetInstance");
			
		}
	}
	if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
	{
		MS->RegisterNotebook(this);
	}
	
	
}

void AEYS_Notebook::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
	{
		MS->UnregisterNotebook();
	}
	Super::EndPlay(EndPlayReason);
}


void AEYS_Notebook::CleaningMission(int32 Finished, int32 Total)
{
	if (NotebookWidgetInstance)
	{
		NotebookWidgetInstance->SetCleaningBox(Finished, Total);
	}

	
	if (Total == Finished && Total > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Inwidget");
		UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
		if (TS)
		{

			TS->UpdateTutorialState(ETutorialStep::CleanDirt, ETutorialStep::GoToBasement);
			TS->UpdateTutorialState(ETutorialStep::CleanWallDirt, ETutorialStep::GoToSnowPile);
		}

		if (NotebookWidgetInstance)
		{
			NotebookWidgetInstance->CleanMissionBox(1);
		}
	}
}
void AEYS_Notebook::FuelingMission(int32 Finished, int32 Total)
{
	if (NotebookWidgetInstance)
	{
		NotebookWidgetInstance->SetFuelingBox(Finished, Total);
	}

	if (Total == Finished && Total > 0)
	{
	

		if (NotebookWidgetInstance)
		{
			NotebookWidgetInstance->CleanMissionBox(2);
		}
	}
}

void AEYS_Notebook::FixingMission(int32 Finished, int32 Total)
{
	if (NotebookWidgetInstance)
	{
		NotebookWidgetInstance->SetFixingBox(Finished, Total);
	}

	if (Total == Finished && Total > 0)
	{


		if (NotebookWidgetInstance)
		{
			NotebookWidgetInstance->CleanMissionBox(3);
		}
	}
}

void AEYS_Notebook::BoilerMission(int32 Finished, int32 Total)
{
	if (NotebookWidgetInstance)
	{
		NotebookWidgetInstance->SetBoilerBox(Finished, Total);
	}

	if (Total == Finished && Total > 0)
	{


		if (NotebookWidgetInstance)
		{
			NotebookWidgetInstance->CleanMissionBox(4);
		}
	}
}

void AEYS_Notebook::SnowPileMission(int32 Finished, int32 Total)
{
	if (NotebookWidgetInstance)
	{
		NotebookWidgetInstance->SetSnowPileBox(Finished, Total);
	}

	if (Total == Finished && Total > 0)
	{


		if (NotebookWidgetInstance)
		{
			NotebookWidgetInstance->CleanMissionBox(5);
		}
	}
}





