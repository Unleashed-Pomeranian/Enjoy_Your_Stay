// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EYS_MissionSubsystem.generated.h"



UENUM(BlueprintType)
enum class EMissionType : uint8
{
	None,
	Cleaning,
	Fixing,
	Fueling,
	Boiler,   
	SnowPile
};
USTRUCT(BlueprintType)
struct FMissionProgress
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 Finished = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Total = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCompleted = false;
};

class AEYS_Notebook;

UCLASS()
class ENJOY_YOUR_STAY_API UEYS_MissionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	// Defter kendini buraya kaydedecek gulum
	void RegisterNotebook(AEYS_Notebook* InNotebook);
	void UnregisterNotebook();

	// 🔥 MÜCADELECİ FONKSİYONLAR: Her aktör (Kir, Tamir objesi vs.) bunları tetikleyecek!
	void RegisterMissionTarget(EMissionType Type); // Haritada obje doğunca hedef sayısını artırır
	void UpdateMissionProgress(EMissionType Type, int32 Amount = 1); // İlerleme kaydedince çağrılır

private:
	UPROPERTY()
	AEYS_Notebook* ActiveNotebook = nullptr;

	UPROPERTY()
	TMap<EMissionType, FMissionProgress> MissionRegistry;

	void RefreshNotebookUI(EMissionType Type);
};
	
