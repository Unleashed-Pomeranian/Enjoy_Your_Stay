
#include "EYS/EYS_MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS/Camera Shake/EYS_MyLegacyCameraShake_Walk.h"
#include "EYS/Camera Shake/EYS_MyLegacyCameraShake_Run.h"
#include "Kismet/GamePlayStatics.h"
#include "Timermanager.h"
#include "EYS/Interactable Actor/EYS_InteractableActor.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"
#include "GameFramework/PlayerController.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/Game Managers/EYS_MissionPostProcessVolume.h"
#include "EYS/Key/EYS_Key.h"
#include "EYS/Game Managers/EYS_UserSettingsSubsystem.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"

// Sets default values
AEYS_MyCharacter::AEYS_MyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
	ChildActorNotebook = CreateDefaultSubobject<UChildActorComponent>(TEXT("Child Actor Notebook"));

	ChildActorNotebook->SetupAttachment(FirstPersonMesh, TEXT("S_Equip_Notebook"));

	MyDialogueComponent = CreateDefaultSubobject<UEYS_QDialoguesListenerComponent>(TEXT("My Dialogue Component"));

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
	MyPC = Cast<AEYS_MyCharacterController>(GetController());
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("InteractUI"), 0.2f, true, false, 0.0f, 0.0f);
	UserSettingsSubsystem = GetGameInstance()->GetSubsystem<UEYS_UserSettingsSubsystem>();
	if (ChildActorNotebook && EquipSocketName.IsValidIndex(1))
	{ChildActorNotebook->AttachToComponent(FirstPersonMesh,FAttachmentTransformRules::SnapToTargetIncludingScale,EquipSocketName[1] );
	}
	if (UEYS_UpgradeSubsystem* UpgradeSys = GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>())
	{
		SprintStaminaMultiplier = UpgradeSys->GetStaminaConsumptionMultiplier();
	}
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
	
		if (IA_eInteract) 	EIC->BindAction(IA_eInteract, ETriggerEvent::Started, this, &AEYS_MyCharacter::Interact);

		if (IA_Action)
		{
			EIC->BindAction(IA_Action, ETriggerEvent::Triggered, this, &AEYS_MyCharacter::Action);
			EIC->BindAction(IA_Action, ETriggerEvent::Started, this, &AEYS_MyCharacter::ActionStart);
			EIC->BindAction(IA_Action, ETriggerEvent::Completed, this, &AEYS_MyCharacter::ActionEnd);
			EIC->BindAction(IA_Action, ETriggerEvent::Canceled, this, &AEYS_MyCharacter::ActionEnd);
		}
		if (IA_Action)
		{
			EIC->BindAction(IA_Action2, ETriggerEvent::Started, this, &AEYS_MyCharacter::Action2);
			EIC->BindAction(IA_Action2, ETriggerEvent::Completed, this, &AEYS_MyCharacter::Action2);
		}
		
		if (IA_Drop) EIC->BindAction(IA_Drop, ETriggerEvent::Completed, this, &AEYS_MyCharacter::DropObject);
			
		if (IA_EquipmentWheel)
		{
			EIC->BindAction(IA_EquipmentWheel, ETriggerEvent::Started, this,&AEYS_MyCharacter::OpenEquipmentWidget);
			EIC->BindAction(IA_EquipmentWheel, ETriggerEvent::Completed, this, &AEYS_MyCharacter::CloseEquipmentWidget);
		}
		
		if (IA_Notebook)
		{
			EIC->BindAction(IA_Notebook, ETriggerEvent::Started, this, &AEYS_MyCharacter::OpenNotebook);
			EIC->BindAction(IA_Notebook, ETriggerEvent::Completed, this, &AEYS_MyCharacter::CloseNotebook);
		}

		if (IA_Mission)
		{
			EIC->BindAction(IA_Mission, ETriggerEvent::Started, this, &AEYS_MyCharacter::EnableMission);
			EIC->BindAction(IA_Mission, ETriggerEvent::Completed, this, &AEYS_MyCharacter::DisableMission);
		}

		if (IA_Pause)  EIC->BindAction(IA_Pause, ETriggerEvent::Started, this, &AEYS_MyCharacter::RequestPauseGame);
		
		if (IA_Sneak)
		{
			EIC->BindAction(IA_Sneak, ETriggerEvent::Started, this, &AEYS_MyCharacter::StartSneak);
			EIC->BindAction(IA_Sneak, ETriggerEvent::Completed, this, &AEYS_MyCharacter::StopSneak);
		}
	}

}

