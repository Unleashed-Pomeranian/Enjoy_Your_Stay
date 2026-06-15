// Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickDialoguesSpeakerComponent.h"
#include "QuickDialoguesValueInterface.h"
#include "Components/ActorComponent.h"
#include "QuickDialoguesListenerComponent.generated.h"

class UQuickDialoguesSpeakerComponent;
struct FDialogueReply;
class UQuickDialoguesBaseNode;
class UQuickDialoguesNodeTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContinueDialogue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueStart);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueTextUpdated, FText, NetText);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayMontageNodeReached, FQuickDialoguesPlayMontageNodeData, MontageData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWidgetOpenerNodeReached, TSubclassOf<UUserWidget>, WidgetToOpen);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueReplyNodeReached, TArray<FDialogueReply>, Replies);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUICKDIALOGUES_API UQuickDialoguesListenerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuickDialoguesListenerComponent();

protected:
	UFUNCTION(BlueprintCallable, Category = "QuickDialogues")
	void SearchForDialogues(const FVector InSpherePos, float InSphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery>>& InObjectTypes, UClass* InActorClassFilter, const TArray<AActor*>& InActorsToIgnore);

	UFUNCTION(BlueprintCallable, Category = "QuickDialogues")
	void StartDialogue(UQuickDialoguesNodeTree* InDialogue, UQuickDialoguesSpeakerComponent* InSpeaker);
	
	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	void EndDialogue();

	UFUNCTION(BlueprintCallable, Category = "QuickDialogues")
	virtual void HandleNode(UQuickDialoguesBaseNode* CurrentNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	void ContinueDialogue();

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandleRootNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandleDialogueNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandleEndPointNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandleReplyNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandleWidgetOpenerNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandlePlayMontageNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandleRandomNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, Category="QuickDialogues")
	virtual void HandleLoopbackNode(UQuickDialoguesBaseNode* InNode);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="QuickDialogues")
	UQuickDialoguesNodeTree* GetCurrentDialogue();
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(BlueprintAssignable, Category = "QuickDialogues")
	FOnDialogueTextUpdated OnDialogueTextUpdated;

	UPROPERTY(BlueprintAssignable, Category = "QuickDialogues")
	FOnDialogueEnd OnDialogueEnd;

	UPROPERTY(BlueprintAssignable, Category = "QuickDialogues")
	FOnDialogueStart OnDialogueStart;

	UPROPERTY(BlueprintAssignable, Category = "QuickDialogues")
	FOnContinueDialogue OnContinueDialogue;

	UPROPERTY(BlueprintAssignable, Category = "QuickDialogues")
	FOnDialogueReplyNodeReached OnDialogueReplyNodeReached;

	UPROPERTY(BlueprintAssignable, Category = "QuickDialogues")
	FOnWidgetOpenerNodeReached OnWidgetOpenerNodeReached;

	UPROPERTY(BlueprintAssignable, Category = "QuickDialogues")
	FOnPlayMontageNodeReached OnPlayMontageNodeReached;

	bool HasReachedDialogueEnd;

	TObjectPtr<UQuickDialoguesNodeTree> CurrentDialogue;

	TWeakObjectPtr<UQuickDialoguesSpeakerComponent> CurrentSpeaker;
	
};
