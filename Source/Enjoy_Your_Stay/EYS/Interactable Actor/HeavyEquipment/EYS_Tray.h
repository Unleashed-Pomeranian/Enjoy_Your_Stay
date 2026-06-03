// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_HeavyEquipmentBase.h"
#include "EYS_Types.h"
#include "EYS_Tray.generated.h"

/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Tray : public AEYS_HeavyEquipmentBase
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

	virtual void DettachActor() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UChildActorComponent* Slot1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UChildActorComponent* Slot2;

	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;

	EFoodType Slot1FoodType;
	EFoodType Slot2FoodType;

public:
	AEYS_Tray();

	
	void SetItemToSlot(int32 SlotIndex, TSubclassOf<class AActor> ItemClass, EFoodType NewFoodType);

	
	bool IsSlotEmpty(int32 SlotIndex) const;
	EFoodType GetFoodTypeInSlot(int32 SlotIndex) const;
	EItemType GetItemTypeInSlot(int32 SlotIndex) const;
	UFUNCTION() int32 CheckItemTypes(TArray<EFoodType> GuestOrders);
	UFUNCTION() void CleanSlots();

};
