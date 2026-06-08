// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Order Widgets/EYS_CartRow_UI.h"

void UEYS_CartRow_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Remove)
	{
		Button_Remove->OnClicked.AddDynamic(this, &UEYS_CartRow_UI::OnRemoveClicked);
	}
}

void UEYS_CartRow_UI::InitRow(FSupermarketProduct Data, UEYS_Supermarket_UI* MainUI)
{
	RowProductData = Data;
	MainMarketUI = MainUI;

	if (Text_Row)
	{
		FString RowStr = FString::Printf(TEXT("- %s (%s%d)"), *RowProductData.ProductName, TEXT("\u20BD"), RowProductData.Price);
		Text_Row->SetText(FText::FromString(RowStr));
	}
}

void UEYS_CartRow_UI::OnRemoveClicked()
{
	if (MainMarketUI)
	{
		// Ana ekrana "Beni bul ve sepetten kaz? gulum" diyoruz
		MainMarketUI->RemoveProductFromCart(RowProductData);
	}
}