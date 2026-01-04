// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/EYS_Phone_UI.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Interactable Actor/EYS_Phone.h"

void UEYS_Phone_UI::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_Close) Button_Close->OnPressed.AddDynamic(this,&UEYS_Phone_UI::CloseWidget);
	
	
}

void UEYS_Phone_UI::CloseWidget()
{
	AEYS_Phone* Phone = Cast<AEYS_Phone>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Phone::StaticClass()));
	if (Phone)
	{
		Phone->CloseUI();
	}
	
}
