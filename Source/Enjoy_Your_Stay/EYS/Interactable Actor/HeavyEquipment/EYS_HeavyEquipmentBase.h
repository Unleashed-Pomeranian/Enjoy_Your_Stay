// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_HeavyEquipmentBase.generated.h"



UCLASS()
class ENJOY_YOUR_STAY_API AEYS_HeavyEquipmentBase : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
public:	
	// Sets default values for this actor's properties
	AEYS_HeavyEquipmentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION() void AttachActor(AEYS_MyCharacter* myPlayer);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void DettachActor();

};
