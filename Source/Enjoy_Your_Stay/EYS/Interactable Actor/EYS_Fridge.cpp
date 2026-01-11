// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_Fridge.h"

AEYS_Fridge::AEYS_Fridge()
{
	StaticMesh_Fridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fridge Static Mesh"));
	StaticMesh_Fridge->SetupAttachment(RootComponent);
	FridgeSlot_01 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Fridge Slot_01"));
	FridgeSlot_01->SetupAttachment(StaticMesh_Fridge);
	FridgeSlot_02 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Fridge Slot_02"));
	FridgeSlot_02->SetupAttachment(StaticMesh_Fridge);
	FridgeSlot_03 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Fridge Slot_03"));
	FridgeSlot_03->SetupAttachment(StaticMesh_Fridge);
	FridgeSlot_04 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Fridge Slot_04"));
	FridgeSlot_04->SetupAttachment(StaticMesh_Fridge);
}