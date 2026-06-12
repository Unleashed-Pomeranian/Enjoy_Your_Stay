// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "EYS_Notebook.generated.h"


class UEYS_NotebookWidget;


UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Notebook : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetMesh;

	
public:	
	// Sets default values for this actor's properties
	AEYS_Notebook();
	UPROPERTY()
	UEYS_NotebookWidget* NotebookWidgetInstance;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_NotebookWidget> NotebookWidgetClass;

public:	


	UFUNCTION() void CleaningMission(int32 Finished, int32 Total);
	UFUNCTION() void FuelingMission(int32 Finished, int32 Total);
	UFUNCTION() void FixingMission(int32 Finished, int32 Total);
	UFUNCTION() void BoilerMission(int32 Finished, int32 Total);
	UFUNCTION() void SnowPileMission(int32 Finished, int32 Total);


};
