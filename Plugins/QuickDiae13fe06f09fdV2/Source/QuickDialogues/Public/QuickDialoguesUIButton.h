//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "QuickDialoguesUIButton.generated.h"

class UOverlay;
class UButton;
class UTextBlock;

UCLASS(Blueprintable)
class QUICKDIALOGUES_API UQuickDialoguesUIButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	/**
	 * Setups the button with its index and text
	 * @param InText the text that should be displayed on top of the button
	 * @param InIndex the index of the button in the reply node
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	void SetupButton(const FText& InText, int32 InIndex);

	/**
	 * @return the index of this button in the reply node 
	 */
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	int32 GetIndex() const { return Index; }

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	UPROPERTY(meta = (BindWidget))
	UOverlay* ButtonOverlay;

	/**
	 * The text that should be displayed on top of the button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Text;

	/**
	 * the index of this button in the reply node 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 Index;
};

USTRUCT(BlueprintType)
struct QUICKDIALOGUES_API FDialogueReply
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	TSubclassOf<UQuickDialoguesUIButton> SelectedClass;
};
