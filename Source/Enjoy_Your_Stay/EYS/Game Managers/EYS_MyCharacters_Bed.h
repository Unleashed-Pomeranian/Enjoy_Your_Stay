// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_MyCharacters_Bed.generated.h"

class AEYS_MySunMoonDaySequenceActor;
class UEYS_Day_UI;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_MyCharacters_Bed : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "True"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAcces = "True"))
	UStaticMeshComponent* StaticMesh;
	
public:	
	// Sets default values for this actor's properties
	AEYS_MyCharacters_Bed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Actor", meta = (AllowPrivateAcces = "True"))
	 AEYS_MySunMoonDaySequenceActor* DayCycleActor;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	 TSubclassOf<UEYS_Day_UI> DayWidgetClass;

	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	 UEYS_Day_UI* DayWidgetInstance = nullptr;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
