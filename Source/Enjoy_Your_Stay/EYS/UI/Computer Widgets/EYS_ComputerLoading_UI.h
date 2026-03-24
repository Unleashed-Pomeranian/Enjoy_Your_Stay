// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "EYS_ComputerLoading_UI.generated.h"

/**
 * 
 */

class UEYS_Computer_UI;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_ComputerLoading_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar_Loading;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Loading;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Loading;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Background;

	
protected:
	virtual void  NativeConstruct() override;
	
	UFUNCTION() void loadingto60();
	UFUNCTION() void SetSecondTimer();
	UFUNCTION() void loadingto100();
	float LoadingPercent=0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UEYS_Computer_UI> ComputerWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UEYS_Computer_UI* ComputerWidgetInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle MyTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UWidgetAnimation* WidgetAnimation;

};
