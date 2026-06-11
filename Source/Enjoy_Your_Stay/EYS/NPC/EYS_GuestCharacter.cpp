// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "EYS_GuestAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/EYS_MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EYS/UI/Order Widgets/EYS_Guest_UI.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS_WorldSubsystem.h"
#include "EYS/Game Managers/EYS_GuestSpawner.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/NPC/EYS_GuestCar.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Tray.h"
#include "EYS_Chair.h"

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
	bIsDriving = false;


}

void AEYS_GuestCharacter::PlayNPCAudio_Implementation()
{

}
void AEYS_GuestCharacter::InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused)
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
	case EGuestStatus::DirtyRoom:
	{
		GetWorld()->GetTimerManager().SetTimer(AbandonTimer, this, &AEYS_GuestCharacter::FGuestAbandon, AbandonTime, false);
		DialogueComponent->UpdateDialog(6);
		bCanInteract = true;
		break;
	}
	case EGuestStatus::AbandonHotel:
	{
		if (AssignedCar)
		{
			AssignedCar->DriveBack();
			Destroy();
			bCanInteract = true;
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
	case EGuestStatus::InRoom:
	{
		bCanInteract = true;
		break;
	}
	case EGuestStatus::GoToDiningHall:
	{
		CurrentStatus = EGuestStatus::WaitingForOrder;
		GetWorld()->GetTimerManager().SetTimer(AbandonTimer, this, &AEYS_GuestCharacter::FGuestAbandon, HallAbandonTime, false);
		bCanInteract = true;
		if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
		{
			TS->UpdateTutorialState(ETutorialStep::WaitGuestOrder, ETutorialStep::TakeGuestOrder);
		}
		break;
	}
	case EGuestStatus::GoToSit:
	{
		SitOnChair();
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
		bCanInteract = true;
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
		MyCharacter = myPlayer;
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
	case EGuestStatus::DirtyRoom:
	{
		GuestStartDialogue(myPlayer);
		GetWorld()->GetTimerManager().ClearTimer(AbandonTimer);
		break;

	}
	case EGuestStatus::WaitingForOrder:
	{
		OrderFood(myPlayer);
		GetWorld()->GetTimerManager().ClearTimer(AbandonTimer);
		break;
	}
		
	case EGuestStatus::WaitingForFood:
	{
		CheckFood(myPlayer);
		break;
	}
		
	case EGuestStatus::ReadyToCheckOut:
	{
		GuestStartDialogue(myPlayer);
		break;
	}
		
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
	GuestRoomID = myPlayer->MyRoomID;
	bIsHaveRoom = true;
	CurrentStatus = EGuestStatus::GoingToRoom;
	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (TS) TS->UpdateTutorialState(ETutorialStep::GiveKeyToGuest, ETutorialStep::SpawnFourthHorrorActor);

	float RandomValue = FMath::RandRange(120.0f, 180.0f);
	GetWorld()->GetTimerManager().ClearTimer(AbandonTimer);
	GetWorld()->GetTimerManager().SetTimer(OrderTimer, this, &AEYS_GuestCharacter::SetDinnerTime, RandomValue, false);

}
void AEYS_GuestCharacter::OnDialogueFinished()
{

	if (MyCharacter && MyCharacter->MyDialogueComponent)
	{
		MyCharacter->MyDialogueComponent->GetOnDialogueEndDelegate().RemoveDynamic(this, &AEYS_GuestCharacter::OnDialogueFinished);
	}
	
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
		case EGuestStatus::DirtyRoom:
		{
			FGuestAbandon();
			break;
		}
		case EGuestStatus::WaitingForOrder:
		{
			if (MyCharacter)
			{
				AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(MyCharacter->GetController());
				if (PC) PC->MobilizeCharacter(false, false, false);
			}
			CurrentStatus = EGuestStatus::WaitingForFood;

			GetWorld()->GetTimerManager().SetTimer(AbandonTimer, this, &AEYS_GuestCharacter::FGuestAbandon, HallAbandonTime, false);
			break;
		}
		

		case EGuestStatus::TakeFood:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "DialogEnd");
			CurrentStatus = EGuestStatus::GoToSit;
			TakeFood(MyCharacter);
			
			break;
		}
		
		case EGuestStatus::WrongOrder:
		{
			CurrentStatus = EGuestStatus::GoingToRoom;
			MoveTo(RoomLocation, 20);
			TS->UpdateTutorialState(ETutorialStep::GiveTrayToGuest, ETutorialStep::GiveWrongFood);
			break;
		
		}
			
		case EGuestStatus::ReadyToCheckOut:
		{
			if (AssignedCar)
			{
				CheckOut(MyCharacter);
				CurrentStatus = EGuestStatus::Leaving;;
				FVector DestroyLocation = AssignedCar->GetActorLocation();
				MoveTo(DestroyLocation, 150);
				
				
			}
			
			break;
		}
	
		default:
			break;
		}
	
}



