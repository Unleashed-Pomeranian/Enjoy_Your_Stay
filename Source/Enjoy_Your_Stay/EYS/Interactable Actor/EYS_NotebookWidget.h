// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "EYS_NotebookWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_NotebookWidget : public UUserWidget
{
	GENERATED_BODY()


	protected:
	UPROPERTY(meta = (BindWidget))
	UGridPanel* GridPanel;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* CleaningBox;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* FixingBox;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* FuelingBox;


	UPROPERTY(meta = (BindWidget))
	UCheckBox* CleaningCheck;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* FixingCheck;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* FuelingCheck;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* CleaningText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FixingText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FuelingText;
public:

	virtual void NativeConstruct() override;
	
	UPROPERTY()
	int32 CurentRow;

public:
	UFUNCTION() void SetCleaningBox(int32 finished,int32 total);
	UFUNCTION() void SetFixingBox(int32 finished, int32 total);
	UFUNCTION() void SetFuelingBox(int32 finished, int32 total);

	
};
