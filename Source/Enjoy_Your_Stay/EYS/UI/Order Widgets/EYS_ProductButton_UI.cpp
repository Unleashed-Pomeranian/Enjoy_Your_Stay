// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_ProductButton_UI.h"

void UEYS_ProductButton_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Item)
	{
		Button_Item->OnClicked.AddDynamic(this, &UEYS_ProductButton_UI::OnButtonClicked);
	}
}

void UEYS_ProductButton_UI::InitButton(FSupermarketProduct Data, UEYS_Supermarket_UI* MainUI)
{
	ProductData = Data;
	MainMarketUI = MainUI;

	if (Text_ProductName)
	{
		Text_ProductName->SetText(FText::FromString(ProductData.ProductName));
	}


	if (Text_ProductPrice)
	{
		FString PriceStr = FString::Printf(TEXT("%s%d"), TEXT("\u20BD"), ProductData.Price);
		Text_ProductPrice->SetText(FText::FromString(PriceStr));
	}


	if (Image_Product && ProductData.ProductImage)
	{
		Image_Product->SetBrushFromTexture(ProductData.ProductImage);
	}
}

void UEYS_ProductButton_UI::OnButtonClicked()
{
	if (MainMarketUI)
	{
	
		MainMarketUI->AddProductToCart(ProductData);
	}
}