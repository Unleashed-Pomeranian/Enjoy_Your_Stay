// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_Boiler.generated.h"


class UBoxComponent;
class UEYS_Boiler_UI;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Boiler : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEYS_Boiler();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TArray<TObjectPtr<UAnimationAsset>> AnimAssets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle MyTimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	int32 Animvalue=0;
	float BoilerCoalValue=0.0f;
	bool bAnimFlip=true;
	UPROPERTY()
	UEYS_Boiler_UI* BoilerWidgetInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_Boiler_UI> BoilerWidgetClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void SetCoalAmount(float FuelAddValue);
	UFUNCTION(BlueprintCallable) void ReduceCoalValue();

};
