// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_InteractableActor.generated.h"


UCLASS()
class ENJOY_YOUR_STAY_API AEYS_InteractableActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
	
	
public:	
	// Sets default values for this actor's properties
	AEYS_InteractableActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EquipmentI", meta = (AllowPrivateAccess = "true"))
	int32 Index;

	UFUNCTION(BlueprintNativeEvent) void FActionStart(AEYS_MyCharacter* myPlayer);
	UFUNCTION(BlueprintNativeEvent) void FSecondAction(AEYS_MyCharacter* myPlayer);
};
