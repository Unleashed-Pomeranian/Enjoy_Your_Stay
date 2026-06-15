//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "QuickDialoguesConnectionDrawingPolicy.h"

FQuickDialoguesConnectionDrawingPolicy::FQuickDialoguesConnectionDrawingPolicy(int32 InBackLayerID,
                                                                               int32 InFrontLayerID, float InZoomFactor,
                                                                               const FSlateRect& InClippingRect,
                                                                               FSlateWindowElementList& InDrawElements,
                                                                               UEdGraph* InGraphObj):
	FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements)
{
}

void FQuickDialoguesConnectionDrawingPolicy::DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom,
	const FConnectionParams& Params)
{

	FConnectionDrawingPolicy::DrawSplineWithArrow(StartGeom, EndGeom, Params);
}

void FQuickDialoguesConnectionDrawingPolicy::DrawSplineWithArrow(const FVector2f& StartPoint, const FVector2f& EndPoint,
	const FConnectionParams& Params)
{
	FConnectionDrawingPolicy::DrawSplineWithArrow(StartPoint, EndPoint, Params);
}

void FQuickDialoguesConnectionDrawingPolicy::DrawConnection(int32 LayerId, const FVector2f& Start, const FVector2f& End,
	const FConnectionParams& Params)
{
	FConnectionDrawingPolicy::DrawConnection(LayerId, Start, End, Params);
}

void FQuickDialoguesConnectionDrawingPolicy::DetermineLinkGeometry(FArrangedChildren& ArrangedNodes,
                                                                   TSharedRef<SWidget>& OutputPinWidget,
                                                                   UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
                                                                   FArrangedWidget*& StartWidgetGeometry,
                                                                   FArrangedWidget*& EndWidgetGeometry)
{
	FConnectionDrawingPolicy::DetermineLinkGeometry(ArrangedNodes, OutputPinWidget, OutputPin, InputPin,
	                                                StartWidgetGeometry, EndWidgetGeometry);
}

void FQuickDialoguesConnectionDrawingPolicy::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
                                                                  FConnectionParams& Params)
{
	FConnectionDrawingPolicy::DetermineWiringStyle(OutputPin, InputPin, Params);
}
