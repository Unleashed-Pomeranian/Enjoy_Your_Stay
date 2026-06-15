//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesBaseGraphNodeWidget.h"

#include "SGraphNode.h"
#include "Nodes/QuickDialoguesDialogueNode.h"
#include "Widgets/SWidget.h"

SQuickDialoguesBaseGraphNodeWidget::SQuickDialoguesBaseGraphNodeWidget(): MyGraphNode(nullptr)
{
}

SQuickDialoguesBaseGraphNodeWidget::SQuickDialoguesBaseGraphNodeWidget(
	UQuickDialoguesBaseGraphNode* MyGraphNode,
	const TSharedPtr<SEditableTextBox>& EditableText): MyGraphNode(MyGraphNode)
{
}

FReply SQuickDialoguesBaseGraphNodeWidget::OnMouseButtonDown(const FGeometry& MyGeometry,
                                                             const FPointerEvent& MouseEvent)
{
	FSlateApplication::Get().ClearKeyboardFocus(EFocusCause::SetDirectly);
	return SGraphNode::OnMouseButtonDown(MyGeometry, MouseEvent);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SQuickDialoguesBaseGraphNodeWidget::Construct(const FArguments& InArgs,
                                                   UQuickDialoguesBaseGraphNode* InGraphNode)
{
	MyGraphNode = InGraphNode;
	GraphNode = InGraphNode;
	InputPins.Empty();
	OutputPins.Empty();
	RightNodeBox.Reset();
	LeftNodeBox.Reset();
	ContentVerticalBox = SAssignNew(ContentVerticalBox, SVerticalBox);
	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	                  .HAlign(HAlign_Center)
	[
		SNew(STextBlock)
		.Text(this, &SQuickDialoguesBaseGraphNodeWidget::GetEditableNodeTitleAsText)
		.Font(FCoreStyle::Get().GetFontStyle("BoldFont"))
		.TextStyle(FAppStyle::Get(), "Graph.Node.NodeTitle")
	];
	this->SetCursor(EMouseCursor::CardinalCross);
	this->GetOrAddSlot(ENodeZone::Center)
	    .HAlign(HAlign_Fill)
	    .VAlign(VAlign_Fill)
	[
		SNew(SBox)
		.MinDesiredWidth(200)
		.MaxDesiredWidth(800)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
			.BorderBackgroundColor(GetNodeColor())
			.Padding(4)
			[
				ContentVerticalBox.ToSharedRef()
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SQuickDialoguesBaseGraphNodeWidget::UpdateGraphNode()
{
}

FText SQuickDialoguesBaseGraphNodeWidget::GetErrorMsg() const
{
	if (const UQuickDialoguesBaseGraphNode* TypedNode = Cast<UQuickDialoguesBaseGraphNode>(GraphNode))
	{
		return FText::FromString(TypedNode->ErrorMsg);
	}
	return FText::GetEmpty();
}

FColor SQuickDialoguesBaseGraphNodeWidget::GetNodeColor() const
{
	if (const UQuickDialoguesBaseGraphNode* TypedNode = Cast<UQuickDialoguesBaseGraphNode>(GraphNode))
	{
		if (!TypedNode->DialogueNode)
		{
			return FColor::Black;
		}

		switch (TypedNode->DialogueNode->GetNodeType())
		{
		case EQuickDialoguesNodeType::Root:
			return FColor::FromHex("3393FF");
		case EQuickDialoguesNodeType::EndPoint:
			return FColor::FromHex("228A22");
		case EQuickDialoguesNodeType::Dialogue:
			return FColor::FromHex("FF10F0");
		case EQuickDialoguesNodeType::Reply:
			return FColor::FromHex("006666");
		case EQuickDialoguesNodeType::WidgetOpener:
			return FColor::FromHex("AAAAAA");
		case EQuickDialoguesNodeType::PlayMontage:
			return FColor::FromHex("1e00ff");
		case EQuickDialoguesNodeType::Random:
			return FColor::FromHex("ACEBEE");
		case EQuickDialoguesNodeType::Loopback:
			return FColor::FromHex("00FF00");
		default:
#if WITH_EDITOR
			UE_LOG(LogTemp, Warning, TEXT("SQuickDialoguesBaseGraphNodeWidget::GetNodeColor(), Unknown NodeType"));
#endif
			return FColor::White;
		}
	}
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("SQuickDialoguesBaseGraphNodeWidget::GetNodeColor(), Unknown NodeType"));
#endif
	return FColor::White;
}

void SQuickDialoguesBaseGraphNodeWidget::SetupErrorSlot()
{
	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	                  .HAlign(HAlign_Center)
	                  .Padding(2.0f)
	[
		SNew(STextBlock)
		.Text(this, &SQuickDialoguesBaseGraphNodeWidget::GetErrorMsg)
		.Font(FCoreStyle::Get().GetFontStyle("BoldFont"))
		.ColorAndOpacity(FLinearColor::Red)
	];
}

void SQuickDialoguesBaseGraphNodeWidget::SetupDefaultPins()
{
	ContentVerticalBox->AddSlot()
	                  .AutoHeight()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SAssignNew(LeftNodeBox, SVerticalBox)
		]

		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]
	];
}
