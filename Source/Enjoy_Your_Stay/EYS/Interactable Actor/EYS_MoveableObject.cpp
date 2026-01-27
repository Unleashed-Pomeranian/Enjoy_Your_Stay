// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_MoveableObject.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Timermanager.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "Kismet/GamePlayStatics.h"


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


void AEYS_MoveableObject::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if(!bIsTrigrred)
	PC->SetInteractionWidget("[E] Open");
	else
	PC->SetInteractionWidget("[E] Close");
}

void AEYS_MoveableObject::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
		DoorInteract();
}

void AEYS_MoveableObject::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void AEYS_MoveableObject::TimelineProgress(float value)
{
    
	   
		FRotator NewRot = FMath::Lerp(StartRot, EndRot, value);
	
		StaticMesh->SetRelativeRotation(NewRot);
		
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
		UKismetSystemLibrary::K2_SetTimer(this, "DoorInteract", 3.0f, false);
		PlayMoveableAudio();

	}
	else
	{
		MainTimeline->Reverse();
		bIsTrigrred = false;
		PlayMoveableAudio();
		UKismetSystemLibrary::K2_ClearTimer(this, "DoorInteract");
	}
}

void AEYS_MoveableObject::PlayMoveableAudio_Implementation()
{
}





