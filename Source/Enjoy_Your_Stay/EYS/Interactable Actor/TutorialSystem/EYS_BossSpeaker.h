// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS_BossSpeaker.generated.h"

class UAudioComponent;
class USoundBase;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_BossSpeaker : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpeakerMesh;

	// Sesi Çalacak Olan Bile?en
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComponent;
	
public:	
	// Sets default values for this actor's properties
	AEYS_BossSpeaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayBossMessage(USoundBase* MessageSound);

};
