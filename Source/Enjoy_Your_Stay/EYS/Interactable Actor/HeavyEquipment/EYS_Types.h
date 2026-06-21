

#pragma once

#include "CoreMinimal.h"
#include "EYS_Types.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None       UMETA(DisplayName = "None"),
	Food      UMETA(DisplayName = "Food"),
	Drink   UMETA(DisplayName = "Drink"),
};
UENUM(BlueprintType)
enum class EFoodType : uint8
{
	//Food
	None       UMETA(DisplayName = "None", Category = "None"),
	Kasha      UMETA(DisplayName = "Kasha", Category = "Food"),
	Vareniki   UMETA(DisplayName = "Vareniki" ,Category = "Food"),
	Pirozhki   UMETA(DisplayName = "Pirozhki" ,Category = "Food"),
	Medovik    UMETA(DisplayName = "Medovik" ,Category = "Food"),
	//Drink
	Kefir_Strawberry    UMETA(DisplayName = "Strawberry Kefir",Category = "Drink"),
	Kefir_Blueberry     UMETA(DisplayName = "Blueberry Kefir", Category = "Drink"),
	Kefir_Banana         UMETA(DisplayName = "Banana Kefir", Category = "Drink"),
	Kefir_Peach         UMETA(DisplayName = "Peach Kefir", Category = "Drink"),

	Count             UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FFoodDatabase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsActivated=false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType= EItemType::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFoodType FoodType= EFoodType::None;

};

UENUM(BlueprintType)
enum class ESurfaceType : uint8 {
	Floor   UMETA(DisplayName = "Floor"),
	Wall    UMETA(DisplayName = "Wall"),
	Exterior UMETA(DisplayName = "Exterior"),
	Horror   UMETA(DisplayName = "Horror"),
};
UENUM(BlueprintType)
enum class ERoomID : uint8
{

	None UMETA(DisplayName = "Common Area"),
	R101 UMETA(DisplayName = "101"),
	R102 UMETA(DisplayName = "102"),
	R103 UMETA(DisplayName = "103"),
	R104 UMETA(DisplayName = "104"),
};
