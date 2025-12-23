// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EYS_MyCharacterController.generated.h"


class UInputMappingContext;
class UUserWidget;
class UEYS_MyCharacter_UI;
class UEYS_EquipmentWheel;

 
UCLASS(abstract)
class ENJOY_YOUR_STAY_API AEYS_MyCharacterController : public APlayerController
{
	GENERATED_BODY()
	


public:
	AEYS_MyCharacterController();
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;


	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_EquipmentWheel> EquipmentWheelClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_MyCharacter_UI> MYCharacterUIClass;
	

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	


public:
	UFUNCTION() void OpenEquipmentWidget();
	UFUNCTION() void CloseEquipmentWidget();
	UFUNCTION() void SetStaminaWidget(float StaminaValue);
	UFUNCTION() void CloseStaminaWidget();
	UFUNCTION() void SetInteractionWidget(FString InterctionText);
	UFUNCTION() void CloseInteractionWidget();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEYS_EquipmentWheel* EquipmentWheelInstance = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEYS_MyCharacter_UI* MyCharacterUIInstance = nullptr;
};
