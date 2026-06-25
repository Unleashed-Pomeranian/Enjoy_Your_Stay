// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_Supermarket_UI.generated.h"


USTRUCT(BlueprintType)
struct FSupermarketProduct: public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	FString ProductName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	TSubclassOf<AEYS_HeavyEquipmentBase> EquipmentClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Product")
	UTexture2D* ProductImage = nullptr;
	bool operator==(const FSupermarketProduct& Other) const
	{
		return ProductName == Other.ProductName && Price == Other.Price && EquipmentClass == Other.EquipmentClass;
	}
};

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Supermarket_UI : public UUserWidget
{
	GENERATED_BODY()

	// WBP (Widget Blueprint) tarafında birebir aynı isimle eşleşecek bileşenler
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_CartList;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_TotalPrice;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Checkout;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox_ProductList;

protected:
	virtual void NativeConstruct() override;

	// Sepette biriken ürün verileri ve toplam bakiye hesabı
	TArray<FSupermarketProduct> ShoppingCart;
	
	int32 TotalCartPrice = 0;

	UFUNCTION()
	void OnCheckoutClicked();

	void UpdateCartUI();
	void PopulateMarketProducts();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial Products")
	TArray<FString> TutorialProducts;
public:
	// Ürün butonuna basıldığında çağrılacak ortak sepet ekleme fonksiyonu
	void AddProductToCart(FSupermarketProduct Product);

	// Sepetten nesne referansıyla güvenli silme yapan fonksiyonumuz
	void RemoveProductFromCart(FSupermarketProduct ProductToRemove);

	// Sepet satırlarını (Çarpılı satır Widget) göstermek için editörden seçeceğimiz sınıf
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market Settings")
	TSubclassOf<UUserWidget> CartRowWidgetClass;

	// Otomatik spawn edilecek Ürün Buton Sınıfı (WBP_ProductButton)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market Settings")
	TSubclassOf<UUserWidget> ProductButtonWidgetClass;

	// Satılacak tüm ürünlerin listesi (Editör'den tıkır tıkır dolduracağın Array)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Market Settings")
	UDataTable* MarketProductsTable;
	
};
