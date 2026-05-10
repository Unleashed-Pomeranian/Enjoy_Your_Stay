// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/NPC/EYS_Chair.h"

AEYS_Chair::AEYS_Chair()
{
	PrimaryActorTick.bCanEverTick = true;
	ChairRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Chair Root"));
	ChairRoot->SetupAttachment(RootComponent);
	TableRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Table Root"));
	TableRoot->SetupAttachment(RootComponent);
    LeaveRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Leave Root"));
	LeaveRoot->SetupAttachment(RootComponent);

}

FTransform AEYS_Chair::GetChairTransform()
{
	return ChairRoot->GetComponentTransform();
}

FTransform AEYS_Chair::GetTableTransform()
{
	return TableRoot->GetComponentTransform();
}

FVector AEYS_Chair::GetLeaveLocation()
{
	return LeaveRoot->GetComponentLocation();
}
