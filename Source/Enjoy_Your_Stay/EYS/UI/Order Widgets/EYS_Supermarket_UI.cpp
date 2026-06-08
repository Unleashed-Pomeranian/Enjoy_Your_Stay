// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_Supermarket_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS/EYS_OrderSpawner.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/UI/Order Widgets/EYS_ProductButton_UI.h"
#include "EYS/UI/Order Widgets/EYS_CartRow_UI.h"

void UEYS_Supermarket_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Checkout)
	{
		Button_Checkout->OnClicked.AddDynamic(this, &UEYS_Supermarket_UI::OnCheckoutClicked);
	}

	// Başlangıçta sepeti temizliyoruz gulum
	ShoppingCart.Empty();
	TotalCartPrice = 0;
	UpdateCartUI();

	// Ürün butonlarını otomatik oluşturup dükkan raflarına diziyoruz
	PopulateMarketProducts();
}

void UEYS_Supermarket_UI::PopulateMarketProducts()
{
	if (!WrapBox_ProductList || !ProductButtonWidgetClass || !MarketProductsTable) return;

	WrapBox_ProductList->ClearChildren();

	// Veritabanındaki tüm satırları (Ürünleri) tek seferde hafızaya çekiyoruz gulum
	TArray<FSupermarketProduct*> AllProducts;
	MarketProductsTable->GetAllRows<FSupermarketProduct>(TEXT("Market UI Populate"), AllProducts);

	for (const FSupermarketProduct* ProductPtr : AllProducts)
	{
		if (ProductPtr)
		{
			if (UEYS_ProductButton_UI* ProductButton = CreateWidget<UEYS_ProductButton_UI>(GetWorld(), ProductButtonWidgetClass))
			{
				// Pointer'ı normal struct yapısına çevirip (*ProductPtr) butona paslıyoruz
				ProductButton->InitButton(*ProductPtr, this);
				WrapBox_ProductList->AddChild(ProductButton);
			}
		}
	}
}

void UEYS_Supermarket_UI::AddProductToCart(FSupermarketProduct Product)
{
	ShoppingCart.Add(Product);
	TotalCartPrice += Product.Price;

	UpdateCartUI();
}

void UEYS_Supermarket_UI::RemoveProductFromCart(FSupermarketProduct ProductToRemove)
{
	// Kırılgan index'ler yerine doğrudan nesneyi aratıp siliyoruz gulum
	int32 RemovedCount = ShoppingCart.RemoveSingle(ProductToRemove);

	if (RemovedCount > 0)
	{
		TotalCartPrice -= ProductToRemove.Price;
		UpdateCartUI();
	}
}

void UEYS_Supermarket_UI::UpdateCartUI()
{
	if (Text_TotalPrice)
	{
		Text_TotalPrice->SetText(FText::FromString(FString::Printf(TEXT("Total: %s%d"), TEXT("\u20BD"), TotalCartPrice)));
	}

	if (!ScrollBox_CartList || !CartRowWidgetClass) return;

	ScrollBox_CartList->ClearChildren();

	// Sepetteki güncel ürünleri tertemiz basıyoruz
	for (const FSupermarketProduct& Item : ShoppingCart)
	{
		if (UEYS_CartRow_UI* RowWidget = CreateWidget<UEYS_CartRow_UI>(GetWorld(), CartRowWidgetClass))
		{
			RowWidget->InitRow(Item, this);
			ScrollBox_CartList->AddChild(RowWidget);
		}
	}
}

void UEYS_Supermarket_UI::OnCheckoutClicked()
{
	if (ShoppingCart.Num() == 0) return;

	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(GetOwningPlayer());
	if (!PC) return;

	if (PC->Money < TotalCartPrice)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Yetersiz Bakiye! Alışveriş Yapılamadı."));
		return;
	}

	PC->SetMoneyWidget(-TotalCartPrice);

	AEYS_OrderSpawner* OrderSpawner = Cast<AEYS_OrderSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_OrderSpawner::StaticClass()));
	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();

	for (const FSupermarketProduct& Item : ShoppingCart)
	{
		if (Item.EquipmentClass)
		{
			if (OrderSpawner)
			{
				OrderSpawner->SetOrderClass(Item.EquipmentClass);
			}

			if (TS)
			{
				TS->RegisterNewOrder(Item.EquipmentClass);
			}
		}
	}

	ShoppingCart.Empty();
	TotalCartPrice = 0;
	UpdateCartUI();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Siparişler başarıyla alındı!"));
}