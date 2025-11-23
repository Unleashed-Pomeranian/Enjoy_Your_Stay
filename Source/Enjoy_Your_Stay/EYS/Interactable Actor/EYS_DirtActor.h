// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/EYS_InteractInterface.h"
#include "GameFramework/Actor.h"
#include "EYS_DirtActor.generated.h"

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_DirtActor : public AActor ,public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DirtMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* DynMath;

	
public:	
	// Sets default values for this actor's properties
	AEYS_DirtActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer) override;

public:	
	// Called every frame
	
	

	float opacityValue = 1.0f;
	float cleaningValue= 0.004f;
};
