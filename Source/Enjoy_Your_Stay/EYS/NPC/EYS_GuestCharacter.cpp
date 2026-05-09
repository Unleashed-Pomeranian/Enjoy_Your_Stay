// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "EYS/NPC/EYS_GuestAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/EYS_MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBag.h"
#include "EYS/Interactable Actor/EYS_Phone.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/Game Managers/EYS_GuestSpawner.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/NPC/EYS_GuestCar.h"


// Sets default values
AEYS_GuestCharacter::AEYS_GuestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ThirdPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Third Person Mesh"));
	ThirdPersonMesh->SetupAttachment(GetCapsuleComponent());
	DialogueComponent = CreateDefaultSubobject<UEYS_QDialoguesSpeakerComponent>(TEXT("DialogueComponent"));
	AIControllerClass = AEYS_GuestAIController::StaticClass();

}

// Called when the game starts or when spawned
void AEYS_GuestCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();
	CachedAIController = Cast<AEYS_GuestAIController>(GetController());

	if(CachedAIController)
	CachedAIController->OnAIMoveComplete.AddUObject(this, &AEYS_GuestCharacter::HandleMoveCompleted);
	CurrentStatus = EGuestStatus::Arriving;
	
	DialogueComponent->UpdateDialog(0);
}

void AEYS_GuestCharacter::PlayNPCAudio_Implementation()
{

}


void AEYS_GuestCharacter::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (PC&&bCanInteract)
		PC->SetInteractionWidget("[E] Talk");


}

void AEYS_GuestCharacter::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "EInInteract");
	Interact(myPlayer);
}
void AEYS_GuestCharacter::HandleMoveCompleted()
{
	switch (CurrentStatus)
	{
	case EGuestStatus::Arriving:
	{

		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::WaitTheGuest, ETutorialStep::TalkWithGuest);
			
			{
				
				GetWorld()->GetTimerManager().SetTimer(AbandonTimer, this, &AEYS_GuestCharacter::FGuestAbandon, AbandonTime, false);
				
			}

		}
	    	CurrentStatus = EGuestStatus::WaitingForCheckIn;
		    bCanInteract = true;
			break;
	}
	case EGuestStatus::AbandonHotel:
	{
		if (AssignedCar)
		{
			AEYS_GuestSpawner* Spawner = Cast<AEYS_GuestSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_GuestSpawner::StaticClass()));
			if (Spawner) Spawner->SetEmptyRoom();
			AssignedCar->DriveBack();
			Destroy();
		}
		break;
	}
	
	case EGuestStatus::GoingToRoom:
	{
		DialogueComponent->UpdateDialog(1);
		CurrentStatus = EGuestStatus::InRoom;
		bCanInteract = true;
		break;
	}

	
	case EGuestStatus::GoToCheckOut:
	{
		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::WaitForCheckout, ETutorialStep::CheckoutGuest);
		}
		DialogueComponent->UpdateDialog(5);
		CurrentStatus = EGuestStatus::ReadyToCheckOut;
		break;
	}
	case EGuestStatus::Leaving:
	{
		if (AssignedCar)
		{
			AssignedCar->DriveBack();
			Destroy();
		}
		break;
	}
		
	default:
		break;
	}
}

void AEYS_GuestCharacter::Interact(AEYS_MyCharacter* myPlayer)
{	
	if (!bCanInteract) return;
	

	
	
	switch (CurrentStatus)
	{

	case EGuestStatus::WaitingForCheckIn:
	{
	
		GuestStartDialogue(myPlayer);
		myPlayer->MyDialogueComponent->GetOnDialogueEndDelegate().AddDynamic(this, &AEYS_GuestCharacter::OnDialogueFinished);
		GetWorld()->GetTimerManager().ClearTimer(AbandonTimer);
		break;
	}
	
	case EGuestStatus::WaitingForKey:
	{
		TakeKey(myPlayer);
		break;
	}
	case EGuestStatus::GoingToRoom:
	{
		break;
	}
		
	case EGuestStatus::InRoom:
	{
		GuestStartDialogue(myPlayer);
		break;
	}
		
	case EGuestStatus::WaitingForFood:
		break;
	case EGuestStatus::ReadyToCheckOut:
	{
		GuestStartDialogue(myPlayer);
	}
		break;
	case EGuestStatus::Leaving:
		break;
	default:
		break;
	}
}

void AEYS_GuestCharacter::MoveTo(FVector Target, float AccceptanceRadius)
{
	CachedAIController->MoveToPoint(Target,AccceptanceRadius);
	bCanInteract = false;
	
}

