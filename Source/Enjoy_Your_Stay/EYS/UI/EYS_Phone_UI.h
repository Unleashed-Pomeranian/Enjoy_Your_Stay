// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EYS_Phone_UI.generated.h"

/**
 * 
 */

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Phone_UI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Close;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_SuperMarket;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SuperMarket;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Ironmonger;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Ironmonger;

protected:
	virtual void NativeConstruct() override;

public:
		UFUNCTION() void CloseWidget();
};
