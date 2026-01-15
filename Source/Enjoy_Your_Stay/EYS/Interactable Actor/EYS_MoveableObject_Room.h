// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/EYS_MoveableObject.h"
#include "EYS_MoveableObject_Room.generated.h"

class AEYS_GuestCharacter;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MoveableObject_Room : public AEYS_MoveableObject
{
	GENERATED_BODY()

protected:
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDoorLocked = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	AEYS_GuestCharacter* AssignedNPCs;
};
