// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_FixActor.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Interactable Actor/EYS_Boiler.h"
// Sets default values
AEYS_FixActor::AEYS_FixActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
		RootComponent = DefaultSceneRoot;
		StaticMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
		StaticMesh->SetupAttachment(DefaultSceneRoot);

		
		
}

// Called when the game starts or when spawned
void AEYS_FixActor::BeginPlay()
{
	Super::BeginPlay();
	
		BoilerActor = Cast<AEYS_Boiler>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Boiler::StaticClass()));
		if (BoilerActor)
		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AEYS_FixActor::SetBoilerFuel, 2.0f, true);

}

// Called every frame
void AEYS_FixActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEYS_FixActor::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	
		PC->SetInteractionWidget("[M1] Fix");

	

}
void AEYS_FixActor::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	if (Value == 2)
		SetPipeMesh();

}
void AEYS_FixActor::Interact(AEYS_MyCharacter* myPlayer)
{
	

}

void AEYS_FixActor::SetPipeMesh()
{
	FixValue = FMath::Clamp(FixValue+1,0.0f,100.0f);

	if (FixValue >= 100.f)
	{
		GetWorld()->SpawnActor<AActor>(SinglePipeRef, GetActorTransform());
		Destroy();
	}
	else if (FixValue > 75.f)
	{
		StaticMesh->SetStaticMesh(PipeMeshes[2]);
	}
	else if (FixValue > 50.f)
	{
		StaticMesh->SetStaticMesh(PipeMeshes[1]);
	}
	else if (FixValue > 25.f)
	{
		StaticMesh->SetStaticMesh(PipeMeshes[0]);
	}
}

void AEYS_FixActor::SetBoilerFuel()
{
	if (!(BoilerActor==nullptr))
	BoilerActor->SetCoalAmount(-1.0f);
}

