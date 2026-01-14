// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EYS_Guest_UI.generated.h"

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_Guest_UI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* Button_TakeOrder;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_TakeOrder;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_RejectOrder;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RejectOrder;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Customer;
	


protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void TakeOrder();
	UFUNCTION() void RejectOrder();

public:
	UFUNCTION() void SetGuestText(FString foodType, int32 roomNum);

};
