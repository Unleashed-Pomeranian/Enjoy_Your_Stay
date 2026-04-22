// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/TutorialSystem/EYS_BossSpeaker.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
// Sets default values
AEYS_BossSpeaker::AEYS_BossSpeaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	SpeakerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeakerMesh"));
	SpeakerMesh->SetupAttachment(DefaultSceneRoot);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void AEYS_BossSpeaker::BeginPlay()
{
	Super::BeginPlay();
	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (TS) { TS->TargetSpeaker = this;}
	
}

// Called every frame
void AEYS_BossSpeaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_BossSpeaker::PlayBossMessage(USoundBase* MessageSound)
{
	if (MessageSound)
	{
		AudioComponent->SetSound(MessageSound);
		AudioComponent->Play();
	}
}

