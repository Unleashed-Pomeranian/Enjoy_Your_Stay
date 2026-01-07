 // Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/EYS_MyCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Enjoy_Your_StayCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Enjoy_Your_Stay.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "EYS_EquipmentWheel.h"
#include "EYS/EYS_MyCharacter.h"

#include "EYS/UI/EYS_MyCharacter_UI.h"

AEYS_MyCharacterController::AEYS_MyCharacterController()
{
	PlayerCameraManagerClass = AEYS_MyCharacterController::StaticClass();
}

void AEYS_MyCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		}
		else {

			UE_LOG(LogEnjoy_Your_Stay, Error, TEXT("Could not spawn mobile controls widget."));

		}
		

	}
	EquipmentWheelInstance = CreateWidget<UEYS_EquipmentWheel>(this, EquipmentWheelClass);
	MyCharacterUIInstance = CreateWidget<UEYS_MyCharacter_UI>(this, MYCharacterUIClass);

	if (MYCharacterUIClass)
	{
		MyCharacterUIInstance->AddToViewport();
	}

	OwnerCharacter = Cast<AEYS_MyCharacter>(GetPawn());
	Money = 1000;
	SetMoneyWidget(0);
}

void AEYS_MyCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}

	
	
	
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

void AEYS_MyCharacterController::SetStaminaWidget(float StaminaValue)
{
	if (!(MyCharacterUIInstance->Overlay->IsVisible()))
	{
		MyCharacterUIInstance->Overlay->SetVisibility(ESlateVisibility::Visible);
	}

	MyCharacterUIInstance->Stamina_ProgressBar->SetPercent(StaminaValue);
}

void AEYS_MyCharacterController::CloseStaminaWidget()
{
	if ((MyCharacterUIInstance->Overlay->IsVisible()))
	{
		MyCharacterUIInstance->Overlay->SetVisibility(ESlateVisibility::Hidden);
	}

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
	}

	
}



void AEYS_MyCharacterController::CloseInteractionWidget()
{
	if ((MyCharacterUIInstance->Interaction_Text->IsVisible()))
	{
		MyCharacterUIInstance->Interaction_Text->SetVisibility(ESlateVisibility::Hidden);
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
	OwnerCharacter->SetActorLocation(SetLocation);
	SetControlRotation(Rotation);
}

