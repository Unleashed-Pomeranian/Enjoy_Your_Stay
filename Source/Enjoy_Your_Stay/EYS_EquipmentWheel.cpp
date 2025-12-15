// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS_EquipmentWheel.h"
#include "Components/Button.h"
#include "EYS/EYS_MyCharacter.h"

void UEYS_EquipmentWheel::NativeConstruct()
{
	Super::NativeConstruct();

	// Null kontrolü ile güvenli binding
	if (Btn_Slot1) Btn_Slot1->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot1);
	if (Btn_Slot2) Btn_Slot2->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot2);
	if (Btn_Slot3) Btn_Slot3->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot3);
	if (Btn_Slot4) Btn_Slot4->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot4);
	if (Btn_Slot5) Btn_Slot5->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot5);
	if (Btn_Slot6) Btn_Slot6->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot6);
	if (Btn_Slot7) Btn_Slot7->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot7);
	if (Btn_Slot8) Btn_Slot8->OnHovered.AddDynamic(this, &UEYS_EquipmentWheel::OnSlot8);

	
}

void UEYS_EquipmentWheel::OnBtnSlotHovered(int32 SlotIndex)
{
	
	AEYS_MyCharacter* OwnerCharacter = Cast<AEYS_MyCharacter>(GetOwningPlayerPawn());

	OwnerCharacter->LastPoseNum = SlotIndex;
	


	

}

void UEYS_EquipmentWheel::EnableButtons(int32 Index,bool bIsEnable, ESlateVisibility VisibleIcon)
{

	switch (Index)
	{
     
	case 3:
	{
		Btn_Slot3->SetIsEnabled(bIsEnable);
		Hammer_Icon->SetVisibility(VisibleIcon);
		break;
	}

	
	case 4:
	{
		Btn_Slot4->SetIsEnabled(bIsEnable);
		Mop_Icon->SetVisibility(VisibleIcon);
		break;
	}
	case 5:
	{
		Btn_Slot5->SetIsEnabled(bIsEnable);
		FuelTank_Icon->SetVisibility(VisibleIcon);
		break;
	}

	case 6:
	{
		Btn_Slot6->SetIsEnabled(bIsEnable);
		Flashlight_Icon->SetVisibility(VisibleIcon);
		break;
	}

	case 7:
	{
		Btn_Slot7->SetIsEnabled(bIsEnable);
		Shovel_Icon->SetVisibility(VisibleIcon);
		break;
	}

	default:

		break;
	}
	

}

