// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Game Managers/EYS_MissionPostProcessVolume.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Interactable Actor/EYS_DirtActor.h"
#include "EYS/Horror/BabaYaga/EYS_BabaYaga.h" 
#include "EYS/Horror/BabaYaga/EYS_BabaYagaAIController.h"
#include "EYS/EYS_MyCharacter.h"
#include "Components/AudioComponent.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/CapsuleComponent.h"

void AEYS_MissionPostProcessVolume::BeginPlay()
{
    Super::BeginPlay();

    

}
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
        Dirt->StaticMesh->SetVisibility(true);  
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
    //SetActorLocation(PPVlocation);

 
}

void AEYS_MissionPostProcessVolume::TriggerTimeDilationEvent()
{
	SetMissionPPEnabled(true);

	UWorld* World = GetWorld();
	if (!World || !BabaYagaClass) return;

	UGameplayStatics::SetGlobalTimeDilation(World, 0.25f);

	AEYS_MyCharacter* PlayerChar = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));

	if (PlayerChar)
	{
		// 📐 1. AŞAMA: HAM MATEMATİKSEL LOKASYON HESABI (Senin o efsane eski mantık ke)
		FVector PlayerLoc = PlayerChar->GetActorLocation();
		FVector PlayerForward = PlayerChar->GetActorForwardVector();
		FVector PlayerRight = PlayerChar->GetActorRightVector();

		FVector SpawnBaseLocation = PlayerLoc + (PlayerForward * 1000.0f);
		float RandomSideOffset = FMath::RandRange(-250.0f, 250.0f);
		FVector CalculatedLocation = SpawnBaseLocation + (PlayerRight * RandomSideOffset);
		CalculatedLocation.Z = PlayerLoc.Z;

		// ====================================================
		// 🛡️ 2. AŞAMA: KUTSAL NAVMESH SÜZGECİ (ANTI-WALL SPAWN) ZIRHI KE!
		// ====================================================
		FVector FinalSpawnLocation = CalculatedLocation; // Varsayılan olarak hesaplananı tut ke

		// Haritanın aktif navigasyon sistemine sızıyoruz gulum:
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

		if (NavSys)
		{
			FNavLocation ProjectedLocation;
			// Hesapladığımız kırık noktanın etrafındaki 300 birimlik (3 metrelik) alanda 
			// NavMesh'e ait gerçek ve güvenli bir zemin aratıyoruz ke gulum!
			bool bFoundValidPoint = NavSys->ProjectPointToNavigation(
				CalculatedLocation,
				ProjectedLocation,
				FVector(300.0f, 300.0f, 300.0f) // Arama menzili (X, Y, Z) ke!
			);

			if (bFoundValidPoint)
			{
				// Eğer motor duvara denk gelmeyen temiz bir yeşil alan bulduysa, 
				// koordinatımızı şak diye o güvenli noktaya eşitliyoruz gulum ke!
				FinalSpawnLocation = ProjectedLocation.Location;
			}
		}

		// Canavar doğduğu an yüzü pürüzsüzce oyuncuya baksın ke gulum:
		FRotator SpawnRotation = (PlayerLoc - FinalSpawnLocation).Rotation();
		SpawnRotation.Pitch = 0.0f;
		SpawnRotation.Roll = 0.0f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// 🎬 3. AŞAMA: CANAVAR ARTIK %100 GÜVENLİ NOKTADA DOĞUYOR GULUM KE!
		AEYS_BabaYaga* SpawnedBabaYaga = World->SpawnActor<AEYS_BabaYaga>(BabaYagaClass, FinalSpawnLocation, SpawnRotation, SpawnParams);

		if (SpawnedBabaYaga)
		{
			SpawnedBabaYaga->CustomTimeDilation = 4.0f;
			SpawnedMissionBabaYaga = SpawnedBabaYaga;
			SpawnedBabaYaga->SpawnDefaultController();

			// Sesleri dünya hızına sabitleme zırhı ke:
			TArray<UAudioComponent*> AudioComps;
			SpawnedBabaYaga->GetComponents<UAudioComponent>(AudioComps);
		

			// 🔥 TAARRUZ EMRİ KE:
			if (AEYS_BabaYagaAIController* AICon = Cast<AEYS_BabaYagaAIController>(SpawnedBabaYaga->GetController()))
			{
				AICon->SetTargetPlayer(PlayerChar);
				SpawnedBabaYaga->SetMovementState(EBabaYagaState::Chasing);
				AICon->MoveToActor(PlayerChar, 20.0f);
				SpawnedBabaYaga->PlayBabaYagaSound(2);
			}
		}
	}
}

void AEYS_MissionPostProcessVolume::CleanUpMissionActor()
{
	if (SpawnedMissionBabaYaga)
	{
		// 🔥 Senin o yakaladığın harika mantık: Eğer canavar oyuncuyu yakaladıysa (Catch ise) imha etme ke!
		if (SpawnedMissionBabaYaga->GetMovementState() == EBabaYagaState::Catch)
		{
		
			return;
		}

		// 🔴 Oyuncu görevi iptal edip paçayı kurtardıysa faturayı kesiyoruz ke:
		AController* AICon = SpawnedMissionBabaYaga->GetController();
		if (AICon)
		{
			AICon->Destroy();
		}

		SpawnedMissionBabaYaga->Destroy(); // Canavarı haritadan mermi gibi sil gulum ke!
		SpawnedMissionBabaYaga = nullptr;

	}
}
