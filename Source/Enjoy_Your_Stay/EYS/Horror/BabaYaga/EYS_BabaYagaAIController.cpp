// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Horror/BabaYaga/EYS_BabaYagaAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "EYS/Horror/BabaYaga/EYS_BabaYaga.h"

#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EYS/Game Managers/EYS_MyPostProcessVolume.h"

#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"


AEYS_BabaYagaAIController::AEYS_BabaYagaAIController()
{
	BabaYagaPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("BabaYagaPerceptionComp"));
	SetPerceptionComponent(*BabaYagaPerceptionComp);
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));

	// 👀 Göz Ayarları (Uzaklığı otelin koridor genişliğine göre ayarla gulum)
	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 2000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f; // Toplam 120 derece ön görüş
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	BabaYagaPerceptionComp->ConfigureSense(*SightConfig);

	// 👂 Kulak Ayarları (Yürüme/Koşma seslerini alma menzili ke)
	HearingConfig->HearingRange = 1500.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	BabaYagaPerceptionComp->ConfigureSense(*HearingConfig);

	BabaYagaPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEYS_BabaYagaAIController::OnTargetPerceived);
	TargetPlayer = nullptr;
}

void AEYS_BabaYagaAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEYS_BabaYagaAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor || !Actor->ActorHasTag("Player")) return;

	AEYS_BabaYaga& BabaYagaCharacter = *Cast<AEYS_BabaYaga>(GetPawn());

	// 👁️ GÖRÜŞ ALGISI: Baba Yaga bizi bizzat gördüyse ke gulum!
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetWorld()->GetTimerManager().ClearTimer(LoseTargetTimerHandle);
			TargetPlayer = Actor;

			// Baba Yaga çığlık atarak (veya hırlayarak) koşma hızına geçer gulum!
			BabaYagaCharacter.SetMovementState(EBabaYagaState::Chasing);
			MoveToActor(TargetPlayer, 70.0f);
		}
		else // Sinsi bir odaya girdik ve kapıyı kapattık, görüş koptu ke!
		{
			// 🔥 5 SANİYELİK HAFIZA SAYAÇ TETİĞİ BURADA VURUR GULUM:
			GetWorld()->GetTimerManager().SetTimer(LoseTargetTimerHandle, this, &AEYS_BabaYagaAIController::StopChasing, 5.0f, false);
		}
	}

	// 👂 SES ALGISI: Koştuk veya sinsi yürümeyi unuttuk, patırtı koptu ke!
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		// Eğer canavar o an bizi GÖRMÜYORSA ama sesimizi duyduysa gulum:
		if (Stimulus.WasSuccessfullySensed())
		{
			// Sesin patladığı o sinsi koordinata doğru anında kudurup koşsun ke!
			BabaYagaCharacter.SetMovementState(EBabaYagaState::Chasing);
			MoveToLocation(Stimulus.StimulusLocation, 70.0f);
		}
	}
}

void AEYS_BabaYagaAIController::StopChasing()
{
	TargetPlayer = nullptr;

	if (AEYS_BabaYaga* BabaYagaCharacter = Cast<AEYS_BabaYaga>(GetPawn()))
	{
		// Sakin devriye hızına geri dön ve etrafta gezin gulum
		BabaYagaCharacter->SetMovementState(EBabaYagaState::Patrolling);
		BabaYagaCharacter->StartPatrol();
	}
}

void AEYS_BabaYagaAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	// Canavar hedefe pürüzsüzce ulaştıysa ve kovaladığı oyuncu varsa gulum:
	if (Result.IsSuccess() && TargetPlayer)
	{
		AEYS_MyCharacter* PlayerCharacter = Cast<AEYS_MyCharacter>(TargetPlayer);
		AActor* BabaYagaActor = GetPawn();

		if (PlayerCharacter && BabaYagaActor)
		{
			
			AEYS_MyCharacterController* MyPC = Cast<AEYS_MyCharacterController>(PlayerCharacter->GetController());

			if (MyPC)
			{
				// 1. Önce karakterin hareketini ve her türlü bakış inputunu şak diye dondur ke!
				MyPC->MobilizeCharacter(true, true, false);
				
				// ==========================================
				// 🎯 KUTSAL TAM KARŞISINA ALMA MATEMATİĞİ KE:
				// ==========================================

				// Baba Yaga'nın tam ön cephesinin (Forward Vector) nereye baktığını bul gulum
				FVector BabaYagaForward = BabaYagaActor->GetActorForwardVector();

				// Oyuncuyu tam Baba Yaga'nın önüne, göz hizası koordinatına çekiyoruz ke!
				// Baba Yaga'nın durduğu yerden kendi önüne doğru tam 80 birim (0.8 metre) bir hedef nokta belirliyoruz gulum
				FVector TargetPlayerLocation = BabaYagaActor->GetActorLocation() + (BabaYagaForward * 80.0f);

				// Z eksenini (Yükseklik) oyuncunun kendi boy hizasında koru ki canavarın içine veya yerin dibine batmasın ke!
				TargetPlayerLocation.Z = PlayerCharacter->GetActorLocation().Z;

				// 📐 TAM YÜZ YÜZE BAKMA ROTASYONU (Face-to-Face)
				// Oyuncunun kamerası ve gövdesi tam olarak canavarın gözünün içine kilitlensin gulum:
				FVector BabaYagaFaceLoc = BabaYagaActor->GetActorLocation();
				BabaYagaFaceLoc.Z += 60.0f; // Canavarın yüz hizası offseti ke

				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TargetPlayerLocation, BabaYagaFaceLoc);

		
				MyPC->SetCharacterPositon(TargetPlayerLocation, 0.0f, 0.0f, TargetRotation);
				float FinalZ = BabaYagaActor->GetActorLocation().Z - 50.0f;
				FVector LockedLocation = FVector(PlayerCharacter->GetActorLocation().X, PlayerCharacter->GetActorLocation().Y, FinalZ);

				PlayerCharacter->SetActorLocation(LockedLocation);
				PlayerCharacter->AttachToActor(BabaYagaActor, FAttachmentTransformRules::KeepWorldTransform);
			
			}

			// 2. 🔍 Haritadaki o özel Post Process Volume aktörünü çağır ke gulum:
			AActor* FoundPPVolume = UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MyPostProcessVolume::StaticClass());
			if (FoundPPVolume)
			{
				AEYS_MyPostProcessVolume* MyPP = Cast<AEYS_MyPostProcessVolume>(FoundPPVolume);
				if (MyPP)
				{
					// Ekranı sinüs dalgasıyla dalga dalga karartıp yırtmaya başla ke!
					MyPP->PlayJumpscareGlitch();
				}
			}

			// Takibi sıfırla ke gulum, fatura kesildi!
			TargetPlayer = nullptr;
		}
	}
	else
	{
		// Devriyedeyse normal rutine devam ke gulum
		if (AEYS_BabaYaga* BabaYagaCharacter = Cast<AEYS_BabaYaga>(GetPawn()))
		{
			BabaYagaCharacter->StartPatrol();

			FTimerHandle PatrolTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, BabaYagaCharacter, &AEYS_BabaYaga::StartPatrol, FMath::RandRange(4.0f, 8.0f), false);
		}
	}
}