// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_CoalBox.generated.h"

class UBoxComponent;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_CoalBox : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh_Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh_Coal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> CoalMeshes;


	
public:	
	// Sets default values for this actor's properties
	AEYS_CoalBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value) override;
	UFUNCTION() void FillingCoal(int32 AddValue);
	UFUNCTION() void DrainingCoal();
	UFUNCTION() void SetCoalMeshCoal();
	UFUNCTION(BlueprintNativeEvent) void PlayCoalAudio();

	UPROPERTY() int32 CoalAmount = 0.0f;
	UPROPERTY() bool bisTakeCoal=false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


};
