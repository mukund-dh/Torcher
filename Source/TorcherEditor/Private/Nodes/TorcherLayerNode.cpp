// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/TorcherLayerNode.h"

UTorcherLayerNode::UTorcherLayerNode()
	: LayerDeviceType(ETorcherTensorDeviceType::Cpu)
	, Gain(1.0f)
	, Confidence(1.0f)
{
}

UEdGraphPin* UTorcherLayerNode::CreateCustomPin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EEdGraphPinDirection::EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName SubCategory = TEXT("TorcherPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, SubCategory, Name);
	Pin->PinType.PinSubCategory = SubCategory;
	return Pin;
}
