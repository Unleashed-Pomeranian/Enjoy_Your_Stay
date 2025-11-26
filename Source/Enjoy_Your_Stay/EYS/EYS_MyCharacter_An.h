// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EYS_MyCharacter_An.generated.h"


class AEYS_MyCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_MyCharacter_An : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    virtual void NativeInitializeAnimation() override;
    UFUNCTION(BlueprintCallable)
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowAbstract = "true"))
    TObjectPtr<AEYS_MyCharacter> OwnerCharacter;

    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowAbstract = "true"))
    TObjectPtr<UCharacterMovementComponent> MoveComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim", meta = (AllowAbstract = "true"))
    float Speed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim", meta = (AllowAbstract = "true"))
    bool bIsInAir;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim", meta = (AllowAbstract = "true"))
    bool bIsInAction=false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim", meta = (AllowAbstract = "true"))
    int32 PoseNum;
   
   
    
};
