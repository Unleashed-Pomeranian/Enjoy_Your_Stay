// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/ComputerSystem/EYS_SecurityCamera.h"

// Sets default values
AEYS_SecurityCamera::AEYS_SecurityCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture Component 2D"));
	SceneCaptureComponent2D->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_SecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	SetActorTransform(CamTransforms[0]);
}

void AEYS_SecurityCamera::SetCameraLocation(int32 value)
{
	
	if (CamTransforms.Num() == 0) return;

	CamNum = FMath::Clamp(CamNum + value, 0, CamTransforms.Num()-1);
	//CamNum = (CamNum + value + CamLocations.Num()) % CamLocations.Num();
	SetActorTransform(CamTransforms[CamNum]);
		
	

}

// Called every frame
void AEYS_SecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

