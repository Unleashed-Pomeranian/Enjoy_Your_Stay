// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "EYS_GuestCar.generated.h"

UENUM(BlueprintType)
enum class EGuestCarState : uint8
{
	Arriving,   
	Parking,    
	Waiting,  
	Exiting,    
	Leaving     
};
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components | Lights", meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* LeftSpotLight = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components | Lights", meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* RightSpotLight = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()float GetSteeringAmount();
	UFUNCTION()void MoveCar();
	UFUNCTION()void SetGuestMesh();
	UFUNCTION() void SetGuestSpawn();
	
	bool bIsParking=false;
	bool bIsLeaving = false;
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicElement3Mat = nullptr;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicElement4Mat = nullptr;

	FTimerHandle CarTimerHandle;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<USkeletalMesh*> GuestMeshes;

	EGuestCarState CurrentState = EGuestCarState::Arriving;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TSubclassOf<AEYS_GuestCharacter> GuestClass;
public:
	/*---------Pathes-----------*/
	AEYS_GuestCar();
	UFUNCTION() void InitializeCar(AEYS_VehicleSplinePath* Path);
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AEYS_VehicleSplinePath* AssignedPath;
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AEYS_VehicleSplinePath* ExitPath;
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AEYS_VehicleSplinePath* GlobalLeavingPath;

	UFUNCTION() void DriveBack();
	UFUNCTION(BlueprintCallable) void SetCarLight(bool bIsActivate);
	UFUNCTION(BlueprintCallable) void SetCarPhysicsActive(bool bIsActive);

};
