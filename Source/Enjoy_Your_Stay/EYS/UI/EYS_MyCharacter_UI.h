// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "EYS_MyCharacter_UI.generated.h"


class UImage;
class UOverlay;
class UProgressBar;
class URichTextBlock;
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_MyCharacter_UI : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	
	
	UPROPERTY(meta = (BindWidget))
	UImage* Stamina_Image;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UOverlay* Overlay;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* Stamina_ProgressBar;
public:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
    UTextBlock* Interaction_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Money_Text;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Hour_Text;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* Text_Subtitle;
	UPROPERTY(meta = (BindWidget))
	UImage* Dot_Image;
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* Text_Mission;

protected:
	UFUNCTION() void SetStaminaBar(float StaminaValue,bool bIsRecovery);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Color")
	TArray<FLinearColor> BarColors;
public:
	UFUNCTION(BlueprintNativeEvent) void SetSubtitle(const FText& Subtitle,float Duration);
	UFUNCTION() void SetMissionText(const FText& MissionText);

	
};
