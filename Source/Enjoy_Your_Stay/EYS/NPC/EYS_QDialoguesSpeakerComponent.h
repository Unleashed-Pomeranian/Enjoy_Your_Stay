// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/QuickDialoguesSpeakerComponent.h"
#include "EYS_QDialoguesSpeakerComponent.generated.h"

/**
 * 
 */
class AEYS_MyCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENJOY_YOUR_STAY_API UEYS_QDialoguesSpeakerComponent : public UQuickDialoguesSpeakerComponent
{
	GENERATED_BODY()


public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuickDialogues")
    bool bRandomDialogueOnBeginPlay = true;

    // Seçilecek adaylar
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuickDialogues")
    TArray<UQuickDialoguesNodeTree*> DialoguePool;
    UFUNCTION(BlueprintCallable)
    void SetDialogueRuntime();
    UFUNCTION() void StartDialogue(AEYS_MyCharacter* myPlayer,int32 dialogueindex);
    UPROPERTY(EditAnywhere)
    AEYS_MyCharacter* MyPlayer;
protected:
    virtual void BeginPlay() override;
};
