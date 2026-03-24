// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_Computer.generated.h"


class UEYS_ComputerLoading_UI;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Computer : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
public:	
	// Sets default values for this actor's properties
	AEYS_Computer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION() void OpenComputer();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UEYS_ComputerLoading_UI> ComputerLoadingWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UEYS_ComputerLoading_UI* ComputerLoadingWidgetInstance;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
