// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/Default/TorcherNNStartNode.h"

UTorcherNNStartNode::UTorcherNNStartNode()
	: Super()
{
	LayerName = TEXT("Start");
}

UEdGraphPin* UTorcherNNStartNode::CreateCustomPin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = TEXT("Outputs");
	FName SubCategory = TEXT("TorcherStartPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, SubCategory, Name);
	// Pin->PinType.PinSubCategory = SubCategory;
	return Pin;
}
