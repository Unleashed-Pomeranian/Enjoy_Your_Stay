#include "EYS/UI/Settings Widgets/EYS_ControlSettings_UI.h"
#include "EYS/UI/Settings Widgets/EYS_KeyBindSetting_UI.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedActionKeyMapping.h"

void UEYS_ControlSettings_UI::NativeConstruct()
{
	Super::NativeConstruct();
	EnhancedInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer());
	if (EnhancedInputSystem) EnhancedInputUserSettings = EnhancedInputSystem->GetUserSettings();

	
	InitializeRows();
	BindRowEvents();
	if(Button_Default)Button_Default->OnPressed.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyDefaultKey);
}

void UEYS_ControlSettings_UI::InitializeRows()
{
	if (Row_MoveForward)
	{
		Row_MoveForward->InitializeSetting("MoveForward", FText::FromString("Move Forward"), GetCurrentKeyForAction("MoveForward"));
	
	}

	if (Row_MoveLeft)
	{
		Row_MoveLeft->InitializeSetting("MoveLeft", FText::FromString("Move Left"), GetCurrentKeyForAction("MoveLeft"));
	}

	if (Row_MoveBackward)
	{
		Row_MoveBackward->InitializeSetting("MoveBackward", FText::FromString("Move Backward"), GetCurrentKeyForAction("MoveBackward"));
	}

	if (Row_MoveRight)
	{
		Row_MoveRight->InitializeSetting("MoveRight", FText::FromString("Move Right"), GetCurrentKeyForAction("MoveRight"));
	}

	if (Row_Sprint)
	{
		Row_Sprint->InitializeSetting("Sprint", FText::FromString("Sprint"), GetCurrentKeyForAction("Sprint"));
	}
	if (Row_Jump)
	{
		Row_Jump->InitializeSetting("Jump", FText::FromString("Jump"), GetCurrentKeyForAction("Jump"));
	}
	if (Row_PrimaryAction)
	{
		Row_PrimaryAction->InitializeSetting("PrimaryAction", FText::FromString("Primary Action"), GetCurrentKeyForAction("PrimaryAction"));
	}

	if (Row_SecondaryAction)
	{
		Row_SecondaryAction->InitializeSetting("SecondaryAction", FText::FromString("Secondary Action"), GetCurrentKeyForAction("SecondaryAction"));
	}

	if (Row_Interact)
	{
		Row_Interact->InitializeSetting("Interact", FText::FromString("Interact"), GetCurrentKeyForAction("Interact"));
	}

	if (Row_Drop)
	{
		Row_Drop->InitializeSetting("Drop", FText::FromString("Drop"), GetCurrentKeyForAction("Drop"));
	}

	if (Row_EquipmentWheel)
	{
		Row_EquipmentWheel->InitializeSetting("EquipmentWheel", FText::FromString("Equipment Wheel"), GetCurrentKeyForAction("EquipmentWheel"));
	}

	if (Row_MissionSense)
	{
		Row_MissionSense->InitializeSetting("MissionSense", FText::FromString("Mission Sense"), GetCurrentKeyForAction("MissionSense"));
	}

	if (Row_Notebook)
	{
		Row_Notebook->InitializeSetting("Notebook", FText::FromString("Notebook"), GetCurrentKeyForAction("Notebook"));
	}
}

FKey UEYS_ControlSettings_UI::GetCurrentKeyForAction(FName ActionName)
{

	if (!EnhancedInputSystem) return EKeys::Invalid;
	TArray<FEnhancedActionKeyMapping> Mappings = EnhancedInputSystem->GetAllPlayerMappableActionKeyMappings();
	for (const FEnhancedActionKeyMapping& Mapping : Mappings)
	{
		// Eğer motor içindeki IMC'de belirlediğin isimle eşleşiyorsa...
		if (Mapping.GetMappingName() == ActionName)
		{
			UE_LOG(LogTemp, Warning, TEXT("Mapping Name: %s Key: %s"),
				*Mapping.GetMappingName().ToString(),
				*Mapping.Key.ToString())
			    return Mapping.Key; 
		}

	}
	
	return EKeys::Invalid; 
	return FKey();
}



void UEYS_ControlSettings_UI::BindRowEvents()
{
	if (Row_MoveForward)
	{
		Row_MoveForward->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_MoveLeft)
	{
		Row_MoveLeft->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_MoveBackward)
	{
		Row_MoveBackward->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_MoveRight)
	{
		Row_MoveRight->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_Sprint)
	{
		Row_Sprint->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_PrimaryAction)
	{
		Row_PrimaryAction->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_SecondaryAction)
	{
		Row_SecondaryAction->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_Interact)
	{
		Row_Interact->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_Drop)
	{
		Row_Drop->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_EquipmentWheel)
	{
		Row_EquipmentWheel->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_MissionSense)
	{
		Row_MissionSense->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}

	if (Row_Notebook)
	{
		Row_Notebook->OnKeyChanged.AddDynamic(this, &UEYS_ControlSettings_UI::ApplyChangedKey);
	}
}



void UEYS_ControlSettings_UI::ApplyChangedKey(FName ActionName, FKey NewKey)
{


	if (EnhancedInputUserSettings)
	{
		// 1. Değiştirilecek tuşun parametrelerini ayarla
		FMapPlayerKeyArgs Args;
		Args.MappingName = ActionName;
		Args.NewKey = NewKey;
		Args.Slot = EPlayerMappableKeySlot::First;

		// 2. Yeni tuşu hafızada (memory) mevcut olanla değiştir
		FGameplayTagContainer FailureReason;
		EnhancedInputUserSettings->MapPlayerKey(Args, FailureReason);

		if (!FailureReason.IsEmpty())
		{
			// Hatayı log ekranına kırmızı yazdırarak bize neden reddettiğini söylesin
			UE_LOG(LogTemp, Error, TEXT("TUS KAYDEDILEMEDI! Sebep: %s"), *FailureReason.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TUS BASARIYLA DEGISTIRILDI VE KAYDEDILDI!"));
			EnhancedInputUserSettings->ApplySettings();
			EnhancedInputUserSettings->SaveSettings();
		}
	}
}

void UEYS_ControlSettings_UI::ApplyDefaultKey()
{
	for (const TPair<FName, FKey>& Pair : DefaultKeyBinding)
	{
		// Pair.Key = Aksiyonun ismi (Örn: "MoveForward")
		// Pair.Value = O aksiyonun varsayılan tuşu (Örn: EKeys::W)
		
		ApplyChangedKey(Pair.Key, Pair.Value);
	}
	EnhancedInputUserSettings->ApplySettings();
	InitializeRows();


}


