// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EYS_MyCharacterController.generated.h"



class UInputMappingContext;
class UUserWidget;
class AEYS_MyCharacter;
class UEYS_MyCharacter_UI;
class UEYS_EquipmentWheel;

 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged,float,NewValue,bool,bIsRecovery);

UCLASS(abstract)
class ENJOY_YOUR_STAY_API AEYS_MyCharacterController : public APlayerController
{
	GENERATED_BODY()
	


public:
	AEYS_MyCharacterController();
	
protected:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_EquipmentWheel> EquipmentWheelClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_MyCharacter_UI> MYCharacterUIClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowAbstract = "true"))
	AEYS_MyCharacter* OwnerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMapping;
	
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	


public:
	UFUNCTION() void OpenEquipmentWidget();
	UFUNCTION() void CloseEquipmentWidget();
	
	UFUNCTION() void SetMoneyWidget(int32 AddValue);
	UFUNCTION(BlueprintCallable) void SetInteractionWidget(FString InterctionText);
	UFUNCTION() void SetHourWidget(float TimeofDay);
	UFUNCTION() void CloseInteractionWidget();
	UFUNCTION(BlueprintCallable) void MobilizeCharacter(bool bLookInput,bool BIsInputModeUI, bool ShowCursor);
	UFUNCTION(BlueprintCallable) void StopPlayer();
	UFUNCTION() void SetCharacterPositon(FVector ActorLocation,float LocationX,float LocationY,FRotator Rotation);
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Money;

	UFUNCTION() void PauseGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEYS_EquipmentWheel* EquipmentWheelInstance = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	UEYS_MyCharacter_UI* MyCharacterUIInstance = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	class UUserWidget* PauseWidgetInstance = nullptr;

	FOnStaminaChanged OnStaminaChanged;
	
};
