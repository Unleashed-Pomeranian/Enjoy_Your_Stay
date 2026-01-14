// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "EYS/NPC/EYS_GuestAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/EYS_MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_FoodBag.h"
#include "EYS/Interactable Actor/EYS_Phone.h"


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
	CachedAIController->OnAIMoveComplete.AddUObject(this, &AEYS_GuestCharacter::HandleMoveCompleted);
	
	MoveTo(MainLock, 20);
}

// Called every frame
void AEYS_GuestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEYS_GuestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEYS_GuestCharacter::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	Interact(myPlayer);
}
void AEYS_GuestCharacter::HandleMoveCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("NPC Move Completed → Interaction Enabled"));
	bCanInteract = true;
	
	
}

void AEYS_GuestCharacter::Interact(AEYS_MyCharacter* myPlayer)
{
	
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "bCanIsqdsdnteract");
	if (bCanInteract)
	{
		if (bIsOrderFood)
		{
			TakeFood(myPlayer);
		}
		else
		{
			if (!bisDialogueEnd)
			{
				GuestStartDialogue(myPlayer);
			}
			else
			{
				if (!bIsHaveRoom)
				{
					if (myPlayer->bIsHaveKey)
						TakeKey(myPlayer);
					else
						GuestStartDialogue(myPlayer);
				}

			}
		}


	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "bCanInteract");
}

void AEYS_GuestCharacter::MoveTo(FVector Target, float AccceptanceRadius)
{
	CachedAIController->MoveToPoint(Target,AccceptanceRadius);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "NOVEE");
}

void AEYS_GuestCharacter::TakeKey(AEYS_MyCharacter* myPlayer)
{
	myPlayer->PoseNum = 0;
	myPlayer->bIsHaveKey = false;
	myPlayer->SetRoot();
	MainLock = myPlayer->RoomLock;
	MoveTo(MainLock, 100.0f);
	bCanInteract = false;
	DialogueNum++;
	RoomNumber = myPlayer->RoomNumb;
	bIsHaveRoom = true;
}
void AEYS_GuestCharacter::destroyme()
{	
	bisDialogueEnd = true;
	if (DialogueNum == 1)
	{
		MoveTo(MainLock, 50);
		OrderFood();
	}
	if(DialogueNum == 2|| DialogueNum == 3)
	{
		MoveTo(MainLock, 50);
	}
}

void AEYS_GuestCharacter::OrderFood()
{
	FoodType= static_cast<EFoodType>(FMath::RandRange(0, static_cast<int32>(EFoodType::Count) - 1));
	FString FoodString = StaticEnum<EFoodType>()->GetDisplayNameTextByValue(static_cast<int64>(FoodType)).ToString();
	AEYS_Phone* Phone = Cast<AEYS_Phone>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Phone::StaticClass()));
	Phone->SetGuestUI(FoodString, RoomNumber);
	bisDialogueEnd = true;
	bIsOrderFood = true;

}

void AEYS_GuestCharacter::TakeFood(AEYS_MyCharacter* myPlayer)
{
	if (myPlayer->HeldEquipment && myPlayer->HeldEquipment->IsA(AEYS_FoodBag::StaticClass()))
	{
		AEYS_FoodBag* FoodBag = Cast<AEYS_FoodBag>(myPlayer->HeldEquipment);
		if(FoodBag->FoodType==FoodType)
		{
			FoodBag->AttachToComponent(ThirdPersonMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Bag");
			myPlayer->HeldEquipment = nullptr;
			DialogueNum = 2;
			bIsOrderFood = false;
		}
		else
		{
			DialogueNum = 3;
			
		}
		bIsOrderFood = false;
		GuestStartDialogue(myPlayer);
	}
}






void AEYS_GuestCharacter::GuestStartDialogue(AEYS_MyCharacter* myPlayer)
{
	FVector NPC_Loc = GetActorLocation();
	FVector Player_Loc = myPlayer->GetActorLocation();
	Player_Loc.Z = NPC_Loc.Z;
	FRotator LookAtRot = (Player_Loc - NPC_Loc).Rotation();

	SetActorRotation(LookAtRot);

	DialogueComponent->StartDialogue(myPlayer, DialogueNum);
	myPlayer->MyDialogueComponent->GetOnDialogueEndDelegate().AddDynamic(this, &AEYS_GuestCharacter::destroyme);

}