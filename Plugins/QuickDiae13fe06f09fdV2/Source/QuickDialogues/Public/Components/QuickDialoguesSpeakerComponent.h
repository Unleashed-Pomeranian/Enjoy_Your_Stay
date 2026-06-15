// Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuickDialoguesSpeakerComponent.generated.h"

struct FQuickDialoguesPlayMontageNodeData;
class UQuickDialoguesNodeTree;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUICKDIALOGUES_API UQuickDialoguesSpeakerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuickDialoguesSpeakerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UQuickDialoguesNodeTree* GetDialogue() const {return Dialogue;}
	void PlayMontageOnOwner(FQuickDialoguesPlayMontageNodeData MontageData) const;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuickDialogues")
	UQuickDialoguesNodeTree* Dialogue;
	
};
