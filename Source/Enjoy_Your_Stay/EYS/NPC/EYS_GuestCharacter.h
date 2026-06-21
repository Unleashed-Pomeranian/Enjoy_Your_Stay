
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EYS/EYS_InteractInterface.h"
#include "EYS/NPC/EYS_QDialoguesSpeakerComponent.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Types.h"
#include "EYS_GuestCharacter.generated.h"


class AEYS_GuestAIController;
class AEYS_GuestCar;
class AEYS_Chair;

UENUM(BlueprintType)
enum class EGuestStatus : uint8
{
	Arriving                UMETA(DisplayName = "Arriving"),
	WaitingForCheckIn       UMETA(DisplayName = "Waiting for Registration"),
	AbandonHotel            UMETA(DisplayName = "Abandon Hotel"),
	WaitingForKey           UMETA(DisplayName = "Waiting for Key"),
	GoingToRoom             UMETA(DisplayName = "Going to Room"),
	InRoom                  UMETA(DisplayName = "In Room"),
	DirtyRoom               UMETA(DisplayName = "DirtyRoom"),
	GoToDiningHall            UMETA(DisplayName = "Go To Dining Hall"),
	WaitingForOrder          UMETA(DisplayName = "Waiting for Order"),
	WaitingForFood         UMETA(DisplayName = "Waiting for Food"),
	TakeFood                UMETA(DisplayName = "Take Food"),
	WrongOrder               UMETA(DisplayName = "Wrong Order"),
	GoToSit                  UMETA(DisplayName = "Go To Sit"),
	Sitting                  UMETA(DisplayName = "Sitting"),
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
	void InteractUI_Implementation(AEYS_MyCharacter* myPlayer, bool bIsFocused) override;
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
	bool bIsCheckOut = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DialogueNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCarrying = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSitting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDriving = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MentalSlateValue = 100.0f;
	UPROPERTY()
	int32 CheckOutDay;
	float CheckOutTime;


protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnyWhere,BlueprintReadWrite) FVector RoomLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UEYS_QDialoguesSpeakerComponent* DialogueComponent;
	
	UFUNCTION(BlueprintNativeEvent) void PlayNPCAudio();
	UFUNCTION() void OrderFood(AEYS_MyCharacter* myPlayer);
	UFUNCTION() void CheckFood(AEYS_MyCharacter* myPlayer);
	UFUNCTION() void TakeFood(AEYS_MyCharacter* myPlayer);
	UFUNCTION() void SitOnChair();
	UFUNCTION() void SetDinnerTime();
	UFUNCTION() void FGuestAbandon();
	UFUNCTION() void OnDialogueFinished();
	UFUNCTION() void FinishDining();
	UFUNCTION()	void TriggerHotelCheckOut();
	UFUNCTION()	void FSpendMoney(const int32 Value);

public:	
	UFUNCTION(BlueprintCallable) virtual void MoveTo(FVector Target,float AccceptanceRadius);
	UFUNCTION() void CheckOut(AEYS_MyCharacter* myPlayer);
	UFUNCTION() void SetGuestMesh(USkeletalMesh* GuestSkin);
	UFUNCTION()	void SetMentalHealth(const float Value);
	UPROPERTY() AEYS_GuestCar* AssignedCar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	EGuestStatus CurrentStatus;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)  FVector DiningHallLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) ERoomID GuestRoomID;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FVector LobyLocation;

	//UFUNCTION() void CorruptTheGuest()
	/*--Timers--*/
	FTimerHandle AbandonTimer;
	FTimerHandle OrderTimer;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly) float AbandonTime = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float HallAbandonTime = 30.0f;

	protected:
	/*--FoodItems--*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EFoodType FoodOrder;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EFoodType DrinkOrder;
	FTimerHandle SitTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UEYS_Guest_UI* GuestWidgetInstance = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UEYS_Guest_UI> GuestWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class AEYS_Tray* GuestTray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Movement")
	AEYS_Chair* TargetChair = nullptr;
	int32 OrderScore = 0;
};
