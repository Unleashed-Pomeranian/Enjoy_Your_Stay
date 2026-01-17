// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Boiler.h"
#include "EYS/UI/EYS_Boiler_UI.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"




// Sets default values
AEYS_Boiler::AEYS_Boiler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(DefaultSceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(SkeletalMesh,FName("Kapak"));
	WidgetMesh = CreateDefaultSubobject<UWidgetComponent>(TEXT("NoteBook Widget"));
	WidgetMesh->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AEYS_Boiler::BeginPlay()
{
	Super::BeginPlay();
	//WidgetMesh->SetWidgetClass(BoilerWidgetClass);
	//if (Widget)
	
		//NotebookWidgetInstance = Cast<UEYS_NotebookWidget>(Widget);
	WidgetMesh->SetWidgetClass(BoilerWidgetClass);
	UUserWidget* Widget = WidgetMesh->GetUserWidgetObject();
		BoilerWidgetInstance = Cast<UEYS_Boiler_UI>(WidgetMesh->GetUserWidgetObject());
		WidgetMesh->SetWidget(BoilerWidgetInstance);
		BoilerWidgetInstance->ProgressBar->SetPercent(BoilerCoalValue / 100);
		//GetWorld()->GetTimerManager().SetTimer(MyTimerHandle,this,&AEYS_Boiler::ReduceCoalValue,5.0f,true);
}

// Called every frame
void AEYS_Boiler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEYS_Boiler::ReduceCoalValue()
{
	BoilerCoalValue = FMath::Clamp(BoilerCoalValue -5.0, 0.0f, 100.0f);
	BoilerWidgetInstance->ProgressBar->SetPercent(BoilerCoalValue / 100);
}
void   AEYS_Boiler::Interact(AEYS_MyCharacter* myPlayer)
{
	return;
}

void   AEYS_Boiler::InteractUI_Implementation(AEYS_MyCharacter* myPlayer)
{
	
}

void   AEYS_Boiler::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{


	if (bAnimFlip)
	{
		// B
		SkeletalMesh->PlayAnimation(AnimAssets[0], false);
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
	
		SkeletalMesh->PlayAnimation(AnimAssets[1], false);
		
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	bAnimFlip = !bAnimFlip; 
}


void AEYS_Boiler::SetCoalAmount(float FuelAddValue)
{
	BoilerCoalValue =  FMath::Clamp(BoilerCoalValue + FuelAddValue, 0.0f, 100.0f);
	BoilerWidgetInstance->ProgressBar->SetPercent(BoilerCoalValue / 100);
}