void AEYS_GuestCharacter::TakeKey(AEYS_MyCharacter* myPlayer)
{
	if (bIsHaveRoom) return;
	myPlayer->bIsHaveKey = false;
	myPlayer->SetRoot(0);
	RoomLocation = myPlayer->RoomLock;
	MoveTo(RoomLocation, 100.0f);
	bCanInteract = false;
	DialogueNum++;
	RoomNumber = myPlayer->RoomNumb;
	bIsHaveRoom = true;
	CurrentStatus = EGuestStatus::GoingToRoom;

}
void AEYS_GuestCharacter::OnDialogueFinished()
{


	    bisDialogueEnd = true;
		UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
		switch (CurrentStatus)
		{

		case EGuestStatus::WaitingForCheckIn:
		{
			if(TS) TS->UpdateTutorialState(ETutorialStep::TalkWithGuest, ETutorialStep::TakeKey);
			CurrentStatus = EGuestStatus::WaitingForKey;
			GetWorld()->GetTimerManager().SetTimer(AbandonTimer, this, &AEYS_GuestCharacter::FGuestAbandon, AbandonTime, false);
		}
			break;
		
		case EGuestStatus::InRoom:
		{
			MoveTo(RoomLocation, 50.0f);
			break;
		}
			
		case EGuestStatus::WaitingForFood:
			break;

		case EGuestStatus::ReadyToCheckOut:
		{
			if (AssignedCar)
			{
				FVector DestroyLocation = AssignedCar->GetActorLocation();
				MoveTo(DestroyLocation, 50);
				CheckOut(MyCharacter);
			}
			

		}
			break;

		default:
			break;
		}
	
}

/**void AEYS_GuestCharacter::CorruptTheGuest()
{
	if (!bIsCheckOut&&!bIsOrderFood)
	{
		if (IsValid(CachedAIController))
		{
			PlayNPCAudio();
			bIsCorrupted = true;
			CachedAIController->CorruptedNPC();
			DialogueNum = 4;
			UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem< UEYS_WorldSubsystem>();
			if (!Director) return;
			Director->bIsAnyGuestCorrupted = true;
			

		}
	}
	
	
}*/

void AEYS_GuestCharacter::OrderFood()
{
	
}

void AEYS_GuestCharacter::FGuestAbandon()
{
	switch (CurrentStatus)
	{

	case EGuestStatus::WaitingForCheckIn:
	{
		bCanInteract = false;
		FVector CarLoc = AssignedCar->GetActorLocation();
		MoveTo(CarLoc, 50.0f);
		CurrentStatus = EGuestStatus::AbandonHotel;
		break;
	}

	case EGuestStatus::WaitingForFood:
	{
		bCanInteract = false;
		MoveTo(RoomLocation, 50.0f);
		CurrentStatus = EGuestStatus::GoingToRoom;
	}
	}
}

void AEYS_GuestCharacter::TakeFood(AEYS_MyCharacter* myPlayer)
{
	

	GuestStartDialogue(myPlayer);

}


void AEYS_GuestCharacter::GuestStartDialogue(AEYS_MyCharacter* myPlayer)
{

	FVector NPC_Loc = GetActorLocation();
	FVector Player_Loc = myPlayer->GetActorLocation();
	Player_Loc.Z = NPC_Loc.Z;
	FRotator LookAtRot = (Player_Loc - NPC_Loc).Rotation();

	SetActorRotation(LookAtRot);

	DialogueComponent->StartDialogue(myPlayer);
	

}
void AEYS_GuestCharacter::DestroyFoodBag()
{
	if(FoodBagRef)
	FoodBagRef->Destroy();
}

void AEYS_GuestCharacter::CheckOut(AEYS_MyCharacter* myPlayer)
{
	if (!myPlayer) return;
	myPlayer->bIsHaveKey = true;
	myPlayer->RoomNumb = RoomNumber;
	myPlayer->SetRoot(2);
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (PC) PC->SetMoneyWidget(500);
	AEYS_GuestSpawner* Spawner = Cast<AEYS_GuestSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_GuestSpawner::StaticClass()));
	if (Spawner) Spawner->SetEmptyRoom();
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::CheckoutGuest, ETutorialStep::PutKey);
	}
}

void AEYS_GuestCharacter::SetGuestMesh(USkeletalMesh* GuestSkin)
{
	if(GuestSkin)
	ThirdPersonMesh->SetSkeletalMesh(GuestSkin, true);
}

