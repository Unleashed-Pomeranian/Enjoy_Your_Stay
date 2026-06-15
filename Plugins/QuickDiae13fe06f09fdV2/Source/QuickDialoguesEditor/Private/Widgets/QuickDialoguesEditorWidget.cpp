//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Widgets/QuickDialoguesEditorWidget.h"

#include "EdGraphUtilities.h"
#include "GraphEditor.h"
#include "QuickDialoguesAssetEditor.h"
#include "QuickDialoguesGraph.h"
#include "QuickDialoguesGraphSchema.h"
#include "QuickDialoguesNodeTree.h"
#include "EdGraph/EdGraphNode.h"
#include "Framework/Commands/GenericCommands.h"
#include "Framework/Commands/UICommandList.h"
#include "Framework/Docking/TabManager.h"
#include "Nodes/QuickDialoguesBaseGraphNode.h"
#include "Nodes/QuickDialoguesLoopbackNode.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

const FName FQuickDialoguesAssetEditor::GraphTabId(TEXT("QuickDialoguesEditor_Graph"));
const FName FQuickDialoguesAssetEditor::DetailViewTabId(TEXT("QuickDialoguesEditor_Properties"));

void SQuickDialoguesEditorWidget::ValidateGraph() const
{
	bool bIsGraphValid = true;
	bool bHasRoot = false;
	bool bHasEndPoint = false;

	for (UEdGraphNode* Node : QuickDialoguesGraph->Nodes)
	{
		UQuickDialoguesBaseGraphNode* TypedNode = Cast<UQuickDialoguesBaseGraphNode>(Node);

		auto SetError = [&](const FString& ErrorMessage)
		{
			TypedNode->bHasCompilerMessage = true;
			TypedNode->ErrorType = EMessageSeverity::Error;
			TypedNode->ErrorMsg = ErrorMessage;
			bIsGraphValid = false;
			TypedNode->ReconstructNode();
		};

		if (!TypedNode || !TypedNode->DialogueNode)
		{
			continue;
		}
		TypedNode->bHasCompilerMessage = false;
		TypedNode->ErrorMsg.Empty();

		const EQuickDialoguesNodeType NodeType = TypedNode->DialogueNode->GetNodeType();

		bool bHasInput = false;
		int32 NumOutputPins = 0;
		int32 NumUnconnectedOutputs = 0;

		for (const UEdGraphPin* Pin : TypedNode->Pins)
		{
			if (Pin->Direction == EGPD_Input && Pin->LinkedTo.Num() > 0)
			{
				for (const UEdGraphPin* LinkedPin : Pin->LinkedTo)
				{
					if (const UQuickDialoguesBaseGraphNode* LinkedGraphNode = Cast<UQuickDialoguesBaseGraphNode>(LinkedPin->GetOwningNode()))
					{
						if (!TypedNode->DialogueNode->GetParents().Contains(LinkedGraphNode->DialogueNode))
						{
							SetError(TEXT("Node mismatch between input connection and Parents, try recreating this node!"));
						}
					}
				}
				bHasInput = true;
			}
			else if (Pin->Direction == EGPD_Output)
			{
				++NumOutputPins;

				for (const UEdGraphPin* LinkedPin : Pin->LinkedTo)
				{
					if (const UQuickDialoguesBaseGraphNode* LinkedGraphNode = Cast<UQuickDialoguesBaseGraphNode>(LinkedPin->GetOwningNode()))
					{
						if (!TypedNode->DialogueNode->GetAllChildren().Contains(LinkedGraphNode->DialogueNode))
						{
							SetError(TEXT("Node mismatch between input connection and Parents, try recreating this node!"));
						}
					}
				}
				
				if (Pin->LinkedTo.Num() == 0)
				{
					++NumUnconnectedOutputs;
				}
			}
		}

		const bool bHasOutput = NumOutputPins > 0 && NumUnconnectedOutputs < NumOutputPins;
		const bool bIsDisconnected = !bHasInput && !bHasOutput;
		const bool bIsRoot = NodeType == EQuickDialoguesNodeType::Root;
		const bool bIsEnd = NodeType == EQuickDialoguesNodeType::EndPoint;
		
		if (!bIsRoot && !bIsEnd && bIsDisconnected)
		{
			continue;
		}

		if (bIsRoot)
		{
			bHasRoot = true;
			if (NumOutputPins == 0 || NumUnconnectedOutputs > 0)
			{
				SetError(TEXT("Root node must have all output pins connected!"));
			}
		}
		else if (bIsEnd)
		{
			bHasEndPoint = true;
			if (!bHasInput)
			{
				SetError(TEXT("EndPoint node must have at least one input connection!"));
			}
		}
		else if (UQuickDialoguesLoopbackNode* LoopbackNode = Cast<UQuickDialoguesLoopbackNode>(TypedNode->DialogueNode))
		{
			if (!IsValid(LoopbackNode->GetChild()))
			{
				SetError(TEXT("Loopback node must have at least one Loopback node child selected"));
			}
		}
		else
		{
			if (!bHasInput)
			{
				SetError(TEXT("This node has output(s) but no input!"));
			}
			else if (NumUnconnectedOutputs > 0)
			{
				SetError(FString::Printf(TEXT("This node has %d unconnected output pin(s)!"), NumUnconnectedOutputs));
			}
		}
	}

	QuickDialoguesGraph->NotifyGraphChanged();

	// Final graph summary validation
	FString Message;
	if (!bIsGraphValid)
	{
		Message += "Some dialogue nodes are missing required connections.\n";
	}
	if (!bHasEndPoint)
	{
		Message += "The graph has no EndPoint!\n";
	}
	if (!bHasRoot)
	{
		Message += "The graph has no Root!\n";
	}

	if (!Message.IsEmpty())
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
	}

	NodeTree->SetHasCompileErrors(!bIsGraphValid);
	NodeTree->SetHasBeenSavedAndValidated(true);
}

