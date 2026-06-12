


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