
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS/NPC/EYS_QDialoguesSpeakerComponent.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Types.h"
#include "EYS_GuestCharacter.generated.h"


class AEYS_GuestAIController;
class AEYS_FoodBag;
class AEYS_GuestCar;

UENUM(BlueprintType)
enum class EGuestStatus : uint8
{
	Arriving                UMETA(DisplayName = "Arriving"),
	WaitingForCheckIn  UMETA(DisplayName = "Waiting for Registration"),
	AbandonHotel UMETA(DisplayName = "Abandon Hotel"),
	WaitingForKey  UMETA(DisplayName = "Waiting for Key"),
	GoingToRoom             UMETA(DisplayName = "Going to Room"),
	InRoom                  UMETA(DisplayName = "In Room"),
	WaitingForFood          UMETA(DisplayName = "Waiting for Food"),
	GoToCheckOut             UMETA(DisplayName = "Go Check Out"),
	ReadyToCheckOut         UMETA(DisplayName = "Ready to Check Out"),
	Leaving                 UMETA(DisplayName = "Leaving")

};
UCLASS(Blueprintable)
class ENJOY_YOUR_STAY_API AEYS_GuestCharacter : public ACharacter, public IEYS_InteractInterface
{
	GENERATED_BODY()

	

	UPROPERTY()
	AEYS_GuestAIController* CachedAIController;


public:
	// Sets default values for this character's properties
	AEYS_GuestCharacter();
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer) override;
	virtual void Interact(AEYS_MyCharacter* myPlayer) override;
	void eInteract_Implementation(AEYS_MyCharacter* myPlayer) override;
	UFUNCTION()
	void HandleMoveCompleted();
	void TakeKey(AEYS_MyCharacter* myPlayer);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ThirdPersonMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	class AEYS_MyCharacter* MyCharacter = nullptr;
public:
	UFUNCTION()
	void GuestStartDialogue(AEYS_MyCharacter* myPlayer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bisDialogueEnd = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanInteract = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHaveRoom = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOrderFood = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCheckOut = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DialogueNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEYS_FoodBag* FoodBagRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MentalSlateValue = 100.0f;
	UPROPERTY()
	int32 CheckOutDay;
	float CheckOutTime;


protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnyWhere,BlueprintReadWrite) FVector RoomLocation;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)  FVector DiningHallLocation;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) int32 RoomNumber;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UEYS_QDialoguesSpeakerComponent* DialogueComponent;
	
	UFUNCTION(BlueprintNativeEvent) void PlayNPCAudio();
	
public:	


	UFUNCTION(BlueprintCallable) virtual void MoveTo(FVector Target,float AccceptanceRadius);
	UFUNCTION() void OnDialogueFinished();

	UFUNCTION() void OrderFood();
	UFUNCTION() void FGuestAbandon();
	UFUNCTION() void TakeFood(AEYS_MyCharacter* myPlayer);
	UFUNCTION() void DestroyFoodBag();
	UFUNCTION() void CheckOut(AEYS_MyCharacter* myPlayer);
	UFUNCTION() void SetGuestMesh(USkeletalMesh* GuestSkin);
	UPROPERTY() AEYS_GuestCar* AssignedCar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	EGuestStatus CurrentStatus;
	

	//UFUNCTION() void CorruptTheGuest()
	/*--Timers--*/
	FTimerHandle AbandonTimer;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly) float AbandonTime = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float HallAbandonTime = 30.0f;

};
