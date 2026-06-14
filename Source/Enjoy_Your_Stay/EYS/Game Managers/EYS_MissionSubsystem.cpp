


#include "EYS/Game Managers/EYS_MissionSubsystem.h"
#include "EYS/Interactable Actor/EYS_Notebook.h"

void UEYS_MissionSubsystem::RegisterNotebook(AEYS_Notebook* InNotebook)
{
	ActiveNotebook = InNotebook;


	if (ActiveNotebook)
	{
		for (const auto& KVP : MissionRegistry)
		{
			RefreshNotebookUI(KVP.Key);
		}
	}
}

void UEYS_MissionSubsystem::UnregisterNotebook()
{
	ActiveNotebook = nullptr;
}

void UEYS_MissionSubsystem::RegisterMissionTarget(EMissionType Type)
{
	

	FMissionProgress& Progress = MissionRegistry.FindOrAdd(Type);
	if (Type == EMissionType::Fueling)
	{
		Progress.Total = 50;
	}
	else if (Type == EMissionType::Boiler)
	{
		Progress.Total = 40;
	}
	else
	{
		Progress.Total++;
	}

	RefreshNotebookUI(Type);
}

void UEYS_MissionSubsystem::UpdateMissionProgress(EMissionType Type, int32 Amount)
{
	if(!MissionRegistry.Contains(Type)) return;

	FMissionProgress& Progress = MissionRegistry[Type];
	if (Progress.bIsCompleted) return;
	if (Type == EMissionType::Fueling)
	{
		Progress.Finished = Amount;
	}
	else if (Type == EMissionType::Boiler)
	{
		Progress.Finished = Amount;
	}
	else
	{
		Progress.Finished += Amount;
	}

	
	if (Progress.Finished >= Progress.Total && Progress.Total > 0)
	{
	
		Progress.Finished = Progress.Total;
		Progress.bIsCompleted = true;
		RefreshNotebookUI(Type);

		Progress.Finished = 0;
		Progress.Total = 0;
		Progress.bIsCompleted = false;
	}
	else
	{
	
		RefreshNotebookUI(Type);
	}
}

void UEYS_MissionSubsystem::RefreshNotebookUI(EMissionType Type)
{
	if (!ActiveNotebook || !MissionRegistry.Contains(Type)) return;

	const FMissionProgress& Progress = MissionRegistry[Type];


	switch (Type)
	{
	case EMissionType::Cleaning:
		ActiveNotebook->CleaningMission(Progress.Finished, Progress.Total);
		break;
	case EMissionType::Fueling:
		ActiveNotebook->FuelingMission(Progress.Finished, Progress.Total);
		break;
	case EMissionType::Fixing:
		ActiveNotebook->FixingMission(Progress.Finished, Progress.Total);
		break;
	case EMissionType::Boiler:
		ActiveNotebook->BoilerMission(Progress.Finished, Progress.Total);
		break;

	case EMissionType::SnowPile:
		ActiveNotebook->SnowPileMission(Progress.Finished, Progress.Total);
		break;

	default:
		break;
	}
}

void UEYS_MissionSubsystem::ProcessCustomerCheckOut(int32 InCustomerScore)
{
	InCustomerScore = FMath::Clamp(InCustomerScore, 0, 100);

	float GeneratedRatingImpact = 0.0f;

	
	float RatingDifference = static_cast<float>(InCustomerScore) - HotelGeneralRating;

	if (RatingDifference < 0.0f)
	{

		float Alpha = FMath::Abs(RatingDifference) / 100.0f;
		float PenaltyMultiplier = FMath::Lerp(1.2f, 2.0f, Alpha);

		GeneratedRatingImpact = RatingDifference * PenaltyMultiplier;
	}
	else
	{
	
		float Alpha = RatingDifference / 100.0f;
		float RewardMultiplier = FMath::Lerp(1.0f, 1.8f, Alpha);

		GeneratedRatingImpact = RatingDifference * RewardMultiplier;
	}

	
	float TargetRating = HotelGeneralRating + GeneratedRatingImpact;
	TargetRating = FMath::Clamp(TargetRating, 0.0f, 100.0f);


	HotelGeneralRating = FMath::Lerp(HotelGeneralRating, TargetRating, CustomerEffectRate);
	SetHotelStars();

}

void UEYS_MissionSubsystem::SetHotelStars()
{
	const float Value = HotelGeneralRating;
	if (ActiveNotebook)
	{
		
		ActiveNotebook->SetStarWidget(Value);
	}
}

