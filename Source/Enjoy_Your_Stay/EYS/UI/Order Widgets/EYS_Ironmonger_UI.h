// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
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
	UButton* Button_Shovel;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Shovel;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_FuelTank;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FuelTank;

private:
	UFUNCTION()
	void OnBtnSlotOrder(int32 SlotIndex);


	UFUNCTION()
	void OnSlot0() { OnBtnSlotOrder(0); }
	UFUNCTION()
	void OnSlot1() { OnBtnSlotOrder(1); }
	UFUNCTION()
	void OnSlot2() { OnBtnSlotOrder(2); }
	
	
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AEYS_InteractableActor_WP>> SpawnActor;

	//UFUNCTION() void FSpawningActor();
};
