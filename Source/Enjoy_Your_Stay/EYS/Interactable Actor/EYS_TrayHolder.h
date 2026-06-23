// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_TrayHolder.generated.h"


class UInstancedStaticMeshComponent;
class  AEYS_Tray;
class UBoxComponent;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_TrayHolder : public AActor,public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInstancedStaticMeshComponent* InstancedStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
public:	
	AEYS_TrayHolder();

protected:

	virtual void BeginPlay() override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION() void AddTray();
	UFUNCTION() void DeleteTray();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEYS_Tray> CurrentTray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tray Settings")
	TArray<FTransform> InstanceTransform;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tray Settings")
	int32 InstanceIndex = -1;
	const int32 MaxTrayCount = 4;
};
