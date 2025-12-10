// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_DirtActor.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "Kismet/GameplayStatics.h"

AEYS_DirtActor::AEYS_DirtActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DirtMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DirtMesh"));
	DirtMesh->SetupAttachment(DefaultSceneRoot);

	
}

// Called when the game starts or when spawned
void AEYS_DirtActor::BeginPlay()
{
	Super::BeginPlay();
	if (DirtMesh)
	{
		DynMath = DirtMesh->CreateDynamicMaterialInstance(0);
		if (DynMath)
		{
			DirtMesh->SetMaterial(0,DynMath);
			opacityValue = FMath::Clamp(opacityValue, 0.0f, 3.0f);
		}
	}

	if (DirtMesh)
	{
		AEYS_Notebook* Notebook = Cast<AEYS_Notebook>(
			UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Notebook::StaticClass()));
		if (Notebook)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "HandleMoveCompleted");
			Notebook->CleaningTotal += 1;
			Notebook->CleaningMission(GetActorTransform());
			
		}
	}
	
}

void AEYS_DirtActor::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	if (Value == 3)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, " test");
		Interact(myPlayer);
	}
}


void AEYS_DirtActor::Interact(AEYS_MyCharacter* myPlayer) 
{
	
	opacityValue -= cleaningValue;
	DynMath->SetScalarParameterValue("Opacity", opacityValue);

	if (opacityValue <= 2.1f)
	{
		cleaningValue = 0.021f;

		if (opacityValue <= 0.2f)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, " destroyed");
			AEYS_Notebook* Notebook = Cast<AEYS_Notebook>(
				UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Notebook::StaticClass()));
			if (Notebook)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "HandleMoveCompleted");
				Notebook->CleaningFinished+=1;
				Notebook->CleaningMission(GetActorTransform());

			}
			Destroy();

		}

	}
}
