//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuickDialoguesTypes.generated.h"

UENUM(BlueprintType)
enum class EQuickDialoguesNodeType : uint8
{
	Root,
	Dialogue,
	EndPoint,
	Reply,
	WidgetOpener,
	PlayMontage,
	Random,
	Loopback
};
