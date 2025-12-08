// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_GuestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "EYS/NPC/EYS_GuestAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/EYS_MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEYS_GuestCharacter::AEYS_GuestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ThirdPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Third Person Mesh"));
	ThirdPersonMesh->SetupAttachment(GetCapsuleComponent());

	AIControllerClass = AEYS_GuestAIController::StaticClass();

}

// Called when the game starts or when spawned
void AEYS_GuestCharacter::BeginPlay()
{
	Super::BeginPlay();
	CachedAIController = Cast<AEYS_GuestAIController>(GetController());
	CachedAIController->OnAIMoveComplete.AddUObject(this, &AEYS_GuestCharacter::HandleMoveCompleted);
	CachedAIController->MoveToPoint(FVector::ZeroVector,200.0f);
	
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "HandleMoveCompleted");
}

void AEYS_GuestCharacter::Interact(AEYS_MyCharacter* myPlayer)
{
	CachedAIController->MoveToPoint(FVector::ZeroVector, 500.0f);

	if (bCanInteract && !bisDialogueEnd)
	{
		StartDialogue(myPlayer);
		DialogueNum += 1;
	}

	if (bCanInteract&&myPlayer->bIsHaveKey&&bisDialogueEnd)
	{
	   
		myPlayer->PoseNum = 0;
		myPlayer->bIsHaveKey = false;
		myPlayer->SetRoot();
		MainLock = myPlayer->RoomLock;
		MoveTo(MainLock, 100.0f);
		bCanInteract = false;
	  
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "bCanInteract");
}

void AEYS_GuestCharacter::MoveTo(FVector Target, float AccceptanceRadius)
{
	CachedAIController->MoveToPoint(Target,AccceptanceRadius);
}



void AEYS_GuestCharacter::StartDialogue_Implementation(AEYS_MyCharacter* myPlayer)
{
}