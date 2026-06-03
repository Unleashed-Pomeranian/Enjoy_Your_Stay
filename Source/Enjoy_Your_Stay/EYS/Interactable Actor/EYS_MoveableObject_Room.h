// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EYS/Interactable Actor/EYS_MoveableObject.h"
#include "EYS_MoveableObject_Room.generated.h"

class AEYS_GuestCharacter;
class AEYS_DirtTarget;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MoveableObject_Room : public AEYS_MoveableObject
{
	GENERATED_BODY()

protected:
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDoorLocked = false;
    virtual void OnDoorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnDoorOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AEYS_DirtTarget*> MyRoomTargets;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	AEYS_GuestCharacter* AssignedNPCs;
};
