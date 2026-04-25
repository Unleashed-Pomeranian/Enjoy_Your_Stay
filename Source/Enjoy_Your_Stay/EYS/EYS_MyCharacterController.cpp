 // Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/EYS_MyCharacterController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Enjoy_Your_StayCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Enjoy_Your_Stay.h"
#include "EYS_EquipmentWheel.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/UI/EYS_MyCharacter_UI.h"
#include "EYS/Game Managers/EYS_TutorialSubsystem.h"

AEYS_MyCharacterController::AEYS_MyCharacterController()
{
	PlayerCameraManagerClass = AEYS_MyCharacterController::StaticClass();
}

void AEYS_MyCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsys =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
		{
			if (DefaultMapping)
			{
				Subsys->AddMappingContext(DefaultMapping, 0);

			}
			if (UEnhancedInputUserSettings* Settings = Subsys->GetUserSettings())
			{
				Settings->RegisterInputMappingContext(DefaultMapping);
			}
		}
	}

	
	if (EquipmentWheelClass) { EquipmentWheelInstance = CreateWidget<UEYS_EquipmentWheel>(this, EquipmentWheelClass); }

	if (MYCharacterUIClass)
	{
		MyCharacterUIInstance = CreateWidget<UEYS_MyCharacter_UI>(this, MYCharacterUIClass);

		if (MyCharacterUIInstance)
		{
			UEYS_TutorialSubsystem* TS = GetGameInstance()->GetSubsystem<UEYS_TutorialSubsystem>();
			if (TS) 
			{ 
				TS->MyCharacterUIIns = MyCharacterUIInstance; 
				TS->SetTutorialStep(ETutorialStep::WaitTheGuest);
			}

			MyCharacterUIInstance->AddToViewport();
		}
	}


	OwnerCharacter = Cast<AEYS_MyCharacter>(GetPawn());
	Money = 2000;
	SetMoneyWidget(0);


}

void AEYS_MyCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AEYS_MyCharacterController::OpenEquipmentWidget()
{

	if (!EquipmentWheelClass)
		return;

	//if (!EquipmentWheelInstance->IsInViewport())
	
		
		MobilizeCharacter(true, true, true);
		int32 SizeX, SizeY;


		GetViewportSize(SizeX, SizeY);
		int32 CenterX = SizeX / 2;
		int32 CenterY = SizeY / 2;
		SetMouseLocation(CenterX, CenterY);
		if (!EquipmentWheelInstance->IsInViewport())
		EquipmentWheelInstance->AddToViewport(10);
		else
			EquipmentWheelInstance -> SetVisibility(ESlateVisibility::Visible);
	
}

void AEYS_MyCharacterController::CloseEquipmentWidget()
{
	MobilizeCharacter(false, false, false);
	//if (EquipmentWheelInstance && EquipmentWheelInstance->IsInViewport())
	EquipmentWheelInstance->SetVisibility(ESlateVisibility::Hidden);

	
	
}



void AEYS_MyCharacterController::SetMoneyWidget(int32 AddValue)
{
	Money += AddValue;
	FString MoneyText = FString::FromInt(Money);
	MyCharacterUIInstance->Money_Text->SetText(FText::FromString(MoneyText));

}

void AEYS_MyCharacterController::SetInteractionWidget(FString InterctionText)
{

	MyCharacterUIInstance->Interaction_Text->SetText(FText::FromString(InterctionText));
	if (!(MyCharacterUIInstance->Interaction_Text->IsVisible()))
	{
		MyCharacterUIInstance->Interaction_Text->SetVisibility(ESlateVisibility::Visible);
		MyCharacterUIInstance->Dot_Image->SetVisibility(ESlateVisibility::Hidden);
	}

	
}



void AEYS_MyCharacterController::CloseInteractionWidget()
{
	if ((MyCharacterUIInstance->Interaction_Text->IsVisible()))
	{
		MyCharacterUIInstance->Interaction_Text->SetVisibility(ESlateVisibility::Hidden);
		MyCharacterUIInstance->Dot_Image->SetVisibility(ESlateVisibility::Visible);
	}


}
void AEYS_MyCharacterController::SetHourWidget(float TimeofDay)
{
	int32 hour = FMath::TruncToInt(TimeofDay);
	int32 minute = (TimeofDay - hour) * 60;
	FString TimeString = FString::Printf(TEXT("%02d:%02d"), hour, minute);
	MyCharacterUIInstance->Hour_Text->SetText(FText::FromString(TimeString));
}

void AEYS_MyCharacterController::MobilizeCharacter(bool bLookInput, bool BIsInputModeUI, bool ShowCursor)
{
	
	SetIgnoreLookInput(bLookInput);
	SetIgnoreMoveInput(bLookInput);
	if (BIsInputModeUI)
	{
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
	}

	bShowMouseCursor = ShowCursor;
	

}

void AEYS_MyCharacterController::SetCharacterPositon(FVector ActorLocation, float LocationX, float LocationY, FRotator Rotation)
{

	
	FVector SetLocation = ActorLocation;
	//SetLocation.Y = ActorLocation.Y + 10;
	SetLocation.Y = ActorLocation.Y + LocationY;
	//SetLocation.X = ActorLocation.X + -8;
	SetLocation.X = ActorLocation.X + LocationX;
	OwnerCharacter->SetActorLocation(FVector(SetLocation.X, SetLocation.Y, OwnerCharacter->GetActorLocation().Z));
	
	SetControlRotation(Rotation);
}

void AEYS_MyCharacterController::PauseGame()
{

	if (!PauseWidgetClass)
	{
		return;
	}

	if (!PauseWidgetInstance)
	{
		PauseWidgetInstance = CreateWidget<UUserWidget>(this, PauseWidgetClass);
	}
	if (PauseWidgetInstance)
	{
		if (PauseWidgetInstance->IsInViewport())
		{
			PauseWidgetInstance->RemoveFromParent();

			SetPause(false);
			SetInputMode(FInputModeGameOnly());
			bShowMouseCursor = false;
		}
		else
		{
			PauseWidgetInstance->AddToViewport();
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;
		}
	}
}

