// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/WashingMachine/EYS_WashingMachineButton.h"
#include "EYS_WashingMachine.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"

// Sets default values
AEYS_WashingMachineButton::AEYS_WashingMachineButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCustomDepthStencilValue(5);
}

// Called when the game starts or when spawned
void AEYS_WashingMachineButton::BeginPlay()
{
	Super::BeginPlay();
	
}
void AEYS_WashingMachineButton::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{

	if (bIsFocused)
	{
		AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
		if (PC)
		{
			if (bCanToggle)
			{
				PC->SetInteractionWidget("[E] Start");
			}
			else
			{
				PC->SetInteractionWidget("[E] Stop");
			}
		}
	}
	StaticMesh->SetRenderCustomDepth(bIsFocused);
}
void AEYS_WashingMachineButton::Interact(AEYS_MyCharacter* myPlayer)
{

}
void AEYS_WashingMachineButton::UpdateButtonRotation()
{
	ButtonCurrentRotation += ButtonStepAmount;

	if (ButtonCurrentRotation >= 360.0f)
	{
		ButtonCurrentRotation = 360.0f;
		GetWorldTimerManager().ClearTimer(ButtonRotationTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Şalter 360 dereceye ulaştı, zamanlayıcı durduruldu"));
	}
	


	if (StaticMesh)
	{
		StaticMesh->SetRelativeRotation(FRotator(ButtonCurrentRotation, 0.0f, 0.0f));

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Şalter Döndü: %0.0f Derece"), ButtonCurrentRotation));

	}
}
void AEYS_WashingMachineButton::SetButtonRotationTimer(float WashingTime, bool bIsStart)
{
	if (bIsStart)
	{
		ButtonCurrentRotation = 90.0f;
		if (StaticMesh)
		{
			StaticMesh->SetRelativeRotation(FRotator(ButtonCurrentRotation, 0.0f, 0.0f));
		}
		float TotalSteps = WashingTime / 2;

		ButtonStepAmount = 300.0f / TotalSteps;
		GetWorld()->GetTimerManager().SetTimer(ButtonRotationTimerHandle, this, &AEYS_WashingMachineButton::UpdateButtonRotation, 2.0f, true);

		bCanToggle = false;
	}
	else
	{
		bCanToggle = true;
		GetWorld()->GetTimerManager().ClearTimer(ButtonRotationTimerHandle);
		StaticMesh->SetRelativeRotation(FRotator(0, 0.0f, 0.0f));
	}
}

void AEYS_WashingMachineButton::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (!bCanToggle) return;
	if (TargetWashingMachine)
	{
		TargetWashingMachine->StartWashing();

	}
}