void AEYS_MyCharacter::SetRoot(int32 Value)
{
	PoseNum = Value;
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

		FirstPersonMesh->SetRelativeLocation(FVector(-10.0f, 0.0f, -70.0f));
		FirstPersonMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	
	
	SetEquipmentMesh(Value);


}

void AEYS_MyCharacter::SetRootBP()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "imhere");
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
		
			
			
			float StaminaDropRate = 0.12f * SprintStaminaMultiplier;
			Stamina = FMath::Clamp(Stamina - StaminaDropRate, 0.0f, 100.0f);
			UKismetSystemLibrary::K2_PauseTimer(this, TEXT("StaminaRecovery"));
			MyPC->OnStaminaChanged.Broadcast(Stamina, bCanSprinting);

			
			if (UserSettingsSubsystem)
			{
				float Scale = UserSettingsSubsystem->CameraShakeIntensity;
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(UEYS_MyLegacyCameraShake_Run::StaticClass(),Scale);

			}
		}

		else
		{
			if (UserSettingsSubsystem)
			{
				float Scale = UserSettingsSubsystem->CameraShakeIntensity;
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(UEYS_MyLegacyCameraShake_Walk::StaticClass(), Scale);

			}

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
	if (UserSettingsSubsystem) {sense = UserSettingsSubsystem->MouseSensitivity;}
		
	
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
void AEYS_MyCharacter::StartSneak(const FInputActionValue& Value)
{
	bIsSneaking = true;
	
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AEYS_MyCharacter::StopSneak(const FInputActionValue& Value)
{
	bIsSneaking = false;

	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
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

void AEYS_MyCharacter::DropObject(const FInputActionValue& Value)
{
	if (HeldEquipment)
	{
		HeldEquipment->DetachActor();
		HeldEquipment = nullptr;
		bIsHandsFull = false;
		SetRoot(0);
		
	}
}

void AEYS_MyCharacter::DetachHeavyEquipment()
{
	if (HeldEquipment)
	{
		HeldEquipment = nullptr;
		bIsHandsFull = false;
		SetRoot(0);
	}

}


void AEYS_MyCharacter::StaminaRecovery()
{
	Stamina = FMath::Clamp(Stamina + 1.0f, 0.0f, 100.0f);
	
	if (Stamina == 100)
	{
		bCanSprinting = true;
		UKismetSystemLibrary::K2_ClearTimer(this, TEXT("StaminaRecovery"));
	}
	MyPC->OnStaminaChanged.Broadcast(Stamina,bCanSprinting);
}

void AEYS_MyCharacter::OpenNotebook(const FInputActionValue& Value)
{
	
	ChildActorNotebook->SetVisibility(true);
	LastPoseNum = PoseNum;
	SetRoot(1);
}
void AEYS_MyCharacter::CloseNotebook(const FInputActionValue& Value)
{
	ChildActorNotebook->SetVisibility(false);
	SetRoot(LastPoseNum);
}
void AEYS_MyCharacter::EnableMission(const FInputActionValue& Value)
{
	if(!MissionPPV) MissionPPV = Cast<AEYS_MissionPostProcessVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MissionPostProcessVolume::StaticClass()));
	
	if (MissionPPV)
	{
		MissionPPV->SetMissionPPEnabled(true);
	}
}

void AEYS_MyCharacter::DisableMission(const FInputActionValue& Value)
{
	if (MissionPPV)
	{	
		MissionPPV->SetMissionPPEnabled(false);
	}
}

void AEYS_MyCharacter::RequestPauseGame(const FInputActionValue& Value)
{
	if (MyPC) MyPC->PauseGame();
}




void AEYS_MyCharacter::OpenEquipmentWidget(const FInputActionValue& Value)
{
	if (!bIsHandsFull&&!bIsHaveKey)
	{
		if (!(GetCharacterMovement()->IsFalling()))
		{
			if (MyPC)
			{
				MyPC->OpenEquipmentWidget();
			}
		}
	}
}

void AEYS_MyCharacter::CloseEquipmentWidget(const FInputActionValue& Value)
{

	if (!bIsHandsFull && !bIsHaveKey)
	{
		if (MyPC)
		{

			MyPC->CloseEquipmentWidget();
		}
		
		SetRoot(LastPoseNum);
	}
}






void AEYS_MyCharacter::InteractUI()
{
	FHitResult Hit;
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetComponentRotation().Vector() * 200.f;
	UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, TArray<AActor*>()
		, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, 1.0f);
	AActor* CurrentHitActor = Hit.GetActor();
	
		if (CurrentHitActor &&Hit.GetActor()->GetClass()->ImplementsInterface(UEYS_InteractInterface::StaticClass()))
		{
			if (CurrentHitActor != LastHitActor)
			{
				// Eski objenin odağını kapat
				if (LastHitActor)
				{
					IEYS_InteractInterface::Execute_InteractUI(LastHitActor, this, false);
				}

				if (MyPC)
				{
					MyPC->CloseInteractionWidget();
				}
				IEYS_InteractInterface::Execute_InteractUI(CurrentHitActor, this, true);
				LastHitActor = CurrentHitActor;
			}
			else
			{
				IEYS_InteractInterface::Execute_InteractUI(CurrentHitActor, this, true);
			}
		}
		else
		{
			if (LastHitActor)
			{
				IEYS_InteractInterface::Execute_InteractUI(LastHitActor, this, false);
				LastHitActor = nullptr;
			}
			MyPC->CloseInteractionWidget();
		}
		
	
}

