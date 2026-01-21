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
class AEYS_HeavyEquipmentBase;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Ironmonger_UI : public UUserWidget
{
	GENERATED_BODY()

	

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CoalSack;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CoalSack;


	UPROPERTY(meta = (BindWidget))
	UButton* Button_FuelTank;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FuelTank;

private:
	UFUNCTION()
	void OnBtnSlotOrder(int32 SlotIndex,int32 Price);

	int32 FuelTankPrice = 250;
	int32 CoalSackPrice=150;
	

	UFUNCTION()
	void OnSlot0() { OnBtnSlotOrder(0,FuelTankPrice); }
	UFUNCTION()
	void OnSlot1() { OnBtnSlotOrder(1, CoalSackPrice); }
	
	
	
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AEYS_HeavyEquipmentBase>> SpawnActor;
	UFUNCTION() void SetEquipmentText();
	//UFUNCTION() void FSpawningActor();
};
