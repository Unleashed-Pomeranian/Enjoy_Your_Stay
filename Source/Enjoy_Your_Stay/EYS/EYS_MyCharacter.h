#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Animation/AnimMontage.h"
#include "EYS/EYS_QDialoguesListenerComponent.h"
#include "EYS_MyCharacter.generated.h"
 


class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AEYS_Notebook;
class AEYS_MyCharacterController;
class AEYS_InteractableActor;
class AEYS_HeavyEquipmentBase;
class AEYS_MissionPostProcessVolume;
class AEYS_Key;
UCLASS(Blueprintable)
class ENJOY_YOUR_STAY_API AEYS_MyCharacter : public ACharacter
{
	GENERATED_BODY()
	

 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildActorNotebook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EYS|Interact")
	TArray<TSubclassOf<AEYS_InteractableActor>> InteractableActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EYS|Interact")
	TSubclassOf<AEYS_Key> KeyActor;
	UPROPERTY()
	AEYS_MyCharacterController* MyPC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UEYS_QDialoguesListenerComponent* MyDialogueComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	AEYS_MissionPostProcessVolume* MissionPPV = nullptr;
public:
	AEYS_MyCharacter();
    virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Action_ForwardTrace();
	void Action_MouseTrace();
	bool bIsSprinting = false;
	bool bCanSprinting = true;
	float Stamina=100.0f;
	float StaminaRecoveryValue = 0.2f;
	class UEYS_UserSettingsSubsystem* UserSettingsSubsystem;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Sprint;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_eInteract;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Drop;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Action;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Action2;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_EquipmentWheel;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Notebook;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Mission;

	


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float walkSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float sprintSpeed = 600.0f;
	

	UFUNCTION() void Move(const FInputActionValue& Value);
	UFUNCTION() void Look(const FInputActionValue& Value);
	UFUNCTION() void StartJump(const FInputActionValue& Value);
	UFUNCTION() void StopJump(const FInputActionValue& Value);
	UFUNCTION() void StartSprint(const FInputActionValue& Value);
	UFUNCTION() void StopSprint(const FInputActionValue& Value);
	UFUNCTION() void DropObject(const FInputActionValue& Value);
	UFUNCTION() void StaminaRecovery();
	UFUNCTION() void OpenNotebook(const FInputActionValue& Value);
	UFUNCTION() void CloseNotebook(const FInputActionValue& Value);
	

	UFUNCTION() void OpenEquipmentWidget(const FInputActionValue& Value);
	UFUNCTION() void CloseEquipmentWidget(const FInputActionValue& Value);

	UFUNCTION() void InteractUI();
	UFUNCTION() void Interact(const FInputActionValue& Value);
	UFUNCTION() void Action(const FInputActionValue& Value);
	UFUNCTION() void Action2(const FInputActionValue& Value);
	UFUNCTION() void ActionStart(const FInputActionValue& Value);
	UFUNCTION() void ActionEnd(const FInputActionValue& Value);
	UFUNCTION() void EnableMission(const FInputActionValue& Value);
	UFUNCTION() void DisableMission(const FInputActionValue& Value);
	

	

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
	int32 PoseNum = 0, LastPoseNum;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
	bool bIsAction=false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
	int32 ActionNum = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	bool bIsKeyMode = false;
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	bool bIsHaveKey = false;
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	FVector RoomLock;
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	int32 RoomNumb;
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	bool bIsDoorLocked = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsPhoneMode = false;
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	bool bIsHandsFull = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsCoalMode= false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EYS|Animation")
	TArray<UAnimMontage*> MyCharacterMontages;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AEYS_HeavyEquipmentBase> HeldEquipment;
	


public:
	UFUNCTION(BlueprintCallable) virtual void SetRoot();
	UFUNCTION(BlueprintCallable) virtual void SetRootBP();
	UFUNCTION() virtual void PlayMontage(int32 MontageIndex);

	UFUNCTION() void SetEquipmentMesh(int32 MeshValue);
};
