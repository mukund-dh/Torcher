// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/TorcherGraphNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

FText UTorcherGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(GetLayerNodeOptions().LayerName);
}

void UTorcherGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("TorcherLayer"), FText::FromString(TEXT("Create Torcher Layers")));

	// HACK! - Initialize actions in memeber variables and then initialize them using and Init function
	UTorcherGraphNode* node = (UTorcherGraphNode*) this;
	Section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Pin")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(TEXT("TorcherEditorStyle"), TEXT("TorcherGraph.AddNodePinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[node] ()
			{
				node->CreatePin(
					EEdGraphPinDirection::EGPD_Output,
					TEXT("Outputs"),
					TEXT("Another Output")
				);

				node->GetGraph()->NotifyGraphChanged();
				node->GetGraph()->Modify();
			}
		))
	);

	Section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Pin")),
		FText::FromString(TEXT("Deletes the last pin")),
		FSlateIcon(TEXT("TorcherEditorStyle"), TEXT("TorcherGraph.DeleteNodePinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[node] ()
			{
				UEdGraphPin* pin = node->GetPinAt(node->Pins.Num() - 1);
				if (pin->Direction != EGPD_Input)
				{
					node->RemovePin(pin);

					node->GetGraph()->NotifyGraphChanged();
					node->GetGraph()->Modify();
					
				}
			}
		))
	);

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

UEdGraphPin* UTorcherGraphNode::CreateCustomPin(EEdGraphPinDirection Direction, FName name)
{
	FName Category = (Direction == EEdGraphPinDirection::EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName SubCategory = TEXT("TorcherPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, name);
	Pin->PinType.PinSubCategory = SubCategory;
	return Pin;
}