void AEYS_MyCharacter::Interact(const FInputActionValue& Value)
{
if (AActor* Target = GetInteractActor(200.0f))
    {
        if (Target->GetClass()->ImplementsInterface(UEYS_InteractInterface::StaticClass()))
        {
            IEYS_InteractInterface::Execute_eInteract(Target, this);
        }
    }
		
}

void AEYS_MyCharacter::Action(const FInputActionValue& Value)
{

	bIsAction = true;
	if (AActor* Target = GetInteractActor(200.0f))
	{
		if (Target->GetClass()->ImplementsInterface(UEYS_InteractInterface::StaticClass()))
		{
			IEYS_InteractInterface::Execute_aInteract(Target, this, PoseNum);
		}
	}
}

void AEYS_MyCharacter::Action2(const FInputActionValue& Value)
{
	AEYS_InteractableActor* Item =
		Cast<AEYS_InteractableActor>(ChildActor->GetChildActor());
	if (Item)
	{
		Item->FSecondAction(this);
	}

	
}
void AEYS_MyCharacter::ActionStart(const FInputActionValue& Value)
{
	AEYS_InteractableActor* Item =
		Cast<AEYS_InteractableActor>(ChildActor->GetChildActor());
	if (Item)
	{
		Item->FActionStart(this);
	}

	
}

void AEYS_MyCharacter::ActionEnd(const FInputActionValue& Value)
{
	bIsAction = false;
	
}



AActor* AEYS_MyCharacter::GetInteractActor(float Distance)
{
	FHitResult Hit;
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetComponentRotation().Vector() * Distance;


	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	bool bHit = UKismetSystemLibrary::LineTraceSingle(
		this, Start, End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, ActorsToIgnore, 
		EDrawDebugTrace::None, Hit, true
	);

	if (bHit && Hit.GetActor())
	{
		return Hit.GetActor();
	}
	return nullptr;
}

/*void AEYS_MyCharacter::Action_MouseTrace()
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
					
					
					
				}

			}
		}
	}
 }*/

void AEYS_MyCharacter::PlayMontage(int32 MontageIndex)
{
	if (UAnimInstance* AnimInst = FirstPersonMesh->GetAnimInstance())
	{

		if (PoseNum == 6)
		{

			AnimInst->Montage_Play(MyCharacterMontages[MontageIndex]);
		}
		else
		{
		
			AnimInst->Montage_Play(MyCharacterMontages[MontageIndex]);
		
			if (MontageIndex == 0)
				SetRoot(0);
		}
	
		
	}


}



void AEYS_MyCharacter::SetEquipmentMesh(int32 MeshValue)
{

	if(ChildActor)
	{
		
		
			if (MeshValue==7)
			{
				ChildActor->SetChildActorClass(TSubclassOf<AActor>(KeyActor));
		
			}
			else
			{
				if (InteractableActors.IsValidIndex(MeshValue))
				{
					ChildActor->SetChildActorClass(TSubclassOf<AActor>(InteractableActors[MeshValue]));
					
				}
			}
			ChildActor->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, EquipSocketName[MeshValue]);
		
	}
	
	
}


