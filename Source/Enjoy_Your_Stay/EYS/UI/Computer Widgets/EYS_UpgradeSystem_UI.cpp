// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Computer Widgets/EYS_UpgradeSystem_UI.h"
#include "EYS/Game Managers/EYS_UpgradeSubsystem.h"

void UEYS_UpgradeSystem_UI::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_GenUp1) Button_GenUp1->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGen1);
	if (Button_GenUp2) Button_GenUp2->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGen2);
	if (Button_GenUp3) Button_GenUp3->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGen3);

	if (Button_BoilerUp1) Button_BoilerUp1->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnBoiler1);
	if (Button_BoilerUp2) Button_BoilerUp2->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnBoiler2);
	if (Button_BoilerUp3) Button_BoilerUp3->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnBoiler3);

	if(Button_GuestUp1) Button_GuestUp1->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGuest1);
	if (Button_GuestUp2) Button_GuestUp2->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGuest2);
	if (Button_GuestUp3) Button_GuestUp3->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGuest3);

	if (Button_MyCharacterUp) Button_MyCharacterUp->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnMyCharacter);
	if (Button_EquipmentUp) Button_EquipmentUp->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnEquipment);
	if (Button_DoormatUp) Button_DoormatUp->OnHovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnDoormat);


	if (Button_GenUp1) Button_GenUp1->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_GenUp2) Button_GenUp2->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_GenUp3) Button_GenUp3->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);


	if (Button_BoilerUp1) Button_BoilerUp1->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_BoilerUp2) Button_BoilerUp2->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_BoilerUp3) Button_BoilerUp3->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);

	if (Button_GuestUp1) Button_GuestUp1->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_GuestUp2) Button_GuestUp2->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_GuestUp3) Button_GuestUp3->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);

	if (Button_MyCharacterUp) Button_MyCharacterUp->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_EquipmentUp) Button_EquipmentUp->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);
	if (Button_DoormatUp) Button_DoormatUp->OnUnhovered.AddDynamic(this, &UEYS_UpgradeSystem_UI::HideUpgradeText);

	if (Button_GenUp1) Button_GenUp1->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGenUp1);
	if (Button_GenUp2) Button_GenUp2->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGenUp2);
	if (Button_GenUp3) Button_GenUp3->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGenUp3);

	if (Button_BoilerUp1) Button_BoilerUp1->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnBoilerUp1);
	if (Button_BoilerUp2) Button_BoilerUp2->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnBoilerUp2);
	if (Button_BoilerUp3) Button_BoilerUp3->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnBoilerUp3);

	if (Button_GuestUp1) Button_GuestUp1->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGuestUp1);
	if (Button_GuestUp2) Button_GuestUp2->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGuestUp2);
	if (Button_GuestUp3) Button_GuestUp3->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnGuestUp3);

	if (Button_MyCharacterUp) Button_MyCharacterUp->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnSingleUp1);
	if (Button_EquipmentUp) Button_EquipmentUp->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnSingleUp2);
	if (Button_DoormatUp) Button_DoormatUp->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::OnSingleUp3);


	if(Button_Close) Button_Close->OnClicked.AddDynamic(this, &UEYS_UpgradeSystem_UI::CloseUpgradeWidget);
	CheckUpgrades();
}

