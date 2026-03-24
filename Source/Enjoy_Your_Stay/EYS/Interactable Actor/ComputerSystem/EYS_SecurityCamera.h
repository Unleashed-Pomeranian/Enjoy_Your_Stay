
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "EYS_SecurityCamera.generated.h"

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_SecurityCamera : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* SceneCaptureComponent2D;
	
public:	
	// Sets default values for this actor's properties
	AEYS_SecurityCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly) 
	TArray<FTransform> CamTransforms;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void SetCameraLocation(int32 value);
	int32 CamNum=0;
};
