// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/WashingMachine/EYS_WashingMachine.h"
#include "EYS/EYS_MyCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Sheet.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Detergent.h"
#include "EYS/Interactable Actor/WashingMachine/EYS_WashingMachineButton.h"
#include "EYS/UI/EYS_WashingMachine_UI.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"




// Sets default values
AEYS_WashingMachine::AEYS_WashingMachine()
{
  
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(DefaultSceneRoot);

	ButtonChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ButtonChildComponent"));
	ButtonChildComponent->SetupAttachment(RootComponent);
	WashingAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("WashingAudioComponent"));
	WashingAudioComponent->SetupAttachment(RootComponent);
	WidgetMesh = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Mesh"));
	WidgetMesh->SetupAttachment(DefaultSceneRoot);
	WashingAudioComponent->bAutoActivate = false;
	for (int32 i = 0; i < 3; i++)
	{
		FString SlotName = FString::Printf(TEXT("SheetSlot_%d"), i + 1);
		USceneComponent* NewSlot = CreateDefaultSubobject<USceneComponent>(*SlotName);
		NewSlot->SetupAttachment(RootComponent);
		SheetSlots.Add(NewSlot);
	}

}

// Called when the game starts or when spawned
void AEYS_WashingMachine::BeginPlay()
{
	Super::BeginPlay();
	if (ButtonChildComponent)
	{
	
		AActor* SpawnedActor = ButtonChildComponent->GetChildActor();
		
		if (SpawnedActor)
		{
			
			WashingMachineButtonRef = Cast<AEYS_WashingMachineButton>(SpawnedActor);
			if (WashingMachineButtonRef)
			{
				WashingMachineButtonRef->SetTargetWashingMachine(this);
			}
			
		}
	}
}

void AEYS_WashingMachine::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
{
	if (!myPlayer) return;

	FString IntText = "";

	if (myPlayer->HeldEquipment)
	{
		if (AEYS_Detergent* MyDetergent = Cast<AEYS_Detergent>(myPlayer->HeldEquipment))
		{
			if (DetergentAmount < 100.0f)
			{
				IntText = "[E] Fill";
			}
			else
			{
				
				IntText = bIsLidOpen ? "[E] Close" : "[E] Open";
			}
		}
		
		else if (AEYS_Sheet* MySheet = Cast<AEYS_Sheet>(myPlayer->HeldEquipment))
		{
			if (!bIsLidOpen)
			{
				IntText = "[E] Open";
			}
			else
			{
				if (MySheet->GetDirtStatus())
				{
					
					IntText = "[E] Place";
				}
				else
				{
					IntText = "Dirty Sheets Only!";
				}
				
			}
		}
	}
	else 
	{
		if (!bIsLidOpen)
		{
			IntText = "[E] Open";
		}
		else
		{
			IntText = "[E] Close";
		}
	}
	if (bIsFocused && !IntText.IsEmpty())
	{
		AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
		if (PC)
		{
			PC->SetInteractionWidget(IntText);
		}
	}
}

void AEYS_WashingMachine::Interact(AEYS_MyCharacter* myPlayer)
{
	
}

void AEYS_WashingMachine::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	if (!myPlayer) return;
	if (bIsWashing) return;

	if (myPlayer->HeldEquipment)
	{
		
		if (AEYS_Detergent* MyDetergent = Cast<AEYS_Detergent>(myPlayer->HeldEquipment))
		{
			if (DetergentAmount < 100.0f)
			{
				float NeededValue = 100.0f - DetergentAmount;
				float PouredAmount = MyDetergent->ConsumeDetergent(NeededValue);
				DetergentAmount += PouredAmount;
				UpdateDetergentUI();
				PlayWashingAudio(4);
				if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
				{
					TS->UpdateTutorialState(ETutorialStep::FillDetergent, ETutorialStep::StartWashingMachine);
				}

			}
			else
			{
			
				ToggleLid();
			}
			return; 
		}

	
		if (AEYS_Sheet* MySheet = Cast<AEYS_Sheet>(myPlayer->HeldEquipment))
		{
			
			if (!bIsLidOpen)
			{
				ToggleLid();
				return;
			}

		
			if (!(MySheet->GetDirtStatus()))
			{
				return;
			}

			bool bFoundEmptySlot = false;
	

			for (int32 i = 0; i < SheetSlots.Num(); i++)
			{
				USceneComponent* CurrentSlot = SheetSlots[i];

				if (CurrentSlot)
				{
					if (CurrentSlot->GetAttachChildren().Num() == 0)
					{

						MySheet->PlaceOnRack(myPlayer, CurrentSlot);

						bFoundEmptySlot = true;
						if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
						{
							TS->UpdateTutorialState(ETutorialStep::PlaceDirtySheet, ETutorialStep::TakeDetergent);
						}

						break;
					}
				}
			}
			return;
		}
	}
	else 
	{
		ToggleLid();
	}
}

