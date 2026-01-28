// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EYS_Day_UI.generated.h"

/**
 * 
 */
class AEYS_MyCharacterController;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Day_UI : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UImage* Background_Image;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Day_Text;
	UPROPERTY(meta = (BindWidget))
	UButton* Start_Button;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Start_Text;

protected:
	virtual void NativeConstruct() override;
	
	
public:
	UFUNCTION() void SetDayText(int32 DayValue);
    UFUNCTION() void StarNewDay();
	UFUNCTION(BlueprintNativeEvent) void PlayAnim();
	UPROPERTY(EditAnywhere) AEYS_MyCharacterController* myPC;
	
};
