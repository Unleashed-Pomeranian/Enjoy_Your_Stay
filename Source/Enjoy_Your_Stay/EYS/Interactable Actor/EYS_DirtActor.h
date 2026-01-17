// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/EYS_InteractInterface.h"
#include "GameFramework/Actor.h"
#include "EYS_DirtActor.generated.h"


class UBoxComponent;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_DirtActor : public AActor ,public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* DynMath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* DirtDecal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

	
public:	
	// Sets default values for this actor's properties
	AEYS_DirtActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value) override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<TObjectPtr<UMaterial>> DirtMaterial;
	UFUNCTION()void test();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UClass* TargetPointRef;
public:	
	// Called every frame
	
	

	float opacityValue = 3.0f;
	float cleaningValue= 0.012f;
};
