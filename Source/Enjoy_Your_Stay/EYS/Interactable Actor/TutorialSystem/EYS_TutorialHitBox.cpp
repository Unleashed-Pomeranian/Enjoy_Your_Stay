// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/TutorialSystem/EYS_TutorialHitBox.h"
#include "Components/BoxComponent.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"


AEYS_TutorialHitBox::AEYS_TutorialHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
	PostProcessVolume = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessVolume"));
	PostProcessVolume->SetupAttachment(BoxCollision);

	
}


// Called when the game starts or when spawned
void AEYS_TutorialHitBox::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEYS_TutorialHitBox::OnOverlapBegin);
	

	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (TS)
	{ 
		TS->TargetHitBox = this;
		
	}
}

void AEYS_TutorialHitBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
		if (TS)
		{
			switch (TS->CurrentStep)
			{
			case ETutorialStep::GoToEntrance:
			{
				TS->SetTutorialStep(ETutorialStep::TakeFlashlight);
				break;
				
			}
			case ETutorialStep::GoToBoosRoom:
			{
				TS->SetTutorialStep(ETutorialStep::TalkWithBoss);
				break;
			}
			case ETutorialStep::GoToGenerator:
			{
				TS->SetTutorialStep(ETutorialStep::ActivateGenerator);
				break;
			}
			case ETutorialStep::FindMop:
			{
				TS->SetTutorialStep(ETutorialStep::TakeMop);

				break;
			}
			case ETutorialStep::GoToBasement:
			{
				TS->SetTutorialStep(ETutorialStep::TakeShovel);

				break;
			}
			case ETutorialStep::GoToBoilerRoom:
			{
				TS->SetTutorialStep(ETutorialStep::FillCoalBox);
				break;
			}

			case ETutorialStep::GoToPhone:
			{
				TS->SetTutorialStep(ETutorialStep::TakePhone);
				break;
			}
			case ETutorialStep::GoToBed:
			{
				TS->SetTutorialStep(ETutorialStep::EndDay);
				break;
			}
			case ETutorialStep::GoToFridge:
			{
				TS->SetTutorialStep(ETutorialStep::PlaceFoodBox);
				break;
 
			}
			case ETutorialStep::GoToHammer:
			{
				TS->SetTutorialStep(ETutorialStep::TakeHammer);
				break;

			}

			case ETutorialStep::GoToComputer:
			{
				TS->SetTutorialStep(ETutorialStep::OpenComputer);
			}
			default:
				break;
			}
			
			
		}
		
	}
}

void AEYS_TutorialHitBox::SpawnEquipment(TSubclassOf<AActor> EquipmentClass)
{
	if(EquipmentClass)
	{
		GetWorld()->SpawnActor<AActor>(EquipmentClass, GetActorTransform());
	}
}

void AEYS_TutorialHitBox::SetHitBoxLocation(const FVector& NewLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "food");
	SetActorLocation(NewLocation,true);
}


