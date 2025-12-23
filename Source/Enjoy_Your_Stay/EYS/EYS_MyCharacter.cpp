
#include "EYS/EYS_MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS/Camera Shake/EYS_MyLegacyCameraShake_Walk.h"
#include "EYS/Camera Shake/EYS_MyLegacyCameraShake_Run.h"
#include "Kismet/GamePlayStatics.h"
#include "Timermanager.h"
#include "EYS/Interactable Actor/EYS_InteractableActor.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "GameFramework/PlayerController.h"
#include "EYS/EYS_MyCharacterController.h"


// Sets default values
AEYS_MyCharacter::AEYS_MyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(GetCapsuleComponent());
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.F, 0.f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	ChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Child Actor"));
	ChildActor->SetupAttachment(FirstPersonMesh, TEXT("RightHand"));

	UCharacterMovementComponent* moveComp = GetCharacterMovement();
	moveComp->bOrientRotationToMovement = false;
	moveComp->RotationRate = FRotator(0.f, 540.f, 0.f);
	moveComp->MaxWalkSpeed = walkSpeed;

	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;


}

// Called when the game starts or when spawned
void AEYS_MyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsys =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
			{
				if (DefaultMapping)
				{
					Subsys->AddMappingContext(DefaultMapping, 0);
					
				}
			}
		}
	}

	MyPC = Cast<AEYS_MyCharacterController>(GetController());
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("InteractUI"), 0.2f, true, false, 0.0f, 0.0f);
}

// Called every frame
void AEYS_MyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEYS_MyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Move)
			EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AEYS_MyCharacter::Move);

		if (IA_Look)
			EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AEYS_MyCharacter::Look);
		if (IA_Jump)
		{
			EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AEYS_MyCharacter::StartJump);
			EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AEYS_MyCharacter::StopJump);
		}

		if (IA_Sprint)
		{
			EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AEYS_MyCharacter::StartSprint);
			EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AEYS_MyCharacter::StopSprint);
		}
	
		EIC->BindAction(IA_eInteract, ETriggerEvent::Started, this, &AEYS_MyCharacter::Interact);
		EIC->BindAction(IA_Action, ETriggerEvent::Triggered, this, & AEYS_MyCharacter::Action);
		EIC->BindAction(IA_Action, ETriggerEvent::Started, this, &AEYS_MyCharacter::ActionStart);
		EIC->BindAction(IA_Action, ETriggerEvent::Completed, this, &AEYS_MyCharacter::ActionEnd);

		
			
			if (IA_EquipmentWheel)
			{
				EIC->BindAction(IA_EquipmentWheel, ETriggerEvent::Started, this,&AEYS_MyCharacter::OpenEquipmentWidget);
				EIC->BindAction(IA_EquipmentWheel, ETriggerEvent::Completed, this, &AEYS_MyCharacter::CloseEquipmentWidget);
			}
		

			
		
	}

}

void AEYS_MyCharacter::SetRoot()
{
	if (PoseNum != 0)
	{
		FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, true);
		FirstPersonMesh->AttachToComponent(FirstPersonCamera, Rules);

		FirstPersonMesh->SetRelativeLocation(FVector(-10.0f, 0.0f, -144.0f));
		FirstPersonMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	else
	{
		FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, true);
		FirstPersonMesh->AttachToComponent(GetCapsuleComponent(), Rules);

		FirstPersonMesh->SetRelativeLocation(FVector(-10.0f, 0.0f, -80.0f));
		FirstPersonMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	if (bIsHaveKey&&PoseNum==2)
	SetEquipmentMesh(6);
	else
	SetEquipmentMesh(PoseNum);


}

void AEYS_MyCharacter::SetRootBP()
{
	FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, true);
	FirstPersonMesh->AttachToComponent(FirstPersonCamera, Rules);

	FirstPersonMesh->SetRelativeLocation(FVector(-10.0f, 0.0f, -144.0f));
	FirstPersonMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}



