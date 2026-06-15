//Copyright (c) 2025 Elia Cantini. All rights reserved.

#include "Nodes/QuickDialoguesReplyNode.h"


UQuickDialoguesReplyNode::UQuickDialoguesReplyNode(): UQuickDialoguesMultiOutputNode()
{
	NodeData = FText::FromString("Unimplemented line of Dialogue"); 
}

TArray<FDialogueReply> UQuickDialoguesReplyNode::GetReplies()
{
	return Replies;
}

void UQuickDialoguesReplyNode::RemoveChildAt(int Index)
{
#if WITH_EDITOR
	Modify();
#endif	
	Super::RemoveChildAt(Index);
	Replies.RemoveAt(Index);
}

FText UQuickDialoguesReplyNode::GetNodeTypeAsText() const
{
	return FText::FromString("Reply Node");
}

void UQuickDialoguesReplyNode::AddReply(FDialogueReply InReply)
{
#if WITH_EDITOR
	Modify();
#endif	
	Replies.Add(InReply);
}

bool UQuickDialoguesReplyNode::SetReplyTextAtIndex(int32 InIndex, const FText& InText)
{

	if (Replies.IsValidIndex(InIndex))
	{
#if WITH_EDITOR
		Modify();
#endif		
		Replies[InIndex].Text = InText;
		return true;
	}
#if WITH_EDITOR
	UE_LOG(LogTemp, Error,
	       TEXT(
		       "UQuickDialoguesReplyNode::SetReplyTextAtIndex(), Index was not a valid Index for the DialogueNode, Something weird happened, the GraphNode and the DialogueNode are not aligned causing an IndexMismatch, Node Recreation is suggested"
	       ));
#endif
	return false;
}

bool UQuickDialoguesReplyNode::SetClassAtIndex(int32 InIndex, TSubclassOf<UQuickDialoguesUIButton> InClass)
{
	if (Replies.IsValidIndex(InIndex))
	{
#if WITH_EDITOR
		Modify();
#endif		
		Replies[InIndex].SelectedClass = InClass;
		return true;
	}
#if WITH_EDITOR
	UE_LOG(LogTemp, Error,
		   TEXT(
			   "UQuickDialoguesReplyNode::SetClassAtIndex(), Index was not a valid Index for the DialogueNode, Something weird happened, the GraphNode and the DialogueNode are not aligned causing an IndexMismatch, Node Recreation is suggested"
		   ));
#endif
	return false;
}

void UQuickDialoguesReplyNode::SetDialogue(FText InText)
{
#if WITH_EDITOR
	Modify();
#endif	
	NodeData = InText;	
}

FText UQuickDialoguesReplyNode::GetNodeDialogueData()
{
	return NodeData;
}
