// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/TorcherGraphNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

UTorcherGraphNode::UTorcherGraphNode()
{
	LayerName = TEXT("UNNAMED LAYER");
}

FText UTorcherGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(LayerName);
}

void UTorcherGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("TorcherLayer"), FText::FromString(TEXT("Create Torcher Layers")));

	// HACK! - Initialize actions in memeber variables and then initialize them using and Init function
	UTorcherGraphNode* node = (UTorcherGraphNode*) this;
	Section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("TorcherEditorStyle"), TEXT("TorcherGraph.DeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[node] ()
			{
				node->GetGraph()->RemoveNode(node);
			}
		))
	);
}

/*UEdGraphPin* UTorcherGraphNode::CreateCustomPin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EEdGraphPinDirection::EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName SubCategory = TEXT("TorcherPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, SubCategory, Name);
	Pin->PinType.PinSubCategory = SubCategory;
	return Pin;
}*/
