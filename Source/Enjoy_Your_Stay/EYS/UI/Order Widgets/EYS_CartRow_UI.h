// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EYS/UI/Order Widgets/EYS_Supermarket_UI.h"
#include "EYS_CartRow_UI.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_CartRow_UI : public UUserWidget
{
	GENERATED_BODY()

	// WBP tarafında eşleşecek çarpı butonu ve yazı alanı
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Remove;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Row;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnRemoveClicked(); // Çarpı butonuna basınca çalışacak fonksiyon

public:
	// Bu satırın temsil ettiği ürünün kopyası ve index'i
	FSupermarketProduct RowProductData;
	

	// Ana market ekranına referans (Oradaki sepet dizisinden silme yapabilmek için)
	UPROPERTY(BlueprintReadWrite, Category = "Cart Row")
	UEYS_Supermarket_UI* MainMarketUI;

	// Satır oluştukça içini dolduracak başlatma fonksiyonu
	void InitRow(FSupermarketProduct Data, UEYS_Supermarket_UI* MainUI);
	
};
