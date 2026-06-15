//Copyright (c) 2025 Elia Cantini. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConnectionDrawingPolicy.h"
#include "UObject/Object.h"


class QUICKDIALOGUESEDITOR_API FQuickDialoguesConnectionDrawingPolicy : public FConnectionDrawingPolicy
{
public:
	FQuickDialoguesConnectionDrawingPolicy(
		int32 InBackLayerID,
		int32 InFrontLayerID,
		float InZoomFactor,
		const FSlateRect& InClippingRect,
		FSlateWindowElementList& InDrawElements,
		UEdGraph* InGraphObj);

	virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params) override;
	virtual void DrawSplineWithArrow(const FVector2f& StartPoint, const FVector2f& EndPoint, const FConnectionParams& Params) override;
	virtual void DrawConnection(int32 LayerId, const FVector2f& Start, const FVector2f& End, const FConnectionParams& Params) override;
	virtual void DetermineLinkGeometry(FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget,
	                                   UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
	                                   FArrangedWidget*& StartWidgetGeometry,
	                                   FArrangedWidget*& EndWidgetGeometry) override;
	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;
};
