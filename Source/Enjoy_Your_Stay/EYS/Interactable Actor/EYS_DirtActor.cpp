// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_DirtActor.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EYS_WorldSubsystem.h"

AEYS_DirtActor::AEYS_DirtActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	DirtDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Dirt Decal"));
	DirtDecal->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject <UBoxComponent> (TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_DirtActor::BeginPlay()
{
	Super::BeginPlay();
	if (DirtDecal)
	{
		const int32 Index = FMath::RandRange(0, DirtMaterial.Num() - 1);
		if(DirtMaterial[Index])
		DirtDecal->SetDecalMaterial(DirtMaterial[Index]);

		DynMath = DirtDecal->CreateDynamicMaterialInstance();
		if (DynMath)
		{
			DirtDecal->SetMaterial(0,DynMath);
			opacityValue = FMath::Clamp(opacityValue, 0.0f, 3.0f);
		}
	}
	UKismetSystemLibrary::K2_SetTimer(this, "test", 0.5f, true);

	if (DirtDecal)
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
void AEYS_DirtActor::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());

	PC->SetInteractionWidget("[M1] Clean");
}
void AEYS_DirtActor::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{
	if (Value == 3)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, " test");
		Interact(myPlayer);
	}
}



void AEYS_DirtActor::test()
{
	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
	if (!Director) return;

		Director->SetMentalSlate(4.0f);
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
