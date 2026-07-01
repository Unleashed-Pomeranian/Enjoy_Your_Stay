
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "EYS/Interactable Actor/HeavyEquipment/EYS_Types.h"
#include "EYS_TutorialSubsystem.generated.h"

UENUM(BlueprintType)
enum class ETutorialStep: uint8
{
	None UMETA(DisplayName = "No Mission"),
	GoToEntrance  UMETA(DisplayName = "Walk to Main Door"),
	TakeFlashlight  UMETA(DisplayName = "Take Flashlight"),
	GoToBoosRoom  UMETA(DisplayName = "Go to Boos Room"),
	TalkWithBoss  UMETA(DisplayName = "Talk With Boss"),
	GoToGenerator UMETA(DisplayName = "Go to Generator"),
	InteractWithGenerator  UMETA(DisplayName = "Interact With Generator"),
	SpawnFirstHorrorActor UMETA(DisplayName = "Spawn First Horror Actor"),
	ActivateGenerator UMETA(DisplayName = "Activate Generator"),
	FindMop UMETA(DisplayName = "Find Mop"),
	TakeMop UMETA(DisplayName = "Take Mop"),
	CleanDirt UMETA(DisplayName = "Clean Dirt"),
	GoToBasement UMETA(DisplayName = "Go To Basement"),
	TakeShovel UMETA(DisplayName = "Take Shovel"),
	SpawnSecondHorrorActor UMETA(DisplayName = "Spawn Second Horror Actor"),
	GoToBoilerRoom UMETA(DisplayName = "Go to Boiler Room"),
	FillCoalBox UMETA(DisplayName = "Fill Coal Box"),
	FillBoiler UMETA(DisplayName = "Fill Boiler"),
	SpawnThirdHorrorActor UMETA(DisplayName = "Spawn Third Horror Actor"),
	GoToPhone UMETA(DisplayName = "Go to Phone"),
	TakePhone UMETA(DisplayName = "Take Phone"),
	OrderSupplies UMETA(DisplayName = "Order Supplies"),
	GoToBed  UMETA(DisplayName = "Go To Bed"),
	EndDay UMETA(DisplayName = "End Day"),
	TakeFoodBox UMETA(DisplayName = "Take Food Box"),
	GoToFridge UMETA(DisplayName = "Go to Fridge"),
	PlaceFoodBox UMETA(DisplayName = "Place Food Box"),
	FindSponge UMETA(DisplayName = "Find Sponge"),
	TakeSponge UMETA(DisplayName = "Take Sponge"),
	CleanWallDirt UMETA(DisplayName = "Clean Wall Dirt"),
	GoToSnowPile UMETA(DisplayName = "Go To Snow Pile"),
	ShovelSnowPile UMETA(DisplayName = "Shovel Snow Pile"),
	WaitTheGuest UMETA(DisplayName = "Wait the Guest"),
	TalkWithGuest UMETA(DisplayName = "Talk With Guest"),
	TakeKey UMETA(DisplayName = "Take Key"),
	GiveKeyToGuest UMETA(DisplayName = "Give Key to Guest"),
	SpawnFourthHorrorActor UMETA(DisplayName = "Spawn Fourth Horror Actor"),
	WaitGuestOrder UMETA(DisplayName = "Wait Guest Order"),
	TakeGuestOrder UMETA(DisplayName = "Take Guest Order"),
	TakeTray   UMETA(DisplayName = "Take Tray"),
	TakeFoodBag UMETA(DisplayName = "Take Food Bag"),
	GiveTrayToGuest UMETA(DisplayName = "Give Tray To Guest"),
	GiveWrongFood UMETA(DisplayName = "Give Wrong Food"),
	GiveRightFood UMETA(DisplayName = "Give Right Food"),
	WaitForPipe UMETA(DisplayName = "Wait For Pipe"),
	GoToHammer UMETA(DisplayName = "Go to Hammer"),
	TakeHammer UMETA(DisplayName = "Take Hammer"),
	FixBrokenPipe UMETA(DisplayName = "Fix Broken Pipe"),
	GoToBedSecond  UMETA(DisplayName = "Go To Bed Second"),
	WaitForCheckout UMETA(DisplayName = "Wait for Checkout"),
	CheckoutGuest UMETA(DisplayName = "Checkout Guest"),
	PutKey UMETA(DisplayName = "Put Key"),
	GoToGuestRoom  UMETA(DisplayName = "Go To Guest Room"),
	CleanCheckOutDirts UMETA(DisplayName = "Clean Checkout Dirts"),
	TakeDirtySheet UMETA(DisplayName = "Take Dirty Sheet"),
	GoToLaundryRoom UMETA(DisplayName = "Go to Washing Room"),
	OpenWashingMachine UMETA(DisplayName = "Open Washing Machine"),
	PlaceDirtySheet UMETA(DisplayName = "Place Dirty Sheet"),
	TakeDetergent UMETA(DisplayName = "Take Detergent"),
	FillDetergent UMETA(DisplayName = "Fill Detergent"),
	StartWashingMachine UMETA(DisplayName = "StartWashingMachine"),
	WaitForWashEnd UMETA(DisplayName = "WaitForWashEnd"),
	TakeCleanSheet UMETA(DisplayName = "TakeCleanSheet"),
	PutCleanSheet UMETA(DisplayName = "PutCleanSheet"),
	GoToBedThird  UMETA(DisplayName = "Go To Bed Third"),
	WaitForUpdate UMETA(DisplayName = "Wait for Update"),
	GoToComputer  UMETA(DisplayName = "Go to Computer"),
	OpenComputer UMETA(DisplayName = "Open Computer"),
	MakeAnyUpgrade   UMETA(DisplayName = "Make Any Update"),
	CloseComputer     UMETA(DisplayName = "Close Computer"),
	EndTutorial       UMETA(DisplayName = "End Tutorial"),

};
UENUM(BlueprintType)
enum class ETutorialPhase : uint8
{
	NoPhase          UMETA(DisplayName = "No Phase"),
	FirstPhase       UMETA(DisplayName = "First Phase"),
	SecondPhase      UMETA(DisplayName = "Second Phase"),
	ThirdPhase        UMETA(DisplayName = "Third Phase"),
};
USTRUCT(BlueprintType)
struct FTutorialMissionData:public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission Data")
	FText MissionObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission Data")
	FText SubtitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission Data")
	float SubtitleDuration = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission Data")
	class USoundBase* BossAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission Data")
	FVector HitBoxLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission Data")
	TSubclassOf<AActor> EquipmentRef = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission Data")
	float DayTime = 10.0f;

};

