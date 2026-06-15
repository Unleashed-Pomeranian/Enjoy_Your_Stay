//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesUIButton.h"
#include "UObject/Interface.h"
#include "UObject/Package.h"
#include "Animation/AnimMontage.h"
#include "QuickDialoguesValueInterface.generated.h"

USTRUCT(BlueprintType)
struct FQuickDialoguesPlayMontageNodeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MontageData")
	UAnimMontage* MontageToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MontageData")
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MontageData")
	FName StartSectionName = NAME_None;
};

UINTERFACE(Blueprintable)
class UQuickDialoguesValueInterface : public UInterface
{
	GENERATED_BODY()
};


class QUICKDIALOGUES_API IQuickDialoguesValueInterface
{
	GENERATED_BODY()
	
public:
	virtual void SetDialogue(FText InText);
	virtual FText GetNodeDialogueData();
	virtual TArray<FDialogueReply> GetReplies();
	virtual void SetChosenIndex(int InIndex);
	virtual TSubclassOf<UUserWidget> GetWidgetToOpen();
	virtual FQuickDialoguesPlayMontageNodeData GetMontageToPlay();
};
