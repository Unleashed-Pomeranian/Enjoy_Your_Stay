// Copyright (c) 2025 Elia Cantini. All rights reserved.


#include "Components/QuickDialoguesSpeakerComponent.h"

#include "QuickDialoguesNodeTree.h"
#include "QuickDialoguesValueInterface.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UQuickDialoguesSpeakerComponent::UQuickDialoguesSpeakerComponent(): Dialogue(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UQuickDialoguesSpeakerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Dialogue && GetOwner())
	{
		Dialogue->SetUp(GetOwner());
	}
}


// Called every frame
void UQuickDialoguesSpeakerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQuickDialoguesSpeakerComponent::PlayMontageOnOwner(FQuickDialoguesPlayMontageNodeData MontageData) const
{
	AActor* Owner = GetOwner();
	if (ACharacter* Character = Cast<ACharacter>(Owner))
	{
		Character->PlayAnimMontage(MontageData.MontageToPlay,MontageData.PlayRate,MontageData.StartSectionName);
	}
}
