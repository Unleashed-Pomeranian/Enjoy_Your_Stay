// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/EYS_InteractInterface.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "EYS_EquipmentWheel.h"
#include "Components/WidgetComponent.h"
#include "Components/PointLightComponent.h"
#include "EYS_Generator.generated.h"

class UEYS_GeneratorActivateWidget;
class AEYS_MyCharacterController;
class AEYS_FuelTank;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Generator : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Fuelingpoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* PointLight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;

	
public:	
	// Sets default values for this actor's properties
	AEYS_Generator();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool bIsWorking = false;
	UFUNCTION() void StartStopTimer();
	UFUNCTION() void SetLightColor(int32 ColorValue);

	
protected:
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	UFUNCTION() bool BrokeGenerator();
	UFUNCTION() void ReduceFuel();
	UFUNCTION() void AddFuel();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
	AEYS_MyCharacterController* PC;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_GeneratorActivateWidget> GeneratorActivateWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEYS_GeneratorActivateWidget* GeneratorActivateWidgetInstance = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FLinearColor> LightColor;
	UPROPERTY()
	AEYS_FuelTank* CurrentFuelTank = nullptr;
	UFUNCTION(BlueprintNativeEvent) void PlayActivateSound();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFuelMissionActive=false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varible")
	float fuelAmount = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varible")
	float GeneratorConsumptionValue = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Varible")
	float GeneratorConsumptionMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EYS | Generator")
	float BreakdownChance = 0.5f;
	bool bAnimFlip = true;
	//Timers
	FTimerHandle TimerHandle_ReduceFuel;
	FTimerHandle TimerHandle_AddFuel;
	//Subsystems
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UEYS_MissionSubsystem* MissionSubsystem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class  UEYS_WorldSubsystem* WorldSubsystem;

public:
	UFUNCTION(BlueprintNativeEvent) void PlayNaturalSound(bool bIsWork);

};
