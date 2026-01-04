// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_OrderSpawner.generated.h"

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_OrderSpawner : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;



	
public:	
	// Sets default values for this actor's properties
	AEYS_OrderSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* test;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void SpawnOrder(UClass* SpawnClass);
};
