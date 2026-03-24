// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Computer Widgets/EYS_Computer_UI.h"
#include "EYS/UI/Computer Widgets/EYS_SecurityCamera_UI.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/UI/Computer Widgets/EYS_UpgradeSystem_UI.h"


void UEYS_Computer_UI::NativeConstruct()
{
	if (Button_SecurityCamera) Button_SecurityCamera->OnPressed.AddDynamic(this, &UEYS_Computer_UI::OpenSecurityWidget);
	if (Button_Close) Button_Close->OnPressed.AddDynamic(this, &UEYS_Computer_UI::CloseComputerWidget);
	if (Button_UpgradeSystem) Button_UpgradeSystem->OnPressed.AddDynamic(this, &UEYS_Computer_UI::OpenUpgradeWidget);

}

void UEYS_Computer_UI::OpenSecurityWidget()
{
	if (SecurityCameraWidgetClass)
	{
		SecurityCameraWidgetInstance = CreateWidget<UEYS_SecurityCamera_UI>(GetWorld(), SecurityCameraWidgetClass);

		if (SecurityCameraWidgetInstance) SecurityCameraWidgetInstance->AddToViewport();
	}
}

void UEYS_Computer_UI::OpenUpgradeWidget()
{
	if (UpgradeSystemWidgetClass)
	{
		UpgradeSystemWidgetInstance = CreateWidget<UEYS_UpgradeSystem_UI>(GetWorld(), UpgradeSystemWidgetClass);

		if (UpgradeSystemWidgetInstance) UpgradeSystemWidgetInstance->AddToViewport();
	}
}

void UEYS_Computer_UI::CloseComputerWidget()
{
	
	AEYS_MyCharacterController* PC = Cast<AEYS_MyCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->MobilizeCharacter(false, false, false);
		RemoveFromParent();
	}

}
