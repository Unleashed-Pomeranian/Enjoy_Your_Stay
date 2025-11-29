// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Key/EYS_KeyHolder.h"

// Sets default values
AEYS_KeyHolder::AEYS_KeyHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AEYS_KeyHolder::BeginPlay()
{
	Super::BeginPlay();
	
}
void AEYS_KeyHolder::SetPose_Implementation()
{

}

// Called every frame
void AEYS_KeyHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEYS_KeyHolder::Interact(AEYS_MyCharacter* myPlayer)
{


}
void AEYS_KeyHolder::eInteract_Implementation(AEYS_MyCharacter* myPlayer)
{
	

}