void UEYS_UpgradeSystem_UI::ShowUpgradeText(int32 SlotIndex)
{
	if (Text_Upgrade)
	{
		Text_Upgrade->SetText(UpgradeText[SlotIndex]);
		Text_Header->SetText(HeaderText[SlotIndex]);
		FString Price = FString(TEXT("$ ")) + UpgradePriceText[SlotIndex];
		Text_UpgradePrice->SetText(FText::FromString(Price));
	    Overlay_UpgradeText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UEYS_UpgradeSystem_UI::HideUpgradeText()
{

	Overlay_UpgradeText->SetVisibility(ESlateVisibility::Hidden);
}



void UEYS_UpgradeSystem_UI::SetGeneratorUpgrade(int32 UpgradeIndex)
{
	UEYS_UpgradeSubsystem* UpgradeSubsystem =
		GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>();
	if (UpgradeSubsystem)
	{
		switch (UpgradeIndex)
		{
		case 0:
		{
			Button_GenUp1->SetIsEnabled(false);
			Button_GenUp2->SetIsEnabled(true);
			UpgradeSubsystem->ApplyGeneratorUpgrade(UpgradeIndex);
			Button_GenUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[0]);
			break;
		}
		case 1:
		{
			Button_GenUp2->SetIsEnabled(false);
			Button_GenUp3->SetIsEnabled(true);
			UpgradeSubsystem->ApplyGeneratorUpgrade(UpgradeIndex);
			Button_GenUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[1]);
			break;
		}
		case 2:
		{
			Button_GenUp3->SetIsEnabled(false);
			UpgradeSubsystem->ApplyGeneratorUpgrade(UpgradeIndex);
			Button_GenUp3->WidgetStyle.Normal.SetResourceObject(DisableTextures[2]);
			break;
		}
		default:
			break;
		}
	}
}

void UEYS_UpgradeSystem_UI::SetBoilerUpgrade(int32 UpgradeIndex)
{

	UEYS_UpgradeSubsystem* UpgradeSubsystem =
		GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>();
	if (UpgradeSubsystem)
	{
		UpgradeSubsystem->ApplyBoilerUpgrade(UpgradeIndex);
		switch (UpgradeIndex)
		{
		case 0:
		{
			Button_BoilerUp1->SetIsEnabled(false);
			Button_BoilerUp2->SetIsEnabled(true);
			Button_BoilerUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[3]);
			break;
		}
		case 1:
		{
			Button_BoilerUp2->SetIsEnabled(false);
			Button_BoilerUp3->SetIsEnabled(true);
			Button_BoilerUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[4]);
			break;
		}
		case 2:
		{
			Button_BoilerUp3->SetIsEnabled(false);
			Button_BoilerUp3->WidgetStyle.Normal.SetResourceObject(DisableTextures[5]);
			break;
		}
		default:
			break;
		}
	}
}

void UEYS_UpgradeSystem_UI::SetGuestUpgrade(int32 UpgradeIndex)
{
	UEYS_UpgradeSubsystem* UpgradeSubsystem =
		GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>();

	if (UpgradeSubsystem)
	{
		UpgradeSubsystem->ApplyGuestUpgrade(UpgradeIndex);
		switch (UpgradeIndex)
		{
		case 0:
		{

			Button_GuestUp1->SetIsEnabled(false);
			Button_GuestUp2->SetIsEnabled(true);
			Button_GuestUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[6]);


			break;
		}
		case 1:
		{
			Button_GuestUp2->SetIsEnabled(false);
			Button_GuestUp3->SetIsEnabled(true);
			Button_GuestUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[7]);
			
			break;
		}
		case 2:
		{
			Button_GuestUp3->SetIsEnabled(false);
			Button_GuestUp3->WidgetStyle.Normal.SetResourceObject(DisableTextures[8]);
			break;
		}
		default:
			break;
		}
	}
}

void UEYS_UpgradeSystem_UI::SetSingleUpgrade(int32 UpgradeIndex)
{
	UEYS_UpgradeSubsystem* UpgradeSubsystem =
		GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>();

	if (UpgradeSubsystem)
	{
		UpgradeSubsystem->ApplySingleUpgrade(UpgradeIndex);
		
			switch (UpgradeIndex)
			{
			case 0:
			{
				Button_MyCharacterUp->SetIsEnabled(false);
				Button_MyCharacterUp->WidgetStyle.Normal.SetResourceObject(DisableTextures[9]);

				break;
			}
			case 1:
			{
				Button_EquipmentUp->SetIsEnabled(false);
				Button_EquipmentUp->WidgetStyle.Normal.SetResourceObject(DisableTextures[10]);

				break;
			}
			case 2:
			{
				Button_DoormatUp->SetIsEnabled(false);
				Button_DoormatUp->WidgetStyle.Normal.SetResourceObject(DisableTextures[11]);
				break;
			}
			default:
				break;
			}

			
	}


		
}

