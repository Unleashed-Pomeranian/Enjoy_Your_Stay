// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_Supermarket_UI.h"
#include "Kismet/GamePlayStatics.h"

#include "EYS/EYS_OrderSpawner.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"
#include "EYS/UI/Order Widgets/EYS_ProductButton_UI.h"
#include "EYS/UI/Order Widgets/EYS_CartRow_UI.h"
#include "EYS/Game Managers/EYS_EconomySubsystem.h"

void UEYS_Supermarket_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Checkout)
	{
		Button_Checkout->OnClicked.AddDynamic(this, &UEYS_Supermarket_UI::OnCheckoutClicked);
	}


	ShoppingCart.Empty();
	TotalCartPrice = 0;
	UpdateCartUI();


	PopulateMarketProducts();
}

void UEYS_Supermarket_UI::PopulateMarketProducts()
{
	if (!WrapBox_ProductList || !ProductButtonWidgetClass || !MarketProductsTable) return;

	WrapBox_ProductList->ClearChildren();

	// Veritabanındaki tüm satırları (Ürünleri) tek seferde hafızaya çekiyoruz gulum
	TArray<FSupermarketProduct*> AllProducts;
	MarketProductsTable->GetAllRows<FSupermarketProduct>(TEXT("Market UI Populate"), AllProducts);
	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
		for (const FSupermarketProduct* ProductPtr : AllProducts)
		{
			if (!ProductPtr) continue;

			if (ProductPtr->ProductName.IsEmpty())
			{
				continue;
			}

			if (TS)
			{

				if (!TS->bIsTutorialFinished || TS->CurrentPhase != ETutorialPhase::ThirdPhase)
				{
					bool bIsAllowed = false;

					for (const FString& Checked : TutorialProducts)
					{
						if (Checked == ProductPtr->ProductName)
						{
							bIsAllowed = true;
							break; 
						}
					}

				
					if (!bIsAllowed)
					{
						continue;
					}
				}
			}

			if (UEYS_ProductButton_UI* ProductButton = CreateWidget<UEYS_ProductButton_UI>(GetWorld(), ProductButtonWidgetClass))
			{
				ProductButton->InitButton(*ProductPtr, this);
				WrapBox_ProductList->AddChild(ProductButton);
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

	UEYS_EconomySubsystem* ES = GetGameInstance()->GetSubsystem<UEYS_EconomySubsystem>();
	if (!ES) return;

		if (!ES->CheckMoney(TotalCartPrice))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Yetersiz Bakiye! Alışveriş Yapılamadı."));
			return;
		}
		ES->UpdateMoney(-TotalCartPrice);

	AEYS_OrderSpawner* OrderSpawner = Cast<AEYS_OrderSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_OrderSpawner::StaticClass()));

	for (const FSupermarketProduct& Item : ShoppingCart)
	{
		if (Item.EquipmentClass)
		{
			if (OrderSpawner)
			{
				OrderSpawner->SetOrderClass(Item.EquipmentClass);
			}

			

		}
	}


	UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
	if (!TS) return;
	if (TS->CurrentStep == ETutorialStep::OrderSupplies)
	{
		TArray<TSubclassOf<AActor>> BasketClasses;
		for (const FSupermarketProduct& Item : ShoppingCart)
		{
			if (Item.EquipmentClass)
			{
				BasketClasses.Add(Item.EquipmentClass);
				
			}
		}
		if (TS && BasketClasses.Num() > 0)
		{
			TS->RegisterNewOrder(BasketClasses);
		}
	}

	ShoppingCart.Empty();
	TotalCartPrice = 0;
	UpdateCartUI();
	
}