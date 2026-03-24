// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/Computer Widgets/EYS_SecurityCamera_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Interactable Actor/ComputerSystem/EYS_SecurityCamera.h"
void UEYS_SecurityCamera_UI::NativeConstruct()
{
	if(Button_Next) Button_Next->OnClicked.AddDynamic(this,&UEYS_SecurityCamera_UI::SetNextCamera);
	if (Button_Prev) Button_Prev->OnClicked.AddDynamic(this, &UEYS_SecurityCamera_UI::SetPrevCamera);
	if (Button_Close) Button_Close->OnClicked.AddDynamic(this, &UEYS_SecurityCamera_UI::FCloseWidget);
	SecurityCamera = Cast<AEYS_SecurityCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_SecurityCamera::StaticClass()));
	SetCameraText();
}

void UEYS_SecurityCamera_UI::SetNextCamera()
{
	
	 
	if (SecurityCamera)	
		SecurityCamera->SetCameraLocation(1);
	else
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "null");
	SetCameraText();
}

void UEYS_SecurityCamera_UI::SetPrevCamera()
{
	if (SecurityCamera)
		SecurityCamera->SetCameraLocation(-1);
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "null");
	SetCameraText();
}

void UEYS_SecurityCamera_UI::SetCameraText()
{
	if (SecurityCamera) {
		FString CamText = "Camera " + FString::FromInt(SecurityCamera->CamNum + 1);
		Text_Camera->SetText(FText::FromString(CamText));
	}
}

void UEYS_SecurityCamera_UI::FCloseWidget()
{
	RemoveFromParent();
}
