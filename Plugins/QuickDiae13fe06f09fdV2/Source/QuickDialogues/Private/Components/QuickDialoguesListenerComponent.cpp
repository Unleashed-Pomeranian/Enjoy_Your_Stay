// Copyright (c) 2025 Elia Cantini. All rights reserved.


#include "Components/QuickDialoguesListenerComponent.h"

#include "QuickDialoguesNodeTree.h"
#include "Components/QuickDialoguesSpeakerComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Nodes/QuickDialoguesBaseNode.h"


// Sets default values for this component's properties
UQuickDialoguesListenerComponent::UQuickDialoguesListenerComponent(): HasReachedDialogueEnd(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuickDialoguesListenerComponent::SearchForDialogues(const FVector SpherePos, float SphereRadius,
                                                          const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes,
                                                          UClass* ActorClassFilter,
                                                          const TArray<AActor*>& ActorsToIgnore)
{
	if (GetWorld() && GetOwner())
	{
		AActor* Owner = GetOwner();
#if WITH_EDITOR
		DrawDebugSphere(GetWorld(), SpherePos, SphereRadius, 12, FColor::Red, false, 1.f);
#endif
		TArray<AActor*> OverlappingActors;
		UKismetSystemLibrary::SphereOverlapActors(Owner, SpherePos, SphereRadius, ObjectTypes, ActorClassFilter,
		                                          ActorsToIgnore, OverlappingActors);

		for (auto OverlappingActor : OverlappingActors)
		{
			if (!IsValid(OverlappingActor))
			{
				continue;
			}
			if (UQuickDialoguesSpeakerComponent* SpeakerComponent = OverlappingActor->GetComponentByClass<
				UQuickDialoguesSpeakerComponent>())
			{
				if (UQuickDialoguesNodeTree* Dialogue = SpeakerComponent->GetDialogue())
				{
					StartDialogue(Dialogue,SpeakerComponent);
				}
			}
		}
	}
}

UQuickDialoguesNodeTree* UQuickDialoguesListenerComponent::GetCurrentDialogue()
{
	return CurrentDialogue;
}

void UQuickDialoguesListenerComponent::StartDialogue(UQuickDialoguesNodeTree* InDialogue,
                                                     UQuickDialoguesSpeakerComponent* InSpeaker)
{
	CurrentDialogue = InDialogue;
	CurrentSpeaker = MakeWeakObjectPtr(InSpeaker);
	if (!CurrentDialogue->GetHasBeenSavedAndValidated() || !CurrentDialogue)
	{
#if WITH_EDITOR
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Dialogue was not saved");
		}
#endif
		return;
	}
	if (CurrentDialogue->GetHasCompileErrors())
	{
#if WITH_EDITOR
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Dialogue has compiles errors, please check");
		}
#endif
		return;
	}
	CurrentDialogue->ResetFromRoot();
	OnDialogueStart.Broadcast();
	ContinueDialogue();
}

void UQuickDialoguesListenerComponent::EndDialogue()
{
	CurrentDialogue = nullptr;
	CurrentSpeaker.Reset();
	HasReachedDialogueEnd = false;
	OnDialogueEnd.Broadcast();
}

void UQuickDialoguesListenerComponent::HandleNode(UQuickDialoguesBaseNode* CurrentNode)
{
	switch (CurrentNode->GetNodeType())
	{
	case EQuickDialoguesNodeType::Root:
		HandleRootNode(CurrentNode);
		break;
	case EQuickDialoguesNodeType::Dialogue:
		HandleDialogueNode(CurrentNode);
		break;
	case EQuickDialoguesNodeType::EndPoint:
		HandleEndPointNode(CurrentNode);
		break;
	case EQuickDialoguesNodeType::Reply:
		HandleReplyNode(CurrentNode);
		break;
	case EQuickDialoguesNodeType::WidgetOpener:
		HandleWidgetOpenerNode(CurrentNode);
		break;
	case EQuickDialoguesNodeType::PlayMontage:
		HandlePlayMontageNode(CurrentNode);
		break;
	case EQuickDialoguesNodeType::Random:
		HandleRandomNode(CurrentNode);
		break;
	case EQuickDialoguesNodeType::Loopback:
		HandleLoopbackNode(CurrentNode);
		break;
	default:
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Unknown node type encountered in dialogue system"));
#endif
		break;
	}
}

void UQuickDialoguesListenerComponent::ContinueDialogue()
{
	if (HasReachedDialogueEnd)
	{
		EndDialogue();
		return;
	}

	if (!IsValid(CurrentDialogue))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("Dialogue is not valid"));
#endif
		EndDialogue();
		return;
	}

	UQuickDialoguesBaseNode* CurrentNode = CurrentDialogue->GetNextNode();

	if (!IsValid(CurrentNode))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("Dialogue node is not valid"));
#endif
		EndDialogue();
		return;
	}

	OnContinueDialogue.Broadcast();
	HandleNode(CurrentNode);
}

void UQuickDialoguesListenerComponent::HandleRootNode(UQuickDialoguesBaseNode* InNode)
{
	ContinueDialogue();
}

void UQuickDialoguesListenerComponent::HandleDialogueNode(UQuickDialoguesBaseNode* InNode)
{
	FText DialogueText = InNode->GetNodeDialogueData();
	OnDialogueTextUpdated.Broadcast(DialogueText);
}

void UQuickDialoguesListenerComponent::HandleEndPointNode(UQuickDialoguesBaseNode* InNode)
{
	HandleDialogueNode(InNode);
	HasReachedDialogueEnd = true;
}

void UQuickDialoguesListenerComponent::HandleReplyNode(UQuickDialoguesBaseNode* InNode)
{
	TArray<FDialogueReply> Replies = InNode->GetReplies();
	OnDialogueReplyNodeReached.Broadcast(Replies);
	HandleDialogueNode(InNode);
}

void UQuickDialoguesListenerComponent::HandleWidgetOpenerNode(UQuickDialoguesBaseNode* InNode)
{
	TSubclassOf<UUserWidget> WidgetToOpen = InNode->GetWidgetToOpen();
	OnWidgetOpenerNodeReached.Broadcast(WidgetToOpen);
}

void UQuickDialoguesListenerComponent::HandlePlayMontageNode(UQuickDialoguesBaseNode* InNode)
{
	HandleDialogueNode(InNode);
	const FQuickDialoguesPlayMontageNodeData MontageData = InNode->GetMontageToPlay();
	if (CurrentSpeaker.IsValid())
	{
		CurrentSpeaker.Get()->PlayMontageOnOwner(MontageData);
	}
	OnPlayMontageNodeReached.Broadcast(MontageData);
}

void UQuickDialoguesListenerComponent::HandleRandomNode(UQuickDialoguesBaseNode* InNode)
{
	ContinueDialogue();
}

void UQuickDialoguesListenerComponent::HandleLoopbackNode(UQuickDialoguesBaseNode* InNode)
{
	ContinueDialogue();
}


// Called when the game starts
void UQuickDialoguesListenerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UQuickDialoguesListenerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
