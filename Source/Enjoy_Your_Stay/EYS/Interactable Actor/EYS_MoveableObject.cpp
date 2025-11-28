// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_MoveableObject.h"
#include "Timermanager.h"


// Sets default values
AEYS_MoveableObject::AEYS_MoveableObject()
{

 	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	PrimaryActorTick.bCanEverTick = true;
	MainTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Main Timeline"));
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
	
	if (!MainTimeline || !MovementCurve) return;

	if (!bIsTrigrred)
	{


		


		MainTimeline->Play();
		StartRot = EndRot = GetActorRotation();
		StartRot.Yaw = RotStartValue;
		EndRot.Yaw = RotEndValue;
		bIsTrigrred = true;


	}
	else{
		MainTimeline->Reverse();
		bIsTrigrred = false;
	}
		
	
	
	
}



void AEYS_MoveableObject::TimelineProgress(float value)
{
    
	   
		FRotator NewRot = FMath::Lerp(StartRot, EndRot, value);
	
		SetActorRotation(NewRot);
		
	
		
}

void AEYS_MoveableObject::TimelineFinished()
{
}



