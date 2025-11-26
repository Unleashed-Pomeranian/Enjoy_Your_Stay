#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EYS_MyCharacter.generated.h"


class UCameraComponent;
class UInputMappingContext;
class UInputAction;


UCLASS(Blueprintable)
class ENJOY_YOUR_STAY_API AEYS_MyCharacter : public ACharacter
{
	GENERATED_BODY()
	
	
 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;
UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMapping;

public:
	AEYS_MyCharacter();
    virtual void Tick(float DeltaTime) override;
   

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetRoot();
	bool bIsSprinting = false;
	bool bCanSprinting = true;
	float Stamina=100.0f;
	float StaminaRecoveryValue = 0.2f;
	
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
	UInputAction* IA_Action;


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Main;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Mission;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Hammer;



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
	UFUNCTION() void StaminaRecovery();
	
	UFUNCTION() void SetMainPose(const FInputActionValue& Value);
	UFUNCTION() void OpenMissionList(const FInputActionValue& Value);
	UFUNCTION() void CloseMissionList(const FInputActionValue& Value);
	UFUNCTION() void EquipHammer(const FInputActionValue& Value);
	UFUNCTION() void Interact(const FInputActionValue& Value);
	UFUNCTION() void Action(const FInputActionValue& Value);
	UFUNCTION() void ActionEnd(const FInputActionValue& Value);
	

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
	int32 PoseNum = 0, LastPoseNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
	bool bIsAction=false;
};
