// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_GuestSpawner.generated.h"

class AEYS_GuestCharacter;
class AEYS_GuestCar;
class AEYS_VehicleSplinePath;
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
	UFUNCTION() void SpawnGuestTimer();
	UFUNCTION() void StartGuestSpawning();
	UPROPERTY(EditAnywhere,BlueprintReadWrite) FVector SpawnLock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector LobyLoc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TSubclassOf<AEYS_GuestCharacter> GuestClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TSubclassOf<AEYS_GuestCar> GuestCarClass;
	UPROPERTY(EditInstanceOnly, Category = "Parking Setup")
	TArray<class AEYS_VehicleSplinePath*> ParkingEntries;
	FTimerHandle GuestTimerHandle;

public:	
	UFUNCTION() void SetEmptyRoom();
	

};
