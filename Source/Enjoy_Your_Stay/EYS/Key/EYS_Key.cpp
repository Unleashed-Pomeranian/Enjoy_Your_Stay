// Fill out your copyright notice in the Description page of Project Settings.
#include "EYS/Key/EYS_Key.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Key/EYS_KeyHolder.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"


// Sets default values
AEYS_Key::AEYS_Key()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot); 
	StaticMesh->SetCustomDepthStencilValue(5);

	
}

// Called when the game starts or when spawned
void AEYS_Key::BeginPlay()
{
	Super::BeginPlay();
	KeyHolder = Cast<AEYS_KeyHolder>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_KeyHolder::StaticClass()));
}

// Called every frame
void AEYS_Key::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_Key::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	



	if (bIsFocused)
	{
		FString RoomNameString = FString::Printf(TEXT("[E] Room %d"), RoomNum);
		AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
		if (PC) PC->SetInteractionWidget(RoomNameString);
	}

	StaticMesh->SetRenderCustomDepth(bIsFocused);

}

void AEYS_Key::Interact(AEYS_MyCharacter* myPlayer)
{

	
}
void AEYS_Key::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (!myPlayer) return;
	if (!(myPlayer->bIsHaveKey))
	{

		
		if (KeyHolder)
		{
			KeyHolder->UpdateKeyDisplay(RoomID,false);
		}
		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::TakeKey, ETutorialStep::GiveKeyToGuest);
		}
		myPlayer->bIsHaveKey = true;
		myPlayer->RoomLock = RoomLocation;
		myPlayer->SetRoot(7);
		myPlayer->MyRoomID = RoomID;
		
		

	}

}

