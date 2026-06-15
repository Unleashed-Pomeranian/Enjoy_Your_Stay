// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EYS_BabaYaga.generated.h"

UENUM(BlueprintType)
enum class EBabaYagaState : uint8
{
	Patrolling    UMETA(DisplayName = "Patrolling"),
	Chasing       UMETA(DisplayName = "Chasing"),
	Catch         UMETA(DisplayName = "Catch")
};

UCLASS()
class ENJOY_YOUR_STAY_API AEYS_BabaYaga : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;
public:
	AEYS_BabaYaga();

	// Hız ve durum yönetim fonksiyonu ke gulum
	void SetMovementState(EBabaYagaState NewState);

	// Rastgele devriye döngüsü tetiği
	void StartPatrol();

	UFUNCTION() void PlayBabaYagaSound(int32 Index);
	FORCEINLINE EBabaYagaState GetMovementState() const { return CurrentState; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EYS | BabaYaga")
	TArray<class USoundBase*> BabaYagaSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EYS | BabaYaga")
	float PatrolSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EYS | BabaYaga")
	float ChaseSpeed = 500.0f; 


private:
	EBabaYagaState CurrentState;
};
