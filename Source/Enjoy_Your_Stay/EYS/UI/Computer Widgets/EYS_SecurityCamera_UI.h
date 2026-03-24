// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EYS_SecurityCamera_UI.generated.h"

/**
 * 
 */
class AEYS_SecurityCamera;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_SecurityCamera_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Camera;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Camera;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Next;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Prev;
    UPROPERTY(meta=(BindWidget))
	UButton* Button_Close;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void SetNextCamera();
	UFUNCTION() void SetPrevCamera();
	UFUNCTION() void SetCameraText();
	UFUNCTION() void FCloseWidget();
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	AEYS_SecurityCamera* SecurityCamera;
};
