// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "EYS_Supermarket_UI.generated.h"

/**
 * 
 */
class AEYS_FoodBox;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Supermarket_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Pirozhki;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Pirozhki;


	UPROPERTY(meta = (BindWidget))
	UButton* Button_Vareniki;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Vareniki;


	UPROPERTY(meta = (BindWidget))
	UButton* Button_Kasha;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Kasha;


	UPROPERTY(meta = (BindWidget))
	UButton* Button_Medovik;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Medovik;


private:
	UFUNCTION()
	void OnBtnSlotOrder(int32 SlotIndex, int32 Price);

	int32 PirozhkiPrice = 250;
	int32 VarenikiPrice = 300;
	int32 KashaPrice = 150;
	int32 MedovikPrice = 150;

	UFUNCTION()
	void OnSlot0() { OnBtnSlotOrder(0, PirozhkiPrice); }
	UFUNCTION()
	void OnSlot1() { OnBtnSlotOrder(1, VarenikiPrice); }
	UFUNCTION()
	void OnSlot2() { OnBtnSlotOrder(2, KashaPrice); }
	UFUNCTION()
	void OnSlot3() { OnBtnSlotOrder(3, MedovikPrice); }

protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AEYS_FoodBox>> FSpawnActor;
	UFUNCTION() void SetFoodBoxText();
	
};
