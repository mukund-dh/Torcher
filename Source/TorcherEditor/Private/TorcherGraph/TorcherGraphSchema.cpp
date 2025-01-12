// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherGraph/TorcherGraphSchema.h"

void UTorcherGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> NewNodeAction(
		new FNewNodeAction(
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Node")),
			FText::FromString(TEXT("Makes a new node")),
			0
		)
	);

	ContextMenuBuilder.AddAction(NewNodeAction);
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location,
	bool bSelectNewNode)
{
	UEdGraphNode* result = NewObject<UEdGraphNode>(ParentGraph);
	result->NodePosX = Location.X;
	result->NodePosY = Location.Y;

	result->CreatePin(
		EGPD_Input,
		TEXT("Inputs"),
		TEXT("SomeInput")
	);

	result->CreatePin(
		EGPD_Output,
		TEXT("Outputs"),
		TEXT("Output1")
	);

	result->CreatePin(
		EGPD_Output,
		TEXT("Oututs"),
		TEXT("Output2")
	);

	ParentGraph->Modify();
	ParentGraph->AddNode(result, true, true);

	return result;
	// return FEdGraphSchemaAction::PerformAction(ParentGraph, FromPin, Location, bSelectNewNode);
}
