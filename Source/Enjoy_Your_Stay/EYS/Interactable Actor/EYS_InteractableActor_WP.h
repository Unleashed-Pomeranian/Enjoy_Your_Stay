// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_EquipmentWheel.h"
#include "EYS_InteractableActor_WP.generated.h"

class UBoxComponent;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_InteractableActor_WP : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	
public:	
	// Sets default values for this actor's properties
	AEYS_InteractableActor_WP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EquipmentI", meta = (AllowPrivateAccess = "true"))
	int32 Index;
	UFUNCTION(BlueprintNativeEvent) void PlayEquipAudio();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


};
