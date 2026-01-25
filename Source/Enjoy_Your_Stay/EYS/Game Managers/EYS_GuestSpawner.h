// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_GuestSpawner.generated.h"

class AEYS_GuestCharacter;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_GuestSpawner : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEYS_GuestSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY() int32 EmptyRooms;
	UPROPERTY()  int32 Rooms;
	UFUNCTION() void SpawnGuest();
	UPROPERTY(EditAnywhere,BlueprintReadWrite) FVector SpawnLock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector LobyLoc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TSubclassOf<AEYS_GuestCharacter> GuestClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION() void SetEmptyRoom();

};
