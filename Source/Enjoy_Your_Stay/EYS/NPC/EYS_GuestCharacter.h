

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS_GuestCharacter.generated.h"

class AEYS_GuestAIController;
UCLASS(Blueprintable)
class ENJOY_YOUR_STAY_API AEYS_GuestCharacter : public ACharacter, public IEYS_InteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ThirdPersonMesh;

	UPROPERTY()
	AEYS_GuestAIController* CachedAIController;

public:
	// Sets default values for this character's properties
	AEYS_GuestCharacter();
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION()
	void HandleMoveCompleted();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	bool bCanInteract = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