void UEYS_UpgradeSystem_UI::CheckUpgrades()
{
	UEYS_UpgradeSubsystem* US =
		GetGameInstance()->GetSubsystem<UEYS_UpgradeSubsystem>();
	switch (US->GeneratorUpgradeLevel)
	{
	case 1:
	{ Button_GenUp1->SetIsEnabled(false), Button_GenUp2->SetIsEnabled(true); 
	Button_GenUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[0]);
	break;
	}
	case 2:
	{ 
		Button_GenUp1->SetIsEnabled(false); Button_GenUp3->SetIsEnabled(true);  
		Button_GenUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[0]);
		Button_GenUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[1]);
		break;
	}

	case 3: { 
		
		Button_GenUp1->SetIsEnabled(false);
		Button_GenUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[0]);
		Button_GenUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[1]);
		Button_GenUp3->WidgetStyle.Normal.SetResourceObject(DisableTextures[2]);
		break;
	
	}



	default:
		break;
	}

	switch (US->BoilerUpgradeLevel)
	{
	case 1:
	{
		Button_BoilerUp1->SetIsEnabled(false), Button_BoilerUp2->SetIsEnabled(true);
		Button_BoilerUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[3]);
		break;
	}
	case 2:
	{
		Button_BoilerUp1->SetIsEnabled(false); Button_BoilerUp3->SetIsEnabled(true);
		Button_BoilerUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[3]);
		Button_BoilerUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[4]);
		break;
	}

	case 3: {

		Button_BoilerUp1->SetIsEnabled(false);
		Button_BoilerUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[3]);
		Button_BoilerUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[4]);
		Button_BoilerUp3->WidgetStyle.Normal.SetResourceObject(DisableTextures[5]);
		break;

	}


	default:
		break;

	}

	switch (US->GuestUpgradeLevel)
	{
	case 1:
	{
		Button_GuestUp1->SetIsEnabled(false), Button_GuestUp2->SetIsEnabled(true);
		Button_GuestUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[6]);
		break;
	}
	case 2:
	{
		Button_GuestUp1->SetIsEnabled(false); Button_GuestUp3->SetIsEnabled(true);
		Button_GuestUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[6]);
		Button_GuestUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[7]);
		break;
	}

	case 3: {

		Button_GuestUp1->SetIsEnabled(false);
		Button_GuestUp1->WidgetStyle.Normal.SetResourceObject(DisableTextures[6]);
		Button_GuestUp2->WidgetStyle.Normal.SetResourceObject(DisableTextures[7]);
		Button_GuestUp3->WidgetStyle.Normal.SetResourceObject(DisableTextures[8]);
		break;

	}


	default:
		break;

	}

	if (US->bMyCharacterUpgradePurchased)
	{
		Button_MyCharacterUp->SetIsEnabled(false);
		Button_MyCharacterUp->WidgetStyle.Normal.SetResourceObject(DisableTextures[9]);
	}
	if (US->bEquipmentUpgradePurchased)
	{
		Button_EquipmentUp->SetIsEnabled(false);
		Button_EquipmentUp->WidgetStyle.Normal.SetResourceObject(DisableTextures[10]);
	}

	if (US->bDoormatUpgradePurchased)
	{
		Button_DoormatUp->SetIsEnabled(false);
		Button_DoormatUp->WidgetStyle.Normal.SetResourceObject(DisableTextures[11]);
	}

}


void UEYS_UpgradeSystem_UI::CloseUpgradeWidget()
{
	RemoveFromParent();
}