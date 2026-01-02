// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/EYS_InteractInterface.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "EYS_EquipmentWheel.h"
#include "Components/WidgetComponent.h"
#include "EYS_Generator.generated.h"

class UEYS_GeneratorActivateWidget;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Generator : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* FuelText;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetMesh;
	
public:	
	// Sets default values for this actor's properties
	AEYS_Generator();
	float fuelAmount = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool bIsWorking = false;
	UFUNCTION(BlueprintNativeEvent) void testlight();
	UFUNCTION() void StartStopTimer();

	
protected:
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION() void ReduceFuel();
	UFUNCTION() void DestroyFuelTank(AEYS_MyCharacter* myPlayer);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_GeneratorActivateWidget> GeneratorActivateWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEYS_GeneratorActivateWidget* GeneratorActivateWidgetInstance = nullptr;
};
