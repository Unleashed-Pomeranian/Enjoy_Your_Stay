// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_OrderSpawner.generated.h"

class USceneComponent;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_OrderSpawner : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TArray<USceneComponent*> RackSlots;


public:
	AEYS_OrderSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UClass*> Orders;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Order System")
	TArray<bool> SlotOccupationMap;

	const int32 TotalSlotCount = 10;
public:	

	UFUNCTION() void SetOrderClass(UClass* SpawnClass);
	UFUNCTION() void SpawnOrder();

};
