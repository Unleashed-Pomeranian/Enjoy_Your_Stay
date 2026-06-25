// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_SnowPileActor.h"
#include "TargetPoints/EYS_DirtTarget.h"
#include "Components/BoxComponent.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/NPC/EYS_GuestCharacter.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/Game Managers/EYS_MissionSubsystem.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"
// Sets default values
AEYS_SnowPileActor::AEYS_SnowPileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEYS_SnowPileActor::OnSnowOverlap);
	}
	if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
	{
		MS->RegisterMissionTarget(EMissionType::SnowPile);
	}
	if (UEYS_UpgradeSubsystem* US = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{

		PlowSpeedMultiplier = US->GetEquipmentUseTimeMultiplier();
	}
	const int32 Index = FMath::RandRange(0, SnowMeshes.Num() - 1);
	if(SnowMeshes[Index])
	{
		StaticMesh->SetStaticMesh(SnowMeshes[Index]);
	}

	SecondPlowValue = PlowValue * 2.0f;
}


// Called every frame
void AEYS_SnowPileActor::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());

	PC->SetInteractionWidget("[M1] Plow");
}
void AEYS_SnowPileActor::aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value)
{

	if (Value == 5&& myPlayer)
	{
		
		Interact(myPlayer);
	}
	else
	{
		return;
	}
}

void AEYS_SnowPileActor::OnSnowOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
	
		AEYS_GuestCharacter* GuestChar = Cast<AEYS_GuestCharacter>(OtherActor);
		if (GuestChar)
		{

			if (PileValue <= 0.002f) return;

		
			GuestChar->SetMentalHealth(SnowMentalDamage);

			
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan,FString::Printf(TEXT("Misafir (%s) kar yiginina daldı! Mentali %f azaldi"), *GuestChar->GetName(), SnowMentalDamage));
		}
	}
}
	

void AEYS_SnowPileActor::PlaySnowAudio_Implementation()
{
}



void AEYS_SnowPileActor::Interact(AEYS_MyCharacter* myPlayer)
{
	float FinalPlowValue = PlowValue * PlowSpeedMultiplier;
	PileValue -= FinalPlowValue;

	PileValue = FMath::Max(PileValue, 0.0f);
	FVector MeshScale = StaticMesh->GetRelativeScale3D();
	MeshScale.Z = PileValue;

	StaticMesh->SetRelativeScale3D(MeshScale);
	if (PileValue <= 0.7f)
	{
		PlowValue = SecondPlowValue;

		if (PileValue <= 0.4f)
		{
			if (MySnowTarget) MySnowTarget->bIsOccupied = false;
			if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
			{
				TS->UpdateTutorialState(ETutorialStep::ShovelSnowPile, ETutorialStep::WaitTheGuest);
			}
			if (UEYS_MissionSubsystem* MS = GetGameInstance()->GetSubsystem<UEYS_MissionSubsystem>())
			{
				MS->UpdateMissionProgress(EMissionType::SnowPile);
			}

			Destroy();

		}

	}
	PlaySnowAudio();
}