void AEYS_GuestCharacter::SetDinnerTime()
{
	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem<UEYS_WorldSubsystem>();
	if (!Director) return;
	 float DayTime = Director->Hour;
	 if (DayTime <= 21.0f&& !bIsCheckOut)
	 {
		 MoveTo(DiningHallLocation, 20.0f);
		 CurrentStatus = EGuestStatus::GoToDiningHall;

	 }
	 else
	 {
		 GetWorld()->GetTimerManager().ClearTimer(OrderTimer);
		 GetWorld()->GetTimerManager().SetTimer(OrderTimer, this, &AEYS_GuestCharacter::SetDinnerTime, 30.0f, false);
	 }
}

void AEYS_GuestCharacter::OrderFood(AEYS_MyCharacter* myPlayer)
{

	UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem<UEYS_WorldSubsystem>();
     FoodOrder = Director->GetRandomType(EItemType::Food);
	 DrinkOrder = Director->GetRandomType(EItemType::Drink);
	FString FoodName = StaticEnum<EFoodType>()->GetDisplayNameTextByValue(static_cast<int64>(FoodOrder)).ToString();
	FString DrinkName = StaticEnum<EFoodType>()->GetDisplayNameTextByValue(static_cast<int64>(DrinkOrder)).ToString();

	if (GuestWidgetClass && myPlayer)
	{
		if(!GuestWidgetInstance)GuestWidgetInstance = CreateWidget<UEYS_Guest_UI>(GetWorld(), GuestWidgetClass);
	}
	if (GuestWidgetInstance)
	{
		GuestWidgetInstance->SetGuestText(FoodName, DrinkName);
		GuestWidgetInstance->OrderDialogEnd.RemoveDynamic(this, &AEYS_GuestCharacter::OnDialogueFinished);
		GuestWidgetInstance->OrderDialogEnd.AddDynamic(this, &AEYS_GuestCharacter::OnDialogueFinished);
		GuestWidgetInstance->AddToViewport();
		AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
		if (PC) PC->MobilizeCharacter(true, true, true);
	}
	FVector NPC_Loc = GetActorLocation();
	FVector Player_Loc = myPlayer->GetActorLocation();
	Player_Loc.Z = NPC_Loc.Z;
	FRotator LookAtRot = (Player_Loc - NPC_Loc).Rotation();

	SetActorRotation(LookAtRot);
}
void AEYS_GuestCharacter::CheckFood(AEYS_MyCharacter* myPlayer)
{
	if (myPlayer->HeldEquipment && myPlayer->HeldEquipment->IsA(AEYS_Tray::StaticClass()))
	{

		GuestTray = Cast<AEYS_Tray>(myPlayer->HeldEquipment);
		if (!GuestTray) return;
		TArray<EFoodType> GuestOrders = { FoodOrder, DrinkOrder };
		OrderScore = GuestTray->CheckItemTypes(GuestOrders);
	
		if (OrderScore >= 2) 
		{
			DialogueComponent->UpdateDialog(2); 
			CurrentStatus = EGuestStatus::TakeFood;
		}
		else if (OrderScore == 1) 
		{
			DialogueComponent->UpdateDialog(3); 
			CurrentStatus = EGuestStatus::TakeFood;
		}
		else 
		{
			DialogueComponent->UpdateDialog(4);
			CurrentStatus = EGuestStatus::WrongOrder;
		}
	
		FTimerHandle InitHandle;
		GetWorld()->GetTimerManager().SetTimer(InitHandle, [myPlayer,this]()
			{
				if (IsValid(myPlayer))
				{
					GuestStartDialogue(myPlayer);
				}
			}, 0.5f, false);
		

	}
}
void AEYS_GuestCharacter::TakeFood(AEYS_MyCharacter* myPlayer)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TakeFood");
	if (!myPlayer || !GuestTray) return;
	

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Infood");
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();

	if (OrderScore >= 2)
	{
		MentalSlateValue += 20.0f;
		if (PC) PC->SetMoneyWidget(200);
		TS->UpdateTutorialState(ETutorialStep::GiveTrayToGuest, ETutorialStep::GiveRightFood);
	}
	else if (OrderScore == 1)
	{
		MentalSlateValue -= 10.0f;
		if (PC) PC->SetMoneyWidget(200);
		TS->UpdateTutorialState(ETutorialStep::GiveTrayToGuest, ETutorialStep::GiveWrongFood);
	}

	
		
	
	bIsCarrying = true;
	GuestTray->AttachToComponent(ThirdPersonMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Tray");
	myPlayer->SetRoot(0);
	myPlayer->HeldEquipment = nullptr;
	myPlayer->bIsHandsFull = false;

	if (UEYS_WorldSubsystem* Director = GetWorld()->GetSubsystem<UEYS_WorldSubsystem>())
	{
		TargetChair = Director->GetAvailableChair();

		if (TargetChair)
		{
			TargetChair->bIsOccupied = true;

		
			FVector SitLocation = TargetChair->GetActorLocation();

			MoveTo(SitLocation, 100.0f);
			CurrentStatus = EGuestStatus::GoToSit;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Infood");
		}
		else
		{
		
			MoveTo(RoomLocation, 50.0f);
			CurrentStatus = EGuestStatus::GoingToRoom;
		}
	}
	
		
}
void AEYS_GuestCharacter::SitOnChair()
{	
		if (TargetChair)
		{
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			if (GuestTray)
			{
				
				GuestTray->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				
			
				FTransform TableTransform = TargetChair->GetTableTransform();
				GuestTray->SetActorTransform(TableTransform);
			}

			
			FTransform ChairTransform = TargetChair->GetChairTransform();
			SetActorLocation(ChairTransform.GetLocation());
			SetActorRotation(ChairTransform.GetRotation());

			CurrentStatus = EGuestStatus::Sitting;
			bIsCarrying = false;
			bIsSitting = true;

			GetWorld()->GetTimerManager().SetTimer(SitTimer, this, &AEYS_GuestCharacter::FinishDining, 30.0f, false);
		}
	
}
void AEYS_GuestCharacter::FinishDining()
{
	bIsSitting = false;
	
	

	if (GuestTray)
	{
		GuestTray->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		GuestTray->CleanSlots();
		GuestTray = nullptr;
	}

	if (TargetChair)
	{
		TargetChair->bIsOccupied = false;
		FVector GetUpLoc = TargetChair->GetLeaveLocation();
	
			SetActorLocation(GetUpLoc);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			TargetChair = nullptr;
	}

	



	CurrentStatus = EGuestStatus::GoingToRoom;
	MoveTo(RoomLocation, 50);
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
	case EGuestStatus::DirtyRoom:
	{
		bCanInteract = false;
		FVector CarLoc = AssignedCar->GetActorLocation();
		MoveTo(CarLoc, 50.0f);
		CurrentStatus = EGuestStatus::AbandonHotel;
		break;
	}
	case EGuestStatus::WaitingForOrder:
	{
		bCanInteract = false;
		MoveTo(RoomLocation, 50.0f);
		CurrentStatus = EGuestStatus::GoingToRoom;
		break;
	}
	case EGuestStatus::WaitingForFood:
	{
		bCanInteract = false;
		MoveTo(RoomLocation, 50.0f);
		CurrentStatus = EGuestStatus::GoingToRoom;
		break;
	}
	default: break;
	}
}
void AEYS_GuestCharacter::GuestStartDialogue(AEYS_MyCharacter* myPlayer)
{

	FVector NPC_Loc = GetActorLocation();
	FVector Player_Loc = myPlayer->GetActorLocation();
	Player_Loc.Z = NPC_Loc.Z;
	FRotator LookAtRot = (Player_Loc - NPC_Loc).Rotation();

	SetActorRotation(LookAtRot);

	myPlayer->MyDialogueComponent->GetOnDialogueEndDelegate().AddDynamic(this, &AEYS_GuestCharacter::OnDialogueFinished);
	DialogueComponent->StartDialogue(myPlayer);
	
	

}
void AEYS_GuestCharacter::CheckOut(AEYS_MyCharacter* myPlayer)
{
	if (!myPlayer) return;
	myPlayer->bIsHaveKey = true;
	myPlayer->MyRoomID = GuestRoomID;
	myPlayer->SetRoot(7);
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(myPlayer->GetController());
	if (PC) PC->SetMoneyWidget(500);
	
	if (UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>())
	{
		TS->UpdateTutorialState(ETutorialStep::CheckoutGuest, ETutorialStep::PutKey);
	}
}

void AEYS_GuestCharacter::SetGuestMesh(USkeletalMesh* GuestSkin)
{
	if (!GuestSkin) return;
	bIsDriving = false;
	ThirdPersonMesh->SetSkeletalMesh(GuestSkin, true);
	if (UClass* AnimBP = GuestSkin->GetPostProcessAnimBlueprint())
	{
		ThirdPersonMesh->SetAnimClass(AnimBP);
	}
}

void AEYS_GuestCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	GetWorld()->GetTimerManager().ClearTimer(OrderTimer);
	GetWorld()->GetTimerManager().ClearTimer(AbandonTimer);

	Super::EndPlay(EndPlayReason);
}