class UEYS_MyCharacter_UI;
class AEYS_BossSpeaker;
class AEYS_TutorialHitBox;
class AEYS_MySunMoonDaySequenceActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirstPhaseEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSecondPhaseEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThirdPhaseEnd);
UCLASS()
class ENJOY_YOUR_STAY_API UEYS_TutorialSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadWrite, Category = "Tutorial")
	ETutorialStep CurrentStep = ETutorialStep::None;
	UPROPERTY(BlueprintReadWrite, Category = "Tutorial")
	ETutorialPhase CurrentPhase = ETutorialPhase::NoPhase;
	UPROPERTY(BlueprintReadWrite, Category = "Tutorial")
	bool bIsTutorialFinished = false;

	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void UpdateTutorialState(ETutorialStep RequiredStep, ETutorialStep NextStep);
	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void SetTutorialStep(ETutorialStep NewStep);
	void CheckTutorialPhase();
	void FinishTutorial();


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Tutorial Data")
	UDataTable* MissionDataTable;

	/*---------------------Tutorial Classes------------------------*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEYS_MyCharacter_UI* MyCharacterUIIns = nullptr;
	UPROPERTY(EditAnywhere, Category = "Audio")
	AEYS_BossSpeaker* TargetSpeaker;
	UPROPERTY(EditAnywhere, Category = "Hitbox")
	AEYS_TutorialHitBox* TargetHitBox;
	UPROPERTY(EditAnywhere, Category = "DaySequenceActor")
	AEYS_MySunMoonDaySequenceActor* DayManager;

	/*---------------------Order Tutorial------------------------*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial Settings")
	TArray<TSubclassOf<AActor>> RequiredOrderItems;


	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void RegisterNewOrder(const TArray<TSubclassOf<AActor>>& OrderedItemClasses);

	/*---------------------FoodBox Tutorial------------------------*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial Settings")
	TArray<EFoodType> FilledFridgeSlots;

	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void RegisterFilledSlot(EFoodType FilledType);

	/*---------------------Checkout Dirt Tutorial------------------------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial Settings")
	int32 DirtValue = 0;
	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void RegisterCheckoutDirt();
	

	/*---------------------Delegate------------------------*/

	UPROPERTY(BlueprintAssignable, Category = "Tutorial")
	FOnFirstPhaseEnd OnFirstPhaseEnd;
	UPROPERTY(BlueprintAssignable, Category = "Tutorial")
	FOnSecondPhaseEnd OnSecondPhaseEnd;

	UPROPERTY(BlueprintAssignable, Category = "Tutorial")
	FOnThirdPhaseEnd OnThirdPhaseEnd;
};
