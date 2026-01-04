// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_Phone.generated.h"

class AEYS_MyCharacterController;
class UEYS_Phone_UI;

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_Phone : public AActor,public IEYS_InteractInterface
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh2;




public:	
	// Sets default values for this actor's properties
	AEYS_Phone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION(BlueprintNativeEvent)  void PlayPhoneMontage(AEYS_MyCharacter* myPlayer);
	UFUNCTION(BlueprintNativeEvent)  void PlayPhoneCloseMontage();
	UFUNCTION(BlueprintCallable) void SetupAttachment(AEYS_MyCharacter* myPlayer);
	UFUNCTION(BlueprintCallable) void SetupCloseAttachment(AEYS_MyCharacter* myPlayer);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Controller")
	AEYS_MyCharacterController* PC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEYS_Phone_UI* PhoneWidgetInstance = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UEYS_Phone_UI> PhoneWidgetClass;

	UPROPERTY() bool bCanInteract= true;
	FTransform PhoneFirstTransform;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void OpenUI();
	UFUNCTION(BlueprintCallable) void CloseUI();
};
