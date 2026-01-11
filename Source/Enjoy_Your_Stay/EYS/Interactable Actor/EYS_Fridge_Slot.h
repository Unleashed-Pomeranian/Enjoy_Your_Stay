// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeavyEquipment/EYS_Types.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_Fridge_Slot.generated.h"

class UBoxComponent;
class UInstancedStaticMeshComponent;
class  AEYS_FoodBag;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Fridge_Slot : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInstancedStaticMeshComponent* InstancedStaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

public:	
	// Sets default values for this actor's properties
	AEYS_Fridge_Slot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 InstanceIndex=-1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TArray<FTransform> InstanceTransform;
	UFUNCTION() void FAddSlot();
	UFUNCTION() void FDeleteSlot();
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
	EFoodType SlotFoodType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEYS_FoodBag> FoodBagActor;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
