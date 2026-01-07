// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "EYS_MyCharacter_UI.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_MyCharacter_UI : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	
	
	UPROPERTY(meta = (BindWidget))
	UImage* Stamina_Image;
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UOverlay* Overlay;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* Stamina_ProgressBar;
	UPROPERTY(EditAnywhere,meta = (BindWidget))
    UTextBlock* Interaction_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Money_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Hour_Text;
};
