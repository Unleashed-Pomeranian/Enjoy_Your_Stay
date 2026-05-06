// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "EYS_GuestCar.generated.h"

/**
 * 
 */
class AEYS_GuestCharacter;
class AEYS_VehicleSplinePath;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_GuestCar : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CarBody;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UChaosWheeledVehicleMovementComponent* WheeledMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CharacterSkeletalMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnPoint;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()float GetSteeringAmount();
	UFUNCTION()void MoveCar();
	UFUNCTION()void SetGuestMesh();
	UFUNCTION() void SetGuestSpawn();
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AEYS_VehicleSplinePath* AssignedPath;
	bool bIsParking=false;
	FTimerHandle CarTimerHandle;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<USkeletalMesh*> GuestMeshes;
UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TSubclassOf<AEYS_GuestCharacter> GuestClass;
public:
	AEYS_GuestCar();
	
};
