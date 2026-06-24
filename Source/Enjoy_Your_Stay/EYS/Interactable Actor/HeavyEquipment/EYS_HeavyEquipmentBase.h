// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS/EYS_MyCharacterController.h"
#include "EYS_HeavyEquipmentBase.generated.h"




UCLASS()
class ENJOY_YOUR_STAY_API AEYS_HeavyEquipmentBase : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEYS_HeavyEquipmentBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION() void PlayHeavyAudio();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* HeavySound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Socket")
	FName AttachedSocket = "HeavyEquipment";


public:	

	UFUNCTION(BlueprintCallable) virtual void DetachActor();
	UFUNCTION() void AttachActor(AEYS_MyCharacter* myPlayer);
	UFUNCTION() void DetachFromPlayer();
	UFUNCTION() void PlaceOnRack(AEYS_MyCharacter* myPlayer, USceneComponent* TargetSlot);
	UFUNCTION() void PlaceOnOrderSpawener( USceneComponent* TargetSlot);
	
};
