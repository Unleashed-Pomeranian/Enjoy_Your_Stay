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

void AEYS_BabaYagaAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn)
	{
		
		MyBabaYagaPawn = Cast<AEYS_BabaYaga>(InPawn);
	}
}

void AEYS_BabaYagaAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	// Koruma kalkanları: Aktör yoksa, oyuncu değilse veya canavar referansımız boştaysa dur ke!
	if (!Actor || !Actor->ActorHasTag("Player") || !MyBabaYagaPawn) return;

	// 👁️ 1. GÖRÜŞ ALGISI: Baba Yaga bizi bizzat gördüyse ke gulum!
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			// Eğer devriye bekleme sayacı dönüyorsa onu şak diye patlat ki kudurup koşsun gulum ke!
			GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);
			GetWorld()->GetTimerManager().ClearTimer(LoseTargetTimerHandle);

			TargetPlayer = Actor;

			// 🔥 SİNSİ SES ZIRHI BURADA VURUYOR GULUM:
			// Eğer canavar ZATEN kovalama modunda DEĞİLSE, yani ilk kez bizi gördüyse sesi ÇAL ke!
			// Eğer zaten kovalıyorsa, bu bloğu pas geçeceği için ses üst üste binip sapıtmayacak gulum!
			if (MyBabaYagaPawn->GetMovementState() != EBabaYagaState::Chasing)
			{
				MyBabaYagaPawn->PlayBabaYagaSound(2); // Çığlığı/hırlamayı sadece 1 kere patlat ke!
			}

			// Durumu güncelle ve hedefe mermi gibi fırla gulum
			MyBabaYagaPawn->SetMovementState(EBabaYagaState::Chasing);
			MoveToActor(TargetPlayer, 70.0f);
		}
		else // Sinsi bir odaya girdik ve kapıyı kapattık, görüş koptu ke!
		{
			// 5 saniyelik takip hafıza tetiği gulum ke
			GetWorld()->GetTimerManager().SetTimer(LoseTargetTimerHandle, this, &AEYS_BabaYagaAIController::StopChasing, 5.0f, false);
		}
	}

	// 👂 2. SES ALGISI: Koştuk veya sinsi yürümeyi unuttuk, patırtı koptu ke!
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		// Eğer canavar o an bizi GÖRMÜYORSA ama sesimizi duyduysa gulum:
		if (Stimulus.WasSuccessfullySensed() && !TargetPlayer)
		{
			GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);

			// 🔥 SES ALGISI İÇİN DE AYNI SİNSİ KORUMA GULUM:
			// Canavar sesi ilk duyduğunda ve kovalama modunda değilse ses çalsın ke!
			if (MyBabaYagaPawn->GetMovementState() != EBabaYagaState::Chasing)
			{
				MyBabaYagaPawn->PlayBabaYagaSound(2);
			}

			// Sesin patladığı o sinsi koordinata doğru anında kudurup koşsun ke!
			MyBabaYagaPawn->SetMovementState(EBabaYagaState::Chasing);
			MoveToLocation(Stimulus.StimulusLocation, 70.0f);
		}
	}
}

void AEYS_BabaYagaAIController::StopChasing()
{
	TargetPlayer = nullptr;

	if (AEYS_BabaYaga* BabaYagaCharacter = Cast<AEYS_BabaYaga>(GetPawn()))
	{
		
		BabaYagaCharacter->SetMovementState(EBabaYagaState::Patrolling);
		BabaYagaCharacter->StartPatrol();
	}
}

void AEYS_BabaYagaAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (!MyBabaYagaPawn) return; // Güvenlik zırhı ke!

	// 👤 1. DURUM: OYUNCUYU YAKALADIK, FATURA KESİM ANI KE!
	if (Result.IsSuccess() && TargetPlayer)
	{
		AEYS_MyCharacter* PlayerCharacter = Cast<AEYS_MyCharacter>(TargetPlayer);

		if (PlayerCharacter)
		{
			AEYS_MyCharacterController* MyPC = Cast<AEYS_MyCharacterController>(PlayerCharacter->GetController());

			if (MyPC)
			{
				MyBabaYagaPawn->SetMovementState(EBabaYagaState::Catch);
				MyPC->MobilizeCharacter(true, true, false);
				MyPC->StopPlayer();
				// Dünyanın en stabil lokasyon ve rotasyon eşitlemesi ke gulum:
				FVector BabaYagaForward = MyBabaYagaPawn->GetActorForwardVector();
				FVector TargetPlayerLocation = MyBabaYagaPawn->GetActorLocation() + (BabaYagaForward * 80.0f);
				TargetPlayerLocation.Z = PlayerCharacter->GetActorLocation().Z;

				FVector BabaYagaFaceLoc = MyBabaYagaPawn->GetActorLocation();
				BabaYagaFaceLoc.Z += 200.0f;

				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TargetPlayerLocation, BabaYagaFaceLoc);

				MyPC->SetCharacterPositon(TargetPlayerLocation, 0.0f, 0.0f, TargetRotation);

				// Senin o asil "Z'yi Sonradan Ezme" zırhın tam burada devreye giriyor gulum ke:
				float FinalZ = MyBabaYagaPawn->GetActorLocation().Z - 50.0f;
				FVector LockedLocation = FVector(PlayerCharacter->GetActorLocation().X, PlayerCharacter->GetActorLocation().Y, FinalZ);

				PlayerCharacter->SetActorLocation(LockedLocation);
				PlayerCharacter->AttachToActor(MyBabaYagaPawn, FAttachmentTransformRules::KeepWorldTransform);
			}

			AActor* FoundPPVolume = UGameplayStatics::GetActorOfClass(GetWorld(), AEYS_MyPostProcessVolume::StaticClass());
			if (FoundPPVolume)
			{
				if (AEYS_MyPostProcessVolume* MyPP = Cast<AEYS_MyPostProcessVolume>(FoundPPVolume))
				{
					MyPP->PlayJumpscareGlitch();
					MyBabaYagaPawn->PlayBabaYagaSound(3);
				}
			}

			TargetPlayer = nullptr;
		}
	}
	// 🚶‍♂️ 2. DURUM: DEVRİYEDE HEDEFE VARILDI KE!
	else
	{
		if (Result.IsSuccess() && MyBabaYagaPawn->GetMovementState() == EBabaYagaState::Patrolling)
		{
			// Eğer arkada dönen sinsi bir devriye sayacı varsa önce onu temizle ke gulum, üst üste binmesinler!
			GetWorld()->GetTimerManager().ClearTimer(PatrolTimerHandle);

			// Canavarı noktaya vardığı o salise orada sabitle gulum, amele gibi titremesin!
			StopMovement();

			// Noktaya varma sesini (Sound 1) SADECE VE SADECE ŞİMDI 1 KERE ÇAL KE!
			MyBabaYagaPawn->PlayBabaYagaSound(1);

			// Sınıf seviyesindeki o güvenli sayaç tıkır tıkır kuruluyor gulum:
			GetWorld()->GetTimerManager().SetTimer(PatrolTimerHandle, MyBabaYagaPawn, &AEYS_BabaYaga::StartPatrol, FMath::RandRange(3.0f, 5.0f), false);
		}
	}
}