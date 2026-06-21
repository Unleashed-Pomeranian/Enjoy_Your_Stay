// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"
#include "EYS_LightBase.generated.h"


UCLASS()
class ENJOY_YOUR_STAY_API AEYS_LightBase : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LightMesh;
	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	ULightComponent* LightComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* DynamicLightMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EYS | Light Settings", meta = (AllowPrivateAccess = "true"))
	FName EmissiveParamName = FName("Emissive");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EYS | Light Settings", meta = (AllowPrivateAccess = "true"))
	bool bHasPower = false;
public:	
	// Sets default values for this actor's properties
	AEYS_LightBase();
	UFUNCTION(BlueprintCallable, Category = "EYS | Light")
	void ToggleLight(bool bActivate);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;





};
