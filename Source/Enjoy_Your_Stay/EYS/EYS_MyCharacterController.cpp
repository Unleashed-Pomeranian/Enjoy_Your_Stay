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

	EquipmentWheelInstance->AddToViewport(10);
	SetIgnoreLookInput(true);
	SetInputMode(FInputModeGameAndUI());
		
	bShowMouseCursor = true;
	
	int32 SizeX, SizeY;

	
	GetViewportSize(SizeX, SizeY);
	int32 CenterX = SizeX / 2;
	int32 CenterY = SizeY / 2;
	SetMouseLocation(CenterX, CenterY);
}

void AEYS_MyCharacterController::CloseEquipmentWidget()
{
	EquipmentWheelInstance->RemoveFromParent();
	SetIgnoreLookInput(false);
	SetInputMode(FInputModeGameOnly());

	bShowMouseCursor = false;
	
}
