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
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value) override;

	UFUNCTION()
	void OnSnowOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varibles", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> SnowMeshes;
	float PileValue = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Varibles", meta = (AllowPrivateAccess = "true"))
	float PlowValue = 0.004f;
	UPROPERTY()
	float SecondPlowValue = 0.08f;
	UPROPERTY(BlueprintReadOnly)
	float PlowSpeedMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snow Settings")
	float SnowMentalDamage = -5.0f;

	UFUNCTION(BlueprintNativeEvent) void PlaySnowAudio();
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class AEYS_DirtTarget* MySnowTarget;

};
