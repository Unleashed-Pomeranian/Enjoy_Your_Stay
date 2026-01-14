// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/QuickDialoguesListenerComponent.h"
#include "EYS_QDialoguesListenerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENJOY_YOUR_STAY_API UEYS_QDialoguesListenerComponent : public UQuickDialoguesListenerComponent
{
	GENERATED_BODY()

	
	

public:
	UFUNCTION() void FStartDialogue(UQuickDialoguesNodeTree* Dialogue,UQuickDialoguesSpeakerComponent* Speaker);
	FOnDialogueEnd& GetOnDialogueEndDelegate();
};
