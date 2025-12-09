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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEYS_NotebookWidget> NotebookWidgetClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void CleaningMission();
	UFUNCTION() void FuelingMission();
	UFUNCTION(BlueprintCallable) void FixingMission();

	UPROPERTY()int32 CleaningFinished=0;
	UPROPERTY()int32 FuelingFinished = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)int32 FixingFinished = 0;
	UPROPERTY()int32 CleaningTotal = 0;
	UPROPERTY()int32 FuelingTotal = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)int32 FixingTotal = 0;

};
