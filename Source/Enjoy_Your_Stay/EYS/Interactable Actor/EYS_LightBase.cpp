// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_LightBase.h"
#include "EYS_WorldSubsystem.h"
// Sets default values
AEYS_LightBase::AEYS_LightBase()
{
	PrimaryActorTick.bCanEverTick = false;


	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	LightMesh->SetupAttachment(DefaultSceneRoot);
	

}

// Called when the game starts or when spawned
void AEYS_LightBase::BeginPlay()
{
	Super::BeginPlay();
	if (LightMesh && LightMesh->GetNumMaterials() > 1)
	{
		
		DynamicLightMaterial = LightMesh->CreateDynamicMaterialInstance(1);

		if (DynamicLightMaterial)
		{
			
			DynamicLightMaterial->SetScalarParameterValue(EmissiveParamName, 5.0f);
		}
	}


	if (GetWorld())
	{
		if (UEYS_WorldSubsystem* WSub = GetWorld()->GetSubsystem<UEYS_WorldSubsystem>())
		{
			WSub->RegisterSingleLight(this);
		}
	}
	
}
void AEYS_LightBase::ToggleLight(bool bActivate)
{
	if (LightComponent)
	{
		LightComponent->SetVisibility(bActivate);
		LightComponent->SetActive(bActivate);
	}
	if (DynamicLightMaterial)
	{
		float TargetEmissive = bActivate ? 5.0f : 0.01f;
		DynamicLightMaterial->SetScalarParameterValue(EmissiveParamName, TargetEmissive);
	}
	bHasPower = bActivate;
}


