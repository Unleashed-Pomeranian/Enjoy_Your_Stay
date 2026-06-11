// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"

#include "EYS_WashingMachine.generated.h"

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_WashingMachine : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* ButtonChildComponent;
	AEYS_WashingMachine();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slots",meta = (AllowPrivateAccess = "true"))
	TArray<USceneComponent*> SheetSlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* WidgetMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Washing Machine | Audio")
	class UAudioComponent* WashingAudioComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;

	UPROPERTY(BlueprintReadOnly, Category = "Washing Machine | References")
	class AEYS_WashingMachineButton* WashingMachineButtonRef;

	UPROPERTY(BlueprintReadOnly, Category = "Washing Machine | States")
	bool bIsLidOpen = false;
	UPROPERTY(BlueprintReadOnly, Category = "Washing Machine | States")
	bool bIsWashing = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Washing Machine | States")
	float DetergentAmount = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Washing Machine | States")
	float WashingDuration = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Washing Machine | Audio")
	TArray<class USoundBase*> WashingSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Washing Machine |Animation")
	TArray<TObjectPtr<UAnimationAsset>> AnimAssets;

	FTimerHandle WashingTimerHandle;
	UFUNCTION() void PlayWashingAudio(int32 SoundIndex);
	UFUNCTION() void ToggleLid();

	UFUNCTION()	void OnWashingComplete();
	UFUNCTION() void UpdateDetergentUI();
		
public:	
	UFUNCTION() void StartWashing();

};
