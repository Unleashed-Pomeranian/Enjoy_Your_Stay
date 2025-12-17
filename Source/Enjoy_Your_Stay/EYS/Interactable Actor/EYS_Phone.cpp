// Fill out your copyright notice in the Description page of Project Settings.
#include "EYS/Interactable Actor/EYS_Phone.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"



// Sets default values
AEYS_Phone::AEYS_Phone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Phone Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Int Phone Mesh"));
	StaticMesh2->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEYS_Phone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_Phone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_Phone::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void AEYS_Phone::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());

	PC->PlayerCameraManager->StartCameraFade(2.0f, 0.0f, 1.5f, FLinearColor::Black, false, true);

	
	FVector SetLocation = GetActorLocation();
	SetLocation.Y = GetActorLocation().Y +10;
	SetLocation.X = GetActorLocation().X + -8;
	FRotator Rotation = {-48,0,0};
	Rotation.Yaw = -90.0f;
	

	myPlayer->SetActorLocation(SetLocation);
	myPlayer->GetController()->SetControlRotation(Rotation);
	PlayPhoneMontage(myPlayer);
	
}

void AEYS_Phone::SetupAttachment(AEYS_MyCharacter* myPlayer)
{
	StaticMesh2->AttachToComponent(myPlayer->FirstPersonMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Phone");
	myPlayer->bIsPhoneMode = true;

}

void AEYS_Phone::PlayPhoneMontage_Implementation(AEYS_MyCharacter* myPlayer)
{
}

