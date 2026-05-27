// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_SnowPileActor.generated.h"


class UBoxComponent;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_SnowPileActor : public AActor,public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	
public:	
	// Sets default values for this actor's properties
	AEYS_SnowPileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value) override;
	float PileValue = 1.0f;
	float PlowValue = 0.004f;

	UFUNCTION(BlueprintNativeEvent) void PlaySnowAudio();
public:	


};