void AEYS_WashingMachine::PlayWashingAudio(int32 SoundIndex)
{
	if (WashingAudioComponent)
	{
	
		if (WashingAudioComponent->IsPlaying())
		{
			WashingAudioComponent->Stop();
		}


		if (WashingSounds.IsValidIndex(SoundIndex) && WashingSounds[SoundIndex])
		{
			WashingAudioComponent->SetSound(WashingSounds[SoundIndex]);
			WashingAudioComponent->Play();
		}
	}
}


void AEYS_WashingMachine::ToggleLid()
{
	if (!bIsLidOpen)
	{
		SkeletalMesh->PlayAnimation(AnimAssets[0], false);
		bIsLidOpen = true;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Makine Kapağı Açıldı."));

		PlayWashingAudio(0);
		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::OpenWashingMachine, ETutorialStep::PlaceDirtySheet);
		}
	}
	else
	{
		SkeletalMesh->PlayAnimation(AnimAssets[1], false);
		bIsLidOpen = false;
		PlayWashingAudio(1);

	}
}

void AEYS_WashingMachine::StartWashing()
{
	if (bIsWashing || bIsLidOpen) return;
	if (DetergentAmount < 99) return;

	bool bHasAtLeastOneSheet = false;


	for (USceneComponent* Slot : SheetSlots)
	{
		if (Slot)
		{
			TArray<USceneComponent*> AttachedChildren = Slot->GetAttachChildren();

			if (AttachedChildren.Num() > 0)
			{
				bHasAtLeastOneSheet = true;
				break;
			}
		}
	}

	if (!bHasAtLeastOneSheet)
	{

		return;
	}
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::StartWashingMachine, ETutorialStep::WaitForWashEnd);
	}
	PlayWashingAudio(2);
	bIsWashing = true;
	GetWorldTimerManager().SetTimer(WashingTimerHandle, this, &AEYS_WashingMachine::OnWashingComplete,WashingDuration, false);
	if(WashingMachineButtonRef) WashingMachineButtonRef->SetButtonRotationTimer(WashingDuration,true);
}


void AEYS_WashingMachine::OnWashingComplete()
{
	bIsWashing = false;
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Yıkama BİTTİ! Slotlar kontrol ediliyor..."));


	for (USceneComponent* Slot : SheetSlots)
	{
		if (Slot)
		{
		
			TArray<USceneComponent*> AttachedChildren = Slot->GetAttachChildren();

			for (USceneComponent* ChildComp : AttachedChildren)
			{
				if (ChildComp)
				{
		
					AActor* ChildActor = ChildComp->GetOwner();

				
					if (AEYS_Sheet* SheetInSlot = Cast<AEYS_Sheet>(ChildActor))
					{
						SheetInSlot->SetDirtStatus(false);

					}
				}
			}
		}
	}
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::WaitForWashEnd, ETutorialStep::TakeCleanSheet);
	}
	if (WashingMachineButtonRef) WashingMachineButtonRef->SetButtonRotationTimer(WashingDuration, false);
	DetergentAmount = 0.0f;
	PlayWashingAudio(3);
	UpdateDetergentUI();
	GetWorldTimerManager().ClearTimer(WashingTimerHandle);
	
}

void AEYS_WashingMachine::UpdateDetergentUI()
{
	if (WidgetMesh)
	{
		
		UUserWidget* UserWidgetInstance = WidgetMesh->GetUserWidgetObject();

		if (UserWidgetInstance)
		{
			
			UEYS_WashingMachine_UI* MachineUI = Cast<UEYS_WashingMachine_UI>(UserWidgetInstance);

			if (MachineUI)
			{
				
				MachineUI->SetSliderBarValue(DetergentAmount);
			}
		}
	}
}