void AEYS_MyCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D input = Value.Get<FVector2D>();
	if (!Controller) return;

	const FRotator controlRot = Controller->GetControlRotation();
	const FRotator yawRot(0.f, controlRot.Yaw, 0.f);

	const FVector forwardDir = FRotationMatrix(yawRot).GetUnitAxis(EAxis::X);
	const FVector rightDir = FRotationMatrix(yawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardDir, input.Y);
	AddMovementInput(rightDir, input.X);

	if (GetVelocity().Size()>0)
	{
		
		if (bIsSprinting && bCanSprinting)
		{

			Stamina = FMath::Clamp(Stamina - 0.2f, 0.0f, 100.0f);
			UKismetSystemLibrary::K2_PauseTimer(this, TEXT("StaminaRecovery"));
			MyPC->SetStaminaWidget(Stamina/100);


			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(UEYS_MyLegacyCameraShake_Run::StaticClass());
		}

		else
		{
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(UEYS_MyLegacyCameraShake_Walk::StaticClass());
		}
		if (Stamina <= 0)
		{
			if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
				MoveComp->MaxWalkSpeed = walkSpeed;
			bCanSprinting = false;
		}

	}
}

void AEYS_MyCharacter::Look(const FInputActionValue& Value)
{
	
	const FVector2D lookAxis = Value.Get<FVector2D>();
	float sense = 0.5f;
	AddControllerYawInput(lookAxis.X * sense);
	AddControllerPitchInput(lookAxis.Y * sense);

}

void AEYS_MyCharacter::StartJump(const FInputActionValue& Value)
{
	Jump();
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(UEYS_MyLegacyCameraShake_Run::StaticClass());
}

void AEYS_MyCharacter::StopJump(const FInputActionValue& Value)
{
	
}

void AEYS_MyCharacter::StartSprint(const FInputActionValue& Value)
{
	if (bCanSprinting)
	{
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
			MoveComp->MaxWalkSpeed = sprintSpeed;

		bIsSprinting = true;
	}
}

void AEYS_MyCharacter::StopSprint(const FInputActionValue& Value)
{
    
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		MoveComp->MaxWalkSpeed = walkSpeed;
	  bIsSprinting = false;
	  UKismetSystemLibrary::K2_SetTimer(this, TEXT("StaminaRecovery"), 0.1f, true, false, 0.0f, 0.0f);
	
}



void AEYS_MyCharacter::StaminaRecovery()
{
	Stamina = FMath::Clamp(Stamina + 1.0f, 0.0f, 100.0f);
	MyPC->SetStaminaWidget(Stamina / 100);
	if (Stamina == 100)
	{
		MyPC->CloseStaminaWidget();
		bCanSprinting = true;
		UKismetSystemLibrary::K2_PauseTimer(this, TEXT("StaminaRecovery"));
	}
	
}


void AEYS_MyCharacter::OpenEquipmentWidget(const FInputActionValue& Value)
{
	if (!(GetCharacterMovement()->IsFalling()))
	{
		if (MyPC)
		{
			GetCharacterMovement()->DisableMovement();
			MyPC->OpenEquipmentWidget();
		}
	}
}

void AEYS_MyCharacter::CloseEquipmentWidget(const FInputActionValue& Value)
{
	if (MyPC)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		MyPC->CloseEquipmentWidget();
	}
	PoseNum = LastPoseNum;
	SetRoot();
}






void AEYS_MyCharacter::InteractUI()
{
	FHitResult* Hit = new FHitResult();
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetComponentRotation().Vector() * 500.f;
	UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, TArray<AActor*>()
		, EDrawDebugTrace::None, *Hit, true, FLinearColor::Red, FLinearColor::Green, 1.0f);
	if (Hit->GetActor() != nullptr)
	{
		if (Hit->GetActor()->GetClass()->ImplementsInterface(UEYS_InteractInterface::StaticClass()))
		{
			//Cast<IEYS_InteractInterface>(Hit->GetActor())->mInteract(this);
			IEYS_InteractInterface::Execute_InteractUI(Hit->GetActor(), this);

	
		}
		else
			MyPC->CloseInteractionWidget();
	
	}

	else
		MyPC->CloseInteractionWidget();
	
}

