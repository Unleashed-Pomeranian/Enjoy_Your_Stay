// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/UI/EYS_GeneratorActivateWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/Interactable Actor/EYS_Generator.h"

void UEYS_GeneratorActivateWidget::NativeConstruct()

{
	Super::NativeConstruct();
	
	
	RadialValue = 0;
	UKismetSystemLibrary::K2_SetTimer(this, "StartGenerator", 0.016f, true);
	 Score = 0;
	 Score_Text->SetText(FText::FromString(FString::FromInt(Score)));
}



void UEYS_GeneratorActivateWidget::StartGenerator()
{
	if (!bIsBetween)
	{
		RadialValue += 0.020f;
		Radial_Slider->SetValue(RadialValue);
		Slider->SetValue(RadialValue);
		if (RadialValue >= 0.99)
			bIsBetween = true;
	}
	else
	{
		RadialValue -= 0.020f;
		Radial_Slider->SetValue(RadialValue);
		Slider->SetValue(RadialValue);
		if (RadialValue <= 0.01)
			bIsBetween = false;

	}

}



void UEYS_GeneratorActivateWidget::TimerFTimer()
{

	FStopTimer();

		UKismetSystemLibrary::K2_SetTimer(this, "FStartTimer", 1.0f, false);
}


void UEYS_GeneratorActivateWidget::FStartTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "turrsadasdrrrr");
	if (Score == 3)
	{
		AEYS_Generator* Generator = Cast<AEYS_Generator>(UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_Generator::StaticClass()));
		Generator->bIsWorking = true;
		Generator->StartStopTimer();
		Generator->testlight();

		RemoveFromParent();
		UKismetSystemLibrary::K2_ClearTimer(this, "StartGenerator");
	}
	else
	{
		RadialValue = 0.0f;
		bIsBetween = false;
		UKismetSystemLibrary::K2_SetTimer(this, "StartGenerator", 0.016f, true);
	}

}

void UEYS_GeneratorActivateWidget::FStopTimer()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "StartGenerator");
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "turrsadasdrrrr");

	const float CurrentValue = RadialValue;

	if (RadialValue >= 0.4f && RadialValue <= 0.8f)
	{
		Score++;



		Score_Text->SetText(FText::FromString(FString::FromInt(Score)));
		
	}

	else
	{
		Score = 0;
		Score_Text->SetText(FText::FromString(FString::FromInt(Score)));
	}
}


