// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MissionPostProcessVolume.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Interactable Actor/EYS_DirtActor.h"

void AEYS_MissionPostProcessVolume::ShowMissions()
{
 
    TArray<AActor*> Found;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEYS_DirtActor::StaticClass(), Found);

    DirtActorss.Empty();
    DirtActorss.Reserve(Found.Num());

    for (AActor* A : Found)
    {
        if (AEYS_DirtActor* Dirt = Cast<AEYS_DirtActor>(A))
        {
            DirtActorss.Add(Dirt);
        }
    }

    for (AEYS_DirtActor* Dirt : DirtActorss)
    {
        if (!Dirt) continue;
        Dirt->StaticMesh->SetVisibility(true);   // bunu DirtActor'a ekle (aşağıda)
    }
}

void AEYS_MissionPostProcessVolume::HideMissions()
{
    for (AEYS_DirtActor* Dirt : DirtActorss)
    {
        if (!Dirt) continue;
        Dirt->StaticMesh->SetVisibility(false);
    }

    DirtActorss.Empty();
}

void AEYS_MissionPostProcessVolume::SetMissionPPEnabled(bool bEnablePPV)
{
  
    bEnablePPV ? ShowMissions() : HideMissions();
}
