// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_TutorialHitBox.generated.h"

class UBoxComponent;
class UPostProcessComponent;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_TutorialHitBox : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	 UBoxComponent* BoxCollision;
	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	 UPostProcessComponent* PostProcessVolume;
public:	
	// Sets default values for this actor's properties
	AEYS_TutorialHitBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UFUNCTION() void SpawnEquipment(TSubclassOf<AActor> EquipmentClass);
	UFUNCTION() void SetHitBoxLocation(const FVector& NewLocation);
	



};
