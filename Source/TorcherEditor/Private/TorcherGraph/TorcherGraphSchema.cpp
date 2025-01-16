// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherGraph/TorcherGraphSchema.h"
#include "Nodes/TorcherGraphNode.h"
#include "Layers/TorcherLayerBaseOptions.h"

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

const FPinConnectionResponse UTorcherGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A == nullptr || B == nullptr)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Couldn't find valid pins"));

	if (A->Direction == B->Direction)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Can't connect two pins of same direction"));

	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT("CONNECTION SUCCESSFUL"));
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location,
                                            bool bSelectNewNode)
{
	UTorcherGraphNode* result = NewObject<UTorcherGraphNode>(ParentGraph);
	result->CreateNewGuid();
	
	result->NodePosX = Location.X;
	result->NodePosY = Location.Y;
	
	FTorcherLayerBaseOptions LayerOptions;
	LayerOptions.LayerName = "TEST LAYER";
	LayerOptions.LayerDeviceType = ETorcherTensorDeviceType::Cuda;
	result->SetLayerNodeOptions(LayerOptions);

	UEdGraphPin* InputPin = result->CreateCustomPin(EEdGraphPinDirection::EGPD_Input, TEXT("SomeInput"));
	result->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, TEXT("Output1"));
	result->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, TEXT("Output2"));

	if (FromPin != nullptr)
	{
		result->GetSchema()->TryCreateConnection(FromPin, InputPin);
	}
	
	ParentGraph->Modify();
	ParentGraph->AddNode(result, true, true);

	return result;
}
