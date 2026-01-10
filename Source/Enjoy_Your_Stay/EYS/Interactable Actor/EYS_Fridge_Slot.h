// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_Fridge_Slot.generated.h"

class UBoxComponent;
class UInstancedStaticMeshComponent;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Fridge_Slot : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInstancedStaticMeshComponent* InstancedStaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

public:	
	// Sets default values for this actor's properties
	AEYS_Fridge_Slot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 InstanceIndex;
	UPROPERTY() TArray<FTransform> InstanceTransform;
	UFUNCTION() void FAddSlot();
	UFUNCTION() void FDeleteSlot();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
