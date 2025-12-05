// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "EYS_EquipmentWheel.generated.h"

/**
 * 
 */


UCLASS()
class ENJOY_YOUR_STAY_API UEYS_EquipmentWheel : public UUserWidget
{
	GENERATED_BODY()

    

protected:

  

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot1;


    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot2;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot3;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot4;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot5;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot6;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot7;

    UPROPERTY(meta = (BindWidget))
    UButton* Btn_Slot8;

    UPROPERTY(meta = (BindWidget))
    UImage* FuelTank_Icon;

    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnBtnSlotHovered(int32 SlotIndex);

    // individual wrappers required for binding (or use lambda in NativeConstruct)
    UFUNCTION()
    void OnSlot1() { OnBtnSlotHovered(0); }
    UFUNCTION()
    void OnSlot2() { OnBtnSlotHovered(1); }
    UFUNCTION()
    void OnSlot3() { OnBtnSlotHovered(2); }
    UFUNCTION()
    void OnSlot4() { OnBtnSlotHovered(3); }
    UFUNCTION()
    void OnSlot5() { OnBtnSlotHovered(4); }
    UFUNCTION()
    void OnSlot6() { OnBtnSlotHovered(5); }
    UFUNCTION()
    void OnSlot7() { OnBtnSlotHovered(6); }
    UFUNCTION()
    void OnSlot8() { OnBtnSlotHovered(7); }

public:
    UFUNCTION() void EnableButtons(int32 Index, bool bIsEnable, ESlateVisibility VisibleIcon);
	
};
