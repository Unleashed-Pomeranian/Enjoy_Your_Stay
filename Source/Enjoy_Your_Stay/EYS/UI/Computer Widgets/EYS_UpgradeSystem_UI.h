// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "EYS_UpgradeSystem_UI.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_UpgradeSystem_UI : public UUserWidget
{
	GENERATED_BODY()
	
	//*********************Buttons****************************
	UPROPERTY(meta=(BindWidget))
	UButton* Button_BoilerUp1;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_BoilerUp2;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_BoilerUp3;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_GenUp1;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_GenUp2;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_GenUp3;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_GuestUp1;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_GuestUp2;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_GuestUp3;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_MyCharacterUp;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_EquipmentUp;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_DoormatUp;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close; 


	//*********************TextBlocks****************************
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Upgrade;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Header;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_UpgradePrice;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentMoney;


	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_UpgradeText;


protected:
	virtual void NativeConstruct() override;
	
	void ShowUpgradeText(int32 SlotIndex);
	UFUNCTION()
	void HideUpgradeText();
	UFUNCTION()
	void OnGen1() { ShowUpgradeText(0); }
	
	UFUNCTION()
	void OnGen2() { ShowUpgradeText(1); }
	UFUNCTION()
	void OnGen3() { ShowUpgradeText(2); }
	UFUNCTION()
	void OnBoiler1() { ShowUpgradeText(3); }
	UFUNCTION()
	void OnBoiler2() { ShowUpgradeText(4); }
	UFUNCTION()
	void OnBoiler3() { ShowUpgradeText(5); }
	UFUNCTION()
	void OnGuest1() { ShowUpgradeText(6); }
	UFUNCTION()
	void OnGuest2() { ShowUpgradeText(7); }
	UFUNCTION()
	void OnGuest3() { ShowUpgradeText(8); }
	UFUNCTION()
	void OnMyCharacter() { ShowUpgradeText(9); }
	UFUNCTION()
	void OnEquipment() { ShowUpgradeText(10); }
	UFUNCTION()
	void OnDoormat() { ShowUpgradeText(11); }

	UFUNCTION() void CloseUpgradeWidget();
	UFUNCTION() void UpdateCurrentMoney();
	
	//*********************GeneratorUp****************************
   void SetGeneratorUpgrade(int32 UpgradeIndex);

	UFUNCTION()
	void OnGenUp1() { SetGeneratorUpgrade(0); }
	UFUNCTION()
	void OnGenUp2() { SetGeneratorUpgrade(1); }
	UFUNCTION()
	void OnGenUp3() { SetGeneratorUpgrade(2); }

	


	//*********************BoilerUp****************************
    void SetBoilerUpgrade(int32 UpgradeIndex);
 
    UFUNCTION()
	void OnBoilerUp1() { SetBoilerUpgrade(0); }
	UFUNCTION()
	void OnBoilerUp2() { SetBoilerUpgrade(1); }
	UFUNCTION()
	void OnBoilerUp3() { SetBoilerUpgrade(2); }

	//*********************GuestUp****************************
	void SetGuestUpgrade(int32 UpgradeIndex);

	UFUNCTION()
	void OnGuestUp1() { SetGuestUpgrade(0); }
	UFUNCTION()
	void OnGuestUp2() { SetGuestUpgrade(1); }
	UFUNCTION()
	void OnGuestUp3() { SetGuestUpgrade(2); }

	//*********************Single****************************
	void SetSingleUpgrade(int32 UpgradeIndex);

	UFUNCTION()
	void OnSingleUp1() { SetSingleUpgrade(0); }
	UFUNCTION()
	void OnSingleUp2() { SetSingleUpgrade(1); }
	UFUNCTION()
	void OnSingleUp3() { SetSingleUpgrade(2); }

	void CheckUpgrades();



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varible")
	TArray<FText> UpgradeText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varible")
	TArray<FText> HeaderText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varible")
	TArray<int32> UpgradePrice;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varible")
	TArray<UTexture2D*> DisableTextures;

};
