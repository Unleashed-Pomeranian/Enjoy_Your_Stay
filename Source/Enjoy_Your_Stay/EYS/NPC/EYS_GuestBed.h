// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EYS/EYS_InteractInterface.h"
#include "EYS/Interactable Actor\HeavyEquipment\EYS_Types.h"
#include "EYS_GuestBed.generated.h"


class AEYS_Sheet;
UCLASS()
class ENJOY_YOUR_STAY_API AEYS_GuestBed : public AActor, public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SheetMesh;


	
public:	
	// Sets default values for this actor's properties
	AEYS_GuestBed();

protected:

	virtual void BeginPlay() override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "RoomID", meta = (AllowPrivateAccess = "true"))
	ERoomID BedRoomID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoomID", meta = (AllowPrivateAccess = "true"))
	bool bIsBedDirty=false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RoomID", meta = (AllowPrivateAccess = "true"))
	bool bIsHasSheet=true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AEYS_Sheet> SheetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UStaticMesh*> SheetMeshes;
	UFUNCTION() void  SetSheetStatus(bool bIsSheetDirty);
	UFUNCTION() void  SetSheetMesh(bool bIstakingSheet);
	UFUNCTION(BlueprintNativeEvent) void  PlayAudioAndVFX();

public:	


};
