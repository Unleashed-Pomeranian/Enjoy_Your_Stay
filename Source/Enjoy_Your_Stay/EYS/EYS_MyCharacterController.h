// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EYS_MyCharacterController.generated.h"


class UInputMappingContext;
class UUserWidget;
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

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_EquipmentWheel> EquipmentWheelClass;

	/** Oluşturulmuş instance */
	UPROPERTY()
	UEYS_EquipmentWheel* EquipmentWheelInstance = nullptr;


public:
	UFUNCTION() void OpenEquipmentWidget();
	UFUNCTION() void CloseEquipmentWidget();
};
