// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/EYS_InteractInterface.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "EYS_EquipmentWheel.h"
#include "EYS_Generator.generated.h"

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

public:	
	// Sets default values for this actor's properties

	AEYS_Generator();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value) override;


	UFUNCTION() void TimerTest();
	UFUNCTION() void DestroyFuelTank(AEYS_MyCharacter* myPlayer);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintNativeEvent) void testlight();

	float fuelAmount= 0.0f;

	
};
