// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_StorageRack.generated.h"

class AEYS_HeavyEquipmentBase;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_StorageRack : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RackMesh;

	// 9 Adet Sahne Kökü (Slot)


	int32 CurrentSlotIndex;
public:	
	// Sets default values for this actor's properties
	AEYS_StorageRack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slots", meta = (AllowPrivateAccess = "true"))
	TArray<USceneComponent*> StorageSlots;



};
