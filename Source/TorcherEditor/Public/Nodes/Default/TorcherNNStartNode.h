// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/TorcherGraphNode.h"
#include "TorcherNNStartNode.generated.h"

/**
 * 
 */
UCLASS()
class TORCHEREDITOR_API UTorcherNNStartNode : public UTorcherGraphNode
{
	GENERATED_BODY()
public:
	// Constructor
	UTorcherNNStartNode();
	
	// UEdGraphNode
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString(TEXT("Start")); }
	virtual FLinearColor GetNodeTitleColor() const override { return FColor::Red; }
	virtual bool CanUserDeleteNode() const override { return false; }

	// UTorcherGraphNode
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) override;
};
