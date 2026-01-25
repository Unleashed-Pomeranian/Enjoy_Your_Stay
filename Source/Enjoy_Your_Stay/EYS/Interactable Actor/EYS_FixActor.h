// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_FixActor.generated.h"
class AEYS_Boiler;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_FixActor : public AActor,public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> PipeMeshes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	FTimerHandle MyTimerHandle;
    
public:	
	// Sets default values for this actor's properties
	AEYS_FixActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	void aInteract_Implementation(AEYS_MyCharacter* myPlayer, int32 Value) override;
	UFUNCTION() void SetPipeMesh();
	UPROPERTY(BlueprintReadOnly) float FixValue = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UClass* SinglePipeRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) AEYS_Boiler* BoilerActor;
	
	UFUNCTION() void SetBoilerFuel();
	UFUNCTION(BlueprintNativeEvent) void PlayFixAudio();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
