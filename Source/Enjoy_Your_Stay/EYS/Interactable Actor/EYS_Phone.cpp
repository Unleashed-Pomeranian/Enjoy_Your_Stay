// Fill out your copyright notice in the Description page of Project Settings.
#include "EYS/Interactable Actor/EYS_Phone.h"
#include "EYS/EYS_MyCharacter.h"
#include "EYS/EYS_MyCharacterController.h"
#include "Kismet/GamePlayStatics.h"
#include "EYS/UI/EYS_Phone_UI.h"
#include "EYS/UI/Order Widgets/EYS_Guest_UI.h"


// Sets default values
AEYS_Phone::AEYS_Phone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Phone Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Int Phone Mesh"));
	StaticMesh2->SetupAttachment(RootComponent);
	PhoneAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PhoneAudio"));
	PhoneAudio->SetupAttachment(RootComponent);
	PhoneAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEYS_Phone::BeginPlay()
{
	Super::BeginPlay();

	AEYS_MyCharacter* Myplayer = Cast<AEYS_MyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PC = Cast<AEYS_MyCharacterController>(Myplayer->GetController());

	PhoneFirstTransform = StaticMesh2->GetRelativeTransform();
}

// Called every frame
void AEYS_Phone::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

}

void AEYS_Phone::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}
void AEYS_Phone::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
   
	if(bCanInteract)
	PC->SetInteractionWidget("[E] Talk");
	else
	PC->SetInteractionWidget("");

}

void AEYS_Phone::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{

	if (bCanInteract)
	{
		PC->PlayerCameraManager->StartCameraFade(2.0f, 0.0f, 1.5f, FLinearColor::Black, false, true);
	

		FRotator Rotation = { -48,180,0 };
		PC->SetCharacterPositon(GetActorLocation(), 10, 8, Rotation);
		PC->MobilizeCharacter(true, true, true);
		PlayPhoneMontage(myPlayer);
		bCanInteract = false;
	}
}

void AEYS_Phone::SetupAttachment(AEYS_MyCharacter* myPlayer)
{
	StaticMesh2->AttachToComponent(myPlayer->FirstPersonMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Phone");
	myPlayer->bIsPhoneMode = true;

}

void AEYS_Phone::SetupCloseAttachment(AEYS_MyCharacter* myPlayer)
{
	myPlayer->bIsPhoneMode = false;
	StaticMesh2->AttachToComponent(SceneRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	StaticMesh2->SetRelativeTransform(PhoneFirstTransform);
	PC->MobilizeCharacter(false, false, false);
	bCanInteract=true;
}

void AEYS_Phone::OpenUI()
{
	if (bIsGuestCalling)
	{
		if (!(GuestWidgetInstance->IsInViewport()))
		{
			GuestWidgetInstance->AddToViewport();
			PhoneAudio->Stop();
		}
	}
	else
	{
		PhoneWidgetInstance = CreateWidget<UEYS_Phone_UI>(PC, PhoneWidgetClass);

		if (PhoneWidgetInstance && !(PhoneWidgetInstance->IsInViewport()))
		{
			PhoneWidgetInstance->AddToViewport();

		}
	}
}

void AEYS_Phone::CloseUI()
{
	if (bIsGuestCalling)
	{
		if (GuestWidgetInstance->IsInViewport())
			GuestWidgetInstance->RemoveFromParent();	
		bIsGuestCalling = false;
	}
	else
	{ 
		if ((PhoneWidgetInstance->IsInViewport()))
			PhoneWidgetInstance->RemoveFromParent();
		
	}

	PlayPhoneCloseMontage();
}

void AEYS_Phone::SetGuestUI(FString Foodtype,int32 RoomNum)
{
	GuestWidgetInstance = CreateWidget<UEYS_Guest_UI>(PC, GuestWidgetClass);
	if (GuestWidgetInstance)
	{
		if (RingingSound)
		{
			PhoneAudio->SetSound(RingingSound);
			PhoneAudio->Play();
		}
		GuestWidgetInstance->SetGuestText(Foodtype, RoomNum);
		bIsGuestCalling = true;
	}
}

void AEYS_Phone::PlayPhoneMontage_Implementation(AEYS_MyCharacter* myPlayer)
{
}

void AEYS_Phone::PlayPhoneCloseMontage_Implementation()
{
}