void AEYS_MyCharacter::Interact(const FInputActionValue& Value)
{




	FHitResult* Hit = new FHitResult();
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetComponentRotation().Vector() * 500.f;
	UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, TArray<AActor*>()
		, EDrawDebugTrace::None, *Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
	if (Hit->GetActor() != nullptr)
	{
		if (Hit->GetActor()->GetClass()->ImplementsInterface(UEYS_InteractInterface::StaticClass()))
		{
			//Cast<IEYS_InteractInterface>(Hit->GetActor())->mInteract(this);
			IEYS_InteractInterface::Execute_eInteract(Hit->GetActor(), this);

		
		}
		
	}

	
		

}

void AEYS_MyCharacter::Action(const FInputActionValue& Value)
{
	if (bIsKeyMode)
		Action_MouseTrace();
	else
		Action_ForwardTrace();
}

void AEYS_MyCharacter::ActionStart(const FInputActionValue& Value)
{
	AEYS_InteractableActor* Item =
		Cast<AEYS_InteractableActor>(ChildActor->GetChildActor());
	if (Item)
	{
		Item->FActionStart();
	}

	ActionNum++;
	
}

void AEYS_MyCharacter::ActionEnd(const FInputActionValue& Value)
{
	bIsAction = false;
	
}

void AEYS_MyCharacter::Action_ForwardTrace()
{
	bIsAction = true;
	FHitResult* Hit = new FHitResult();
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetComponentRotation().Vector() * 500.f;
	UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, TArray<AActor*>()
		, EDrawDebugTrace::None, *Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
	if (Hit->GetActor() != nullptr)
	{
		if (Hit->GetActor()->GetClass()->ImplementsInterface(UEYS_InteractInterface::StaticClass()))
		{
			//Cast<IEYS_InteractInterface>(Hit->GetActor())->mInteract(this);
			IEYS_InteractInterface::Execute_aInteract(Hit->GetActor(), this,PoseNum);
		
		}
	}
}

void AEYS_MyCharacter::Action_MouseTrace()
{
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		
		FHitResult* Hit = new FHitResult();
		FVector WorldLocation;
		FVector WorldDirection;
		
		bool bDeprojectSuccess = PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		FVector Start = WorldLocation;
		
		float TraceDistance = 150.0f;
		FVector End = Start + (WorldDirection * TraceDistance);
		
		UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, TArray<AActor*>()
			, EDrawDebugTrace::None, *Hit, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		if (Hit->GetActor() != nullptr)
		{
			;
			if (Hit->GetActor()->GetClass()->ImplementsInterface(UEYS_InteractInterface::StaticClass()))
			{
			
				//Cast<IEYS_InteractInterface>(Hit->GetActor())->mInteract(this);
				IEYS_InteractInterface::Execute_aInteract(Hit->GetActor(), this,PoseNum);
				if (bIsHaveKey)
				{
					PoseNum = 2;
					SetRoot();
					
				}

			}
		}
	}
 }

void AEYS_MyCharacter::PlayMontage(int32 MontageIndex)
{
	if (UAnimInstance* AnimInst = FirstPersonMesh->GetAnimInstance())
	{
	
		AnimInst->Montage_Play(MyCharacterMontages[0]);
		PoseNum = 0;
		SetRoot();
		
	}


}



void AEYS_MyCharacter::SetEquipmentMesh(int32 MeshValue)
{

	if(ChildActor)
	{
		if (MeshValue==1)
		{
			ChildActor->SetChildActorClass(TSubclassOf<AActor>(NotebookActor));
		}

		else
		{
			ChildActor->SetChildActorClass(TSubclassOf<AActor>(InteractableActors[MeshValue]));
		}

	}
	
}

