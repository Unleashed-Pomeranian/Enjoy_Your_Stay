// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_MoveableObject.generated.h"

class UBoxComponent;
class AEYS_GuestCharacter;
class UTimelineComponent;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MoveableObject : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timeline Actor | Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline Actor | Mesh", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* MovementCurve;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timeline Actor | Mesh", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timeline Actor | Mesh", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBox;
	

public:	
	// Sets default values for this actor's properties
	AEYS_MoveableObject();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	 AEYS_GuestCharacter* AssignedNPCs;

	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()  void TimelineProgress(float value);
	UFUNCTION()  void TimelineFinished();

	UFUNCTION(BlueprintCallable)
	void DoorInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline Actor | Mesh")
	UTimelineComponent* MainTimeline;
	
   

public:	
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FRotator StartRot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FRotator EndRot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotStartValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotEndValue;
	UPROPERTY(EditAnywhere)
	bool bIsTrigrred = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDoorLocked = false;
	 
	
};
