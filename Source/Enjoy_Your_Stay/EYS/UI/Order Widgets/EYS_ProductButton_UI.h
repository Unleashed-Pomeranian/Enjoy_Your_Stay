// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"

#include "Components/Image.h"
#include "EYS/UI/Order Widgets/EYS_Supermarket_UI.h"
#include "EYS_ProductButton_UI.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_ProductButton_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_Item;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Item;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ProductName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ProductPrice;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Product;
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClicked();

public:
	
	UPROPERTY(BlueprintReadWrite, Category = "Product Settings")
	FSupermarketProduct ProductData;

	
	UPROPERTY(BlueprintReadWrite, Category = "Product Settings")
	UEYS_Supermarket_UI* MainMarketUI;

	UFUNCTION(BlueprintCallable, Category = "Product Settings")
	void InitButton(FSupermarketProduct Data, UEYS_Supermarket_UI* MainUI);
};
	

