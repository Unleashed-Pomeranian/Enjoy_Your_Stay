// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_WashingMachineButton.generated.h"



UCLASS()
class ENJOY_YOUR_STAY_API AEYS_WashingMachineButton : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
public:	
	// Sets default values for this actor's properties
	AEYS_WashingMachineButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Washing Machine")
	class AEYS_WashingMachine* TargetWashingMachine;

	UPROPERTY(BlueprintReadOnly, Category = "Washing Machine | Animation")
	float ButtonCurrentRotation = 300.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Washing Machine | Animation")
	float ButtonStepAmount = 25.0f;
	FTimerHandle ButtonRotationTimerHandle;

	void UpdateButtonRotation();
	
public:
	FORCEINLINE void SetTargetWashingMachine(class AEYS_WashingMachine* InWashingMachine) { TargetWashingMachine = InWashingMachine; }
	bool bCanToggle = true;
	void SetButtonRotationTimer(float StepAmount,bool bIsStart);
};