void SQuickDialoguesEditorWidget::OnCompileClicked() const
{
	ValidateGraph();
}

void SQuickDialoguesEditorWidget::Construct(const FArguments& InArgs,
                                            UQuickDialoguesNodeTree* InNodeTree, UQuickDialoguesGraph* InGraph,
                                            FAssetEditorToolkit* InToolKit)
{
	NodeTree = InNodeTree;
	QuickDialoguesGraph = InGraph;

	CommandList = MakeShareable(new FUICommandList);
	CreateCommandList();
	GraphEditor = CreateGraphEditorWidget();
	AddToolbar(InToolKit);
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SNew(SBorder)
			.Padding(10)
			.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
			[
				GraphEditor.ToSharedRef()
			]
		]
	];
}

void SQuickDialoguesEditorWidget::AddToolbar(FAssetEditorToolkit* InToolkit)
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		CommandList,
		FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder)
		{
			Builder.AddToolBarButton(
				FUIAction(FExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::OnCompileClicked)),
				NAME_None,
				FText::FromString("Validate dialogue"),
				FText::FromString("Validate the dialogue and check for any node error"),
				FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Success")
			);
		})
	);
	InToolkit->AddToolbarExtender(ToolbarExtender);
}


UObject* SQuickDialoguesEditorWidget::GetSelectedNode() const
{
	if (SelectedGraphNode.IsValid())
	{
		return SelectedGraphNode.Get();
	}
	return nullptr;
}

void SQuickDialoguesEditorWidget::RefreshEditor() const
{
	if (GraphEditor.IsValid())
	{
		GraphEditor->NotifyGraphChanged();
	}
}

FReply SQuickDialoguesEditorWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (CommandList->ProcessCommandBindings(InKeyEvent))
	{
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply SQuickDialoguesEditorWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FSlateApplication::Get().ClearAllUserFocus(EFocusCause::Cleared);
	return SCompoundWidget::OnMouseButtonDown(MyGeometry, MouseEvent);
}

TSharedRef<SGraphEditor> SQuickDialoguesEditorWidget::CreateGraphEditorWidget()
{
	
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged =
		SGraphEditor::FOnSelectionChanged::CreateRaw(this, &SQuickDialoguesEditorWidget::OnSelectedNodesChanged);

	return SNew(SGraphEditor)
		.GraphToEdit(QuickDialoguesGraph)
		.IsEditable(true)
		.GraphEvents(InEvents);
}

void SQuickDialoguesEditorWidget::CreateCommandList()
{
	CommandList->MapAction(
		FGenericCommands::Get().Delete,
		FUIAction(FExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::DeleteSelectedNodes),
		          FCanExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::CanDeleteNodes))
	);

	CommandList->MapAction(
		FGenericCommands::Get().Copy,
		FUIAction(FExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::CopySelectedNodes),
		          FCanExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::CanCopyNodes))
	);
	CommandList->MapAction(
		FGenericCommands::Get().Paste,
		FUIAction(FExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::PasteNodes),
		          FCanExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::CanPasteNodes))
	);

	CommandList->MapAction(FGenericCommands::Get().Cut,
	                       FUIAction(FExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::CutSelectedNodes),
	                                 FCanExecuteAction::CreateSP(this, &SQuickDialoguesEditorWidget::CanCutNodes)));
}

void SQuickDialoguesEditorWidget::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection)
{
	UObject* SelectedObject = nullptr;

	if (NewSelection.Num() > 0)
	{
		SelectedGraphNode = Cast<UQuickDialoguesBaseGraphNode>(NewSelection.Array()[0]);

		if (SelectedGraphNode.IsValid())
		{
			SelectedObject = SelectedGraphNode->DialogueNode;
		}
		else
		{
			SelectedObject = NewSelection.Array()[0];
		}
	}

	OnNodeSelectionChanged.ExecuteIfBound(SelectedObject);
}

