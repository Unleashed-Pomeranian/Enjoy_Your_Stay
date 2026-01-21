// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MyCharacters_Bed.h"
#include "EYS/Game Managers/EYS_MySunMoonDaySequenceActor.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/UI/EYS_Day_UI.h"

// Sets default values
AEYS_MyCharacters_Bed::AEYS_MyCharacters_Bed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Defaul Scene Root"));
	RootComponent = DefaultSceneRoot;
	StaticMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_MyCharacters_Bed::BeginPlay()
{
	Super::BeginPlay();
	DayCycleActor = Cast<AEYS_MySunMoonDaySequenceActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MySunMoonDaySequenceActor::StaticClass()));
	
}



// Called every frame
void AEYS_MyCharacters_Bed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void   AEYS_MyCharacters_Bed::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void   AEYS_MyCharacters_Bed::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (DayCycleActor->GetTimeOfDay()>=21.9f)
	{
		PC->SetInteractionWidget("[E] Sleep");
	}
	else
		PC->SetInteractionWidget("You can't sleep.");
}

void   AEYS_MyCharacters_Bed::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (DayCycleActor->GetTimeOfDay() >= 21.9f)
	{
		AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
		if (!PC) return;
		if (DayWidgetClass)
			DayWidgetInstance = CreateWidget<UEYS_Day_UI>(PC, DayWidgetClass);

		if (DayWidgetInstance)
		{
			DayNum++;
			DayWidgetInstance->SetDayText(DayNum);
			DayWidgetInstance->SetFocus();
			DayWidgetInstance->AddToViewport();
			DayCycleActor->SetTimeOfDay(10.0f);
			DayCycleActor->FSetTimer();
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());
			DayWidgetInstance->myPC = PC;
			UGameplayStatics::SetGamePaused(GetWorld(), true);

		}
	}
}

