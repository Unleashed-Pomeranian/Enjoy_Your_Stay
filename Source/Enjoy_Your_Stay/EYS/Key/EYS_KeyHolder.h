// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS/Interactable Actor\HeavyEquipment\EYS_Types.h"
#include "EYS_KeyHolder.generated.h"

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_KeyHolder : public AActor , public IEYS_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEYS_KeyHolder();

	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;


   UFUNCTION(BlueprintCallable)
   void UpdateKeyDisplay(ERoomID TargetRoom, bool bNewVisibility);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 LastRoomNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector LastLocation;
};