void SQuickDialoguesEditorWidget::DeleteSelectedNodes() const
{
	if (CanDeleteNodes())
	{
		const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "DeleteSelectedNodes", "Delete Selected Nodes"));

		for (UObject* SelectedObj : GraphEditor->GetSelectedNodes())
		{
			if (UQuickDialoguesBaseGraphNode* GraphNode = Cast<UQuickDialoguesBaseGraphNode>(SelectedObj))
			{
				const UQuickDialoguesGraphSchema* Schema = Cast<UQuickDialoguesGraphSchema>(
					QuickDialoguesGraph->GetSchema());
				if (Schema)
				{
					Schema->DeleteNode(GraphNode);
				}
				GraphNode->Modify();
			}
		}
	}
}

bool SQuickDialoguesEditorWidget::CanDeleteNodes() const
{
	return GraphEditor->GetSelectedNodes().Num() > 0;
}

void SQuickDialoguesEditorWidget::CopySelectedNodes() const
{
	if (!GraphEditor.IsValid())
	{
		return;
	}

	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();
	FString ExportedText;
	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);

	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

bool SQuickDialoguesEditorWidget::CanCopyNodes() const
{
	return GraphEditor->GetSelectedNodes().Num() > 0;
}

void SQuickDialoguesEditorWidget::PasteNodes() const
{
	if (!GraphEditor.IsValid())
	{
		return;
	}

	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "PasteSelectedNodes", "Paste Selected Nodes"));

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	const FVector2D PasteLocation = GraphEditor->GetPasteLocation2f();

	GraphEditor->ClearSelectionSet();

	QuickDialoguesGraph->Modify();

	TSet<UEdGraphNode*> PastedNodes;
	FEdGraphUtilities::ImportNodesFromText(QuickDialoguesGraph, ClipboardContent, PastedNodes);
	UEdGraphNode* FirstNode = nullptr;

	for (UEdGraphNode* Node : PastedNodes)
	{
		if (Node)
		{
			if (!FirstNode)
			{
				FirstNode = Node;
			}
		}
	}

	if (FirstNode)
	{
		const FVector2D Delta = PasteLocation - FVector2D(FirstNode->NodePosX, FirstNode->NodePosY);
		for (UEdGraphNode* Node : PastedNodes)
		{
			if (!Node)
			{
				continue;
			}

			Node->Modify();
			Node->CreateNewGuid();
			for (UEdGraphPin* Pin : Node->Pins)
			{
				Pin->Modify();
				Pin->BreakAllPinLinks(true);
			}
			if (UQuickDialoguesBaseGraphNode* GraphNode = Cast<UQuickDialoguesBaseGraphNode>(Node))
			{
				EQuickDialoguesNodeType NodeType = GraphNode->DialogueNode->GetNodeType();
				if (QuickDialoguesGraph->GetRootNode() && NodeType == EQuickDialoguesNodeType::Root)
				{
					GraphNode->DestroyNode();
#if WITH_EDITOR
					UE_LOG(LogTemp, Error,
					       TEXT(
						       "SQuickDialoguesEditor::PasteNodes(), Attempted to paste a Root node while 1 was already in the Graph"
					       ))
#endif
					continue;
				}
				if (GraphNode->DialogueNode)
				{
					const FName UniqueName = NodeTree->GetNodeNameFromType(GraphNode->DialogueNode->GetNodeType());
					GraphNode->DialogueNode->Modify();
					UQuickDialoguesBaseNode* Dup = DuplicateObject<UQuickDialoguesBaseNode>(
						GraphNode->DialogueNode,
						GraphNode->DialogueNode->GetTree(),
						UniqueName
					);
					Dup->NodeGuid = FGuid::NewGuid();
					GraphNode->SetNode(Dup);
				}
				else
				{
					UQuickDialoguesBaseNode* NewNode = NewObject<UQuickDialoguesBaseNode>(GraphNode);
					NewNode->NodeGuid = FGuid::NewGuid();
					GraphNode->SetNode(NewNode);
				}
				GraphNode->DialogueNode->ResetConnections();
			}
			Node->NodePosX += Delta.X * 1.0f;
			Node->NodePosY += Delta.Y * 1.0f;
			Node->ReconstructNode();
		}
	}
	GraphEditor->NotifyGraphChanged();
}

bool SQuickDialoguesEditorWidget::CanPasteNodes() const
{
	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);
	return !ClipboardContent.IsEmpty();
}

void SQuickDialoguesEditorWidget::CutSelectedNodes() const
{
	if (GraphEditor.IsValid())
	{
		CopySelectedNodes();
		DeleteSelectedNodes();
	}
}

bool SQuickDialoguesEditorWidget::CanCutNodes() const
{
	return GraphEditor->GetSelectedNodes().Num() > 0;
}

