// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "EYS_Computer_UI.generated.h"

/**
 * 
 */
class UEYS_SecurityCamera_UI;
class UEYS_UpgradeSystem_UI;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Computer_UI : public UUserWidget
{

	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Background;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_SecurityCamera;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_UpgradeSystem;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;
	
protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void OpenSecurityWidget();
	UFUNCTION() void OpenUpgradeWidget();
	UFUNCTION() void CloseComputerWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UEYS_SecurityCamera_UI> SecurityCameraWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UEYS_SecurityCamera_UI* SecurityCameraWidgetInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UEYS_UpgradeSystem_UI> UpgradeSystemWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UEYS_UpgradeSystem_UI* UpgradeSystemWidgetInstance;
};
