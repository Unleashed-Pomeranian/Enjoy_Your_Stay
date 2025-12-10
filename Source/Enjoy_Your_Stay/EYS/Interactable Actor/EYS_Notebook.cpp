// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "EYS/Interactable Actor/EYS_NotebookWidget.h"
#include "Blueprint/UserWidget.h"


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

	
	
}

// Called every frame
void AEYS_Notebook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_Notebook::CleaningMission(FTransform test)
{

	if (NotebookWidgetInstance)
	{
		
		NotebookWidgetInstance->SetCleaningBox(CleaningFinished, CleaningTotal);
	}

	if (CleaningTotal == CleaningFinished)
	{
		Closelight(test);
	}
}

void AEYS_Notebook::FuelingMission()
{
	
	if (NotebookWidgetInstance)
	{
		NotebookWidgetInstance->SetFuelingBox(FuelingFinished, FuelingTotal);
		
	}
}

void AEYS_Notebook::FixingMission()
{
	NotebookWidgetInstance->SetFixingBox(FixingFinished, FixingTotal);
}

void AEYS_Notebook::Closelight_Implementation(FTransform test)
{
}




