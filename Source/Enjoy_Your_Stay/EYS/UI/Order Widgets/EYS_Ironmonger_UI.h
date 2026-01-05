// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "EYS_Ironmonger_UI.generated.h"


/**
 * 
 */
class AEYS_InteractableActor_WP;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Ironmonger_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Hammer;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Hammer;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Hammer;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Shovel;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Shovel;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Shovel;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_FuelTank;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FuelTank;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_FuelTank;

private:
	UFUNCTION()
	void OnBtnSlotOrder(int32 SlotIndex,int32 Price);

	int32 HammerPrice=250;
	int32 ShovelPrice=300;
	int32 FuelTankPrice=150;

	UFUNCTION()
	void OnSlot0() { OnBtnSlotOrder(0,HammerPrice); }
	UFUNCTION()
	void OnSlot1() { OnBtnSlotOrder(1, ShovelPrice); }
	UFUNCTION()
	void OnSlot2() { OnBtnSlotOrder(2, FuelTankPrice); }
	
	
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AEYS_InteractableActor_WP>> SpawnActor;
	UFUNCTION() void SetEquipmentText();
	//UFUNCTION() void FSpawningActor();
};
