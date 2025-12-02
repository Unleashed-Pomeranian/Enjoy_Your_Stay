// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_MoveableObject.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "Timermanager.h"


// Sets default values
AEYS_MoveableObject::AEYS_MoveableObject()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;

 	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	MainTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Main Timeline"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);
	bIsTrigrred = false;
	bIsDoorLocked = false;
}


void AEYS_MoveableObject::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineFloat MovementValue;
	MovementValue.BindUFunction(this, FName("TimelineProgress"));
	FOnTimelineEvent TimeLineEnded;
	TimeLineEnded.BindUFunction(this, FName("TimelineFinished"));

	if (MovementCurve)
	{
		MainTimeline->AddInterpFloat(MovementCurve, MovementValue);
		

	}
 
	
}

void AEYS_MoveableObject::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Interact(myPlayer);
}

void AEYS_MoveableObject::Interact(AEYS_MyCharacter* myPlayer)
{
	if (!bIsDoorLocked)
	{
		DoorInteract();
	
	}
	
	else
	{
		myPlayer->PlayMontage();
		
	}
	
}

void AEYS_MoveableObject::TimelineProgress(float value)
{
    
	   
		FRotator NewRot = FMath::Lerp(StartRot, EndRot, value);
	
		StaticMesh->SetRelativeRotation(NewRot);

		//SetActorRotation(NewRot);
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Play");
		
}

void AEYS_MoveableObject::TimelineFinished()
{
}

void AEYS_MoveableObject::DoorInteract()
{
	if (!MainTimeline || !MovementCurve) return;

	if (!bIsTrigrred)
	{
		MainTimeline->Play();
		StartRot = EndRot = StaticMesh->GetRelativeRotation();
		StartRot.Yaw = RotStartValue;
		EndRot.Yaw = RotEndValue;
		
		bIsTrigrred = true;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "true");

	}
	else
	{
		MainTimeline->Reverse();
		bIsTrigrred = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "fasle");
	}
}





