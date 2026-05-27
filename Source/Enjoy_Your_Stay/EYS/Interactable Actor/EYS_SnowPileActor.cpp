// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_SnowPileActor.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
// Sets default values
AEYS_SnowPileActor::AEYS_SnowPileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject <UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void AEYS_SnowPileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEYS_SnowPileActor::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());

	PC->SetInteractionWidget("[M1] Plow");
}
void AEYS_SnowPileActor::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, " in");
	if (Value == 5&& myPlayer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, " in2");
		Interact(myPlayer);
	}
	else
	{
		return;
	}
}

void AEYS_SnowPileActor::PlaySnowAudio_Implementation()
{
}



void AEYS_SnowPileActor::Interact(AEYS_MyCharacter* myPlayer)
{

	PileValue -= PlowValue;
	PileValue = FMath::Max(PileValue, 0.0f);
	FVector MeshScale = StaticMesh->GetRelativeScale3D();
	MeshScale.Z = PileValue;
	StaticMesh->SetRelativeScale3D(MeshScale);
	if (PileValue <= 0.7f)
	{
		PlowValue = 0.006f;

		if (PileValue <= 0.002f)
		{
		
			Destroy();

		}

	}
	PlaySnowAudio();
}


